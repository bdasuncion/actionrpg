#include <stdlib.h>
#include <stdbool.h>
#include "GBATypes.h"
#include "GBAObject.h"
#include "GBAVideo.h"
#include "GBADMA.h"
#include "CharacterSkullDemon.h"
#include "ImageSkullDemon.h"
#include "GBACharacterActionEvent.h"
#include "UtilCommonValues.h"
#include "ManagerVram.h"
#include "ManagerSound.h"
#include "ManagerCharacterActionEvents.h"
#include "CharacterSkullDemon.h"
#include "SpriteSetSkullDemon.h"
#include "CharacterCommon.h"
#include "MapCommon.h"
#include "GBAMap.h"
#include "ManagerCharacters.h"
#include "ManagerPrinter.h"

extern const EDirections directions[EDirectionsCount];

#define SKULLDEMON_LENGTH 14
#define SKULLDEMON_WIDTH 10
#define SKULLDEMON_HEIGHT 36

#define SKULLDEMON_SCRCNVRTWIDTH 16
#define SKULLDEMON_SCRCNVRTHEIGHT 28

#define SKULLDEMON_SCREENDISPLAYOFFSET_X 10
#define SKULLDEMON_SCREENDISPLAYOFFSET_Y 28

#define SKULLDEMON_PAL_CNT 1

#define skulldemon_WALK_MVMNT_CTRL_MAX 4

#define MAX_DIST_FOR_CHASE 80

#define SKULLDEMON_ATTACK_ANIMATIONFRAME_START 3
#define SKULLDEMON_ATTACK_ANIMATIONFRAME_END 4

#define SKULLDEMON_NATTACK_ZPOS_OFFSET 16

const u8 skulldemon_scrConversionMeasurements[EScrCnvrtMeasureCount] = {
	SKULLDEMON_SCRCNVRTWIDTH,
	SKULLDEMON_SCRCNVRTHEIGHT
};

const u8 skulldemon_boundingBoxMeasurements[EBBCnvrtMeasurementCount] = {
	SKULLDEMON_LENGTH,
	SKULLDEMON_WIDTH,
	SKULLDEMON_HEIGHT,
};

const s32 skulldemon_walkOffsetX[EDirectionsCount][skulldemon_WALK_MVMNT_CTRL_MAX] = {
    {0,0,0,0,0},
	{1*MOVE_DIAG,0,1*MOVE_DIAG,0,1*MOVE_DIAG},
	{1*MOVE_STR,0,1*MOVE_STR,0,1*MOVE_STR},
	{1*MOVE_DIAG,0,1*MOVE_DIAG,0,1*MOVE_DIAG},
	{0,0,0,0,0},
	{-1*MOVE_DIAG,0,-1*MOVE_DIAG,0,-1*MOVE_DIAG},
	{-1*MOVE_STR,0,-1*MOVE_STR,0,-1*MOVE_STR},
	{-1*MOVE_DIAG,0,-1*MOVE_DIAG,0,-1*MOVE_DIAG}
};

const s32 skulldemon_walkOffsetY[EDirectionsCount][skulldemon_WALK_MVMNT_CTRL_MAX] = {
    {1*MOVE_STR,0,1*MOVE_STR,0,1*MOVE_STR},
	{1*MOVE_DIAG,0,1*MOVE_DIAG,0,1*MOVE_DIAG},
	{0,0,0,0,0},
	{-1*MOVE_DIAG,0,-1*MOVE_DIAG,0,-1*MOVE_DIAG},
	{-1*MOVE_STR,0,-1*MOVE_STR,0,-1*MOVE_STR},
	{-1*MOVE_DIAG,0,-1*MOVE_DIAG,0,-1*MOVE_DIAG},
	{0,0,0,0,0},
	{1*MOVE_DIAG,0,1*MOVE_DIAG,0,1*MOVE_DIAG}
};

const OffsetPoints skulldemon_scanSurroundingOffset[8][2] = {
    {{-24,0},{24,64}},
	{{-24,0},{24,64}},
	{{0,-24},{64,24}},
	{{-24,-64},{24,0}},
	{{-24,-64},{24,0}},
	{{-24,-64},{24,0}},
	{{-64,-24},{0,24}},
	{{-24,0},{24,64}}
};

const OffsetPoints skulldemon_strike_offsetValues[8][2] = {
    {{0, 16}, {0, 32}},
	{{0, 16}, {0, 32}},
	{{16, -6}, {32, -6}},
	{{0, -16}, {0, -16}},
	{{0, -16}, {0, -16}},
	{{0, -16}, {0, -16}},
	{{-16, 6}, {-32, 6}},
	{{0, 16}, {0, 32}},
};

const BoundingBox skulldemon_strikeCollisionBox[8] = {
	{ -8, 8, 8, 24, 8, 18, 0,0,0,0},
	{ -8, 8, 8, 24, 8, 18, 0,0,0,0},
	{ 8, 24, -8, 8, 8, 18, 0,0,0,0},
	{ -8, 8, -24, -8, 8, 18, 0,0,0,0},
	{ -8, 8, -24, -8, 8, 18, 0,0,0,0},
	{ -8, 8, -24, -8, 8, 18, 0,0,0,0},
	{ -24, -8, -8, 8, 8, 18, 0,0,0,0},
	{ -8, 8, 8, 24, 8, 18, 0,0,0,0}
};

const OffsetPoints skulldemon_scanLastKnownPosition = { 16, 16 };

void skulldemon_actionWalk(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection);
void skulldemon_actionChaseTarget(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection);
void skulldemon_actionAttack(CharacterAttr* character,const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection);
void skulldemon_actionStunned(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection);
bool skulldemon_isHit(CharacterAttr *character, CharacterActionEvent *actionEvent);
	
CharFuncAction skulldemon_actions[] = {
	&skulldemon_actionWalk,
	//&skulldemon_actionChaseTarget,
	//&skulldemon_actionAttack,
	//&skulldemon_actionStunned
};


void skulldemon_walkAroundController(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection);
void skulldemon_doAction(CharacterAttr* character, const MapInfo *mapInfo, 
    const CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection);
void skulldemon_getBoundingBoxMoving(const CharacterAttr* character, int *count, BoundingBox *boundingBox);
void skulldemon_getBoundingBoxStanding(const CharacterAttr* character, int *count, BoundingBox *boundingBox);
int skulldemon_setPosition(CharacterAttr* character, OBJ_ATTR *oamBuf, 
	const Position *scr_pos, const ScreenDimension *scr_dim);
void skulldemon_checkMapCollision(CharacterAttr* character, const MapInfo* mapInfo);
void skulldemon_checkCollision(CharacterAttr* character, bool isOtherCharBelow,
	bool *checkNext, const CharacterAttr* otherCharacter);
	
void skulldemon_init(CharacterAttr* character, ControlTypePool* controlPool) {
//use library to get id
	character->id = 0;
	//use enum of character type
	character->type = SKULLDEMON;
	
	//set to 0
	commonCharacterInit(character, ESkullDemonInitialize, ESkullDemonWalk, EDown);
	commonCharacterSetPosition(character, 0, 0, 0, EDown);
	character->controller = &skulldemon_walkAroundController;
	character->doAction = &skulldemon_doAction;
	character->setPosition = &skulldemon_setPosition;
	character->getBounds = &skulldemon_getBoundingBoxMoving;
	character->checkCollision = &skulldemon_checkCollision;
	character->checkMapCollision = &skulldemon_checkMapCollision;
	character->isHit = &skulldemon_isHit;
		
	//character->spriteDisplay.baseImageId = sprite_vram_findIdByType(ECharSizeLarge);
	character->spriteDisplay.baseImageId = sprite_vram_findIdByType(ECharSizeMedium);
	//character->spriteDisplay.baseImageId = sprite_vram_findIdByType(ECharSizeSmall);
	character->spriteDisplay.imageUpdateStatus = EUpdate;
	character->spriteDisplay.basePalleteId = sprite_palette_findId(SKULLDEMON, SKULLDEMON_PAL_CNT);
	sprite_palette_copy32_ID(skull_demon_walking_side_pal, character->spriteDisplay.basePalleteId);
	character->spriteDisplay.palleteUpdateStatus = EUpdate;
	//CharacterAIControl *charControl = mchar_getControlType(controlPool);
	CharacterAIControl *charControl = (CharacterAIControl*)mchar_findFreeControlType(controlPool);
	charControl->type = EControlAiType;
	//charControl->countAction = 0;
	//charControl->currentAction = MAXACTIONS;
	charControl->countAction = 1;
	charControl->currentAction = 0;
	character->nextAction = ESkullDemonWalk;
	charControl->rightBlocked = false;
	charControl->leftBlocked = false;
	charControl->upBlocked = false;
	charControl->downBlocked = false;
	charControl->currentStatus = ESkullDemonAIStateWalkAround;
	charControl->wayPointCnt = 2;
	charControl->wayPointCurrent = 0;
	
	//charControl->patrolPoints[0] = {141, 77, 1};
	//charControl->patrolPoints[1] = {141, 176, 1};
	charControl->wayPoints[0].x = 141;
	charControl->wayPoints[0].y = 77;
	charControl->wayPoints[0].z = 1;
	charControl->wayPoints[1].x = 141;
	charControl->wayPoints[1].y = 200;
	charControl->wayPoints[1].z = 1;
	
	character->free = (ControlTypeUnion*)charControl;
	
	character->stats.maxLife = 10;
	character->stats.currentLife = 3;
	character->stats.currentStatus = ESkullDemonAIStateWalkAround;
}

void skulldemon_doAction(CharacterAttr* character,
	const MapInfo *mapInfo, const CharacterCollection *characterCollection,
	CharacterActionCollection *charActionCollection) {
	int boundBoxCount = 0;
	CharBoundingBox boundingBox;
	
	if (character->nextAction < ESkullDemonActionCount) {
		skulldemon_actions[character->nextAction](character, mapInfo, 
		    characterCollection, charActionCollection);
	}
}

void skulldemon_actionWalk(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection) {
	bool isLastFrame = false;
	int nextScreenFrame, nextAnimationFrame;
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
	    character->movementCtrl.maxFrames = skulldemon_WALK_MVMNT_CTRL_MAX;
		character->movementCtrl.currentFrame = 0;
	}
	
	character->action = character->nextAction;
	character->direction = character->nextDirection;
	
	if (character->movementCtrl.currentFrame >= character->movementCtrl.maxFrames) {
	    character->movementCtrl.currentFrame = 0;
	}
	
	character->delta.x = skulldemon_walkOffsetX[character->direction][character->movementCtrl.currentFrame];
	character->position.x += character->delta.x;
		
	character->delta.y = skulldemon_walkOffsetY[character->direction][character->movementCtrl.currentFrame];
	character->position.y += character->delta.y;
	/*if (commonGetCurrentAnimationFrame(character) == 0 || commonGetCurrentAnimationFrame(character) == 2) {
		character->delta.x = skulldemon_walkOffsetX[character->direction][character->movementCtrl.currentFrame];
		character->position.x += character->delta.x;
		
		character->delta.y = skulldemon_walkOffsetY[character->direction][character->movementCtrl.currentFrame];
		character->position.y += character->delta.y;
	} else {
		character->delta.x = 0;
		character->delta.y = 0;
	}
	
	commonGravityEffect(character, common_zOffsetDown);*/
	
	++character->movementCtrl.currentFrame;
	character->spriteDisplay.spriteSet = skulldemonWalking[character->direction];
	
	boundingBox.startX = CONVERT_2POS(position->x) + skulldemon_scanSurroundingOffset[character->direction][0].x;
	boundingBox.startY = CONVERT_2POS(position->y) + skulldemon_scanSurroundingOffset[character->direction][0].y;
	boundingBox.endX = CONVERT_2POS(position->x) + skulldemon_scanSurroundingOffset[character->direction][1].x;
	boundingBox.endY = CONVERT_2POS(position->y) + skulldemon_scanSurroundingOffset[character->direction][1].y;

	/*charControl->target = *commonFindCharTypeInBoundingBox(characterCollection, &boundingBox, 
		STARTPLAYABLECHARTYPE, ENDPLAYABLECHARACTERTYPE);
		
	if (commonIsFoundPosition(&charControl->target)) {
		//charControl->currentStatus = EZombieStatusHuntTarget;
	}*/
}

void skulldemon_getBoundingBoxMoving(const CharacterAttr* character, 
	int *count, BoundingBox *boundingBox) {
	*count = 1;
	u16 x = CONVERT_TO_BOUNDINGBOX_X(character->position.x, skulldemon_boundingBoxMeasurements);
	u16 y = CONVERT_TO_BOUNDINGBOX_Y(character->position.y, skulldemon_boundingBoxMeasurements);
	u16 z = commonConvertBoundingBoxZ(character->position.z);
	boundingBox->startX = x;
	boundingBox->startY = y;
	boundingBox->endX = x + skulldemon_boundingBoxMeasurements[EBBCnvrtLength];
	boundingBox->endY = y + skulldemon_boundingBoxMeasurements[EBBCnvrtWidth];
	boundingBox->startZ = z;
	boundingBox->endZ = z + SKULLDEMON_HEIGHT;
	/*boundingBox->direction = character->direction;
	boundingBox->isMoving = true;
	boundingBox->isMovable = false;*/
}

int skulldemon_setPosition(CharacterAttr* character,
	OBJ_ATTR *oamBuf, 
	const Position *scr_pos,
	const ScreenDimension *scr_dim) 
{

	int charStartX, charStartY, charEndX, charEndY, numberOfShadow = 0;
	
	character->spriteDisplay.baseY = CONVERT_TO_SCRYPOS(character->position.y, 
		scr_pos->y, skulldemon_scrConversionMeasurements);
	character->spriteDisplay.baseX = CONVERT_TO_SCRXPOS(character->position.x, 
		scr_pos->x, skulldemon_scrConversionMeasurements);
	character->spriteDisplay.baseY -= CONVERT_TO_SCRZPOS(character->position.z);
	
	charStartX = CONVERT_2POS(character->position.x) - SKULLDEMON_SCREENDISPLAYOFFSET_X;
	charStartY = CONVERT_2POS(character->position.y) - CONVERT_2POS(character->position.z);
	charEndX = CONVERT_2POS(character->position.x) + SKULLDEMON_SCREENDISPLAYOFFSET_X;
	charEndY = charStartY - SKULLDEMON_SCREENDISPLAYOFFSET_Y;
	
	//mprinter_printf("%d %d %d %d\n", charStartX, charStartY, charEndX, charEndY);
	//mprinter_printf("%d %d\n", CONVERT_2POS(character->position.y), CONVERT_2POS(character->position.z));
	if (commonIsInScreen(charStartX, charEndX, charStartY, charEndY, scr_pos, scr_dim)) {
		character->spriteDisplay.imageUpdateStatus = ((!character->spriteDisplay.isInScreen)*EUpdate) + 
		    (character->spriteDisplay.isInScreen*character->spriteDisplay.imageUpdateStatus);
		character->spriteDisplay.isInScreen = true;
		commonSetToOamBuffer(&character->spriteDisplay, oamBuf);
		
		numberOfShadow = commonSetShadow(character->spriteDisplay.baseX, 
			character->spriteDisplay.baseY + character->distanceFromGround + SKULLDEMON_SCRCNVRTHEIGHT,
			&oamBuf[character->spriteDisplay.spriteSet->set[character->spriteDisplay.currentAnimationFrame].numberOflayers]);
			
		return character->spriteDisplay.spriteSet->set[character->spriteDisplay.currentAnimationFrame].numberOflayers + numberOfShadow;
	}
	
	character->spriteDisplay.isInScreen = false;
	return 0;
}

void skulldemon_checkCollision(CharacterAttr* character, bool isOtherCharBelow,
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

bool skulldemon_isHit(CharacterAttr *character, CharacterActionEvent *actionEvent) {
	CharacterAIControl *charControl = (CharacterAIControl*)character->free;
	return false;
	/*if (character->stats.currentStatus == EStatusNoActionCollision) {
		return false;
	}
	character->stats.currentLife -= 1;
	//character->stats.currentStatus = EStatusNoActionCollision;
	charControl->currentStatus = ESkullDemonAIStateStunned;
	//add hit animation
	if (character->stats.currentLife <= 0) {
		commonRemoveCharacter(character);
	}
	return true;*/
}

void skulldemon_checkMapCollision(CharacterAttr* character, const MapInfo* mapInfo) {
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

