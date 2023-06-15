#include <stdlib.h>
#include <stdbool.h>
#include "GBATypes.h"
#include "GBAObject.h"
#include "GBAVideo.h"
#include "GBADMA.h"
#include "GBACharacterActionEvent.h"
#include "UtilCommonValues.h"
#include "SpriteSetWerewolf.h"
#include "ManagerVram.h"
#include "CharacterWerewolf.h"

#include "CharacterCommon.h"

#include "ManagerPrinter.h"

extern const EDirections directions[EDirectionsCount];

extern const unsigned short werewolfupperbody_run_down_pal[16];

#define WEREWOLF_LENGTH 16
#define WEREWOLF_WIDTH 16
#define WEREWOLF_HEIGHT 32

#define WEREWOLF_SCRCNVRTWIDTH 16
#define WEREWOLF_SCRCNVRTHEIGHT 30

#define WEREWOLF_SCREENDISPLAYOFFSET_X 10
#define WEREWOLF_SCREENDISPLAYOFFSET_Y 28

#define WEREWOLF_PAL_CNT 1

#define werewolf_RUN_MVMNT_CTRL_MAX 8

const u8 werewolf_scrConversionMeasurements[EScrCnvrtMeasureCount] = {
	WEREWOLF_SCRCNVRTWIDTH,
	WEREWOLF_SCRCNVRTHEIGHT
};

const u8 werewolf_boundingBoxMeasurements[EBBCnvrtMeasurementCount] = {
	WEREWOLF_LENGTH,
	WEREWOLF_WIDTH,
	WEREWOLF_HEIGHT,
};

const s32 werewolf_runOffsetX[EDirectionsCount][werewolf_RUN_MVMNT_CTRL_MAX] = {
    {0,0,0,0,0},
	{1*MOVE_DIAG,2*MOVE_DIAG,1*MOVE_DIAG,2*MOVE_DIAG,1*MOVE_DIAG},
	{1*MOVE_STR,2*MOVE_STR,1*MOVE_STR,2*MOVE_STR,1*MOVE_STR},
	{1*MOVE_DIAG,2*MOVE_DIAG,1*MOVE_DIAG,2*MOVE_DIAG,1*MOVE_DIAG},
	{0,0,0,0,0},
	{-1*MOVE_DIAG,-2*MOVE_DIAG,-1*MOVE_DIAG,-2*MOVE_DIAG,-1*MOVE_DIAG},
	{-1*MOVE_STR,-2*MOVE_STR,-1*MOVE_STR,-2*MOVE_STR,-1*MOVE_STR},
	{-1*MOVE_DIAG,-2*MOVE_DIAG,-1*MOVE_DIAG,-2*MOVE_DIAG,-1*MOVE_DIAG}
};

const s32 werewolf_runOffsetY[EDirectionsCount][werewolf_RUN_MVMNT_CTRL_MAX] = {
    {1*MOVE_STR,2*MOVE_STR,1*MOVE_STR,2*MOVE_STR,1*MOVE_STR},
	{1*MOVE_DIAG,2*MOVE_DIAG,1*MOVE_DIAG,2*MOVE_DIAG,1*MOVE_DIAG},
	{0,0,0,0,0},
	{-1*MOVE_DIAG,-2*MOVE_DIAG,-1*MOVE_DIAG,-2*MOVE_DIAG,-1*MOVE_DIAG},
	{-1*MOVE_STR,-2*MOVE_STR,-1*MOVE_STR,-2*MOVE_STR,-1*MOVE_STR},
	{-1*MOVE_DIAG,-2*MOVE_DIAG,-1*MOVE_DIAG,-2*MOVE_DIAG,-1*MOVE_DIAG},
	{0,0,0,0,0},
	{1*MOVE_DIAG,2*MOVE_DIAG,1*MOVE_DIAG,2*MOVE_DIAG,1*MOVE_DIAG}
};

const CharFuncCollisionReaction werewolf_collisionReactions[][8] = {
    {	&common_noMovement,
		&common_noMovement,
		&common_noMovement,
		&common_noMovement,
		&common_noMovement,
		&common_noMovement,
		&common_noMovement,
		&common_noMovement },
	{	&common_movingDownOffset,
		&common_movingRightDownOffset,
		&common_movingRightOffset,
		&common_movingRightUpOffset,
		&common_movingUpOffset,
		&common_movingLeftUpOffset,
		&common_movingLeftOffset,
		&common_movingLeftDownOffset}
};

const CharFuncCollisionReaction werewolf_mapCollisionReactions[8] = {
	&common_mapMovingDownOffset,
	&common_mapMovingRightDownOffset,
	&common_mapMovingRightOffset,
	&common_mapMovingRightUpOffset,
	&common_mapMovingUpOffset,
	&common_mapMovingLeftUpOffset,
	&common_mapMovingLeftOffset,
	&common_mapMovingLeftDownOffset
};


const CommonMapCollision werewolf_mapCollision[] = {
    &commonMovingDownMapCollision,
	&commonMovingRightDownMapCollision,
	&commonMovingRightMapCollision,
	&commonMovingRightUpMapCollision,
	&commonMovingUpMapCollision,
	&commonMovingLeftUpMapCollision,
	&commonMovingLeftMapCollision,
	&commonMovingLeftDownMapCollision
};

const OffsetPoints werewolf_scanSurroundingOffset[8][2] = {
    {{-24,0},{24,64}},
	{{-24,0},{24,64}},
	{{0,-24},{64,24}},
	{{-24,-64},{24,0}},
	{{-24,-64},{24,0}},
	{{-24,-64},{24,0}},
	{{-64,-24},{0,24}},
	{{-24,0},{24,64}}
};

void werewolf_scanSurroundingsController(CharacterAttr* character);
void werewolf_actionWalk(CharacterAttr* character, const MapInfo *mapInfo, 
    const CharacterCollection *characterCollection);
void werewolf_actionFindTarget(CharacterAttr* character, const MapInfo *mapInfo, 
    const CharacterCollection *characterCollection);
void werewolf_getBounds(const CharacterAttr* character, int *count, CharBoundingBox *boundingBox);
int werewolf_setPosition(CharacterAttr* character, OBJ_ATTR *oamBuf, 
    const Position *scr_pos, const ScreenDimension *scr_dim);

void werewolf_getBoundingBoxStanding(const CharacterAttr* character, 
	int *count, BoundingBox *boundingBox);
void werewolf_getBoundingBoxMoving(const CharacterAttr* character, 
	int *count, BoundingBox *boundingBox);

void werewolf_checkMapCollision(CharacterAttr* character, const MapInfo* mapInfo);
	
void werewolf_checkCollision(const CharacterAttr* character, bool isOtherCharBelow,
	bool *checkNext, const CharacterAttr* otherCharacter);

void werewolf_checkActionEventCollision(CharacterAttr *alisa, CharacterActionCollection *actionEvents);

CharFuncAction werewolf_actions[] = {
	NULL,
	&werewolf_actionWalk,
	&werewolf_actionFindTarget
};

void werewolf_doAction(CharacterAttr* character, const MapInfo *mapInfo, 
    const CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection);

void werewolf_init(CharacterAttr* character, ControlTypePool* controlPool) {

//use library to get id
	character->id = 0;
	//use enum of character type
	character->type = WEREWOLF;
	
	//set to 0
	commonCharacterInit(character, EWerewolfInitialize, EWerewolfWalk, EDown);
	commonCharacterSetPosition(character, 0, 0, 1, EDown);
	character->controller = &werewolf_scanSurroundingsController;
	character->doAction = &werewolf_doAction;
	character->setPosition = &werewolf_setPosition;
	//character->getBounds = &werewolf_getBounds;
	character->getBounds = &werewolf_getBoundingBoxStanding;
	character->checkCollision = &werewolf_checkCollision;
	character->checkMapCollision = &werewolf_checkMapCollision;
	character->checkActionCollision = &werewolf_checkActionEventCollision;
		
	character->spriteDisplay.baseImageId = sprite_vram_findIdByType(ECharSizeSmall);
	character->spriteDisplay.imageUpdateStatus = EUpdate;
	character->spriteDisplay.basePalleteId = sprite_palette_findId(WEREWOLF, WEREWOLF_PAL_CNT);
	sprite_palette_copy32_ID(werewolfupperbody_run_down_pal, character->spriteDisplay.basePalleteId);
	character->spriteDisplay.palleteUpdateStatus = EUpdate;
	CharacterAIControl *charControl = mchar_getControlType(controlPool);
	charControl->type = EControlAiType;
	charControl->countAction = 0;
	charControl->currentAction = MAXACTIONS;
	charControl->rightBlocked = false;
	charControl->leftBlocked = false;
	charControl->upBlocked = false;
	charControl->downBlocked = false;
	character->free = charControl;
	character->stats.maxLife = 10;
	character->stats.currentLife = 5;
}

void werewolf_doAction(CharacterAttr* character,
	const MapInfo *mapInfo, const CharacterCollection *characterCollection,
	CharacterActionCollection *charActionCollection) {
	
	int boundBoxCount = 0;
	CharBoundingBox boundingBox;
	
	if (character->nextAction < EWerewolfActionCount) {
		werewolf_actions[character->nextAction](character, mapInfo, 
		    characterCollection, charActionCollection);
	}
	
	//TODO Check BG collision here
	//character->getBounds(character, &boundBoxCount, &boundingBox);
	//mapInfo->collisionCheck(mapInfo, &boundingBox, character->direction);
}

void werewolf_actionWalk(CharacterAttr* character,
	const MapInfo *mapInfo, const CharacterCollection *characterCollection) {
	bool isLastFrame = false;
	Position *position = &character->position;
	CharacterAIControl *charControl = (CharacterAIControl*)character->free;
	BoundingBox boundingBox;
	
	character->spriteDisplay.imageUpdateStatus = ENoUpdate;
	character->spriteDisplay.palleteUpdateStatus = ENoUpdate;
	if (commonUpdateAnimation(character) == EUpdate) {
		character->spriteDisplay.imageUpdateStatus = EUpdate;
		character->spriteDisplay.palleteUpdateStatus = EUpdate;
	}
	
	if (character->action != character->nextAction) {
	    character->movementCtrl.maxFrames = werewolf_RUN_MVMNT_CTRL_MAX;
		character->movementCtrl.currentFrame = 0;
	}
	
	character->action = character->nextAction;
	character->direction = character->nextDirection;
	
	if (character->movementCtrl.currentFrame >= character->movementCtrl.maxFrames) {
	    character->movementCtrl.currentFrame = 0;
	}
	
	character->delta.x = werewolf_runOffsetX[character->direction][character->movementCtrl.currentFrame];
	character->position.x += character->delta.x;
	
	character->delta.y = werewolf_runOffsetY[character->direction][character->movementCtrl.currentFrame];
	character->position.y += character->delta.y;
	
	commonGravityEffect(character, common_zOffsetDown);
	
	++character->movementCtrl.currentFrame;
	character->spriteDisplay.spriteSet = werewolfRun[character->direction];
	
	boundingBox.startX = position->x + werewolf_scanSurroundingOffset[character->direction][0].x;
	boundingBox.startY = position->y + werewolf_scanSurroundingOffset[character->direction][0].y;
	boundingBox.endX = position->x + werewolf_scanSurroundingOffset[character->direction][1].x;
	boundingBox.endY = position->y + werewolf_scanSurroundingOffset[character->direction][1].y;
	
	charControl->target = *commonFindCharTypeInBoundingBox(characterCollection, &boundingBox, 
		STARTPLAYABLECHARTYPE, ENDPLAYABLECHARACTERTYPE);
		
	if (commonIsFoundPosition(&charControl->target)) {
		charControl->currentStatus = EWerewolfStatusHuntTarget;
	}
}

void werewolf_actionFindTarget(CharacterAttr* character,
	const MapInfo *mapInfo, const CharacterCollection *characterCollection) {
	bool isLastFrame = false;
	int i;
	CharacterAIControl *charControl = (CharacterAIControl*)character->free;
	Position *position = &character->position;
	BoundingBox boundingBox;
	
	//character->position.z = CONVERT_2MOVE(1);
	
	boundingBox.startX = position->x + werewolf_scanSurroundingOffset[character->direction][0].x;
	boundingBox.startY = position->y + werewolf_scanSurroundingOffset[character->direction][0].y;
	boundingBox.endX = position->x + werewolf_scanSurroundingOffset[character->direction][1].x;
	boundingBox.endY = position->y + werewolf_scanSurroundingOffset[character->direction][1].y;
	
	charControl->target = *commonFindCharTypeInBoundingBox(characterCollection, &boundingBox, 
		STARTPLAYABLECHARTYPE, ENDPLAYABLECHARACTERTYPE);
	
	if (commonIsFoundPosition(&charControl->target)) {
		charControl->currentStatus = EWerewolfStatusHuntTarget;
	}
	
	//charControl->target = NULL;
	character->spriteDisplay.imageUpdateStatus = ENoUpdate;
	character->spriteDisplay.palleteUpdateStatus = ENoUpdate;
	
	character->delta.x = 0;
	character->delta.y = 0;
	if (commonUpdateAnimation(character) == EUpdate) {
		character->spriteDisplay.imageUpdateStatus = EUpdate;
		character->spriteDisplay.palleteUpdateStatus = EUpdate;
	}
	
	commonGravityEffect(character, common_zOffsetDown);
	
	character->action = character->nextAction;
	character->direction = character->nextDirection;
		
	character->spriteDisplay.spriteSet = werewolfStand[character->direction];
}

int werewolf_setPosition(CharacterAttr* character,
	OBJ_ATTR *oamBuf, 
	const Position *scr_pos,
	const ScreenDimension *scr_dim) 
{

	int charStartX, charStartY, charEndX, charEndY;
	int numberOfShadow = 0;
	character->spriteDisplay.baseY = CONVERT_TO_SCRYPOS(character->position.y, 
		scr_pos->y, werewolf_scrConversionMeasurements);
	character->spriteDisplay.baseX = CONVERT_TO_SCRXPOS(character->position.x, 
		scr_pos->x, werewolf_scrConversionMeasurements);
	character->spriteDisplay.baseY -= CONVERT_TO_SCRZPOS(character->position.z);
	
	charStartX = CONVERT_2POS(character->position.x) - WEREWOLF_SCREENDISPLAYOFFSET_X;
	charStartY = CONVERT_2POS(character->position.y);
	charEndX = CONVERT_2POS(character->position.x) + WEREWOLF_SCREENDISPLAYOFFSET_X;
	charEndY = CONVERT_2POS(character->position.y) - WEREWOLF_SCREENDISPLAYOFFSET_Y;
	
	if (commonIsInScreen(charStartX, charEndX, charStartY, charEndY, scr_pos, scr_dim)) {
		character->spriteDisplay.imageUpdateStatus = ((!character->spriteDisplay.isInScreen)*EUpdate) + 
		    (character->spriteDisplay.isInScreen*character->spriteDisplay.imageUpdateStatus);
		character->spriteDisplay.isInScreen = true;
		commonSetToOamBuffer(&character->spriteDisplay, oamBuf);
		
		numberOfShadow = commonSetShadow(character->spriteDisplay.baseX, 
			character->spriteDisplay.baseY + character->distanceFromGround + WEREWOLF_SCRCNVRTHEIGHT,
			&oamBuf[character->spriteDisplay.spriteSet->set[character->spriteDisplay.currentAnimationFrame].numberOflayers]);
			
		return character->spriteDisplay.spriteSet->set[character->spriteDisplay.currentAnimationFrame].numberOflayers + numberOfShadow;
	}
	
	character->spriteDisplay.isInScreen = false;
	return 0;
}

void werewolf_getBoundingBoxMoving(const CharacterAttr* character, 
	int *count, BoundingBox *boundingBox) {
	*count = 1;

	u16 x = CONVERT_TO_BOUNDINGBOX_X(character->position.x, werewolf_boundingBoxMeasurements);
	u16 y = CONVERT_TO_BOUNDINGBOX_Y(character->position.y, werewolf_boundingBoxMeasurements);
	s16 z = commonConvertBoundingBoxZ(character->position.z);
	boundingBox->startX = x;
	boundingBox->startY = y;
	boundingBox->endX = x + werewolf_boundingBoxMeasurements[EBBCnvrtLength];
	boundingBox->endY = y + werewolf_boundingBoxMeasurements[EBBCnvrtWidth];
	boundingBox->startZ = z;
	boundingBox->endZ = z + WEREWOLF_HEIGHT;
	//boundingBox->height = werewolf_boundingBoxMeasurements[EBBCnvrtHeight];
	boundingBox->direction = character->direction;
	boundingBox->isMoving = true;
	boundingBox->isMovable = false;
}

void werewolf_getBoundingBoxStanding(const CharacterAttr* character, 
	int *count, BoundingBox *boundingBox) {
	*count = 1;
	u16 x = CONVERT_TO_BOUNDINGBOX_X(character->position.x, werewolf_boundingBoxMeasurements);
	u16 y = CONVERT_TO_BOUNDINGBOX_Y(character->position.y, werewolf_boundingBoxMeasurements);
	s16 z = commonConvertBoundingBoxZ(character->position.z);
	boundingBox->startX = x;
	boundingBox->startY = y;
	boundingBox->endX = x + werewolf_boundingBoxMeasurements[EBBCnvrtLength];
	boundingBox->endY = y + werewolf_boundingBoxMeasurements[EBBCnvrtWidth];
	//boundingBox->height = werewolf_boundingBoxMeasurements[EBBCnvrtHeight];
	boundingBox->startZ = z;
	boundingBox->endZ = z + WEREWOLF_HEIGHT;
	boundingBox->direction = character->direction;
	boundingBox->isMoving = false;
	boundingBox->isMovable = false;
}

void werewolf_checkMapCollision(CharacterAttr* character, const MapInfo* mapInfo) {
	int count;
	BoundingBox mapBoundingBox, characterBoundingBox;
	CharacterPlayerControl *charControl = (CharacterAIControl*)character->free;
	int fallingDown;

	character->getBounds(character, &count, &characterBoundingBox);
	commonGetBoundsFromMap(CONVERT_2POS(character->position.x), CONVERT_2POS(character->position.y), mapInfo, &mapBoundingBox);
	fallingDown = common_fallingDown(character, &characterBoundingBox, &mapBoundingBox);
	
	character->distanceFromGround = fallingDown;
	
	if (fallingDown > 0) {
		commonFallingDownCollision(character, mapInfo);
	} 
	
    commonCharacterMapEdgeCheck(character, mapInfo);
	werewolf_mapCollision[character->direction](character, mapInfo, 
	    werewolf_mapCollisionReactions[character->direction]);
}

void werewolf_checkCollision(const CharacterAttr* character, bool isOtherCharBelow,
	bool *checkNext, const CharacterAttr* otherCharacter) {
	
	int count;
	BoundingBox charBoundingBox, otherCharBoundingBox;
	 
	*checkNext = common_checkNext(isOtherCharBelow, &character->position, &otherCharacter->position);
	if (!*checkNext) {
		return;
	}
	
	character->getBounds(character, &count, &charBoundingBox);
	otherCharacter->getBounds(otherCharacter, &count, &otherCharBoundingBox);
	
	werewolf_collisionReactions[charBoundingBox.isMoving][character->direction]
	    (character, &charBoundingBox, &otherCharBoundingBox);
}

void werewolf_checkActionEventCollision(CharacterAttr *character, CharacterActionCollection *actionEvents) {
    int i, j, count;
	bool isHit;
	BoundingBox charBoundingBox;
	character->getBounds(character, &count, &charBoundingBox);
	for (i = 0; i < actionEvents->count; ++i) {
		CharacterActionEvent *charActionEvent = &actionEvents->currentActions[i];

		//for (j = 0; j < charActionEvent->count; ++j) {
			//isHit |= commonCollissionPointInBounds(&charActionEvent->collisionPoints[j], &charBoundingBox);
			isHit |= hasCollision(&charActionEvent->collisionBox, &charBoundingBox);
		//}
		if (isHit) {
		    character->stats.currentLife -= 1;
			if (character->stats.currentLife <= 0) {
				commonRemoveCharacter(character);
			}
			break;
		}
	}
}

