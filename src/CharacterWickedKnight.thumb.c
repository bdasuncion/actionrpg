#include <stdlib.h>
#include <stdbool.h>
#include "GBATypes.h"
#include "GBAObject.h"
#include "GBAVideo.h"
#include "GBADMA.h"
#include "CharacterWickedKnight.h"
#include "ImageWickedKnight.h"
#include "GBACharacterActionEvent.h"
#include "UtilCommonValues.h"
#include "ManagerVram.h"
#include "ManagerSound.h"
#include "ManagerCharacterActionEvents.h"
#include "CharacterWickedKnight.h"
#include "SpriteSetWickedKnight.h"
#include "CharacterCommon.h"
#include "MapCommon.h"
#include "GBAMap.h"
#include "ManagerCharacters.h"
#include "ManagerPrinter.h"

extern const EDirections directions[EDirectionsCount];

#define WICKEDKNIGHT_LENGTH 14
#define WICKEDKNIGHT_WIDTH 10
#define WICKEDKNIGHT_HEIGHT 36

#define WICKEDKNIGHT_SCRCNVRTWIDTH 16
#define WICKEDKNIGHT_SCRCNVRTHEIGHT 28

#define WICKEDKNIGHT_SCREENDISPLAYOFFSET_X 10
#define WICKEDKNIGHT_SCREENDISPLAYOFFSET_Y 28

#define WICKEDKNIGHT_PAL_CNT 1

#define wickedknight_WALK_MVMNT_CTRL_MAX 4

//#define MAX_DIST_FOR_CHASE 80

#define WICKEDKNIGHT_ATTACK_ANIMATIONFRAME_START 3
#define WICKEDKNIGHT_ATTACK_ANIMATIONFRAME_END 4

#define WICKEDKNIGHT_NATTACK_ZPOS_OFFSET 16

const u8 wickedknight_scrConversionMeasurements[EScrCnvrtMeasureCount] = {
	WICKEDKNIGHT_SCRCNVRTWIDTH,
	WICKEDKNIGHT_SCRCNVRTHEIGHT
};

const u8 wickedknight_boundingBoxMeasurements[EBBCnvrtMeasurementCount] = {
	WICKEDKNIGHT_LENGTH,
	WICKEDKNIGHT_WIDTH,
	WICKEDKNIGHT_HEIGHT,
};

const s32 wickedknight_walkOffsetX[EDirectionsCount][wickedknight_WALK_MVMNT_CTRL_MAX] = {
    {0,0,0,0,0},
	{1*MOVE_DIAG,0,1*MOVE_DIAG,0,1*MOVE_DIAG},
	{1*MOVE_STR,0,1*MOVE_STR,0,1*MOVE_STR},
	{1*MOVE_DIAG,0,1*MOVE_DIAG,0,1*MOVE_DIAG},
	{0,0,0,0,0},
	{-1*MOVE_DIAG,0,-1*MOVE_DIAG,0,-1*MOVE_DIAG},
	{-1*MOVE_STR,0,-1*MOVE_STR,0,-1*MOVE_STR},
	{-1*MOVE_DIAG,0,-1*MOVE_DIAG,0,-1*MOVE_DIAG}
};

const s32 wickedknight_walkOffsetY[EDirectionsCount][wickedknight_WALK_MVMNT_CTRL_MAX] = {
    {1*MOVE_STR,0,1*MOVE_STR,0,1*MOVE_STR},
	{1*MOVE_DIAG,0,1*MOVE_DIAG,0,1*MOVE_DIAG},
	{0,0,0,0,0},
	{-1*MOVE_DIAG,0,-1*MOVE_DIAG,0,-1*MOVE_DIAG},
	{-1*MOVE_STR,0,-1*MOVE_STR,0,-1*MOVE_STR},
	{-1*MOVE_DIAG,0,-1*MOVE_DIAG,0,-1*MOVE_DIAG},
	{0,0,0,0,0},
	{1*MOVE_DIAG,0,1*MOVE_DIAG,0,1*MOVE_DIAG}
};

const OffsetPoints wickedknight_scanSurroundingOffset[8][2] = {
    {{-24,0},{24,64}},
	{{-24,0},{24,64}},
	{{0,-24},{64,24}},
	{{-24,-64},{24,0}},
	{{-24,-64},{24,0}},
	{{-24,-64},{24,0}},
	{{-64,-24},{0,24}},
	{{-24,0},{24,64}}
};

const OffsetPoints wickedknight_strike_offsetValues[8][2] = {
    {{0, 16}, {0, 32}},
	{{0, 16}, {0, 32}},
	{{16, -6}, {32, -6}},
	{{0, -16}, {0, -16}},
	{{0, -16}, {0, -16}},
	{{0, -16}, {0, -16}},
	{{-16, 6}, {-32, 6}},
	{{0, 16}, {0, 32}},
};

const BoundingBox wickedknight_strikeCollisionBox[8] = {
	{ -8, 8, 8, 24, 8, 18, 0,0,0,0},
	{ -8, 8, 8, 24, 8, 18, 0,0,0,0},
	{ 8, 24, -8, 8, 8, 18, 0,0,0,0},
	{ -8, 8, -24, -8, 8, 18, 0,0,0,0},
	{ -8, 8, -24, -8, 8, 18, 0,0,0,0},
	{ -8, 8, -24, -8, 8, 18, 0,0,0,0},
	{ -24, -8, -8, 8, 8, 18, 0,0,0,0},
	{ -8, 8, 8, 24, 8, 18, 0,0,0,0}
};

const OffsetPoints wickedknight_scanLastKnownPosition = { 16, 16 };

void wickedknight_actionWalk(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection);
void wickedknight_actionChaseTarget(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection);
void wickedknight_actionAttack(CharacterAttr* character,const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection);
void wickedknight_actionStunned(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection);
bool wickedknight_isHit(CharacterAttr *character, CharacterActionEvent *actionEvent);
	
const CharFuncAction wickedknight_actions[] = {
	&wickedknight_actionWalk,
	&wickedknight_actionChaseTarget,
	&wickedknight_actionAttack,
	&wickedknight_actionStunned
};


void wickedknight_walkAroundController(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection);
void wickedknight_doAction(CharacterAttr* character, const MapInfo *mapInfo, 
    const CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection);
void wickedknight_getBoundingBoxMoving(const CharacterAttr* character, int *count, BoundingBox *boundingBox);
void wickedknight_getBoundingBoxStanding(const CharacterAttr* character, int *count, BoundingBox *boundingBox);
int wickedknight_setPosition(CharacterAttr* character, OBJ_ATTR *oamBuf, 
	const Position *scr_pos, const ScreenDimension *scr_dim);
void wickedknight_checkMapCollision(CharacterAttr* character, const MapInfo* mapInfo);
void wickedknight_checkCollision(CharacterAttr* character, bool isOtherCharBelow,
	bool *checkNext, const CharacterAttr* otherCharacter);
	
void wickedknight_init(CharacterAttr* character, ControlTypePool* controlPool, 
	CharacterWaypoints *charWaypoints) {
//use library to get id
	character->id = 0;
	//use enum of character type
	character->type = WICKEDKNIGHT;
	
	//set to 0
	commonCharacterInit(character, EWickedKnightInitialize, EWickedKnightWalk, EDown);
	commonCharacterSetPosition(character, 0, 0, 0, EDown);
	character->controller = &wickedknight_walkAroundController;
	character->doAction = &wickedknight_doAction;
	character->setPosition = &wickedknight_setPosition;
	character->getBounds = &wickedknight_getBoundingBoxMoving;
	character->checkCollision = &wickedknight_checkCollision;
	character->checkMapCollision = &wickedknight_checkMapCollision;
	character->isHit = &wickedknight_isHit;
		
	//character->spriteDisplay.baseImageId = sprite_vram_findIdByType(ECharSizeLarge);
	character->spriteDisplay.baseImageId = sprite_vram_findIdByType(ECharSizeMedium);
	//character->spriteDisplay.baseImageId = sprite_vram_findIdByType(ECharSizeSmall);
	character->spriteDisplay.imageUpdateStatus = EUpdate;
	character->spriteDisplay.basePalleteId = sprite_palette_findId(WICKEDKNIGHT, WICKEDKNIGHT_PAL_CNT);
	sprite_palette_copy32_ID(wickedknight_body_walk_side_pal, character->spriteDisplay.basePalleteId);
	character->spriteDisplay.palleteUpdateStatus = EUpdate;
	//CharacterAIControl *charControl = mchar_getControlType(controlPool);
	CharacterAIControl *charControl = (CharacterAIControl*)mchar_findFreeControlType(controlPool);
	charControl->type = EControlAiType;
	//charControl->countAction = 0;
	//charControl->currentAction = MAXACTIONS;
	charControl->countAction = 1;
	charControl->currentAction = 0;
	character->nextAction = EWickedKnightWalk;
	charControl->rightBlocked = false;
	charControl->leftBlocked = false;
	charControl->upBlocked = false;
	charControl->downBlocked = false;
	charControl->currentStatus = EWickedKnightAIStateWalkAround;
	
	charControl->wayPointCnt = charWaypoints->wayPointCnt;
	charControl->wayPointCurrent = 0;
	charControl->wayPoints = charWaypoints->wayPoints;
	
	character->free = (ControlTypeUnion*)charControl;
	
	character->stats.maxLife = 10;
	character->stats.currentLife = 3;
	character->stats.currentStatus = EWickedKnightAIStateWalkAround;
}

void wickedknight_doAction(CharacterAttr* character,
	const MapInfo *mapInfo, const CharacterCollection *characterCollection,
	CharacterActionCollection *charActionCollection) {
	int boundBoxCount = 0;
	CharBoundingBox boundingBox;
	
	if (character->nextAction < EWickedKnightActionCount) {
		wickedknight_actions[character->nextAction](character, mapInfo, 
		    characterCollection, charActionCollection);
	}
}

void wickedknight_actionWalk(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection) {
	bool isLastFrame = false;
	int nextScreenFrame, nextAnimationFrame;
	Position *position = &character->position;
	CharacterAIControl *charControl = (CharacterAIControl*)character->free;
	BoundingBox searchArea;
	
	character->spriteDisplay.imageUpdateStatus = ENoUpdate;
	character->spriteDisplay.palleteUpdateStatus = ENoUpdate;
	if (commonUpdateCharacterAnimation(character) == EUpdate) {
		character->spriteDisplay.imageUpdateStatus = EUpdate;
		character->spriteDisplay.palleteUpdateStatus = EUpdate;
	}
	
	if (character->action != character->nextAction) {
	    character->movementCtrl.maxFrames = wickedknight_WALK_MVMNT_CTRL_MAX;
		character->movementCtrl.currentFrame = 0;
	}
			
	if (character->movementCtrl.currentFrame >= character->movementCtrl.maxFrames) {
	    character->movementCtrl.currentFrame = 0;
	}
	
	character->action = character->nextAction;
	character->direction = character->nextDirection;
	
	character->delta.x = wickedknight_walkOffsetX[character->direction][character->movementCtrl.currentFrame];
	character->position.x += character->delta.x;
		
	character->delta.y = wickedknight_walkOffsetY[character->direction][character->movementCtrl.currentFrame];
	character->position.y += character->delta.y;
	
	commonGravityEffect(character, common_zOffsetDown);
	
	++character->movementCtrl.currentFrame;
	character->spriteDisplay.spriteSet = wickedknightWalking[character->direction];
}

void wickedknight_actionChaseTarget(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection) {
	bool isLastFrame = false;
	int nextScreenFrame, nextAnimationFrame, xDist, yDist;
	Position *position = &character->position;
	CharacterAIControl *charControl = (CharacterAIControl*)character->free;
	BoundingBox boundingBox;
	
	character->spriteDisplay.imageUpdateStatus = ENoUpdate;
	character->spriteDisplay.palleteUpdateStatus = ENoUpdate;
	if (commonUpdateCharacterAnimation(character) == EUpdate) {
		character->spriteDisplay.imageUpdateStatus = EUpdate;
		character->spriteDisplay.palleteUpdateStatus = EUpdate;
	}
	
	if (character->action != character->nextAction) {
	    character->movementCtrl.maxFrames = wickedknight_WALK_MVMNT_CTRL_MAX;
		character->movementCtrl.currentFrame = 0;
	}
		
	character->action = character->nextAction;
	character->direction = character->nextDirection;
	
	if (character->movementCtrl.currentFrame >= character->movementCtrl.maxFrames) {
	    character->movementCtrl.currentFrame = 0;
	}

	character->delta.x = wickedknight_walkOffsetX[character->direction][character->movementCtrl.currentFrame];
	character->position.x += character->delta.x;
	
	character->delta.y = wickedknight_walkOffsetY[character->direction][character->movementCtrl.currentFrame];
	character->position.y += character->delta.y;
	
	commonGravityEffect(character, common_zOffsetDown);
	
	++character->movementCtrl.currentFrame;
	character->spriteDisplay.spriteSet = wickedknightWalking[character->direction];
}

void wickedknight_actionAttack(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection) {
	bool isLastFrame = false;
	int nextScreenFrame, nextAnimationFrame, xDist, yDist;
	Position *position = &character->position;
	CharacterAIControl *charControl = (CharacterAIControl*)character->free;
	BoundingBox boundingBox;
		
	character->spriteDisplay.imageUpdateStatus = ENoUpdate;
	character->spriteDisplay.palleteUpdateStatus = ENoUpdate;
	if (commonUpdateCharacterAnimation(character) == EUpdate) {
		character->spriteDisplay.imageUpdateStatus = EUpdate;
		character->spriteDisplay.palleteUpdateStatus = EUpdate;
		character->delta.x = 0;
		character->delta.y = 0;
		character->delta.z = 0;
	}
	
	character->action = character->nextAction;
	character->direction = character->nextDirection;
	
	commonGravityEffect(character, common_zOffsetDown);
	
	++character->movementCtrl.currentFrame;
	character->spriteDisplay.spriteSet = wickedknightAttacking[character->direction];
	
	commonGetCharacterNextFrame(character, &nextScreenFrame, &nextAnimationFrame, &isLastFrame);
	//currentAnimationFrame = commonGetCurrentAnimationFrame(character);
	if (isLastFrame) {
		character->nextAction = EWickedKnightChaseTarget;
	}
}

void wickedknight_actionStunned(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection) {
	CharacterAIControl *charControl = (CharacterAIControl*)character->free;
	++charControl->actions[charControl->currentAction].currentFrame;
	if (charControl->actions[charControl->currentAction].currentFrame >= 
		charControl->actions[charControl->currentAction].doForNumFrames) {
		commonInitializeAISetActions(charControl);
		charControl->currentStatus = EWickedKnightAIStateHuntTarget;
		charControl->currentAction = MAXACTIONS;
	}
}

void wickedknight_getBoundingBoxMoving(const CharacterAttr* character, 
	int *count, BoundingBox *boundingBox) {
	*count = 1;
	u16 x = CONVERT_TO_BOUNDINGBOX_X(character->position.x, wickedknight_boundingBoxMeasurements);
	u16 y = CONVERT_TO_BOUNDINGBOX_Y(character->position.y, wickedknight_boundingBoxMeasurements);
	u16 z = commonConvertBoundingBoxZ(character->position.z);
	boundingBox->startX = x;
	boundingBox->startY = y;
	boundingBox->endX = x + wickedknight_boundingBoxMeasurements[EBBCnvrtLength];
	boundingBox->endY = y + wickedknight_boundingBoxMeasurements[EBBCnvrtWidth];
	boundingBox->startZ = z;
	boundingBox->endZ = z + WICKEDKNIGHT_HEIGHT;
}

int wickedknight_setPosition(CharacterAttr* character,
	OBJ_ATTR *oamBuf, 
	const Position *scr_pos,
	const ScreenDimension *scr_dim) 
{

	int charStartX, charStartY, charEndX, charEndY, numberOfShadow = 0;
	
	character->spriteDisplay.baseY = CONVERT_TO_SCRYPOS(character->position.y, 
		scr_pos->y, wickedknight_scrConversionMeasurements);
	character->spriteDisplay.baseX = CONVERT_TO_SCRXPOS(character->position.x, 
		scr_pos->x, wickedknight_scrConversionMeasurements);
	character->spriteDisplay.baseY -= CONVERT_TO_SCRZPOS(character->position.z);
	
	charStartX = CONVERT_2POS(character->position.x) - WICKEDKNIGHT_SCREENDISPLAYOFFSET_X;
	charStartY = CONVERT_2POS(character->position.y) - CONVERT_2POS(character->position.z);
	charEndX = CONVERT_2POS(character->position.x) + WICKEDKNIGHT_SCREENDISPLAYOFFSET_X;
	charEndY = charStartY - WICKEDKNIGHT_SCREENDISPLAYOFFSET_Y;
	
	if (commonIsInScreen(charStartX, charEndX, charStartY, charEndY, scr_pos, scr_dim)) {
		character->spriteDisplay.imageUpdateStatus = ((!character->spriteDisplay.isInScreen)*EUpdate) + 
		    (character->spriteDisplay.isInScreen*character->spriteDisplay.imageUpdateStatus);
		character->spriteDisplay.isInScreen = true;
		commonSetToOamBuffer(&character->spriteDisplay, oamBuf);
		
		numberOfShadow = commonSetShadow(character->spriteDisplay.baseX, 
			character->spriteDisplay.baseY + character->distanceFromGround + WICKEDKNIGHT_SCRCNVRTHEIGHT,
			&oamBuf[character->spriteDisplay.spriteSet->set[character->spriteDisplay.currentAnimationFrame].numberOflayers]);
			
		return character->spriteDisplay.spriteSet->set[character->spriteDisplay.currentAnimationFrame].numberOflayers + numberOfShadow;
	}
	
	character->spriteDisplay.isInScreen = false;
	return 0;
}

void wickedknight_checkCollision(CharacterAttr* character, bool isOtherCharBelow,
	bool *checkNext, const CharacterAttr* otherCharacter) {
	
	int count;
	BoundingBox charBoundingBox, otherCharBoundingBox;
	*checkNext = common_checkNext(isOtherCharBelow, &character->position, &otherCharacter->position);
	if (!*checkNext) {
		return;
	}
	
	character->getBounds(character, &count, &charBoundingBox);
	otherCharacter->getBounds(otherCharacter, &count, &otherCharBoundingBox);
	
	common_collisionReactions[character->direction]
	    (character, &charBoundingBox, &otherCharBoundingBox);
}

bool wickedknight_isHit(CharacterAttr *character, CharacterActionEvent *actionEvent) {
	CharacterAIControl *charControl = (CharacterAIControl*)character->free;
	//return false;
	if (character->stats.currentStatus == EStatusNoActionCollision) {
		return false;
	}
	character->stats.currentLife -= 1;
	//character->stats.currentStatus = EStatusNoActionCollision;
	charControl->currentStatus = EWickedKnightAIStateStunned;
	//add hit animation
	if (character->stats.currentLife <= 0) {
		commonRemoveCharacter(character);
	}
	return true;
}

void wickedknight_checkMapCollision(CharacterAttr* character, const MapInfo* mapInfo) {
	int count;
	BoundingBox mapBoundingBox, characterBoundingBox;
	CharacterAIControl *charControl = (CharacterAIControl*)character->free;
	int fallingDown;

	character->getBounds(character, &count, &characterBoundingBox);
	commonGetBoundsFromMap(CONVERT_2POS(character->position.x), CONVERT_2POS(character->position.y), mapInfo, &mapBoundingBox);
	fallingDown = common_fallingDown(character, &characterBoundingBox, &mapBoundingBox);
	
	character->distanceFromGround = fallingDown;
	
	if (fallingDown > 0) {
		commonFallingDownCollision(character, mapInfo);
	}
	
    commonCharacterMapEdgeCheck(character, mapInfo);
	common_mapCollision[character->direction](character, mapInfo, 
	    common_mapCollisionReactions[character->direction]);
}
