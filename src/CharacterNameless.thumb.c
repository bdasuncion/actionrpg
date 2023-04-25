#include <stdlib.h>
#include <stdbool.h>
#include "GBATypes.h"
#include "GBAObject.h"
#include "GBAVideo.h"
#include "GBADMA.h"
#include "GBACharacterActionEvent.h"
#include "UtilCommonValues.h"
#include "CharacterNameless.h"
#include "ManagerVram.h"
#include "ManagerSound.h"
#include "CharacterCommon.h"
#include "MapCommon.h"
#include "sprite_maincharacterlower_stand.h"

#define NAMELESS_SCRCNVRTWIDTH 32
#define NAMELESS_SCRCNVRTHEIGHT 64

#define NAMELESS_LENGTH 20
#define NAMELESS_WIDTH 55
#define NAMELESS_HEIGHT 18

#define NAMELESS_PAL_CNT 1

const u8 nameless_scrConversionMeasurements[EScrCnvrtMeasureCount] = {
	NAMELESS_SCRCNVRTWIDTH,
	NAMELESS_SCRCNVRTHEIGHT
};

const u8 nameless_boundingBoxMeasurements[EBBCnvrtMeasurementCount] = {
	NAMELESS_LENGTH,
	NAMELESS_WIDTH,
	NAMELESS_HEIGHT,
};

extern const SpriteSet maincharacter_stand;
extern const SpriteSet maincharacter_walk;
extern const SpriteSet ghosthand_appear;
extern const SpriteSet ghosltyman;
extern const unsigned short maincharacterlower_walk_pal[16];

void nameless_doAction(CharacterAttr* nameless, const MapInfo *mapInfo, 
    const void *dummy, CharacterActionCollection *charActionCollection);
int nameless_setPosition(CharacterAttr* nameless,
	OBJ_ATTR *oamBuf, 
	const Position *scr_pos,
	const ScreenDimension *scr_dim);
void nameless_getBoundingBox(const CharacterAttr* nameless, int *count, BoundingBox *boundingBox);
void nameless_checkCollision(CharacterAttr* alisa, bool isOtherCharBelow,
	bool *checkNext, const CharacterAttr* otherCharacter);
void nameless_checkMapCollision(CharacterAttr* alisa, const MapInfo* mapInfo);
void nameless_actionStand(CharacterAttr* nameless,const MapInfo *mapInfo, const void *dummy);
void nameless_actionWalk(CharacterAttr* nameless, const MapInfo *mapInfo, const void *dummy);
//TODO: Put in common
void checkForEventsNameless(CharacterAttr* nameless, MapInfo *mapInfo);
const CharFuncAction nameless_actions[] = {
	&nameless_actionStand,
	&nameless_actionWalk
};

void nameless_init(CharacterAttr* nameless) {	
	//use library to get id
	nameless->id = 0;
	//use enum of character type
	nameless->type = NAMELESS;
	
	nameless->spriteDisplay.baseImageId = sprite_vram_findIdByType(ECharSizeSmall);
	nameless->spriteDisplay.imageUpdateStatus = EUpdate;
	nameless->spriteDisplay.basePalleteId = sprite_palette_findId(NAMELESS, NAMELESS_PAL_CNT);
	
	sprite_palette_copy32_ID(maincharacterlower_walk_pal, nameless->spriteDisplay.basePalleteId);
	sprite_palette_copy32_ID(maincharacterlower_walk_pal, nameless->spriteDisplay.basePalleteId);
	
	commonCharacterInit(nameless, ENamelessInitialize, ENamelessStand, ELeft);
	commonCharacterSetPosition(nameless, 0, 0, 0, ELeft);
	nameless->controller = &nameless_controller;
	nameless->doAction = &nameless_doAction;
	nameless->setPosition = &nameless_setPosition;
	nameless->getBounds = &nameless_getBoundingBox;
	nameless->checkCollision = &nameless_checkCollision;
	nameless->checkMapCollision = &nameless_checkMapCollision;
}

void nameless_doAction(CharacterAttr* nameless, const MapInfo *mapInfo, 
    const void *dummy, CharacterActionCollection *charActionCollection) {
	
	
	if (nameless->nextAction < ENamelessActionCount) {
	    nameless_actions[nameless->nextAction](nameless, mapInfo, dummy, charActionCollection);
	}
	
	commonCheckForEvents(nameless, mapInfo);
}

int nameless_setPosition(CharacterAttr* nameless,
	OBJ_ATTR *oamBuf, 
	const Position *scr_pos,
	const ScreenDimension *scr_dim) {
	
	nameless->spriteDisplay.baseY = CONVERT_TO_SCRYPOS(nameless->position.y, 
		scr_pos->y, nameless_scrConversionMeasurements);
	nameless->spriteDisplay.baseX = CONVERT_TO_SCRXPOS(nameless->position.x, 
		scr_pos->x, nameless_scrConversionMeasurements);
	
	//TODO add in screen check
	commonSetToOamBuffer(&nameless->spriteDisplay, oamBuf);
	nameless->spriteDisplay.isInScreen = true;
		
    return nameless->spriteDisplay.spriteSet->set->numberOflayers;
}

void nameless_getBoundingBox(const CharacterAttr* nameless, int *count, BoundingBox *boundingBox) {
    *count = 1;
	u16 x = CONVERT_TO_BOUNDINGBOX_X(nameless->position.x, nameless_boundingBoxMeasurements);
	u16 y = CONVERT_TO_BOUNDINGBOX_Y(nameless->position.y, nameless_boundingBoxMeasurements);
	boundingBox->startX = x;
	boundingBox->startY = y;
	boundingBox->endX = x + nameless_boundingBoxMeasurements[EBBCnvrtLength];
	boundingBox->endY = y + nameless_boundingBoxMeasurements[EBBCnvrtWidth];
	//boundingBox->height = alisa_boundingBoxMeasurements[EBBCnvrtHeight];
	boundingBox->direction = nameless->direction;
}

void nameless_checkCollision(CharacterAttr* nameless, bool isOtherCharBelow,
	bool *checkNext, const CharacterAttr* otherCharacter) {
	*checkNext = false;
}

void nameless_checkMapCollision(CharacterAttr* nameless, const MapInfo* mapInfo) {
}

void nameless_actionStand(CharacterAttr* nameless, const MapInfo *mapInfo, 
    const void *dummy) {

    bool isLastFrame = false;
	nameless->spriteDisplay.imageUpdateStatus = ENoUpdate;
	nameless->spriteDisplay.palleteUpdateStatus = ENoUpdate;
	if (commonInitializeAction(nameless) == EUpdate) {
		nameless->spriteDisplay.currentAnimationFrame = 0;
		nameless->spriteDisplay.imageUpdateStatus = EUpdate;
		nameless->spriteDisplay.palleteUpdateStatus = EUpdate;
	}
	
	nameless->action = nameless->nextAction;
	nameless->direction = nameless->nextDirection;
	
	nameless->movementCtrl.maxFrames = 0;
	nameless->movementCtrl.currentFrame = 0;
	
	nameless->spriteDisplay.spriteSet = &maincharacter_stand;
}

void nameless_actionWalk(CharacterAttr* nameless, const MapInfo *mapInfo, 
    const void *dummy) {
    bool isLastFrame = false;
	nameless->spriteDisplay.imageUpdateStatus = ENoUpdate;
	nameless->spriteDisplay.palleteUpdateStatus = ENoUpdate;
	if (commonUpdateAnimation(nameless) == EUpdate) {
		nameless->spriteDisplay.imageUpdateStatus = EUpdate;
		nameless->spriteDisplay.palleteUpdateStatus = EUpdate;
	}
	
	if (nameless->action != nameless->nextAction) {
	    nameless->movementCtrl.maxFrames = 1;
		nameless->movementCtrl.currentFrame = 0;
	}
	
	nameless->action = nameless->nextAction;
	nameless->direction = nameless->nextDirection;
	
	if (nameless->movementCtrl.currentFrame&1) {
	    nameless->position.x += -1;
		nameless->movementCtrl.currentFrame = 0;
	} else {
	    ++nameless->movementCtrl.currentFrame;
	}
		
	
	nameless->spriteDisplay.spriteSet = &maincharacter_walk;
	//nameless->spriteDisplay.spriteSet = &ghosthand_appear;
	//nameless->spriteDisplay.spriteSet = &ghosltyman;
}