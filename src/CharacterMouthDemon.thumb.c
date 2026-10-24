#include <stdlib.h>
#include <stdbool.h>
#include "GBATypes.h"
#include "GBAObject.h"
#include "GBAVideo.h"
#include "GBADMA.h"
#include "GBACharacterActionEvent.h"
#include "UtilCommonValues.h"
#include "SpriteSetAlisa.h"
#include "ManagerVram.h"
#include "ManagerSound.h"
#include "ManagerCharacterActionEvents.h"
#include "ManagerPrinter.h"
#include "CharacterMouthDemon.h"
#include "CharacterCommon.h"
#include "MapCommon.h"
#include "GBAMap.h"
#include "ManagerCharacters.h"
#include "ManagerPrinter.h"

#include "ImageMouthDemon.h"
#include "SpriteSetMouthDemon.h"

#include "DebugLogMgba.h"

#define MOUTHDEMON_LENGTH 32
#define MOUTHDEMON_WIDTH 10
#define MOUTHDEMON_HEIGHT 16

#define MOUTHDEMON_SCRCNVRTWIDTH 32
#define MOUTHDEMON_SCRCNVRTHEIGHT 16

#define MOUTHDEMON_PAL_CNT 1

const u8 mouthDemon_boundingBoxMeasurements[EBBCnvrtMeasurementCount] = {
	MOUTHDEMON_LENGTH,
	MOUTHDEMON_WIDTH,
	MOUTHDEMON_HEIGHT,
};

const u8 mouthdemon_scrConversionMeasurements[EScrCnvrtMeasureCount] = {
	MOUTHDEMON_SCRCNVRTWIDTH,
	MOUTHDEMON_SCRCNVRTHEIGHT
};

#define MOUTHDEMON_FLOAT_MVMNT_CTRL_MAX 5
#define MOUTHDEMON_FLOAT 150

const s32 moluthdemon_floatOffsetZ[1][MOUTHDEMON_FLOAT_MVMNT_CTRL_MAX] = {
	{1*MOVE_STR,0,0,0,0},
};

void moutDemon_actionFloat(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection);
void moutDemon_actionFloatUp(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection);
void moutDemon_actionFloatDown(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection);
	

int mouthDemon_setPosition(CharacterAttr* character, OBJ_ATTR *oamBuf,  const Position *scr_pos,
	const ScreenDimension *scr_dim);

void mouthDemon_getBoundingBoxMoving(const CharacterAttr* character, 
	int *count, BoundingBox *boundingBox);
	
void mouthDemon_checkCollision(CharacterAttr* character, bool isOtherCharBelow,
	bool *checkNext, const CharacterAttr* otherCharacter);
	
void mouthDemon_checkMapCollision(CharacterAttr* character, const MapInfo* mapInfo);

bool mouthDemon_isHit(CharacterAttr *character, CharacterActionEvent *actionEvent);
	
const CharFuncAction mouthDemon_actions[] = {
	&moutDemon_actionFloat,
	&moutDemon_actionFloatUp,
	&moutDemon_actionFloatDown
};

void mouthDemon_floatController(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection);

void mouthDemon_doAction(CharacterAttr* character,
	const MapInfo *mapInfo, const CharacterCollection *characterCollection,
	CharacterActionCollection *charActionCollection) {
	int boundBoxCount = 0;
	CharBoundingBox boundingBox;
	
	//mprinter_printf("ACTION: ACTUAL:%d EXPECTED:%d", character->nextAction, EGhoulHurt);
	if (character->nextAction < EMouthDemonActionCount) {
		mouthDemon_actions[character->nextAction](character, mapInfo, 
		    characterCollection, charActionCollection);
	}
}
	
void mouthDemon_init(CharacterAttr* character, ControlTypePool* controlPool, 
	CharacterWaypoints *charWaypoints) {
//use library to get id
	character->id = 0;
	//use enum of character type
	character->type = MOUTHDEMON;
	
	//set to 0
	commonCharacterInit(character, EMouthDemonInitialize, EMouthDemonFloat, EDown);
	commonCharacterSetPosition(character, 0, 0, 0, EDown);
	character->controller = &mouthDemon_floatController;
	character->doAction = &mouthDemon_doAction;
	character->setPosition = &mouthDemon_setPosition;
	character->getBounds = &mouthDemon_getBoundingBoxMoving;
	character->checkCollision = &mouthDemon_checkCollision;
	character->checkMapCollision = &mouthDemon_checkMapCollision;
	character->isHit = &mouthDemon_isHit;
		
	character->spriteDisplay.baseImageId = sprite_vram_findIdByType(ECharSizeSmall);
	character->spriteDisplay.imageUpdateStatus = EUpdate;
	character->spriteDisplay.basePalleteId = sprite_palette_findId(MOUTHDEMON, MOUTHDEMON_PAL_CNT);
	sprite_palette_copy32_ID(mouthdemon_pal, character->spriteDisplay.basePalleteId);
	character->spriteDisplay.palleteUpdateStatus = EUpdate;
	//CharacterAIControl *charControl = mchar_getControlType(controlPool);
	CharacterAIControl *charControl = (CharacterAIControl*)mchar_findFreeControlType(controlPool);
	charControl->type = EControlAiType;
	//charControl->countAction = 0;
	//charControl->currentAction = MAXACTIONS;
	charControl->countAction = 1;
	charControl->currentAction = 0;
	character->nextAction = EMouthDemonFloat;
	charControl->rightBlocked = false;
	charControl->leftBlocked = false;
	charControl->upBlocked = false;
	charControl->downBlocked = false;
	charControl->currentStatus = EMouthDemonAIStateFloat;
	charControl->revive = false;
	
	if (charWaypoints != NULL && charWaypoints->wayPointCnt > 1) {
		charControl->wayPointCnt = charWaypoints->wayPointCnt;
		charControl->wayPointCurrent = 0;
		charControl->wayPoints = charWaypoints->wayPoints;
	} else {
		charControl->wayPointCnt = 0;
		charControl->wayPointCurrent = 0;
		//charControl->wayPoints = NULL;
	}
		
	character->free = (ControlTypeUnion*)charControl;
	
	character->stats.maxLife = 10;
	character->stats.currentLife = 44;
	character->stats.currentStatus = EMouthDemonAIStateFloat;
	
	character->inducedMove = NULL;
	character->finalDelta.x = 0;
	character->finalDelta.y = 0;
	character->finalDelta.z = 0;
	character->delta.x = 0;
	character->delta.y = 0;
	character->delta.z = 0;
}

void moutDemon_actionFloat(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection) {
	mprinter_printf("FLOAT STEADY\n");
	if (commonUpdateCharacterAnimation(character) == EUpdate) {
		character->spriteDisplay.imageUpdateStatus = EUpdate;
		character->spriteDisplay.palleteUpdateStatus = EUpdate;
	}
	
	character->spriteDisplay.currentAnimationFrame = 0;
	character->spriteDisplay.numberOfFramesPassed = 0; 
	
	character->spriteDisplay.spriteSet = &mouth_demon_floating_left;
}

void moutDemon_actionFloatUp(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection) {
	mprinter_printf("FLOAT UP\n");
	if (commonUpdateCharacterAnimation(character) == EUpdate) {
		character->spriteDisplay.imageUpdateStatus = EUpdate;
		character->spriteDisplay.palleteUpdateStatus = EUpdate;
	}
	
	if (character->action != character->nextAction) {
	    character->movementCtrl.maxFrames = MOUTHDEMON_FLOAT_MVMNT_CTRL_MAX;
		character->movementCtrl.currentFrame = 0;
	}
	
	character->action = character->nextAction;
	
	character->movementCtrl.currentFrame = (!(character->movementCtrl.currentFrame >= 
		character->movementCtrl.maxFrames))*character->movementCtrl.currentFrame;
		
	character->delta.z = moluthdemon_floatOffsetZ[0][character->movementCtrl.currentFrame];
	character->position.z += character->delta.z;
	
	character->spriteDisplay.currentAnimationFrame = 0;
	character->spriteDisplay.numberOfFramesPassed = 0; 
	
	character->spriteDisplay.spriteSet = &mouth_demon_floating_left;
}

void moutDemon_actionFloatDown(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection) {
	mprinter_printf("FLOAT DOWN\n");
	if (commonUpdateCharacterAnimation(character) == EUpdate) {
		character->spriteDisplay.imageUpdateStatus = EUpdate;
		character->spriteDisplay.palleteUpdateStatus = EUpdate;
	}
	
	if (character->action != character->nextAction) {
	    character->movementCtrl.maxFrames = MOUTHDEMON_FLOAT_MVMNT_CTRL_MAX;
		character->movementCtrl.currentFrame = 0;
	}
	
	character->action = character->nextAction;
	
	character->movementCtrl.currentFrame = (!(character->movementCtrl.currentFrame >= 
		character->movementCtrl.maxFrames))*character->movementCtrl.currentFrame;
		
	character->delta.z = -moluthdemon_floatOffsetZ[0][character->movementCtrl.currentFrame];
	character->position.z += character->delta.z;
	
	character->spriteDisplay.currentAnimationFrame = 0;
	character->spriteDisplay.numberOfFramesPassed = 0; 
	
	character->spriteDisplay.spriteSet = &mouth_demon_floating_left;
}

#define MOUTHDEMON_SCREENDISPLAYOFFSET_X 8
#define MOUTHDEMON_SCREENDISPLAYOFFSET_Y 16

int mouthDemon_setPosition(CharacterAttr* character,
	OBJ_ATTR *oamBuf, 
	const Position *scr_pos,
	const ScreenDimension *scr_dim) 
{

	int charStartX, charStartY, charEndX, charEndY, numberOfShadow = 0;
	
	character->spriteDisplay.baseY = CONVERT_TO_SCRYPOS(character->position.y, 
		scr_pos->y, mouthdemon_scrConversionMeasurements);
	character->spriteDisplay.baseX = CONVERT_TO_SCRXPOS(character->position.x, 
		scr_pos->x, mouthdemon_scrConversionMeasurements);
	character->spriteDisplay.baseY -= CONVERT_TO_SCRZPOS(character->position.z);
	
	charStartX = CONVERT_2POS(character->position.x) - MOUTHDEMON_SCREENDISPLAYOFFSET_X;
	charStartY = CONVERT_2POS(character->position.y) - CONVERT_2POS(character->position.z);
	charEndX = CONVERT_2POS(character->position.x) + MOUTHDEMON_SCREENDISPLAYOFFSET_Y;
	charEndY = charStartY - MOUTHDEMON_SCREENDISPLAYOFFSET_Y;
	
	if (commonIsInScreen(charStartX, charEndX, charStartY, charEndY, scr_pos, scr_dim)) {
		character->spriteDisplay.imageUpdateStatus = ((!character->spriteDisplay.isInScreen)*EUpdate) + 
		    (character->spriteDisplay.isInScreen*character->spriteDisplay.imageUpdateStatus);
		character->spriteDisplay.isInScreen = true;
		commonSetToOamBuffer(&character->spriteDisplay, oamBuf);
		
		numberOfShadow = commonSetShadow(character->spriteDisplay.baseX, 
			character->spriteDisplay.baseY + character->distanceFromGround + MOUTHDEMON_SCRCNVRTHEIGHT,
			&oamBuf[character->spriteDisplay.spriteSet->set[character->spriteDisplay.currentAnimationFrame].numberOflayers]);
			
		return character->spriteDisplay.spriteSet->set[character->spriteDisplay.currentAnimationFrame].numberOflayers + numberOfShadow;
	}
	
	character->spriteDisplay.isInScreen = false;
	return 0;
}

void mouthDemon_getBoundingBoxMoving(const CharacterAttr* character, 
	int *count, BoundingBox *boundingBox) {
	*count = 1;
	u16 x = CONVERT_TO_BOUNDINGBOX_X(character->position.x, mouthDemon_boundingBoxMeasurements);
	u16 y = CONVERT_TO_BOUNDINGBOX_Y(character->position.y, mouthDemon_boundingBoxMeasurements);
	u16 z = commonConvertBoundingBoxZ(character->position.z);
	boundingBox->startX = x;
	boundingBox->startY = y;
	boundingBox->endX = x + mouthDemon_boundingBoxMeasurements[EBBCnvrtLength];
	boundingBox->endY = y + mouthDemon_boundingBoxMeasurements[EBBCnvrtWidth];
	boundingBox->startZ = z;
	boundingBox->endZ = z + MOUTHDEMON_HEIGHT;
}

void mouthDemon_checkCollision(CharacterAttr* character, bool isOtherCharBelow,
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

void mouthDemon_checkMapCollision(CharacterAttr* character, const MapInfo* mapInfo) {
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

bool mouthDemon_isHit(CharacterAttr *character, CharacterActionEvent *actionEvent) {
	CharacterAIControl *charControl = (CharacterAIControl*)character->free;
	//return false;
	if (character->stats.currentStatus == EStatusNoActionCollision) {
		return false;
	}
	//EDirections sourceDirection;
	//common_faceTarget(&character->position, &actionEvent->source->position, 
	//	&sourceDirection);
	EDirections charDirection = character->faceDirection;
	
	charControl->countAction = 1;
	charControl->currentAction = 0;
	
	int stunTime;
	//if (sourceDirection != charDirection) {
	stunTime = 40;
	character->controller = &mouthDemon_floatController;
	//charControl->actions[charControl->currentAction] = ((ActionControl){stunTime, 0, character->direction, character->faceDirection, EGhoulHurt});
	character->nextAction = EMouthDemonFloat;
		
	character->stats.currentLife -= actionEvent->value;
	//character->stats.currentStatus = EStatusNoActionCollision;
	//charControl->currentStatus = EGhoulAIStateStunned;
	//add hit animation

	return true;
}
