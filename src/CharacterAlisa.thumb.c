#include <stdlib.h>
#include <stdbool.h>
#include "GBATypes.h"
#include "GBAObject.h"
#include "GBAVideo.h"
#include "GBADMA.h"
#include "UtilCommonValues.h"
#include "SpriteSetAlisa.h"
#include "ManagerVram.h"
#include "ManagerSound.h"
#include "CharacterAlisa.h"
#include "CharacterCommon.h"
#include "MapCommon.h"

#define alisa_IMAGE_COUNT 1
#define alisa_PALETTE_COUNT 1

#define alisa_RUN_MVMNT_CTRL_MAX 5


#define SLASH_STARTSOUND_FRAME 3

extern const EDirections directions[EDirectionsCount];
extern const Sound soundeffect_slash;

const s32 alisa_runOffsetX[EDirectionsCount][alisa_RUN_MVMNT_CTRL_MAX] = {
    {0,0,0,0,0},
	{1,2,1,2,1},
	{2,2,2,2,2},
	{1,2,1,2,1},
	{0,0,0,0,0},
	{-1,-2,-1,-2,-1},
	{-2,-2,-2,-2,-2},
	{-1,-2,-1,-2,-1}
};

const s32 alisa_runOffsetY[EDirectionsCount][alisa_RUN_MVMNT_CTRL_MAX] = {
    {2,2,2,2,2},
	{1,2,1,2,1},
	{0,0,0,0,0},
	{-1,-2,-1,-2,-1},
	{-2,-2,-2,-2,-2},
	{-1,-2,-1,-2,-1},
	{0,0,0,0,0},
	{1,2,1,2,1}
};

#define ALISA_SCRCNVRTWIDTH 16
#define ALISA_SCRCNVRTHEIGHT 24

#define ALISA_LENGTH 12
#define ALISA_WIDTH 10
#define ALISA_HEIGHT 18

#define ALISA_PAL_CNT 2

const u8 alisa_scrConversionMeasurements[EScrCnvrtMeasureCount] = {
	ALISA_SCRCNVRTWIDTH,
	ALISA_SCRCNVRTHEIGHT
};

const u8 alisa_boundingBoxMeasurements[EBBCnvrtMeasurementCount] = {
	ALISA_LENGTH,
	ALISA_WIDTH,
	ALISA_HEIGHT,
};

extern const SpriteSet maincharacter_stand;
extern const SpriteSet maincharacter_walk;
extern const unsigned short alisa_standwithsword_side_pal[16];
extern const unsigned short sword_side_pal[16];

void alisa_controller(CharacterAttr* alisa);
void alisa_doAction(CharacterAttr *alisa, const MapInfo *mapInfo, const void *dummy);
void checkForEvents(CharacterAttr* alisa, MapInfo *mapInfo);
void alisa_actionStand(CharacterAttr* alisa, const MapInfo *mapInfo);
void alisa_actionRun(CharacterAttr* alisa, const MapInfo *mapInfo);
void alisa_actionSlash(CharacterAttr* alisa, const MapInfo *mapInfo);

int alisa_setPosition(CharacterAttr* alisa, 
	OBJ_ATTR *oamBuf, 	
	const Position *scrpos,
	const ScreenDimension *scrdim);

void alisa_draw(CharacterAttr* alisa);

void alisa_getBounds(const CharacterAttr* alisa, 
	int *count, CharBoundingBox *boundingBox);
	
void alisa_getBoundingBox(const CharacterAttr* alisa, 
	int *count, BoundingBox *boundingBox);

void alisa_checkMapCollision(CharacterAttr* alisa, const MapInfo *mapInfo);

void alisa_checkCollision(CharacterAttr* alisa, bool isOtherCharBelow,
	bool *checkNext, const CharacterAttr* otherCharacter);

void transferToBoundingBox(const EventTransfer *transfer, BoundingBox *boundingBox);



const CharFuncAction alisa_actions[] = {
	&alisa_actionStand,
	&alisa_actionRun,
	&alisa_actionSlash
};

CharFuncCollisionReaction alisa_collisionReactions[] = {
    &common_movingDown,
	&common_movingRightDownOffset,
	&common_movingRight,
	&common_movingRightUpOffset,
	&common_movingUp,
	&common_movingLeftUpOffset,
	&common_movingLeft,
	&common_movingLeftDownOffset
};

CommonMapCollision alisa_mapCollision[] = {
    &commonMovingDownMapCollision,
	&commonMovingRightDownMapCollision,
	&commonMovingRightMapCollision,
	&commonMovingRightUpMapCollision,
	&commonMovingUpMapCollision,
	&commonMovingLeftUpMapCollision,
	&commonMovingLeftMapCollision,
	&commonMovingLeftDownMapCollision
};

void alisa_init(CharacterAttr* alisa)
{	
	//use library to get id
	alisa->id = 0;
	//use enum of character type
	alisa->type = ALISA;
	
	alisa->spriteDisplay.baseImageId = sprite_vram_findId();
	alisa->spriteDisplay.imageUpdateStatus = EUpdate;
	alisa->spriteDisplay.basePalleteId = sprite_palette_findId(ALISA, ALISA_PAL_CNT);
	//if (1) {
	    sprite_palette_copy32_ID(alisa_standwithsword_side_pal, alisa->spriteDisplay.basePalleteId);
	    sprite_palette_copy32_ID(sword_side_pal, alisa->spriteDisplay.basePalleteId + 1);
	//}
	//alisa->spriteDisplay.palleteUpdateStatus = EUpdate;	
	
	
	commonCharacterInit(alisa, EAlisaInitialize, EAlisaStand, EDown);
	commonCharacterSetPosition(alisa, 0, 0, 0, EDown);
	alisa->controller = &alisa_controller;
	alisa->doAction = &alisa_doAction;
	alisa->setPosition = &alisa_setPosition;
	alisa->getBounds = &alisa_getBoundingBox;
	alisa->checkCollision = &alisa_checkCollision;
	alisa->checkMapCollision = &alisa_checkMapCollision;
}

void alisa_doAction(CharacterAttr* alisa,
	const MapInfo *mapInfo, const void *dummy) {
	
	
	if (alisa->nextAction < EAlisaActionCount) {
		alisa_actions[alisa->nextAction](alisa, mapInfo, NULL);
	}
	
	commonCheckForEvents(alisa, mapInfo);
}
/*
void checkForEvents(CharacterAttr* alisa,
	MapInfo *mapInfo) {
	int boundBoxCount = 0, i;
	BoundingBox eventBox, alisaBoundingBox;
	for (i = 0; i < mapInfo->eventTranferCount; ++i) {
		transferToBoundingBox(&mapInfo->tranfers[i], &eventBox);
		alisa->getBounds(alisa, &boundBoxCount, &alisaBoundingBox);
		if (hasCollision(&alisaBoundingBox, &eventBox)) {
			mapInfo->transferTo = &mapInfo->tranfers[i];
			mapInfo->mapFunction = &fadeToBlack;
			break;
		}
	}
}*/

//TODO move to common
/*
void transferToBoundingBox(const EventTransfer *transfer, BoundingBox *boundingBox) {
    boundingBox->startX = transfer->x;
	boundingBox->startY = transfer->y;
	boundingBox->endX = transfer->x + transfer->width;
	boundingBox->endY = transfer->y + transfer->height;
}*/

int alisa_setPosition(CharacterAttr* alisa,
	OBJ_ATTR *oamBuf, 
	const Position *scr_pos,
	const ScreenDimension *scr_dim) 
{
	alisa->spriteDisplay.baseY = CONVERT_TO_SCRYPOS(alisa->position.y, 
		scr_pos->y, alisa_scrConversionMeasurements);
	alisa->spriteDisplay.baseX = CONVERT_TO_SCRXPOS(alisa->position.x, 
		scr_pos->x, alisa_scrConversionMeasurements);
	
	//TODO add in screen check
	commonSetToOamBuffer(&alisa->spriteDisplay, oamBuf);
	alisa->spriteDisplay.isInScreen = true;
	
    return alisa->spriteDisplay.spriteSet->set[alisa->spriteDisplay.currentAnimationFrame].numberOflayers;
}

void alisa_actionStand(CharacterAttr* alisa,
	const MapInfo *mapInfo) {	
    bool isLastFrame = false;
	alisa->spriteDisplay.imageUpdateStatus = ENoUpdate;
	alisa->spriteDisplay.palleteUpdateStatus = ENoUpdate;
	if (initializeAction(alisa) == EUpdate) {
		alisa->spriteDisplay.currentAnimationFrame = 0;
		alisa->spriteDisplay.imageUpdateStatus = EUpdate;
		alisa->spriteDisplay.palleteUpdateStatus = EUpdate;
	}
	
	alisa->action = alisa->nextAction;
	alisa->direction = alisa->nextDirection;
	
	alisa->movementCtrl.maxFrames = 0;
	alisa->movementCtrl.currentFrame = 0;
	
	alisa->spriteDisplay.spriteSet = alisaStandWithSwordSet[alisa->direction];
	//alisa->spriteDisplay.spriteSet = &maincharacter_stand;
}

void alisa_actionRun(CharacterAttr* alisa, const MapInfo *mapInfo) {
    bool isLastFrame = false;
	alisa->spriteDisplay.imageUpdateStatus = ENoUpdate;
	alisa->spriteDisplay.palleteUpdateStatus = ENoUpdate;
	if (updateAnimation(alisa) == EUpdate) {
		alisa->spriteDisplay.imageUpdateStatus = EUpdate;
		alisa->spriteDisplay.palleteUpdateStatus = EUpdate;
	}
	
	if (alisa->action != alisa->nextAction) {
	    alisa->movementCtrl.maxFrames = alisa_RUN_MVMNT_CTRL_MAX;
		alisa->movementCtrl.currentFrame = 0;
	}
	
	alisa->action = alisa->nextAction;
	alisa->direction = alisa->nextDirection;
	
	if (alisa->movementCtrl.currentFrame >= alisa->movementCtrl.maxFrames) {
	    alisa->movementCtrl.currentFrame = 0;
	}
	//if (character->spriteDisplay.numberOfFramesPassed >= 5)
	//     mprinter_printf("XXXXXXXXXXXXXXXXXXXXXXXXXXXX FRAME %d\n", character->spriteDisplay.numberOfFramesPassed);
	//mprinter_printf("X OFFSET %d\n", alisa_runOffsetX[character->spriteDisplay.numberOfFramesPassed][character->direction]);
	
	//mprinter_printf("DIRECTION %d\n", character->direction);
	//mprinter_printf("JAPANESE %d\n", 'か');
	//mprinter_printf("JAPANESE2 %d\n", 'め');
	//mprinter_printf("JAPANESE3 %d\n", '火');
	alisa->position.x +=
		alisa_runOffsetX[alisa->direction][alisa->movementCtrl.currentFrame];
		
	alisa->position.y +=
		alisa_runOffsetY[alisa->direction][alisa->movementCtrl.currentFrame];
	
	++alisa->movementCtrl.currentFrame;
	alisa->spriteDisplay.spriteSet = alisaRunSet[alisa->direction];
	//alisa->spriteDisplay.spriteSet = &maincharacter_walk;
}

void alisa_actionSlash(CharacterAttr* alisa,
	const MapInfo *mapInfo) {
	
	alisa->spriteDisplay.imageUpdateStatus = ENoUpdate;
	alisa->spriteDisplay.palleteUpdateStatus = ENoUpdate;
	
	if (updateAnimation(alisa) == EUpdate) {
		alisa->spriteDisplay.imageUpdateStatus = EUpdate;
		alisa->spriteDisplay.palleteUpdateStatus = EUpdate;
	}
	
	alisa->movementCtrl.maxFrames = 0;
	alisa->movementCtrl.currentFrame = 0;
	
	alisa->action = alisa->nextAction;
	alisa->direction = alisa->nextDirection;
	
	if (alisa->spriteDisplay.currentAnimationFrame == SLASH_STARTSOUND_FRAME && alisa->spriteDisplay.numberOfFramesPassed == 0) {
	    if (alisa->direction == ELeft) {
	        msound_setChannelTest(&soundeffect_slash, false, 0, 6);
		} else if (alisa->direction == EUpleft || alisa->direction == EDownleft) {
		    msound_setChannelTest(&soundeffect_slash, false, 0, 6);
		} else if (alisa->direction == ERight) {
		    msound_setChannelTest(&soundeffect_slash, false, 6, 0);
		} else if (alisa->direction == EUpright || alisa->direction == EDownright) {
		    msound_setChannelTest(&soundeffect_slash, false, 6, 0);
		} else {
		    msound_setChannelTest(&soundeffect_slash, false, 0, 0);
		}
	}
	alisa->spriteDisplay.spriteSet = alisaSlashSet[alisa->direction];
}

/*void alisa_getBounds(const CharacterAttr* alisa, 
	int *count, CharBoundingBox *boundingBox) {
	*count = 1;
	u16 x = CONVERT_TO_BOUNDINGBOX_X(alisa->position.x, alisa_boundingBoxMeasurements);
	u16 y = CONVERT_TO_BOUNDINGBOX_Y(alisa->position.y, alisa_boundingBoxMeasurements);
	boundingBox->upperLeftPt.x = x;
	boundingBox->upperLeftPt.y = y;
	boundingBox->upperLeftPt.z = 0;
	boundingBox->length = alisa_boundingBoxMeasurements[EBBCnvrtLength];
	boundingBox->width = alisa_boundingBoxMeasurements[EBBCnvrtWidth];
	boundingBox->height = alisa_boundingBoxMeasurements[EBBCnvrtHeight];
}*/

void alisa_getBoundingBox(const CharacterAttr* alisa, 
	int *count, BoundingBox *boundingBox) {
	*count = 1;
	u16 x = CONVERT_TO_BOUNDINGBOX_X(alisa->position.x, alisa_boundingBoxMeasurements);
	u16 y = CONVERT_TO_BOUNDINGBOX_Y(alisa->position.y, alisa_boundingBoxMeasurements);
	boundingBox->startX = x;
	boundingBox->startY = y;
	boundingBox->endX = x + alisa_boundingBoxMeasurements[EBBCnvrtLength];
	boundingBox->endY = y + alisa_boundingBoxMeasurements[EBBCnvrtWidth];
	//boundingBox->height = alisa_boundingBoxMeasurements[EBBCnvrtHeight];
	boundingBox->direction = alisa->direction;
}

void alisa_checkMapCollision(CharacterAttr* alisa, const MapInfo* mapInfo) {
    int count;
    BoundingBox alisaBoundingBox, mapBoundingBox;
    commonCharacterMapEdgeCheck(alisa, mapInfo);
	commonGetBoundsFromMap(alisa->position.x, alisa->position.y, mapInfo, &mapBoundingBox);	
	alisa_mapCollision[alisa->direction](alisa, mapInfo, alisa_collisionReactions[alisa->direction]);
}

void alisa_checkCollision(CharacterAttr* alisa, bool isOtherCharBelow,
	bool *checkNext, const CharacterAttr* otherCharacter) {
	
	int count;
	BoundingBox alisaBoundingBox, otherCharBoundingBox;
	alisa->getBounds(alisa, &count, &alisaBoundingBox);
	otherCharacter->getBounds(otherCharacter, &count, &otherCharBoundingBox);
	
	*checkNext = common_checkNext(isOtherCharBelow, &alisaBoundingBox, &otherCharBoundingBox);
	if (!*checkNext) {
		return;
	}
	
	alisa_collisionReactions[alisa->direction](alisa, &alisaBoundingBox, &otherCharBoundingBox);
}
