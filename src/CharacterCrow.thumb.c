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
#include "CharacterCrow.h"
#include "SpriteSetCrow.h"
#include "CharacterCommon.h"
#include "MapCommon.h"

#define CROW_SCRCNVRTWIDTH 8
#define CROW_SCRCNVRTHEIGHT 12

#define CROW_LENGTH 8
#define CROW_WIDTH 16
#define CROW_HEIGHT 16

#define CROW_PAL_CNT 1

#define CROW_ON_CAW 255

extern const EDirections directions[EDirectionsCount];

const u8 crow_scrConversionMeasurements[EScrCnvrtMeasureCount] = {
	CROW_SCRCNVRTWIDTH,
	CROW_SCRCNVRTHEIGHT
};

const u8 crow_boundingBoxMeasurements[EBBCnvrtMeasurementCount] = {
	CROW_LENGTH,
	CROW_WIDTH,
	CROW_HEIGHT,
};

CharFuncAction crow_actions[] = {
	&crow_actionStand
};

void crow_init(CharacterAttr* crow, ControlTypePool* controlPool) {
//use library to get id
	crow->id = 0;
	//use enum of character type
	crow->type = CROW;
	
	crow->spriteDisplay.baseImageId = sprite_vram_findIdByType(ECharSizeSmall);
	crow->spriteDisplay.imageUpdateStatus = EUpdate;
	crow->spriteDisplay.basePalleteId = sprite_palette_findId(CROW, CROW_PAL_CNT);
	
	sprite_palette_copy32_ID(crow_pal, crow->spriteDisplay.basePalleteId);
//	sprite_palette_copy32_ID(sword_side_pal, alisa->spriteDisplay.basePalleteId + 1);
		
	commonCharacterInit(crow, ECrowInitialize, ECrowStand, EDown);
	commonCharacterSetPosition(crow, 0, 0, 0, EDown);
	crow->controller = &crow_controller;
	crow->doAction = &crow_doAction;
	crow->setPosition = &crow_setPosition;
	crow->getBounds = &crow_getBoundingBox;
	crow->checkCollision = &crow_checkCollision;
	crow->checkMapCollision = &crow_checkMapCollision;
	crow->free = mchar_getControlType(controlPool);
	
	crow->movementCtrl.maxFrames = CROW_ON_CAW;
	crow->movementCtrl.currentFrame = 0;
}

void crow_doAction(CharacterAttr* crow,
	const MapInfo *mapInfo, const void *dummy, 
	CharacterActionCollection *charActionCollection) {
	int boundBoxCount = 0;
	CharBoundingBox boundingBox;
	
	if (crow->nextAction < ECrowActionCount) {
		crow_actions[crow->nextAction](crow, mapInfo, dummy, charActionCollection);
	}
	
	//TODO Check BG collision here
	crow->getBounds(crow, &boundBoxCount, &boundingBox);
	//mapInfo->collisionCheck(mapInfo, &boundingBox, character->direction);
}
	
void crow_actionStand(CharacterAttr* crow,
	const MapInfo *mapInfo, const void *dummy) {
	bool isLastFrame = false;
	CharacterAIControl *charControl = (CharacterAIControl*)crow->free;
	crow->spriteDisplay.imageUpdateStatus = ENoUpdate;
	crow->spriteDisplay.palleteUpdateStatus = ENoUpdate;
	if (commonUpdateAnimation(crow) == EUpdate) {
		crow->spriteDisplay.imageUpdateStatus = EUpdate;
		crow->spriteDisplay.palleteUpdateStatus = EUpdate;
	}
	
	crow->action = crow->nextAction;
	crow->direction = crow->nextDirection;
	
	++crow->movementCtrl.currentFrame;
	if (crow->movementCtrl.currentFrame >= crow->movementCtrl.maxFrames) {
		int distance = charControl->target.x - crow->position.x, rightPhaseDelay, leftPhaseDelay;
		crow->movementCtrl.currentFrame = 0;
		distance = distance >> 4;
		rightPhaseDelay = 6*(distance < 0);
		leftPhaseDelay = 6*(distance > 0);
		distance *= (distance < 0)*(-1) + (distance >= 0)*1;
	    msound_setChannel3d(&soundeffect_crow, false, rightPhaseDelay, leftPhaseDelay, distance);
	}
	
	crow->spriteDisplay.spriteSet = &crow_standing;
}

int crow_setPosition(CharacterAttr* crow,
	OBJ_ATTR *oamBuf, 
	const Position *scr_pos,
	const ScreenDimension *scr_dim) 
{
	crow->spriteDisplay.baseY = CONVERT_TO_SCRYPOS(crow->position.y, 
		scr_pos->y, crow_scrConversionMeasurements);
	crow->spriteDisplay.baseX = CONVERT_TO_SCRXPOS(crow->position.x, 
		scr_pos->x, crow_scrConversionMeasurements);
	
	//TODO add in screen check
	commonSetToOamBuffer(&crow->spriteDisplay, oamBuf);
	crow->spriteDisplay.isInScreen = true;
	
    return crow->spriteDisplay.spriteSet->set[crow->spriteDisplay.currentAnimationFrame].numberOflayers;
}

void crow_getBoundingBox(const CharacterAttr* character, 
	int *count, BoundingBox *boundingBox) {
	*count = 1;
	u16 x = CONVERT_TO_BOUNDINGBOX_X(character->position.x, crow_boundingBoxMeasurements);
	u16 y = CONVERT_TO_BOUNDINGBOX_Y(character->position.y, crow_boundingBoxMeasurements);
	boundingBox->startX = x;
	boundingBox->startY = y;
	boundingBox->endX = x + crow_boundingBoxMeasurements[EBBCnvrtLength];
	boundingBox->endY = y + crow_boundingBoxMeasurements[EBBCnvrtWidth];
	//boundingBox->height = werewolf_boundingBoxMeasurements[EBBCnvrtHeight];
}

void crow_checkMapCollision(CharacterAttr* character, const MapInfo* mapInfo) {
    int x = 1 + 1;
}

void crow_checkCollision(const CharacterAttr* character, bool isOtherCharBelow,
	bool *checkNext, const CharacterAttr* otherCharacter) {
}
