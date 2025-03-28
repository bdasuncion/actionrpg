#include <stdlib.h>
#include  <stdarg.h>
#include  <stdbool.h>
#include "GBAObject.h"
#include "GBAVideo.h"
#include "GBADMA.h"
#include "GBATimer.h"
#include "GBACharacter.h"
#include "GBACharacterType.h"
#include "ManagerCharacterActionEvents.h"
#include "ManagerCharacters.h"
#include "ManagerVram.h"
#include "ManagerPrinter.h"
#include "MapCommon.h"
#include "UtilCommonValues.h"
#include "CharacterCommon.h"

//#include "DebugLogMgba.h"
//#include <string.h>
//#include <stdio.h>
#include <assert.h>

#define IMG8X8W  8
#define IMG16X16W  32
#define IMG32X32W  128
#define IMG64X64W  512

#define IMG8X16W  16
#define IMG8X32W  32
#define IMG16X32W  64
#define IMG32X64W  256
#define COLLISIONCHECKNEXT_DIST_MAX 32
#define HEIGHT_CONVERSION 8

extern const FuncCharacterInit character_InitFunctionsCollection[];

void commonControllerDummy(CharacterAttr* charAtt, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection) {
}

void commonActionDummy(CharacterAttr* charAtt, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection) {
}

int commonSetPositionDummy(CharacterAttr* charAtt, OBJ_ATTR *oamBuf, 
	const Position *scr_pos,
	const ScreenDimension *scr_dim) {
	return 0;
}

void commonGetBoundsDummy(const CharacterAttr* charAtt,
	int *count, BoundingBox *collisionBox) {
	*count = 0;
	collisionBox = NULL;
}
	
void commonCollisionCheckDummy(CharacterAttr *charAtt, bool isOtherCharBelow,
	bool *checkNext, const CharacterAttr *checkWithCharAtt) {
}
	
void commonMapCollisionDummy(CharacterAttr* charAtt, const MapInfo* mapInfo) {
}

void commonActionCollisionDummy(CharacterAttr *charAtt, 
	CharacterActionCollection *actionEvents, AttackEffectCollection *attackEffects) {
}

bool commonIsHitDummy(struct CharacterAttr *charAtt, struct CharacterActionEvent *actionEvent) {
	return false;
}

//const CharacterAttr openSlot = {&commonControllerDummy, &commonActionDummy, &commonSetPositionDummy, &commonGetBoundsDummy, 
 //   &funcCollisionCheckDummy, &funcMapCollisionDummy, &funcActionCollisionDummy, NULL, 0, NONE,0,0,0,0,0, NULL, {0, -1, 0}, NULL, NULL };
#define FARTARGET_SIZE 5
const EDirections FAR_TARGET[FARTARGET_SIZE ][FARTARGET_SIZE] = {
 {EUpleft, EUpleft, EUp, EUpright, EUpright},
 {EUpleft, EUpleft, EUp, EUpright, EUpright},
 {ELeft, ELeft, EUnknown, ERight, ERight},
 {EDownleft, EDownleft, EDown, EDownright, EDownright},
 {EDownleft, EDownleft, EDown, EDownright, EDownright}
};

//UL UL UL U  U  U  U  UR UR UR
//UL UL UL U  U  U  U  UR UR UR 
//UL UL UL UL U  U  UR UR UR UR 
//L  L  UL UL X  X  UR UR R  R
//L  L  L  X  X  X  X  R  R  R
//L  L  L  X  X  X  X  R  R  R
//L  L  DL DL X  X  DR DR R  R
//DL DL DL DL D  D  DR DR DR DR
//DL DL DL D  D  D  D  DR DR DR
//DL DL DL D  D  D  D  DR DR DR

#define FARTARGET_16x16_SIZE 10

const EDirections FAR_TARGET_16x16[FARTARGET_16x16_SIZE][FARTARGET_16x16_SIZE] = {
 {EUpleft, EUpleft, EUpleft, EUp,  EUp,  EUp,  EUp, EUpright, EUpright, EUpright},
 {EUpleft, EUpleft, EUpleft, EUp, EUp, EUp, EUp, EUpright, EUpright, EUpright},
 {EUpleft, EUpleft, EUpleft, EUpleft, EUp, EUp, EUpright, EUpright, EUpright, EUpright},
 {ELeft, ELeft, EUpleft, EUpleft, EUnknown, EUnknown, EUpright, EUpright, ERight, ERight},
 {ELeft, ELeft, ELeft, EUnknown, EUnknown, EUnknown, EUnknown, ERight, ERight, ERight},
 {ELeft, ELeft, ELeft, EUnknown, EUnknown, EUnknown, EUnknown, ERight, ERight, ERight},
 {ELeft, ELeft, EDownleft, EDownleft, EUnknown, EUnknown, EDownright, EDownright, ERight, ERight},
 {EDownleft, EDownleft, EDownleft, EDownleft, EDown, EDown, EDownright, EDownright, EDownright, EDownright},
 {EDownleft, EDownleft, EDownleft, EDown, EDown, EDown, EDown, EDownright, EDownright, EDownright},
 {EDownleft, EDownleft, EDownleft, EDown, EDown, EDown, EDown, EDownright, EDownright, EDownright}
};

//UL UL UL UL UL UL U  U  U  U  U  U  U  U  UR UR UR UR UR UR
//UL UL UL UL UL UL U  U  U  U  U  U  U  U  UR UR UR UR UR UR
//UL UL UL UL UL UL UL U  U  U  U  U  U  UR UR UR UR UR UR UR
//UL UL UL UL UL UL UL U  U  U  U  U  U  UR UR UR UR UR UR UR
//UL UL UL UL UL UL UL UL U  U  U  U  UR UR UR UR UR UR UR UR
//UL UL UL UL UL UL UL UL U  U  U  U  UR UR UR UR UR UR UR UR
//L  L  UL UL UL UL UL UL UL U  U  UR UR UR UR UR UR UR R  R 
//L  L  L  L  UL UL UL UL UL U  U  UR UR UR UR UR R  R  R  R 
//L  L  L  L  L  L  UL UL UL X  X  UR UR UR R  R  R  R  R  R
//L  L  L  L  L  L  L  L  X  X  X  X  R  R  R  R  R  R  R  R
//L  L  L  L  L  L  L  L  X  X  X  X  R  R  R  R  R  R  R  R
//L  L  L  L  L  L  DL DL DL X  X  DR DR DR R  R  R  R  R  R
//L  L  L  L  DL DL DL DL DL D  D  DR DR DR DR DR R  R  R  R
//L  L  DL DL DL DL DL DL DL D  D  DR DR DR DR DR DR DR R  R
//DL DL DL DL DL DL DL DL D  D  D  D  DR DR DR DR DR DR DR DR
//DL DL DL DL DL DL DL DL D  D  D  D  DR DR DR DR DR DR DR DR
//DL DL DL DL DL DL DL D  D  D  D  D  D  DR DR DR DR DR DR DR
//DL DL DL DL DL DL DL D  D  D  D  D  D  DR DR DR DR DR DR DR
//DL DL DL DL DL DL D  D  D  D  D  D  D  D  DR DR DR DR DR DR
//DL DL DL DL DL DL D  D  D  D  D  D  D  D  DR DR DR DR DR DR

#define FARTARGET_8x8_SIZE 20

const EDirections FAR_TARGET_8x8[FARTARGET_8x8_SIZE][FARTARGET_8x8_SIZE] = {
 {EUpleft, EUpleft, EUpleft, EUpleft, EUpleft, EUpleft, EUp, EUp, EUp, EUp, EUp, EUp, EUp, EUp, EUpright, EUpright, EUpright, EUpright, EUpright, EUpright},
 {EUpleft, EUpleft, EUpleft, EUpleft, EUpleft, EUpleft, EUp, EUp, EUp, EUp, EUp, EUp, EUp, EUp, EUpright, EUpright, EUpright, EUpright, EUpright, EUpright},
 {EUpleft, EUpleft, EUpleft, EUpleft, EUpleft, EUpleft, EUpleft, EUp, EUp, EUp, EUp, EUp, EUp, EUp, EUp, EUpright, EUpright, EUpright, EUpright, EUpright, EUpright, EUpright},
 {EUpleft, EUpleft, EUpleft, EUpleft, EUpleft, EUpleft, EUpleft, EUp, EUp, EUp, EUp, EUp, EUp, EUp, EUp, EUpright, EUpright, EUpright, EUpright, EUpright, EUpright, EUpright},
 {EUpleft, EUpleft, EUpleft, EUpleft, EUpleft, EUpleft, EUpleft, EUpleft, EUp, EUp, EUp, EUp, EUpright, EUpright, EUpright, EUpright, EUpright, EUpright, EUpright, EUpright},
 {EUpleft, EUpleft, EUpleft, EUpleft, EUpleft, EUpleft, EUpleft, EUpleft, EUp, EUp, EUp, EUp, EUpright, EUpright, EUpright, EUpright, EUpright, EUpright, EUpright, EUpright},
 {ELeft, ELeft, EUpleft, EUpleft, EUpleft, EUpleft, EUpleft, EUpleft, EUpleft, EUp, EUp, EUpright, EUpright, EUpright, EUpright, EUpright, EUpright, EUpright, ERight, ERight},
 {ELeft, ELeft, ELeft, ELeft, EUpleft, EUpleft, EUpleft, EUpleft, EUpleft, EUnknown, EUnknown, EUpright, EUpright, EUpright, EUpright, EUpright, ERight, ERight, ERight, ERight},
 {ELeft, ELeft, ELeft, ELeft, ELeft, ELeft, EUpleft, EUpleft, EUpleft, EUnknown, EUnknown, EUpright, EUpright, EUpright, ERight, ERight, ERight, ERight, ERight, ERight},
 {ELeft, ELeft, ELeft, ELeft, ELeft, ELeft, ELeft, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, ERight, ERight, ERight, ERight, ERight, ERight, ERight},
 {ELeft, ELeft, ELeft, ELeft, ELeft, ELeft, ELeft, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, ERight, ERight, ERight, ERight, ERight, ERight, ERight},
 {ELeft, ELeft, ELeft, ELeft, ELeft, ELeft, EDownleft, EDownleft, EDownleft, EUnknown, EUnknown, EDownright, EDownright, EDownright, ERight, ERight, ERight, ERight, ERight, ERight},
 {ELeft, ELeft, ELeft, ELeft,  EDownleft, EDownleft,  EDownleft, EDownleft, EDownleft, EUnknown, EUnknown, EDownright, EDownright,  EDownright, EDownright,  EDownright, ERight, ERight, ERight, ERight},
 {ELeft, ELeft, EDownleft, EDownleft,  EDownleft, EDownleft,  EDownleft, EDownleft, EDownleft, EDown, EDown, EDownright, EDownright,  EDownright, EDownright,  EDownright, EDownright, EDownright, ERight, ERight},
 {EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDown, EDown,  EDown, EDown, EDownright, EDownright, EDownright, EDownright, EDownright, EDownright, EDownright, EDownright},
 {EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDown, EDown,  EDown, EDown, EDownright, EDownright, EDownright, EDownright, EDownright, EDownright, EDownright, EDownright},
 {EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDown, EDown,  EDown, EDown, EDown, EDown, EDownright, EDownright, EDownright, EDownright, EDownright, EDownright, EDownright},
 {EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDown, EDown,  EDown, EDown, EDown, EDown, EDownright, EDownright, EDownright, EDownright, EDownright, EDownright, EDownright},
 {EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDown, EDown, EDown, EDown, EDown, EDown, EDown, EDown, EDownright, EDownright, EDownright, EDownright, EDownright, EDownright},
 {EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDown, EDown, EDown, EDown, EDown, EDown, EDown, EDown, EDownright, EDownright, EDownright, EDownright, EDownright, EDownright}
};

#define NEARTARGET_SIZE 5

const EDirections NEAR_TARGET[NEARTARGET_SIZE][NEARTARGET_SIZE] = {
 {EUpleft, EUpleft, EUp, EUpright, EUpright},
 {EUpleft, EUpleft, EUp, EUpright, EUpright},
 {ELeft, ELeft, EUnknown, ERight, ERight},
 {EDownleft, EDownleft, EDown, EDownright, EDownright},
 {EDownleft, EDownleft, EDown, EDownright, EDownright}
};

#define MIDRANGE_NEARTARGET_SIZE 8

const EDirections MIDRANGE_NEAR_TARGET[MIDRANGE_NEARTARGET_SIZE][MIDRANGE_NEARTARGET_SIZE] = {
 {EUpleft, EUpleft, EUpleft, EUp, EUp, EUpright, EUpright, EUpright},
 {EUpleft, EUpleft, EUpleft, EUp, EUp, EUpright, EUpright, EUpright},
     {EUpleft, ELeft, ELeft, EUp, EUp, ERight, ERight, EUpright},
      {ELeft, ELeft, ELeft, ELeft, ERight, ERight, ERight, ERight},
	  {ELeft, ELeft, ELeft, ELeft, ERight, ERight, ERight, ERight},
    {EDownleft, ELeft, ELeft,  EDown, EDown, ERight, ERight, EDownright},
 {EDownleft, EDownleft, EDownleft, EDown, EDown, EDownright, EDownright, EDownright},
 {EDownleft, EDownleft, EDownleft, EDown, EDown, EDownright, EDownright, EDownright}
};

#define FAR_DIST_OFFSET 80
//#define NEAR_DIST_OFFSET 20

#define NEAR_DIST_OFFSET 32

void handleFarDistance(int distanceX, int distanceY, EDirections *goDirection) {
	if (abs(distanceX) > abs(distanceY)) {
		if (distanceX < 0) {
			*goDirection = ELeft;
		} else {
			*goDirection = ERight;
		}
	} else {
		if (distanceY < 0) {
			*goDirection = EUp;
		} else {
			*goDirection = EDown;
		}
	}
}

void findInScreen(Position *current, Position *targetPos, int height, EDirections *goDirection, bool *isNear) {
	int distanceX = targetPos->x - current->x;
	int distanceY = targetPos->y - current->y;
	
	if (height > 0) {
		int min = current->z;
		int max = current->z + height;
		if (!(targetPos->z <= max && targetPos->z >= min)) {
			*isNear = false;
			*goDirection = EUnknown;
			return;
		}
	}
	mprinter_printf("Z TARGET %d\n", targetPos->z);
	
	int offsetDistanceX = distanceX + FAR_DIST_OFFSET;
	int offsetDistanceY = distanceY + FAR_DIST_OFFSET;
	
	offsetDistanceX = DIVIDE_BY_8(offsetDistanceX);
	offsetDistanceY = DIVIDE_BY_8(offsetDistanceY);

	*goDirection = FAR_TARGET_8x8[offsetDistanceY][offsetDistanceX];
	if (*goDirection == EUnknown) {
		distanceX = targetPos->x - current->x + NEAR_DIST_OFFSET;
		distanceY = targetPos->y - current->y + NEAR_DIST_OFFSET;
		distanceX = DIVIDE_BY_8(distanceX);
		distanceY = DIVIDE_BY_8(distanceY);
		*isNear = true;
		*goDirection = MIDRANGE_NEAR_TARGET[distanceY][distanceX];
		return;
	}
	*isNear = false;
}

void findDirection(Position *current, Position *targetPos, EDirections *goDirection) {	
	int distanceX = targetPos->x - current->x;
	int distanceY = targetPos->y - current->y;
	bool isNear;
	
	int offsetDistanceX = distanceX + FAR_DIST_OFFSET;
	int offsetDistanceY = distanceY + FAR_DIST_OFFSET;
	
	offsetDistanceX = DIVIDE_BY_32(offsetDistanceX);
	offsetDistanceY = DIVIDE_BY_32(offsetDistanceY);
	
	if (offsetDistanceX >= FARTARGET_SIZE || offsetDistanceY >= FARTARGET_SIZE || offsetDistanceX < 0 || offsetDistanceY < 0) {
		handleFarDistance(distanceX, distanceY, goDirection);
		return;
	}
	
	findInScreen(current, targetPos, -1, goDirection, &isNear);
}

/*void common_findDirectionOfTargetCharacter(Position *current, Position *target, EDirections *goDirection) {
	Position currentConverted = {CONVERT_2POS(current->x), CONVERT_2POS(current->y), CONVERT_2POS(current->z)};
	Position targetConverted = {CONVERT_2POS(target->x), CONVERT_2POS(target->y), CONVERT_2POS(target->z)};
	
	findDirection(&currentConverted, &targetConverted, goDirection);
}*/

void common_findDirectionOfTargetCharacterInScreen(Position const *current, Position const *target, 
	EDirections *goDirection, bool *isNear) {
	Position currentPos = {CONVERT_2POS(current->x), CONVERT_2POS(current->y), CONVERT_2POS(current->z)};
	Position targetPos = {CONVERT_2POS(target->x), CONVERT_2POS(target->y), CONVERT_2POS(target->z)};
	
	int distanceX = targetPos.x - currentPos.x;
	int distanceY = targetPos.y - currentPos.y;
	
	int offsetDistanceX = distanceX + FAR_DIST_OFFSET;
	int offsetDistanceY = distanceY + FAR_DIST_OFFSET;
	
	offsetDistanceX = DIVIDE_BY_32(offsetDistanceX);
	offsetDistanceY = DIVIDE_BY_32(offsetDistanceY);
	//mprinter_printf("CHECKING %d,%d\n", offsetDistanceX, offsetDistanceY);
	if (offsetDistanceX >= FARTARGET_SIZE || offsetDistanceY >= FARTARGET_SIZE || offsetDistanceX < 0 || offsetDistanceY < 0) {
		*goDirection = EUnknown;
		*isNear = false;
		return;
	}
	
	findInScreen(&currentPos, &targetPos, 24, goDirection, isNear);
}

void common_findDirectionOfPosition(const Position *current, const Position *targetPos, EDirections *goDirection) {
	Position currentConverted = {CONVERT_2POS(current->x), CONVERT_2POS(current->y), CONVERT_2POS(current->z)};
	
	findDirection(&currentConverted, targetPos, goDirection);
}

void commonRemoveCharacter(CharacterAttr *character) {
    character->type = NONE;
    commonCharacterSetPosition(character, 0, -1, 0, EDown);

	character->controller = &commonControllerDummy;
	character->doAction = &commonActionDummy;
	character->setPosition = &commonSetPositionDummy;
	character->getBounds = &commonGetBoundsDummy;
	character->checkCollision = &commonCollisionCheckDummy;
	character->checkMapCollision = &commonMapCollisionDummy;
	character->isHit = &commonIsHitDummy;

	character->spriteDisplay.baseImageId = 0;
	character->spriteDisplay.imageUpdateStatus = ENoUpdate;
	character->spriteDisplay.basePalleteId = 0;
	character->spriteDisplay.palleteUpdateStatus = ENoUpdate;
	mchar_removeControl((CharacterBaseControl*)character->free);
}
void commonDoCharacterEvent(CharacterAttr *character, const MapInfo *mapInfo, const CharacterCollection *charCollection);

void commonCharacterSetPosition(CharacterAttr* character, int x, int y, int z, EDirections direction) {
	character->position.x = CONVERT_2MOVE(x);
	character->position.y = CONVERT_2MOVE(y);
	character->position.z = CONVERT_2MOVE(z);
	character->direction = direction;
	character->nextDirection = direction;
}

const s32 uncompressedCopySize[SPRITESHAPE_COUNT][SPRITESIZE_COUNT] = {
    {IMG8X8W, IMG16X16W, IMG32X32W, IMG64X64W},
	{IMG8X16W, IMG8X32W, IMG16X32W, IMG32X64W},
	{IMG8X16W, IMG8X32W, IMG16X32W, IMG32X64W}
};

void commonCharacterInit(CharacterAttr* character, int initialize, int nextAction, EDirections direction) {
	character->spriteDisplay.currentAnimationFrame = 0;
	character->spriteDisplay.numberOfFramesPassed = 0;
	character->action = initialize;
	character->direction = direction;
	character->nextAction = nextAction;
	character->nextDirection = direction;
}

void commonCharacterMapEdgeCheck(CharacterAttr* character, const MapInfo *mapInfo) {
    int count;
	BoundingBox charBoundingBox;
	character->getBounds(character, &count, &charBoundingBox);
	
	bool leftEdge = (charBoundingBox.startX < 0);
	bool rightEdge = (charBoundingBox.endX > mapInfo->width);
	bool upperEdge = (charBoundingBox.startY < 0);
	bool lowerEdge = (charBoundingBox.endY > mapInfo->height);
	character->position.x -= CONVERT_2MOVE(leftEdge*(charBoundingBox.startX));
	character->position.y -= CONVERT_2MOVE(upperEdge*(charBoundingBox.startY));
	character->position.x -= CONVERT_2MOVE(rightEdge*(charBoundingBox.endX - mapInfo->width));
	character->position.y -= CONVERT_2MOVE(lowerEdge*(charBoundingBox.endY - mapInfo->height));

	if (character->free->type == EControlAiType) {
		((CharacterAIControl*)character->free)->downBlocked |= lowerEdge;
		((CharacterAIControl*)character->free)->upBlocked |= upperEdge;
		((CharacterAIControl*)character->free)->leftBlocked |= leftEdge;
		((CharacterAIControl*)character->free)->rightBlocked |= rightEdge;
	}	
}

const CharFuncCollisionReaction common_collisionReactions[8] = {
	&common_movingDownOffset,
	&common_movingRightDownOffset,
	&common_movingRightOffset,
	&common_movingRightUpOffset,
	&common_movingUpOffset,
	&common_movingLeftUpOffset,
	&common_movingLeftOffset,
	&common_movingLeftDownOffset
};

const CharFuncCollisionReaction common_mapCollisionReactions[8] = {
	&common_mapMovingDownOffset,
	&common_mapMovingRightDownOffset,
	&common_mapMovingRightOffset,
	&common_mapMovingRightUpOffset,
	&common_mapMovingUpOffset,
	&common_mapMovingLeftUpOffset,
	&common_mapMovingLeftOffset,
	&common_mapMovingLeftDownOffset
};

const CharFuncCollisionReaction common_mapCollisionReactionsWhileFallingDown[8] = {
	&common_mapMovingDownOffsetWhileFallingDown,
	&common_mapMovingRightDownOffsetWhileFallingDown,
	&common_mapMovingRightOffsetWhileFallingDown,
	&common_mapMovingRightUpOffsetWhileFallingDown,
	&common_mapMovingUpOffsetWhileFallingDown,
	&common_mapMovingLeftUpOffsetWhileFallingDown,
	&common_mapMovingLeftOffsetWhileFallingDown,
	&common_mapMovingLeftDownOffsetWhileFallingDown
};

const CommonMapCollision common_mapCollision[8] = {
    &commonMovingDownMapCollision,
	&commonMovingRightDownMapCollision,
	&commonMovingRightMapCollision,
	&commonMovingRightUpMapCollision,
	&commonMovingUpMapCollision,
	&commonMovingLeftUpMapCollision,
	&commonMovingLeftMapCollision,
	&commonMovingLeftDownMapCollision
};

const Position NOT_FOUND_POSITION = {-1, -1, -1};

const s32 common_zOffsetDown =  -2*MOVE_STR;

extern const SpriteDisplay common_shadowDisplay;
extern const unsigned short shadow_pal[];
EWRAM bool shouldSetShadow = true;

void commonInitShadow() {
	lzss2vram(common_shadowDisplay.spriteSet->set[0].layers[0].image, common_shadowDisplay.baseImageId);
}

void commonReverseDisplayShadow() {
	shouldSetShadow = !shouldSetShadow;
}

int commonSetShadow(int x, int y, OBJ_ATTR *oamBuf){
	if (shouldSetShadow) {
		SpriteDisplay shadowDisplay = common_shadowDisplay;
		shadowDisplay.baseY = y - 1;
		shadowDisplay.baseX = x;
		shadowDisplay.isInScreen = true;

		commonSetToOamBuffer(&shadowDisplay, oamBuf);
		return 1;
	}
	return 0;
}

void commonSetToOamBuffer(const SpriteDisplay *spriteDisplay, OBJ_ATTR *oamBuf) {
    int i, xScreen, yScreen, id = spriteDisplay->baseImageId;
	int currentAnimation = spriteDisplay->currentAnimationFrame;
	const int maxAnimation = spriteDisplay->spriteSet->numberOfAnimation;
	const int numberOfLayers = spriteDisplay->spriteSet->set[currentAnimation].numberOflayers;
	
	//BRYAN temporary assert
	assert(currentAnimation < maxAnimation);
	
    for (i = 0; i < numberOfLayers; ++i) {

        yScreen = (spriteDisplay->baseY + 
			spriteDisplay->spriteSet->set[currentAnimation].layers[i].offsetY) & 0x00FF;
	
		oamBuf[i].attr0 = ATTR0_SET(yScreen, 
		    spriteDisplay->spriteSet->set[currentAnimation].layers[i].shape);

        xScreen = (spriteDisplay->baseX + 
			spriteDisplay->spriteSet->set[currentAnimation].layers[i].offsetX) & 0x01FF;
		
		oamBuf[i].attr1 = ATTR1_SET(xScreen, 
			spriteDisplay->spriteSet->set[currentAnimation].layers[i].size,
			spriteDisplay->spriteSet->set[currentAnimation].layers[i].hflip, 
			spriteDisplay->spriteSet->set[currentAnimation].layers[i].vflip);
		
		id += spriteDisplay->spriteSet->set[currentAnimation].layers[i].idOffset;
		
		oamBuf[i].attr2 =  ATTR2_SET(id,
		    spriteDisplay->basePalleteId + 
			spriteDisplay->spriteSet->set[currentAnimation].layers[i].palleteidOffset, 3);
		
		oamBuf[i].fill = 0;
	}
}

void commonSetToOamBufferAsMask(SpriteDisplay *spriteDisplay, OBJ_ATTR *oamBuf, SPRITESHAPE shape,
		SPRITESIZE size) {
    int i, xScreen, yScreen, id = spriteDisplay->baseImageId;
	
    for (i = 0; i < 1; ++i) {

        yScreen = (spriteDisplay->baseY) & 0x00FF;

		oamBuf[i].attr0 = ATTR0_SETASMASK(yScreen, shape);

        xScreen = (spriteDisplay->baseX) & 0x01FF;
		
		oamBuf[i].attr1 = ATTR1_SET(xScreen, size,0, 0);
		
		oamBuf[i].attr2 =  ATTR2_SET(id,
		    spriteDisplay->basePalleteId, 3);
			
		oamBuf[i].fill = 0;
	}
}

void commonSetToOamBufferAsObjWindow(SpriteDisplay *spriteDisplay, OBJ_ATTR *oamBuf) {
	int i, xScreen, yScreen, id = spriteDisplay->baseImageId;

    for (i = 0; i < spriteDisplay->spriteSet->set[spriteDisplay->currentAnimationFrame].numberOflayers; ++i) {

        yScreen = (spriteDisplay->baseY + 
			spriteDisplay->spriteSet->set[spriteDisplay->currentAnimationFrame].layers[i].offsetY) & 0x00FF;

		oamBuf[i].attr0 = ATTR0_SETASWINOBJ(yScreen, 
		    spriteDisplay->spriteSet->set[spriteDisplay->currentAnimationFrame].layers[i].shape);

        xScreen = (spriteDisplay->baseX + 
			spriteDisplay->spriteSet->set[spriteDisplay->currentAnimationFrame].layers[i].offsetX) & 0x01FF;

		oamBuf[i].attr1 = ATTR1_SET(xScreen, 
			spriteDisplay->spriteSet->set[spriteDisplay->currentAnimationFrame].layers[i].size,
			spriteDisplay->spriteSet->set[spriteDisplay->currentAnimationFrame].layers[i].hflip, 
			spriteDisplay->spriteSet->set[spriteDisplay->currentAnimationFrame].layers[i].vflip);

		id += spriteDisplay->spriteSet->set[spriteDisplay->currentAnimationFrame].layers[i].idOffset;

		oamBuf[i].attr2 =  ATTR2_SET(id,
		    spriteDisplay->basePalleteId + 
			spriteDisplay->spriteSet->set[spriteDisplay->currentAnimationFrame].layers[i].palleteidOffset, 3);

		oamBuf[i].fill = 0;
	}
}

void commonDrawDisplay(SpriteDisplay *spriteDisplay) {
	int i, id = spriteDisplay->baseImageId;
	if (spriteDisplay->imageUpdateStatus == EUpdate) {
		for (i = 0; i < spriteDisplay->spriteSet->set[spriteDisplay->currentAnimationFrame].numberOflayers; ++i) {
		    
			id += spriteDisplay->spriteSet->set[spriteDisplay->currentAnimationFrame].layers[i].idOffset;
		    if (spriteDisplay->spriteSet->set[spriteDisplay->currentAnimationFrame]
			    .layers[i].compression == LZSS_COMPRESSION) {
				//gbatimer_profileStart();
			    lzss2vram(
			        spriteDisplay->spriteSet->set[spriteDisplay->currentAnimationFrame].layers[i].image, id);
				//time[i] = gbatimer_profileStop();
			} else {
			   // gbatimer_profileStart();
		    	sprite_vram_copy32_ID(
			        spriteDisplay->spriteSet->set[spriteDisplay->currentAnimationFrame].layers[i].image,
			        uncompressedCopySize[spriteDisplay->spriteSet->set[spriteDisplay->currentAnimationFrame].layers[i].shape]
					    [spriteDisplay->spriteSet->set[spriteDisplay->currentAnimationFrame].layers[i].size], id);
				//time[2] = gbatimer_profileStop();
			}
		}
	}
}

UpdateStatus commonInitializeAction(CharacterAttr* character) {
    if (character->nextAction != character->action) {
		character->spriteDisplay.currentAnimationFrame = 0;
		character->spriteDisplay.numberOfFramesPassed = 0; 
	    return EUpdate;
	} else if (character->nextDirection != character->direction) {
		return EUpdate;
	}
	
	return ENoUpdate;
}

UpdateStatus commonUpdateAnimation(SpriteDisplay *spriteDisplay) {
	int frameCount = spriteDisplay->spriteSet->numberOfAnimation;
	
	++spriteDisplay->numberOfFramesPassed;
	if (spriteDisplay->numberOfFramesPassed >= 
	    spriteDisplay->spriteSet->set[spriteDisplay->currentAnimationFrame].displayForNumFrames) {
		spriteDisplay->numberOfFramesPassed = 0;
		++spriteDisplay->currentAnimationFrame;
		if (spriteDisplay->currentAnimationFrame >= frameCount) {
			spriteDisplay->currentAnimationFrame = 0;
		}
		return EUpdate;
	}
	return ENoUpdate;
}

UpdateStatus commonUpdateCharacterAnimation(CharacterAttr* character) {
	if(commonInitializeAction(character) != ENoUpdate) {
	    return EUpdate;
	}
	
	return commonUpdateAnimation(&character->spriteDisplay);
}

bool commonAnimation_IsLastFrame(const SpriteDisplay* spriteDisplay) {
	int animationframeCount = spriteDisplay->spriteSet->numberOfAnimation;
	int displayCurrentAnimationForNumberOfFrames = spriteDisplay->spriteSet->set[spriteDisplay->currentAnimationFrame].displayForNumFrames;
	return (spriteDisplay->currentAnimationFrame + 1) >= animationframeCount && 
		(spriteDisplay->numberOfFramesPassed + 1) >= displayCurrentAnimationForNumberOfFrames;
	
}

void getNextFrame(const SpriteDisplay* spriteDisplay, int *nextScreenFrame, 
    int *nextAnimationFrame, bool *isLastFrame) {
	int frameCount = spriteDisplay->spriteSet->numberOfAnimation;
	
	*isLastFrame = false;
	*nextAnimationFrame = spriteDisplay->currentAnimationFrame;
	*nextScreenFrame = spriteDisplay->numberOfFramesPassed + 1;
	if (*nextScreenFrame >= 
	    spriteDisplay->spriteSet->set[spriteDisplay->currentAnimationFrame].displayForNumFrames) {
		*nextScreenFrame = 0;
		*nextAnimationFrame += 1;
		if (*nextAnimationFrame >= frameCount) {
		    *isLastFrame = true;
			*nextAnimationFrame = 0;
		}
	}
}

void commonGetCharacterNextFrame(const CharacterAttr* character, int *nextScreenFrame, 
    int *nextAnimationFrame, bool *isLastFrame) {	
	
	if (character->nextDirection != character->direction || character->nextAction != character->action) {
	    *nextScreenFrame = 0;
		*nextAnimationFrame = 0;
		*isLastFrame = false;
		return;
	}
	
	getNextFrame(&character->spriteDisplay, nextScreenFrame, nextAnimationFrame, isLastFrame);
}

bool commonIsInScreen(int charStartX, int charEndX, int charStartY, int charEndY, 
    const Position *scr_pos, const ScreenDimension *scr_dim) {
	int screenStartX = scr_pos->x, screenEndX = scr_pos->x + scr_dim->width;
	int screenStartY = scr_pos->y, screenEndY = scr_pos->y + scr_dim->height;
	
	return (charStartX >= screenStartX && charStartX <= screenEndX ||
	    charEndX >= screenStartX && charEndX <= screenEndX) &&
		(charStartY >= screenStartY && charStartY <= screenEndY ||
		charEndY >= screenStartY && charEndY <= screenEndY);
}

bool common_checkNext(bool isOtherCharBelow, const Position *characterPos, 
    const Position *othercharacterPos) {
	int distance = CONVERT_2POS(othercharacterPos->y) - CONVERT_2POS(characterPos->y);
	bool negativeDist = distance < 0;
	distance *= (negativeDist*(-1)) + ((!negativeDist));
	/*if (isOtherCharBelow && (CONVERT_2POS(othercharacterPos->y) - CONVERT_2POS(characterPos->y)) > COLLISIONCHECKNEXT_DIST_MAX) {
		return false;
	} else if ((CONVERT_2POS(characterPos->y)  - CONVERT_2POS(othercharacterPos->y)) >  COLLISIONCHECKNEXT_DIST_MAX) {
		return false;
	}*/
	
	return (distance <= COLLISIONCHECKNEXT_DIST_MAX);
}

void commonHandleBlockedPath(CharacterAIControl *charControl, EDirections *goDirection) {
	if (*goDirection == EUnknown) {
		return;
	}
	if(charControl->leftBlocked) {
		*goDirection = EUp;
	}
	if(charControl->rightBlocked) {
		*goDirection = EDown;
	}
	if(charControl->upBlocked) {
		*goDirection = ERight;
	}
	if(charControl->downBlocked) {
		*goDirection = ELeft;
	}
}

bool inBounds(int value, int min, int max) {
    return (value >= min & value <= max);
}

bool isOverlap(const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox) {
    return (inBounds(charBoundingBox->startX, otherCharBoundingBox->startX, otherCharBoundingBox->endX) |
		inBounds(otherCharBoundingBox->startX, charBoundingBox->startX, charBoundingBox->endX) |
	    inBounds(charBoundingBox->endX, otherCharBoundingBox->startX, otherCharBoundingBox->endX) |
	    inBounds(otherCharBoundingBox->endX, charBoundingBox->startX, charBoundingBox->endX))
		&
		(inBounds(charBoundingBox->startY, otherCharBoundingBox->startY, otherCharBoundingBox->endY) | 
		inBounds(otherCharBoundingBox->startY, charBoundingBox->startY, charBoundingBox->endY) |
		inBounds(charBoundingBox->endY, otherCharBoundingBox->startY, otherCharBoundingBox->endY)|
		inBounds(otherCharBoundingBox->endY, charBoundingBox->startY, charBoundingBox->endY));
}

bool hasCollision(const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox) {
    return isOverlap(charBoundingBox, otherCharBoundingBox) &
		(inBounds(charBoundingBox->startZ, otherCharBoundingBox->startZ, otherCharBoundingBox->endZ) | 
		inBounds(otherCharBoundingBox->startZ, charBoundingBox->startZ, charBoundingBox->endZ) | 
		inBounds(charBoundingBox->endZ, otherCharBoundingBox->startZ, otherCharBoundingBox->endZ) |
		inBounds(otherCharBoundingBox->endZ, charBoundingBox->startZ, charBoundingBox->endZ)); 
}

void convertWaypointToBoundingBox(const Position *wayPoint, BoundingBox *boundingBox) {
	boundingBox->startX = wayPoint->x + 8;
	boundingBox->endX =  wayPoint->x - 8;
	boundingBox->startY =  wayPoint->y + 8;
	boundingBox->endY =  wayPoint->y - 8;
	boundingBox->startZ =  wayPoint->z;
	boundingBox->endZ =   wayPoint->z + 32;
}

bool commonHasReachedWaypoint(const Position *waypoint, const BoundingBox *boundingBox) {
	BoundingBox waypointBox;
	convertWaypointToBoundingBox(waypoint, &waypointBox);
	return hasCollision(&waypointBox, boundingBox);
}

bool commonCollissionPointInBounds(const Position *collisionPoint, const BoundingBox *boundingBox) {

    return inBounds(collisionPoint->x, boundingBox->startX, boundingBox->endX) &
		inBounds(collisionPoint->y, boundingBox->startY, boundingBox->endY) &
		inBounds(collisionPoint->z, boundingBox->startZ, boundingBox->endZ);
}

bool commonPositionInBounds(const Position *position, const BoundingBox *boundingBox) {

    return inBounds(CONVERT_2POS(position->x), boundingBox->startX, boundingBox->endX) &
		inBounds(CONVERT_2POS(position->y), boundingBox->startY, boundingBox->endY);
}	

void common_noMovement(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox) {
	//common_fallingDown(character, charBoundingBox, otherCharBoundingBox);
}
	
void common_movingRightOffset(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox) {
	bool didCollide = hasCollision(charBoundingBox, otherCharBoundingBox) | hasCollision(otherCharBoundingBox, charBoundingBox);
	int xoffset = (charBoundingBox->endX - otherCharBoundingBox->startX)*(charBoundingBox->endX < otherCharBoundingBox->endX);
	int deltaX = CONVERT_2POS(character->delta.x);
	bool greaterThanXOffset = xoffset > deltaX;
	character->collisionCtrl.hasCollision = didCollide;
	
	xoffset = (deltaX*greaterThanXOffset) + (xoffset*(!greaterThanXOffset));
	xoffset *= didCollide;
	
	character->position.x -= CONVERT_2MOVE(xoffset);
	
	if (character->free->type == EControlAiType) {
		((CharacterAIControl*)character->free)->rightBlocked |= (xoffset != 0);
	}
}
	
void common_movingLeftOffset(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox) {
	bool didCollide = hasCollision(charBoundingBox, otherCharBoundingBox) | hasCollision(otherCharBoundingBox, charBoundingBox);
	int xoffset = (otherCharBoundingBox->endX - charBoundingBox->startX)*(charBoundingBox->startX > otherCharBoundingBox->startX);
	int deltaX = CONVERT_2POS(-character->delta.x);
	bool greaterThanXOffset = xoffset > deltaX;
	
	character->collisionCtrl.hasCollision = didCollide;
	xoffset = (deltaX*greaterThanXOffset) + (xoffset*(!greaterThanXOffset));
	xoffset *= didCollide;
	
	//mprinter_printf("qwe %d\n", CONVERT_2MOVE(xoffset));
	character->position.x += CONVERT_2MOVE(xoffset);
	
	if (character->free->type == EControlAiType) {
		((CharacterAIControl*)character->free)->leftBlocked |= (xoffset != 0);
	}
}

void common_movingUpOffset(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox) {
	bool didCollide = hasCollision(charBoundingBox, otherCharBoundingBox) | hasCollision(otherCharBoundingBox, charBoundingBox);
	
	int yoffset = (otherCharBoundingBox->endY - charBoundingBox->startY)*(charBoundingBox->startY > otherCharBoundingBox->startY);
	int deltaY = CONVERT_2POS(-character->delta.y);
	bool greaterThanYOffset = yoffset > deltaY;
	character->collisionCtrl.hasCollision = didCollide;
	yoffset = (deltaY*greaterThanYOffset) + (yoffset*(!greaterThanYOffset));
	yoffset *= didCollide;

	character->position.y += CONVERT_2MOVE(yoffset);
	
	if (character->free->type == EControlAiType) {
		((CharacterAIControl*)character->free)->upBlocked |= (yoffset != 0);
	}
}

void common_movingDownOffset(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox) {
	bool didCollide = hasCollision(charBoundingBox, otherCharBoundingBox) | hasCollision(otherCharBoundingBox, charBoundingBox);
	
	int yoffset = (charBoundingBox->endY - otherCharBoundingBox->startY)*(charBoundingBox->endY < otherCharBoundingBox->endY);
	int deltaY = CONVERT_2POS(character->delta.y);
	bool greaterThanYOffset = yoffset > deltaY;
	character->collisionCtrl.hasCollision = didCollide;
	yoffset = (deltaY*greaterThanYOffset) + (yoffset*(!greaterThanYOffset));
	yoffset *= didCollide;
	
	character->position.y -= CONVERT_2MOVE(yoffset);
	
	if (character->free->type == EControlAiType) {
		((CharacterAIControl*)character->free)->downBlocked |= (yoffset != 0);
	}
}
	
void common_movingRightUpOffset(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox) {
	bool didCollide = hasCollision(charBoundingBox, otherCharBoundingBox) | hasCollision(otherCharBoundingBox, charBoundingBox);
	character->collisionCtrl.hasCollision = didCollide;
	int xOffset = (charBoundingBox->endX - otherCharBoundingBox->startX);
	int yOffset = (otherCharBoundingBox->endY - charBoundingBox->startY);
	int deltaX = CONVERT_2POS(character->position.x) - CONVERT_2POS(character->position.x - character->delta.x);
	//int deltaY = CONVERT_2POS(-character->delta.y);
	int deltaY = CONVERT_2POS(character->position.y - character->delta.y) - CONVERT_2POS(character->position.y);
	
	bool doOffsetY = (xOffset > yOffset);
	bool greaterThanYOffset = yOffset > deltaY;
	bool greaterThanXOffset = xOffset > deltaX;
	character->collisionCtrl.hasCollision = didCollide;
	xOffset *= (charBoundingBox->endX < otherCharBoundingBox->endX);
	yOffset *= (charBoundingBox->startY > otherCharBoundingBox->startY);
	xOffset = (deltaX*greaterThanXOffset) + (xOffset*(!greaterThanXOffset));
	yOffset = (deltaY*greaterThanYOffset) + (yOffset*(!greaterThanYOffset));
	
	xOffset *= (!doOffsetY)*didCollide;
	yOffset *= doOffsetY*didCollide;
		
	character->position.y += CONVERT_2MOVE(yOffset);
	character->position.x -= CONVERT_2MOVE(xOffset);
	
	if (character->free->type == EControlAiType) {
		((CharacterAIControl*)character->free)->rightBlocked |= (xOffset != 0);
		((CharacterAIControl*)character->free)->upBlocked |= (yOffset != 0);
	}
}

void common_movingLeftUpOffset(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox) {
	bool didCollide = hasCollision(charBoundingBox, otherCharBoundingBox) | hasCollision(otherCharBoundingBox, charBoundingBox);
	character->collisionCtrl.hasCollision = didCollide;
	int xOffset = (otherCharBoundingBox->endX - charBoundingBox->startX);
	int yOffset = (otherCharBoundingBox->endY - charBoundingBox->startY);
	//int deltaX = CONVERT_2POS(-character->delta.x);
	int deltaX = CONVERT_2POS(character->position.x - character->delta.x) - CONVERT_2POS(character->position.x) ;
	//int deltaY = CONVERT_2POS(-character->delta.y);
	int deltaY = CONVERT_2POS(character->position.y - character->delta.y) - CONVERT_2POS(character->position.y);
		
	bool doOffsetY = (xOffset > yOffset);
	bool greaterThanYOffset = yOffset > deltaY;
	bool greaterThanXOffset = xOffset > deltaX;
	character->collisionCtrl.hasCollision = didCollide;
	
	xOffset *= (charBoundingBox->startX > otherCharBoundingBox->startX);
	yOffset *= (charBoundingBox->startY > otherCharBoundingBox->startY);
		
	xOffset = (deltaX*greaterThanXOffset) + (xOffset*(!greaterThanXOffset));
	yOffset = (deltaY*greaterThanYOffset) + (yOffset*(!greaterThanYOffset));
		
	xOffset *= (!doOffsetY)*didCollide;
	yOffset *= doOffsetY*didCollide;
	
	character->position.y += CONVERT_2MOVE(yOffset);
	character->position.x += CONVERT_2MOVE(xOffset);
	
	if (character->free->type == EControlAiType) {
		((CharacterAIControl*)character->free)->leftBlocked |= (xOffset != 0);
		((CharacterAIControl*)character->free)->upBlocked |= (yOffset != 0);
	}
}

void common_movingRightDownOffset(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox) {
	bool didCollide = hasCollision(charBoundingBox, otherCharBoundingBox) | hasCollision(otherCharBoundingBox, charBoundingBox);
	character->collisionCtrl.hasCollision = didCollide;
	int xOffset = (charBoundingBox->endX - otherCharBoundingBox->startX);
	int yOffset = (charBoundingBox->endY - otherCharBoundingBox->startY);
	//int deltaX = CONVERT_2POS(character->delta.x);
	int deltaX = CONVERT_2POS(character->position.x) - CONVERT_2POS(character->position.x - character->delta.x);
	//int deltaY = CONVERT_2POS(character->delta.y);
	int deltaY = CONVERT_2POS(character->position.y) - CONVERT_2POS(character->position.y - character->delta.y);

	bool doOffsetY = (xOffset > yOffset);
	bool greaterThanYOffset = yOffset > deltaY;
	bool greaterThanXOffset = xOffset > deltaX;
	character->collisionCtrl.hasCollision = didCollide;
	xOffset *= (charBoundingBox->endX < otherCharBoundingBox->endX);
	yOffset *= (charBoundingBox->endY < otherCharBoundingBox->endY);
	xOffset = (deltaX*greaterThanXOffset) + (xOffset*(!greaterThanXOffset));
	yOffset = (deltaY*greaterThanYOffset) + (yOffset*(!greaterThanYOffset));
	xOffset *= (!doOffsetY)*didCollide;
	yOffset *= doOffsetY*didCollide;
	
	character->position.y -= CONVERT_2MOVE(yOffset);
	character->position.x -= CONVERT_2MOVE(xOffset);
	
	if (character->free->type == EControlAiType) {
		((CharacterAIControl*)character->free)->rightBlocked |= (xOffset != 0);
		((CharacterAIControl*)character->free)->downBlocked |= (yOffset != 0);
	}
}

void common_movingLeftDownOffset(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox) {
	bool didCollide = hasCollision(charBoundingBox, otherCharBoundingBox) | hasCollision(otherCharBoundingBox, charBoundingBox);
	character->collisionCtrl.hasCollision = didCollide;
	int xOffset = (otherCharBoundingBox->endX - charBoundingBox->startX);
	int yOffset = (charBoundingBox->endY - otherCharBoundingBox->startY);
	//int deltaX = CONVERT_2POS(-character->delta.x);
	int deltaX = CONVERT_2POS(character->position.x - character->delta.x) - CONVERT_2POS(character->position.x) ;
	//int deltaY = CONVERT_2POS(character->delta.y);
	int deltaY = CONVERT_2POS(character->position.y) - CONVERT_2POS(character->position.y - character->delta.y);

	bool doOffsetY = (xOffset > yOffset);
	bool greaterThanYOffset = yOffset > deltaY;
	bool greaterThanXOffset = xOffset > deltaX;
	character->collisionCtrl.hasCollision = didCollide;
	xOffset *= (charBoundingBox->startX > otherCharBoundingBox->startX);
	yOffset *= (charBoundingBox->endY < otherCharBoundingBox->endY);
	xOffset = (deltaX*greaterThanXOffset) + (xOffset*(!greaterThanXOffset));	
	yOffset = (deltaY*greaterThanYOffset) + (yOffset*(!greaterThanYOffset));
	xOffset *= (!doOffsetY)*didCollide;
	yOffset *= doOffsetY*didCollide;
	
	character->position.y -= CONVERT_2MOVE(yOffset);
	character->position.x += CONVERT_2MOVE(xOffset);
	
	if (character->free->type == EControlAiType) {
		((CharacterAIControl*)character->free)->leftBlocked |= (xOffset != 0);
		((CharacterAIControl*)character->free)->downBlocked |= (yOffset != 0);
	}
}

void common_adjustOnInit(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox) {
	int zoffset1 = (otherCharBoundingBox->endZ - charBoundingBox->startZ);
	
	if (zoffset1 >= 0) {
		character->position.z = CONVERT_2MOVE(otherCharBoundingBox->endZ + 1);
	}
}

int common_fallingDown(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox) {
	int zoffset1 = (otherCharBoundingBox->endZ - charBoundingBox->startZ);
	int deltaZ = CONVERT_2POS(-character->delta.z);
	
	if (zoffset1 >= 0 && zoffset1 <= deltaZ) {
		character->position.z = CONVERT_2MOVE(otherCharBoundingBox->endZ + 1);
		return 0;
	}
		
	return -zoffset1;
}

int common_fallingDownOnBoundingBox(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox) {
	bool didOverlap = isOverlap(charBoundingBox, otherCharBoundingBox);
	int zoffset1 = (otherCharBoundingBox->endZ - charBoundingBox->startZ);
	int deltaZ = CONVERT_2POS(-character->delta.z);
	
	if (didOverlap && zoffset1 >= 0 && zoffset1 <= deltaZ) {
		character->position.z = CONVERT_2MOVE(otherCharBoundingBox->endZ + 1);
		return 0;
	} else if (didOverlap && zoffset1 < 0) {
		return -zoffset1;
	}
	
	return -1;
}

void commonGravityEffect(CharacterAttr *character, int zOffsetDown) {
	int isAboveGround;
	character->verticalDirection = EVDown;
	character->delta.z = zOffsetDown;
	character->position.z += character->delta.z;
}

int commonConvertBoundingBoxZ(int zPos) {
	bool belowGround = zPos < 0;
	int adjust =  (belowGround*(-1)) + ((!belowGround)*(1));
	return adjust*CONVERT_TO_BOUNDINGBOX_Z(adjust*zPos);
}

void common_mapMovingRightOffsetWhileFallingDown(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox) {
	if (charBoundingBox->startZ - CONVERT_2POS(character->delta.z) > otherCharBoundingBox->endZ) {
		return;
	}
	common_mapMovingRightOffset(character, charBoundingBox, otherCharBoundingBox);
}

void common_mapMovingRightOffset(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox) {
	bool didCollide = hasCollision(charBoundingBox, otherCharBoundingBox);
	int xoffset = (charBoundingBox->endX - otherCharBoundingBox->startX);
	character->collisionCtrl.hasCollision = didCollide;
	xoffset += 1;
	xoffset *= didCollide;
	character->position.x -= CONVERT_2MOVE(xoffset);
	if (character->free->type == EControlAiType) {
		((CharacterAIControl*)character->free)->rightBlocked |= (xoffset != 0);
	}
}

void common_mapMovingLeftOffsetWhileFallingDown(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox) {
	if (charBoundingBox->startZ - CONVERT_2POS(character->delta.z) > otherCharBoundingBox->endZ) {
		return;
	}
	common_mapMovingLeftOffset(character, charBoundingBox, otherCharBoundingBox);
}
	
void common_mapMovingLeftOffset(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox) {
	bool didCollide = hasCollision(charBoundingBox, otherCharBoundingBox);
	int xoffset = (otherCharBoundingBox->endX - charBoundingBox->startX);
	character->collisionCtrl.hasCollision = didCollide;
	xoffset += 1;
	xoffset *= didCollide;
	character->position.x += CONVERT_2MOVE(xoffset);
	if (character->free->type == EControlAiType) {
		((CharacterAIControl*)character->free)->leftBlocked |= (xoffset != 0);
	}
}

void common_mapMovingUpOffsetWhileFallingDown(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox) {
	if (charBoundingBox->startZ - CONVERT_2POS(character->delta.z) > otherCharBoundingBox->endZ) {
		return;
	}
	common_mapMovingUpOffset(character, charBoundingBox, otherCharBoundingBox);
}

void common_mapMovingUpOffset(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox) {
	bool didCollide = hasCollision(charBoundingBox, otherCharBoundingBox);
	int yoffset = (otherCharBoundingBox->endY - charBoundingBox->startY);
	character->collisionCtrl.hasCollision = didCollide;
	yoffset += 1;
	yoffset *= didCollide;
	character->position.y += CONVERT_2MOVE(yoffset);
	if (character->free->type == EControlAiType) {
		((CharacterAIControl*)character->free)->upBlocked |= (yoffset != 0);
	}
}

void common_mapMovingDownOffsetWhileFallingDown(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox) {
	if (charBoundingBox->startZ - CONVERT_2POS(character->delta.z) > otherCharBoundingBox->endZ) {
		return;
	}
	common_mapMovingDownOffset(character, charBoundingBox, otherCharBoundingBox);
}

void common_mapMovingDownOffset(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox) {
	bool didCollide = hasCollision(charBoundingBox, otherCharBoundingBox);
	int yoffset = (charBoundingBox->endY - otherCharBoundingBox->startY);
	character->collisionCtrl.hasCollision = didCollide;
	yoffset += 1;
	yoffset *= didCollide;
	character->position.y -= CONVERT_2MOVE(yoffset);
	if (character->free->type == EControlAiType) {
		((CharacterAIControl*)character->free)->downBlocked |= (yoffset != 0);
	}  
}

void common_mapMovingRightUpOffsetWhileFallingDown(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox) {
	if (charBoundingBox->startZ - CONVERT_2POS(character->delta.z) > otherCharBoundingBox->endZ) {
		return;
	}
	common_mapMovingRightUpOffset(character, charBoundingBox, otherCharBoundingBox);
}

void common_mapMovingRightUpOffset(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox) {
	bool didCollide = hasCollision(charBoundingBox, otherCharBoundingBox);
	int xOffset = (charBoundingBox->endX - otherCharBoundingBox->startX);
	int yOffset = (otherCharBoundingBox->endY - charBoundingBox->startY);
	bool doOffsetY = (xOffset > yOffset);
	character->collisionCtrl.hasCollision = didCollide;
	yOffset += 1;
	yOffset *= doOffsetY*didCollide;
	xOffset += 1;
	xOffset *= (!doOffsetY)*didCollide;
	character->position.y += CONVERT_2MOVE(yOffset);
	character->position.x -= CONVERT_2MOVE(xOffset);
	if (character->free->type == EControlAiType) {
		((CharacterAIControl*)character->free)->upBlocked |= (yOffset != 0);
		((CharacterAIControl*)character->free)->rightBlocked |= (xOffset != 0);
	}  
}

void common_mapMovingLeftUpOffsetWhileFallingDown(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox) {
	if (charBoundingBox->startZ - CONVERT_2POS(character->delta.z) > otherCharBoundingBox->endZ) {
		return;
	}
	common_mapMovingLeftUpOffset(character, charBoundingBox, otherCharBoundingBox);
}

void common_mapMovingLeftUpOffset(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox) {
	bool didCollide = hasCollision(charBoundingBox, otherCharBoundingBox);
	int xOffset = (otherCharBoundingBox->endX - charBoundingBox->startX);
	int yOffset = (otherCharBoundingBox->endY - charBoundingBox->startY);
	bool doOffsetY = (xOffset > yOffset);
	character->collisionCtrl.hasCollision = didCollide;
	yOffset += 1;
	yOffset *= doOffsetY*didCollide;
	xOffset += 1;
	xOffset *= (!doOffsetY)*didCollide;
	character->position.y += CONVERT_2MOVE(yOffset);
	character->position.x += CONVERT_2MOVE(xOffset);
	
	if (character->free->type == EControlAiType) {
		((CharacterAIControl*)character->free)->upBlocked |= (yOffset != 0);
		((CharacterAIControl*)character->free)->leftBlocked |= (xOffset != 0);
	}
}

void common_mapMovingRightDownOffsetWhileFallingDown(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox) {
	if (charBoundingBox->startZ - CONVERT_2POS(character->delta.z) > otherCharBoundingBox->endZ) {
		return;
	}
	common_mapMovingRightDownOffset(character, charBoundingBox, otherCharBoundingBox);
}

void common_mapMovingRightDownOffset(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox) {
	bool didCollide = hasCollision(charBoundingBox, otherCharBoundingBox);
	int xOffset = (charBoundingBox->endX - otherCharBoundingBox->startX);
	int yOffset = (charBoundingBox->endY - otherCharBoundingBox->startY);
	bool doOffsetY = (xOffset > yOffset);
	character->collisionCtrl.hasCollision = didCollide;
	yOffset += 1;
	yOffset *= doOffsetY*didCollide;
	xOffset += 1;
	xOffset *= (!doOffsetY)*didCollide;
	character->position.y -= CONVERT_2MOVE(yOffset);
	character->position.x -= CONVERT_2MOVE(xOffset);
	if (character->free->type == EControlAiType) {
		((CharacterAIControl*)character->free)->downBlocked |= (yOffset != 0);
		((CharacterAIControl*)character->free)->rightBlocked |= (xOffset != 0);
	}
}

void common_mapMovingLeftDownOffsetWhileFallingDown(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox) {
	if (charBoundingBox->startZ - CONVERT_2POS(character->delta.z) > otherCharBoundingBox->endZ) {
		return;
	}
	common_mapMovingLeftDownOffset(character, charBoundingBox, otherCharBoundingBox);
}

void common_mapMovingLeftDownOffset(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox) {
	bool didCollide = hasCollision(charBoundingBox, otherCharBoundingBox);
	int xOffset = (otherCharBoundingBox->endX - charBoundingBox->startX);
	int yOffset = (charBoundingBox->endY - otherCharBoundingBox->startY);
	bool doOffsetY = (xOffset > yOffset);
	character->collisionCtrl.hasCollision = didCollide;
	yOffset += 1;
	yOffset *= doOffsetY*didCollide;
	xOffset += 1;
	xOffset *= (!doOffsetY)*didCollide;
	character->position.y -= CONVERT_2MOVE(yOffset);
	character->position.x += CONVERT_2MOVE(xOffset);
	if (character->free->type == EControlAiType) {
		((CharacterAIControl*)character->free)->downBlocked |= (yOffset != 0);
		((CharacterAIControl*)character->free)->leftBlocked |= (xOffset != 0);
	}
}

void commonGetBoundsFromMap(s32 x, s32 y, const MapInfo* mapInfo, BoundingBox *charBoundingBox) {
	    int blockX = DIVIDE_BY_16(x);
	    int blockY = DIVIDE_BY_16(y)*DIVIDE_BY_16(mapInfo->width);
	    u8 height = mapInfo->heightMap[blockX + blockY].height;
		//u8 height = mapInfo->heightMap[blockX + blockY].height;
		int result = 1;
		charBoundingBox->startX = (x - GET_REMAINDER_16(x));
		charBoundingBox->endX = (charBoundingBox->startX + 15);
		charBoundingBox->startY = (y - GET_REMAINDER_16(y));
		charBoundingBox->endY = (charBoundingBox->startY + (15));
		charBoundingBox->startZ = 0;
		charBoundingBox->endZ =  height*HEIGHT_CONVERSION;
}

void commonCheckMapCollision(CharacterAttr *character, const MapInfo* mapInfo, const Position *point, 
    const BoundingBox *characterBoundingBox, const CharFuncCollisionReaction reaction) {
	BoundingBox mapBoundingBox;
	commonGetBoundsFromMap(point->x, point->y, mapInfo, &mapBoundingBox);
	reaction(character, characterBoundingBox, &mapBoundingBox);
}

void commonMovingUpMapCollision(CharacterAttr *character, const MapInfo* mapInfo, 
	CharFuncCollisionReaction reaction) {
    int count, i;
    BoundingBox characterBoundingBox;
	for (i = 0; i < 2; ++i) {
		character->getBounds(character, &count, &characterBoundingBox);
		Position points[] = { { characterBoundingBox.startX, characterBoundingBox.startY - 1, 0},
			{ characterBoundingBox.endX, characterBoundingBox.startY - 1, 0} };
	
		commonCheckMapCollision(character, mapInfo, &points[i], &characterBoundingBox, reaction);
	}
	
}

void commonMovingDownMapCollision(CharacterAttr *character, const MapInfo* mapInfo, 
	CharFuncCollisionReaction reaction) {
    int count, i;
    BoundingBox characterBoundingBox;
	for (i = 0; i < 2; ++i) {
		character->getBounds(character, &count, &characterBoundingBox);
		Position points[] = { { characterBoundingBox.startX, characterBoundingBox.endY, 0},
        { characterBoundingBox.endX, characterBoundingBox.endY, 0} };
		commonCheckMapCollision(character, mapInfo, &points[i], &characterBoundingBox, reaction);
	}		
}

void commonMovingRightMapCollision(CharacterAttr *character, const MapInfo* mapInfo, 
	CharFuncCollisionReaction reaction) {
    int count, i;
    BoundingBox characterBoundingBox;
	for (i = 0; i < 2; ++i) {
		character->getBounds(character, &count, &characterBoundingBox);
		Position points[] = { { characterBoundingBox.endX, characterBoundingBox.startY, 0},
        { characterBoundingBox.endX, characterBoundingBox.endY, 0} };
	
		commonCheckMapCollision(character, mapInfo, &points[i], &characterBoundingBox, reaction);
	}
}

void commonMovingLeftMapCollision(CharacterAttr *character, const MapInfo* mapInfo, 
	CharFuncCollisionReaction reaction) {
    int count, i;
    BoundingBox characterBoundingBox;
	for (i = 0; i < 2; ++i) {
		character->getBounds(character, &count, &characterBoundingBox);
		Position points[] = { { characterBoundingBox.startX - 1, characterBoundingBox.startY, 0},
			{ characterBoundingBox.startX - 1, characterBoundingBox.endY, 0} };
	
		commonCheckMapCollision(character, mapInfo, &points[i], &characterBoundingBox, reaction);
	}
}

void commonMovingLeftUpMapCollision(CharacterAttr *character, const MapInfo* mapInfo, 
	CharFuncCollisionReaction reaction) {
    int count, i;
    BoundingBox characterBoundingBox;
	for (i = 0; i < 3; ++i) {
		character->getBounds(character, &count, &characterBoundingBox);
		Position points[] = { { characterBoundingBox.startX - 1, characterBoundingBox.endY, 0},
			{ characterBoundingBox.endX, characterBoundingBox.startY - 1, 0}, 
			{ characterBoundingBox.startX - 1, characterBoundingBox.startY - 1, 0}};
	
		commonCheckMapCollision(character, mapInfo, &points[i], &characterBoundingBox, reaction);
	}
}

void commonMovingLeftDownMapCollision(CharacterAttr *character, const MapInfo* mapInfo, 
	CharFuncCollisionReaction reaction) {
    int count, i;
    BoundingBox characterBoundingBox;
	for (i = 0; i < 3; ++i) {
		character->getBounds(character, &count, &characterBoundingBox);
		Position points[] = { { characterBoundingBox.startX - 1, characterBoundingBox.startY - 1, 0},
			{ characterBoundingBox.endX, characterBoundingBox.endY, 0},
			{ characterBoundingBox.startX - 1, characterBoundingBox.endY, 0} };
	
		commonCheckMapCollision(character, mapInfo, &points[i], &characterBoundingBox, reaction);
	}
}

void commonMovingRightUpMapCollision(CharacterAttr *character, const MapInfo* mapInfo, 
	CharFuncCollisionReaction reaction) {
    int count, i;
    BoundingBox characterBoundingBox, mapBoundingBox;
    for (i = 0; i < 3; ++i) {
		character->getBounds(character, &count, &characterBoundingBox);
		Position points[] = { { characterBoundingBox.endX, characterBoundingBox.endY, 0},
			{ characterBoundingBox.startX - 1, characterBoundingBox.startY - 1, 0},
			{ characterBoundingBox.endX, characterBoundingBox.startY - 1, 0} };
	
		commonCheckMapCollision(character, mapInfo, &points[i], &characterBoundingBox, reaction);
	}
}

void commonMovingRightDownMapCollision(CharacterAttr *character, const MapInfo* mapInfo, 
	CharFuncCollisionReaction reaction) {
    int count, i;
    BoundingBox characterBoundingBox, mapBoundingBox;
    for (i = 0; i < 3; ++i) {
		character->getBounds(character, &count, &characterBoundingBox);
		Position points[] = { { characterBoundingBox.endX, characterBoundingBox.startY - 1, 0},
			{ characterBoundingBox.startX - 1, characterBoundingBox.endY, 0},
			{ characterBoundingBox.endX, characterBoundingBox.endY, 0} };
	
		commonCheckMapCollision(character, mapInfo, &points[i], &characterBoundingBox, reaction);
	}
}

void commonFallingDownRight(CharacterAttr *character, const BoundingBox *charBoundingBox, 
	const BoundingBox *otherCharBoundingBox) {
	//mprinter_printf("RIGHT ");
	bool didCollide = hasCollision(charBoundingBox, otherCharBoundingBox);
	if (didCollide) {
		int offset = charBoundingBox->endX - otherCharBoundingBox->startX;
		character->position.x -= CONVERT_2MOVE(offset + 1);
	}
}

void commonFallingDownLeft(CharacterAttr *character, const BoundingBox *charBoundingBox, 
	const BoundingBox *otherCharBoundingBox) {
	//mprinter_printf("LEFT %d %d %d %d other %d %d %d %d", charBoundingBox->startX, charBoundingBox->startY,
	//charBoundingBox->endX, charBoundingBox->endY, otherCharBoundingBox->startX, otherCharBoundingBox->startY,
	//otherCharBoundingBox->endX, otherCharBoundingBox->endY);
	bool didCollide = hasCollision(charBoundingBox, otherCharBoundingBox);
	if (didCollide) {
		int offset = otherCharBoundingBox->endX - charBoundingBox->startX;
		character->position.x += CONVERT_2MOVE(offset + 1);
	}
}

void commonFallingDownUp(CharacterAttr *character, const BoundingBox *charBoundingBox, 
	const BoundingBox *otherCharBoundingBox) {
	//mprinter_printf("UP ");
	bool didCollide = hasCollision(charBoundingBox, otherCharBoundingBox);
	if (didCollide) {
		int offset = otherCharBoundingBox->endY - charBoundingBox->startY;
		character->position.y += CONVERT_2MOVE(offset + 1);
	}
}

void commonFallingDownDown(CharacterAttr *character, const BoundingBox *charBoundingBox, 
	const BoundingBox *otherCharBoundingBox) {
	//mprinter_printf("DOWN\n");
	bool didCollide = hasCollision(charBoundingBox, otherCharBoundingBox);
	if (didCollide) {
		int offset = charBoundingBox->endY - otherCharBoundingBox->startY;
		character->position.y -= CONVERT_2MOVE(offset + 1);
	}
}

const CharFuncFallingCollision fallingDownReaction[] = {
	&commonFallingDownRight, &commonFallingDownLeft, &commonFallingDownUp, &commonFallingDownDown
};

int commonCharacterSetToOAMBuffer(CharacterCollection *charCollection,
	OAMCollection *oamCollection,
	int currentOAMIdx,
	const Position *scr_pos,
	const ScreenDimension *scr_dim) {
	if (charCollection) {
		int charIdx, oamIdx, idxRemoveOam;
		OBJ_ATTR *oamBuffer = oamCollection->data;
		
		for (charIdx = 0, oamIdx = currentOAMIdx; charIdx < charCollection->displaySize; ++charIdx) {
			oamIdx += charCollection->
				charactersForDisplay[charIdx]->setPosition(
					charCollection->charactersForDisplay[charIdx], 
					&oamBuffer[oamIdx], scr_pos, scr_dim);
		}
		return oamIdx;
	}

	return 0;
}

void commonFallingDownCollision(CharacterAttr *character, MapInfo *mapInfo) {
	BoundingBox characterBoundingBox, mapBoundingBox;
	int count, i;
	for (i = 0; i < 4; ++i) {
		character->getBounds(character, &count, &characterBoundingBox);
		Position points[] = { 
			{ character->position.x + CONVERT_2MOVE(8), character->position.y, 0},
			{ character->position.x - CONVERT_2MOVE(8), character->position.y, 0},
			{ character->position.x, character->position.y - CONVERT_2MOVE(8), 0},
			{ character->position.x, character->position.y + CONVERT_2MOVE(8), 0} };	
		commonGetBoundsFromMap(CONVERT_2POS(points[i].x), CONVERT_2POS(points[i].y), mapInfo, &mapBoundingBox);
		fallingDownReaction[i](character, &characterBoundingBox, &mapBoundingBox);
	}
}

void commonSetCharacterEvent(CharacterAttr *character, const CharacterEventControl *eventControl) {
   CharacterEventControl *charControl = (CharacterEventControl*)character->free;
   charControl->type = eventControl->type;
   charControl->width = eventControl->width;
   charControl->height = eventControl->height;
   charControl->countAction = eventControl->countAction;
   charControl->currentAction = 0;
   charControl->returnControl = eventControl->returnControl;
   charControl->isRunning = true;
   charControl->actions = eventControl->actions;
}

void commonTriggerCharacterEvent(CharacterAttr *character, const MapInfo *mapInfo, const CharacterCollection *charCollection) {
	//TODO Make this generic
   CharacterAttr *targetCharacter = mchar_findCharacterType(charCollection, ALISA);
   CharacterEventControl *charControl = (CharacterEventControl*)character->free;

   int count;
   BoundingBox eventBox, targetBox;
   eventBox.startX = character->position.x - charControl->width;
   eventBox.endX = character->position.x + charControl->width;
   eventBox.startY = character->position.y - charControl->height;
   eventBox.endY = character->position.y + charControl->height;
	//TODO initialize z
    if (targetCharacter) {
       charControl->target = &targetCharacter->position;
    }
   
	targetCharacter->getBounds(targetCharacter, &count, &targetBox);
	if (hasCollision(&eventBox, &targetBox)) {
	    character->controller = &commonDoCharacterEvent;
		//TODO check this
		//charCollection->charactersDoEvent[charCollection->characterEventCurrentSize] = character;
		//++charCollection->characterEventCurrentSize;
	}
}

void commonDoActionOneCycle(CharacterAttr *character, const MapInfo *mapInfo, 
    CharacterCollection *charCollection) {
    CharacterEventControl *eventControl = (CharacterEventControl*)character->free;
	int nextScreenFrame, nextAnimationFrame;
    bool isLastFrame = false;
    	   
	ActionControl actionControl = eventControl->actions[eventControl->currentAction];
	
	character->nextDirection = actionControl.direction;
	character->nextAction = actionControl.action;
	
	commonGetCharacterNextFrame(character, &nextScreenFrame, &nextAnimationFrame, &isLastFrame);
	
	if (isLastFrame) {
	    ++eventControl->currentAction;
		if (eventControl->currentAction >= eventControl->countAction) {
			character->controller = eventControl->returnControl;
			eventControl->currentAction = 0;
			eventControl->countAction = 0;
			--charCollection->characterEventCurrentSize;
			charCollection->charactersDoEvent[charCollection->characterEventCurrentSize] = NULL;
		} 
	}
}

void commonDoActionByFrames(CharacterAttr *character, const MapInfo *mapInfo, CharacterCollection *charCollection) {
}

void commonDoCharacterEvent(CharacterAttr *character, const MapInfo *mapInfo, const CharacterCollection *charCollection) {
    CharacterEventControl *eventControl = (CharacterEventControl*)character->free;
	int nextScreenFrame, nextAnimationFrame;
    bool isLastFrame = false;
    	   
	ActionControl actionControl = eventControl->actions[eventControl->currentAction];
	
	character->nextDirection = actionControl.direction;
	character->nextAction = actionControl.action;
	
	commonGetCharacterNextFrame(character, &nextScreenFrame, &nextAnimationFrame, &isLastFrame);
	
	//TODO Check to change this
	/*if (isLastFrame) {
	    character->controller = eventControl->returnControl;
		--charCollection->characterEventCurrentSize;
		charCollection->charactersDoEvent[charCollection->characterEventCurrentSize] = NULL;
	}*/
 }
 
 void transferToBoundingBox(const EventTransfer *transfer, BoundingBox *boundingBox) {
    boundingBox->startX = transfer->x;
	boundingBox->startY = transfer->y;
	boundingBox->endX = transfer->x + transfer->width;
	boundingBox->endY = transfer->y + transfer->length;
	boundingBox->startZ = transfer->zOffset;
	boundingBox->endZ = transfer->zOffset + 32;
}

 void commonCheckForEvents(CharacterAttr* character, MapInfo *mapInfo) {
	int boundBoxCount = 0, i;
	BoundingBox eventBox, characterBoundingBox;
	character->getBounds(character, &boundBoxCount, &characterBoundingBox);
	for (i = 0; i < mapInfo->eventTransferCount; ++i) {
		transferToBoundingBox(&mapInfo->tranfers[i], &eventBox);
		if (hasCollision(&characterBoundingBox, &eventBox)) {
			mapInfo->transferTo = &mapInfo->tranfers[i];
			mapInfo->mapFunction = &fadeToBlack;
			mapInfo->screenEffect.processScreenEffect = &mapCommon_defaultEffect;
			break;
		}
	}
}
void commonInitializeAISetActions(CharacterAIControl *charControl) {
	int i;
	for (i = 0; i < charControl->countAction; ++i) {
		charControl->actions[i].currentFrame = 0;
		charControl->actions[i].doForNumFrames = 0;
	}
	charControl->countAction = 0;
	charControl->currentAction = 0;
}
int commonGetCurrentAnimationFrame(const CharacterAttr* character) {
	return character->spriteDisplay.currentAnimationFrame;
}

int commonGetCurrentDisplayFrame(const CharacterAttr* character) {
	return character->spriteDisplay.numberOfFramesPassed;
}

bool common_shouldDoNextAction(CharacterAttr* character) {
    int nextScreenFrame, nextAnimationFrame;
	bool isLastFrame = false;
	CharacterAIControl *charControl = (CharacterAIControl*)character->free;
		
	commonGetCharacterNextFrame(character, &nextScreenFrame, &nextAnimationFrame, &isLastFrame);

	return (charControl->actions[charControl->currentAction].doForNumFrames == DOACTIONUNTILEND & isLastFrame) ||
		(charControl->actions[charControl->currentAction].doForNumFrames != DOACTIONUNTILEND & 
		    charControl->actions[charControl->currentAction].currentFrame >= 
			charControl->actions[charControl->currentAction].doForNumFrames);
}

bool common_shouldDoIntializeActions(CharacterAttr* character) {
   CharacterAIControl *charControl = (CharacterAIControl*)character->free;
   return charControl->currentAction >= MAXACTIONS | ((charControl->currentAction + 1) >= charControl->countAction &
	common_shouldDoNextAction(character));
}

const Position* commonFindCharTypeInBoundingBox(const CharacterCollection *characterCollection, 
    const BoundingBox *boundingBox, CHARACTERTYPE fromType, CHARACTERTYPE toType) {
	int i;
	for (i = 0; i < characterCollection->currentSize; ++i) {
		if (characterCollection->characters[i]->type >= fromType && 
			characterCollection->characters[i]->type <= toType) {
			if (commonPositionInBounds(&characterCollection->characters[i]->position, boundingBox)) {
				return &characterCollection->characters[i]->position;
			}
		}
	}
	return &NOT_FOUND_POSITION;
}

const Position* commonFindCharTypePositionByDistance(const CharacterCollection *characterCollection, 
    const Position *refPos, int dist, CHARACTERTYPE fromType, CHARACTERTYPE toType) {
	int i, distX, distY;
	for (i = 0; i < characterCollection->currentSize; ++i) {
		if (characterCollection->characters[i]->type >= fromType && 
			characterCollection->characters[i]->type <= toType) {
			distX = CONVERT_2POS(refPos->x) - CONVERT_2POS(characterCollection->characters[i]->position.x);
			distX *= distX;
			distY = CONVERT_2POS(refPos->y) - CONVERT_2POS(characterCollection->characters[i]->position.y);
			distY *= distY;
			dist *= dist;
			if (dist >= distX + distY) {
				return &characterCollection->characters[i]->position;
			}
		}
	}
	return &NOT_FOUND_POSITION;
}

bool commonIsCharTypeInArea(const BoundingBox *area, const CharacterCollection *characterCollection, CHARACTERTYPE findType) {
	int count, i;
    BoundingBox characterBoundingBox;
	for (i = 0; i < characterCollection->currentSize; ++i) {
		if (characterCollection->characters[i]->type != findType) {
			continue;
		}
		characterCollection->characters[i]->getBounds(characterCollection->characters[i], 
			&count, &characterBoundingBox);
		if (hasCollision(area, &characterBoundingBox)) {
			return true;
		}
	}
	return false;
}

void commonSetCharType(const Position* position, const MapInfo *mapInfo, 
	CHARACTERTYPE type, CharacterCollection *characterCollection, 
	CharacterActionCollection *charActionCollection, CharacterAttr *character,
	ControlTypePool* controlPool, CharacterWaypoints *charWaypoints) {
	
	character_InitFunctionsCollection[type](character, controlPool, charWaypoints);
	commonCharacterSetPosition(character, position->x, position->y, position->z, EDown);
	character->doAction(character, mapInfo, characterCollection, charActionCollection);
	character->checkMapCollision(character, mapInfo);
}

void createBoundingBoxAtPosition(const Position* position, BoundingBox *boundingBox) {
	boundingBox->startX = position->x - 16;
	boundingBox->endX = position->x + 16;
	boundingBox->startY = position->y - 16;
	boundingBox->endY = position->y + 16;
	boundingBox->startZ = position->z - 16;
	boundingBox->endZ = position->z + 32;
}

void commonRegenerateCharTypeAt(const BoundingBox *boundingBoxCheckArea, const Position* position, const MapInfo *mapInfo, CHARACTERTYPE type, 
	CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection, 
	ControlTypePool* controlPool, CharacterWaypoints *charWaypoints) {
	BoundingBox charBoundingBox;
	int countBox, i;
	for (i = 0; i < characterCollection->currentSize; ++i) {
		if (characterCollection->characters[i]->type == NONE) {
			return;
		}
		countBox = 0;
		characterCollection->characters[i]->getBounds(characterCollection->characters[i], 
			&countBox, &charBoundingBox);
		if (hasCollision(boundingBoxCheckArea, &charBoundingBox)) {
			return;
		}
	}
	CharacterAttr *character = characterCollection->charactersForDisplay[characterCollection->displaySize];
	if (character->type != NONE) {
		return;
	}
	commonSetCharType(position, mapInfo, type, characterCollection, charActionCollection, character, controlPool, charWaypoints);
	characterCollection->characters[characterCollection->currentSize] = character;
	++characterCollection->currentSize;
	++characterCollection->displaySize;
}

void commonRemoveActionOnInit(CharacterAttr* character, CharacterActionCollection *charActionCollection) {
	if (commonGetCurrentAnimationFrame(character) == 0 && commonGetCurrentDisplayFrame(character) == 0) {
		mchar_actione_remove(character, charActionCollection);
	}
}
bool commonIsFoundPosition(const Position* position) {
	return (position->x != -1) & (position->y != -1);
}

EDirections commonReverseDirection(EDirections direction) {
 return (direction+4)&EDirectionsMax;
}

void common_findPosition(const Position *current, const Position *target, 
	const EDirections blocked, EDirections *direction) {
	if (blocked == ELeft || blocked == ERight) {
		int yDirection = current->y - target->y;
		if (yDirection < 0) {
			*direction = EDown;
		} else {
			*direction = EUp;
		}	
	} else if (blocked == EUp || blocked == EDown) {
		int xDirection = current->x - target->x;
		if (xDirection < 0) {
			*direction = ERight;
		} else {
			*direction = ELeft;
		}
	} 
}

void common_doGoAroundObstacle(const Position *current, const Position *target, 
	CharacterAIControl *charControl, int action, int duration) {
	EDirections goTarget;
	if (charControl->leftBlocked) {
		charControl->currentAction = 0;
		charControl->countAction = 1;
		common_findPosition(current, target, ELeft, &goTarget);
		charControl->actions[0] = ((ActionControl){duration, 0, goTarget, action});
		charControl->leftBlocked = false;
	} else if (charControl->rightBlocked) {
		charControl->currentAction = 0;
		charControl->countAction = 1;
		common_findPosition(current, target, ERight, &goTarget);
		charControl->actions[0] = ((ActionControl){duration, 0, goTarget, action});
		charControl->rightBlocked = false;
	} else if (charControl->upBlocked) {
		charControl->currentAction = 0;
		charControl->countAction = 1;
		common_findPosition(current, target, EUp, &goTarget);
		charControl->actions[0] = ((ActionControl){duration, 0, goTarget, action});
		charControl->upBlocked = false;
	} else if (charControl->downBlocked) {
		charControl->currentAction = 0;
		charControl->countAction = 1;
		common_findPosition(current, target, EDown, &goTarget);
		charControl->actions[0] = ((ActionControl){duration, 0, goTarget, action});
		charControl->downBlocked = false;
	}
}

void common_doSetActions(CharacterAIControl *charControl, CharacterAttr* character)  {
	if (charControl->currentAction < charControl->countAction) {
		character->nextAction = charControl->actions[charControl->currentAction].action;
		character->nextDirection = charControl->actions[charControl->currentAction].direction;
		++charControl->actions[charControl->currentAction].currentFrame;
		if (charControl->actions[charControl->currentAction].currentFrame >= 
			charControl->actions[charControl->currentAction].doForNumFrames) {
			charControl->actions[charControl->currentAction].currentFrame = 0;
			++charControl->currentAction;
		}
	}
}