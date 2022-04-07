#include <stdlib.h>
#include <stdbool.h>
#include "GBATypes.h"
#include "GBAObject.h"
#include "GBAVideo.h"
#include "GBADMA.h"
#include "GBACharacterActionEvent.h"
#include "UtilCommonValues.h"
#include "SpriteSetZombie.h"
#include "ManagerVram.h"
#include "CharacterZombie.h"
#include "ImageZombie.h"
#include "CharacterCommon.h"
#include "ManagerPrinter.h"

extern const EDirections directions[EDirectionsCount];

#define ZOMBIE_LENGTH 16
#define ZOMBIE_WIDTH 16
#define ZOMBIE_HEIGHT 24

#define ZOMBIE_SCRCNVRTWIDTH 16
#define ZOMBIE_SCRCNVRTHEIGHT 26

#define ZOMBIE_SCREENDISPLAYOFFSET_X 10
#define ZOMBIE_SCREENDISPLAYOFFSET_Y 28

#define ZOMBIE_PAL_CNT 1

#define zombie_WALK_MVMNT_CTRL_MAX 5

#define MAX_DIST_FOR_CHASE 80
const u8 zombie_scrConversionMeasurements[EScrCnvrtMeasureCount] = {
	ZOMBIE_SCRCNVRTWIDTH,
	ZOMBIE_SCRCNVRTHEIGHT
};

const u8 zombie_boundingBoxMeasurements[EBBCnvrtMeasurementCount] = {
	ZOMBIE_LENGTH,
	ZOMBIE_WIDTH,
	ZOMBIE_HEIGHT,
};

const s32 zombie_walkOffsetX[EDirectionsCount][zombie_WALK_MVMNT_CTRL_MAX] = {
    {0,0,0,0,0},
	{1,0,0,0,1},
	{1,0,1,0,1},
	{1,0,0,0,1},
	{0,0,0,0,0},
	{-1,0,0,0,-1},
	{-1,0,-1,0,-1},
	{-1,0,0,0,-1}
};

const s32 zombie_walkOffsetY[EDirectionsCount][zombie_WALK_MVMNT_CTRL_MAX] = {
    {1,0,1,0,1},
	{1,0,0,0,1},
	{0,0,0,0,0},
	{-1,0,0,0,-1},
	{-1,0,-1,0,-1},
	{-1,0,0,0,-1},
	{0,0,0,0,0},
	{1,0,0,0,1}
};

const OffsetPoints zombie_scanSurroundingOffset[8][2] = {
    {{-24,0},{24,64}},
	{{-24,0},{24,64}},
	{{0,-24},{64,24}},
	{{-24,-64},{24,0}},
	{{-24,-64},{24,0}},
	{{-24,-64},{24,0}},
	{{-64,-24},{0,24}},
	{{-24,0},{24,64}}
};

const OffsetPoints zombie_scanLastKnownPosition = { 16, 16 };

void zombie_actionWalk(CharacterAttr* character,
	const MapInfo *mapInfo, const CharacterCollection *characterCollection);
void zombie_actionChaseTarget(CharacterAttr* character,
	const MapInfo *mapInfo, const CharacterCollection *characterCollection);
void zombie_actionAttack(CharacterAttr* character,
	const MapInfo *mapInfo, const CharacterCollection *characterCollection);
void zombie_actionStunned(CharacterAttr* character,
	const MapInfo *mapInfo, const CharacterCollection *characterCollection);
	
CharFuncAction zombie_actions[] = {
	&zombie_actionWalk,
	&zombie_actionChaseTarget,
	&zombie_actionAttack,
	&zombie_actionStunned
};


void zombie_walkAroundController(CharacterAttr* character);
void zombie_doAction(CharacterAttr* character, const MapInfo *mapInfo, 
    const CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection);
void zombie_getBoundingBoxMoving(const CharacterAttr* character, int *count, BoundingBox *boundingBox);
void zombie_getBoundingBoxStanding(const CharacterAttr* character, int *count, BoundingBox *boundingBox);
int zombie_setPosition(CharacterAttr* character, OBJ_ATTR *oamBuf, 
	const Position *scr_pos, const ScreenDimension *scr_dim);
void zombie_checkMapCollision(CharacterAttr* character, const MapInfo* mapInfo);
void zombie_checkCollision(const CharacterAttr* character, bool isOtherCharBelow,
	bool *checkNext, const CharacterAttr* otherCharacter);
void zombie_checkActionEventCollision(CharacterAttr *character, CharacterActionCollection *actionEvents);
	
void zombie_init(CharacterAttr* character, ControlTypePool* controlPool) {

//use library to get id
	character->id = 0;
	//use enum of character type
	character->type = ZOMBIE;
	
	//set to 0
	commonCharacterInit(character, EZombieInitialize, EZombieWalk, EDown);
	commonCharacterSetPosition(character, 0, 0, 0, EDown);
	character->controller = &zombie_walkAroundController;
	character->doAction = &zombie_doAction;
	character->setPosition = &zombie_setPosition;
	character->getBounds = &zombie_getBoundingBoxMoving;
	character->checkCollision = &zombie_checkCollision;
	character->checkMapCollision = &zombie_checkMapCollision;
	character->checkActionCollision = &zombie_checkActionEventCollision;
		
	character->spriteDisplay.baseImageId = sprite_vram_findId();
	character->spriteDisplay.imageUpdateStatus = EUpdate;
	character->spriteDisplay.basePalleteId = sprite_palette_findId(ZOMBIE, ZOMBIE_PAL_CNT);
	sprite_palette_copy32_ID(zombie_walk_up_pal, character->spriteDisplay.basePalleteId);
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
	character->stats.currentLife = 3;
	character->stats.currentStatus = EStatusNormal;
}

void zombie_doAction(CharacterAttr* character,
	const MapInfo *mapInfo, const CharacterCollection *characterCollection,
	CharacterActionCollection *charActionCollection) {
	
	int boundBoxCount = 0;
	CharBoundingBox boundingBox;
	
	if (character->nextAction < EZombieActionCount) {
		zombie_actions[character->nextAction](character, mapInfo, 
		    characterCollection, charActionCollection);
	}
}

void zombie_actionWalk(CharacterAttr* character,
	const MapInfo *mapInfo, const CharacterCollection *characterCollection) {
	bool isLastFrame = false;
	int nextScreenFrame, nextAnimationFrame;
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
	    character->movementCtrl.maxFrames = zombie_WALK_MVMNT_CTRL_MAX;
		character->movementCtrl.currentFrame = 0;
	}
	
	character->action = character->nextAction;
	character->direction = character->nextDirection;
	
	if (character->movementCtrl.currentFrame >= character->movementCtrl.maxFrames) {
	    character->movementCtrl.currentFrame = 0;
	}
	
	//commonGetNextFrame(character, &nextScreenFrame, &nextAnimationFrame, &isLastFrame);
	//mprinter_printf("nextAnimationFrame %d\n", nextAnimationFrame);
	if (commonGetCurrentAnimationFrame(character) == 0 || commonGetCurrentAnimationFrame(character) == 2) {
		character->delta.x = zombie_walkOffsetX[character->direction][character->movementCtrl.currentFrame];
		character->position.x += character->delta.x;
		
		character->delta.y = zombie_walkOffsetY[character->direction][character->movementCtrl.currentFrame];
		character->position.y += character->delta.y;
	} else {
		character->delta.x = 0;
		character->delta.y = 0;
	}
	
	++character->movementCtrl.currentFrame;
	character->spriteDisplay.spriteSet = zombieWalk[character->direction];
	
	boundingBox.startX = position->x + zombie_scanSurroundingOffset[character->direction][0].x;
	boundingBox.startY = position->y + zombie_scanSurroundingOffset[character->direction][0].y;
	boundingBox.endX = position->x + zombie_scanSurroundingOffset[character->direction][1].x;
	boundingBox.endY = position->y + zombie_scanSurroundingOffset[character->direction][1].y;
	
	charControl->target = *commonFindCharTypeInBoundingBox(characterCollection, &boundingBox, 
		STARTPLAYABLECHARTYPE, ENDPLAYABLECHARACTERTYPE);
		
	if (commonIsFoundPosition(&charControl->target)) {
		//mprinter_printf("FOUND TARGET");
		charControl->currentStatus = EZombieStatusHuntTarget;
	}
}

void zombie_actionChaseTarget(CharacterAttr* character,
	const MapInfo *mapInfo, const CharacterCollection *characterCollection) {
	bool isLastFrame = false;
	int nextScreenFrame, nextAnimationFrame, xDist, yDist;
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
	    character->movementCtrl.maxFrames = zombie_WALK_MVMNT_CTRL_MAX;
		character->movementCtrl.currentFrame = 0;
	}
	
	character->action = character->nextAction;
	character->direction = character->nextDirection;
	
	if (character->movementCtrl.currentFrame >= character->movementCtrl.maxFrames) {
	    character->movementCtrl.currentFrame = 0;
	}
	
	if (commonGetCurrentAnimationFrame(character) == 0 || commonGetCurrentAnimationFrame(character) == 2) {
		character->delta.x = zombie_walkOffsetX[character->direction][character->movementCtrl.currentFrame];
		character->position.x += character->delta.x;
		
		character->delta.y = zombie_walkOffsetY[character->direction][character->movementCtrl.currentFrame];
		character->position.y += character->delta.y;
	} else {
		character->delta.x = 0;
		character->delta.y = 0;
	}
	
	++character->movementCtrl.currentFrame;
	character->spriteDisplay.spriteSet = zombieChase[character->direction];
	
	charControl->target = *commonFindCharTypePositionByDistance(characterCollection,
		&character->position, MAX_DIST_FOR_CHASE, STARTPLAYABLECHARTYPE, ENDPLAYABLECHARACTERTYPE);
	
	if (!commonIsFoundPosition(&charControl->target)) {
		charControl->currentStatus = EZombieStatusWalkAround;
	}
}

void zombie_actionAttack(CharacterAttr* character,
	const MapInfo *mapInfo, const CharacterCollection *characterCollection) {
	bool isLastFrame = false;
	int nextScreenFrame, nextAnimationFrame, xDist, yDist;
	Position *position = &character->position;
	CharacterAIControl *charControl = (CharacterAIControl*)character->free;
	BoundingBox boundingBox;
	
	character->spriteDisplay.imageUpdateStatus = ENoUpdate;
	character->spriteDisplay.palleteUpdateStatus = ENoUpdate;
	
	character->delta.x = 0;
	character->delta.y = 0;
	
	if (commonUpdateAnimation(character) == EUpdate) {
		character->spriteDisplay.imageUpdateStatus = EUpdate;
		character->spriteDisplay.palleteUpdateStatus = EUpdate;
	}
	
	character->action = character->nextAction;
	character->direction = character->nextDirection;
	
	character->spriteDisplay.spriteSet = zombieAttack[character->direction];
	
	commonGetNextFrame(character, &nextScreenFrame, &nextAnimationFrame, &isLastFrame);
	
	if (isLastFrame) {
		charControl->target = *commonFindCharTypePositionByDistance(characterCollection,
		&character->position, MAX_DIST_FOR_CHASE, STARTPLAYABLECHARTYPE, ENDPLAYABLECHARACTERTYPE);
	
		if (!commonIsFoundPosition(&charControl->target)) {
			charControl->currentStatus = EZombieStatusWalkAround;
		}
	}
}

void zombie_actionStunned(CharacterAttr* character,
	const MapInfo *mapInfo, const CharacterCollection *characterCollection) {
	bool isLastFrame = false;
	int nextScreenFrame, nextAnimationFrame, xDist, yDist;
	Position *position = &character->position;
	CharacterAIControl *charControl = (CharacterAIControl*)character->free;
	BoundingBox boundingBox;
	
	character->spriteDisplay.imageUpdateStatus = ENoUpdate;
	character->spriteDisplay.palleteUpdateStatus = ENoUpdate;
	
	character->delta.x = 0;
	character->delta.y = 0;
	
	if (commonUpdateAnimation(character) == EUpdate) {
		character->spriteDisplay.imageUpdateStatus = EUpdate;
		character->spriteDisplay.palleteUpdateStatus = EUpdate;
	}
	
	character->action = character->nextAction;
	character->direction = character->nextDirection;
	
	character->spriteDisplay.spriteSet = zombieStunned[character->direction];
}

void zombie_getBoundingBoxMoving(const CharacterAttr* character, 
	int *count, BoundingBox *boundingBox) {
	*count = 1;
	u16 x = CONVERT_TO_BOUNDINGBOX_X(character->position.x, zombie_boundingBoxMeasurements);
	u16 y = CONVERT_TO_BOUNDINGBOX_Y(character->position.y, zombie_boundingBoxMeasurements);
	boundingBox->startX = x;
	boundingBox->startY = y;
	boundingBox->endX = x + zombie_boundingBoxMeasurements[EBBCnvrtLength];
	boundingBox->endY = y + zombie_boundingBoxMeasurements[EBBCnvrtWidth];
	//boundingBox->height = werewolf_boundingBoxMeasurements[EBBCnvrtHeight];
	boundingBox->direction = character->direction;
	boundingBox->isMoving = true;
	boundingBox->isMovable = false;
}

void zombie_getBoundingBoxStanding(const CharacterAttr* character, 
	int *count, BoundingBox *boundingBox) {
	*count = 1;
	u16 x = CONVERT_TO_BOUNDINGBOX_X(character->position.x, zombie_boundingBoxMeasurements);
	u16 y = CONVERT_TO_BOUNDINGBOX_Y(character->position.y, zombie_boundingBoxMeasurements);
	boundingBox->startX = x;
	boundingBox->startY = y;
	boundingBox->endX = x + zombie_boundingBoxMeasurements[EBBCnvrtLength];
	boundingBox->endY = y + zombie_boundingBoxMeasurements[EBBCnvrtWidth];
	//boundingBox->height = werewolf_boundingBoxMeasurements[EBBCnvrtHeight];
	boundingBox->direction = character->direction;
	boundingBox->isMoving = false;
	boundingBox->isMovable = false;
}

int zombie_setPosition(CharacterAttr* character,
	OBJ_ATTR *oamBuf, 
	const Position *scr_pos,
	const ScreenDimension *scr_dim) 
{

	int charStartX, charStartY, charEndX, charEndY;
	
	character->spriteDisplay.baseY = CONVERT_TO_SCRYPOS(character->position.y, 
		scr_pos->y, zombie_scrConversionMeasurements);
	character->spriteDisplay.baseX = CONVERT_TO_SCRXPOS(character->position.x, 
		scr_pos->x, zombie_scrConversionMeasurements);
	
	charStartX = character->position.x - ZOMBIE_SCREENDISPLAYOFFSET_X;
	charStartY = character->position.y;
	charEndX = character->position.x + ZOMBIE_SCREENDISPLAYOFFSET_X;
	charEndY = character->position.y - ZOMBIE_SCREENDISPLAYOFFSET_Y;
	
	if (commonIsInScreen(charStartX, charEndX, charStartY, charEndY, scr_pos, scr_dim)) {
		character->spriteDisplay.imageUpdateStatus = ((!character->spriteDisplay.isInScreen)*EUpdate) + 
		    (character->spriteDisplay.isInScreen*character->spriteDisplay.imageUpdateStatus);
		character->spriteDisplay.isInScreen = true;
		commonSetToOamBuffer(&character->spriteDisplay, oamBuf);
		return character->spriteDisplay.spriteSet->set[character->spriteDisplay.currentAnimationFrame].numberOflayers;
	}
	
	character->spriteDisplay.isInScreen = false;
	return 0;
}

void zombie_checkMapCollision(CharacterAttr* character, const MapInfo* mapInfo) {
    commonCharacterMapEdgeCheck(character, mapInfo);
	common_mapCollision[character->direction](character, mapInfo, 
	    common_mapCollisionReactions[character->direction]);
}

void zombie_checkCollision(const CharacterAttr* character, bool isOtherCharBelow,
	bool *checkNext, const CharacterAttr* otherCharacter) {
	
	int count;
	BoundingBox charBoundingBox, otherCharBoundingBox;
	character->getBounds(character, &count, &charBoundingBox);
	otherCharacter->getBounds(otherCharacter, &count, &otherCharBoundingBox);
	 
	*checkNext = common_checkNext(isOtherCharBelow, &charBoundingBox, &otherCharBoundingBox);
	if (!*checkNext) {
		return;
	}
	common_collisionReactions[charBoundingBox.isMoving][character->direction]
	    (character, &charBoundingBox, &otherCharBoundingBox);
}

void zombie_checkActionEventCollision(CharacterAttr *character, CharacterActionCollection *actionEvents) {
    int i, j, count;
	bool isHit;
	BoundingBox charBoundingBox;
	CharacterAIControl *charControl = (CharacterAIControl*)character->free;
	
	if (character->stats.currentStatus == EStatusNoActionCollision) {
		return;
	}
	for (i = 0; i < actionEvents->count; ++i) {
		CharacterActionEvent *charActionEvent = &actionEvents->currentActions[i];

		character->getBounds(character, &count, &charBoundingBox);
		for (j = 0; j < charActionEvent->count; ++j) {
			isHit |= commonPositionInBounds(&charActionEvent->collisionPoints[j], &charBoundingBox);
		}
		if (isHit) {
			character->stats.currentLife -= 1;
			//character->stats.currentStatus = EStatusNoActionCollision;
			charControl->currentStatus = EZombieStatusStunned;
			if (character->stats.currentLife <= 0) {
				commonRemoveCharacter(character);
			}
			break;
		}
	}
}
