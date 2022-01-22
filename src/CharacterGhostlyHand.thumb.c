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
#include "CharacterGhostHand.h"

#define GHOSTLYHAND_SCRCNVRTWIDTH 10
#define GHOSTLYHAND_SCRCNVRTHEIGHT 24

#define GHOSTLYHAND_LENGTH 12
#define GHOSTLYHAND_WIDTH 10
#define GHOSTLYHAND_HEIGHT 18

#define GHOSTLYHAND_PAL_CNT 1

const u8 ghostlyHand_scrConversionMeasurements[EScrCnvrtMeasureCount] = {
	GHOSTLYHAND_SCRCNVRTWIDTH,
	GHOSTLYHAND_SCRCNVRTHEIGHT
};

const u8 ghostlyHand_boundingBoxMeasurements[EBBCnvrtMeasurementCount] = {
	GHOSTLYHAND_LENGTH,
	GHOSTLYHAND_WIDTH,
	GHOSTLYHAND_HEIGHT,
};

extern const Sound soundeffect_window_hit;
extern const SpriteSet ghosthand_hidden;
extern const SpriteSet ghosthand_appear;
extern const unsigned short ghostly_hand_pal[16];

void ghostlyHand_controller(CharacterAttr* ghostlyHand, const MapInfo *mapInfo, CharacterCollection *charCollection);
int ghostlyHand_setPosition(CharacterAttr* ghostlyHand, OBJ_ATTR *oamBuf,
	const Position *scr_pos, const ScreenDimension *scr_dim);
void ghostlyHand_getBoundingBox(const CharacterAttr* nameless, int *count, BoundingBox *boundingBox);
void ghostlyHand_checkCollision(CharacterAttr* nameless, bool isOtherCharBelow,
	bool *checkNext, const CharacterAttr* otherCharacter);
void ghostlyHand_checkMapCollision(CharacterAttr* nameless, const MapInfo* mapInfo);
void ghostlyHand_doAction(CharacterAttr* ghostlyHand, const MapInfo *mapInfo,
    const CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection);

void ghostlyHand_doHide(CharacterAttr* ghostlyHand, const MapInfo *mapInfo, 
    const CharacterCollection *characterCollection);
void ghostlyHand_doAppear(CharacterAttr* ghostlyHand, const MapInfo *mapInfo, 
    const CharacterCollection *characterCollection);

const CharFuncAction ghostlyHand_actions[] = {
	&ghostlyHand_doHide,
	&ghostlyHand_doAppear
};

void ghostlyHand_init(CharacterAttr* ghostlyHand, ControlTypePool* controlPool)
{	
	//use library to get id
	ghostlyHand->id = 0;
	//use enum of character type
	ghostlyHand->type = GHOSTHAND;
	
	ghostlyHand->spriteDisplay.baseImageId = sprite_vram_findId();
	ghostlyHand->spriteDisplay.imageUpdateStatus = EUpdate;
	ghostlyHand->spriteDisplay.basePalleteId = sprite_palette_findId(GHOSTHAND, GHOSTLYHAND_PAL_CNT);
	
	sprite_palette_copy32_ID(ghostly_hand_pal, ghostlyHand->spriteDisplay.basePalleteId);
		
	commonCharacterInit(ghostlyHand, EGhosthandInitialize, EGhosthandHidden, ELeft);
	commonCharacterSetPosition(ghostlyHand, 0, 0, 0, ELeft);
	ghostlyHand->controller = &ghostlyHand_controller;
	ghostlyHand->doAction = &ghostlyHand_doAction;
	ghostlyHand->setPosition = &ghostlyHand_setPosition;
	ghostlyHand->getBounds = &ghostlyHand_getBoundingBox;
	ghostlyHand->checkCollision = &ghostlyHand_checkCollision;
	ghostlyHand->checkMapCollision = &ghostlyHand_checkMapCollision;
	ghostlyHand->free = mchar_getControlType(controlPool);
}

void ghostlyHand_doAction(CharacterAttr* ghostlyHand, const MapInfo *mapInfo, 
    const CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection) {
    if (ghostlyHand->nextAction < EGhosthandActionCount) {
        ghostlyHand_actions[ghostlyHand->nextAction](ghostlyHand, mapInfo, characterCollection, 
		charActionCollection);
	}
}

int ghostlyHand_setPosition(CharacterAttr* ghostlyHand,
	OBJ_ATTR *oamBuf, 
	const Position *scr_pos,
	const ScreenDimension *scr_dim) {
	
	ghostlyHand->spriteDisplay.baseY = CONVERT_TO_SCRYPOS(ghostlyHand->position.y, 
		scr_pos->y, ghostlyHand_scrConversionMeasurements);
	ghostlyHand->spriteDisplay.baseX = CONVERT_TO_SCRXPOS(ghostlyHand->position.x, 
		scr_pos->x, ghostlyHand_scrConversionMeasurements);
	
	//TODO add in screen check
	commonSetToOamBuffer(&ghostlyHand->spriteDisplay, oamBuf);
	ghostlyHand->spriteDisplay.isInScreen = true;
	
    return ghostlyHand->spriteDisplay.spriteSet->set[ghostlyHand->spriteDisplay.currentAnimationFrame].numberOflayers;
}

void ghostlyHand_getBoundingBox(const CharacterAttr* nameless, int *count, BoundingBox *boundingBox) {
}

void ghostlyHand_checkCollision(CharacterAttr* nameless, bool isOtherCharBelow,
	bool *checkNext, const CharacterAttr* otherCharacter) {
}

void ghostlyHand_checkMapCollision(CharacterAttr* nameless, const MapInfo* mapInfo) {
}

void ghostlyHand_doHide(CharacterAttr* ghostlyHand, const MapInfo *mapInfo, 
    const CharacterCollection *characterCollection) {
    bool isLastFrame = false;
	ghostlyHand->spriteDisplay.imageUpdateStatus = ENoUpdate;
	ghostlyHand->spriteDisplay.palleteUpdateStatus = ENoUpdate;
	if (commonInitializeAction(ghostlyHand) == EUpdate) {
		ghostlyHand->spriteDisplay.currentAnimationFrame = 0;
		ghostlyHand->spriteDisplay.imageUpdateStatus = EUpdate;
		ghostlyHand->spriteDisplay.palleteUpdateStatus = EUpdate;
	}
	
	ghostlyHand->action = ghostlyHand->nextAction;
	ghostlyHand->direction = ghostlyHand->nextDirection;
	
	ghostlyHand->movementCtrl.maxFrames = 0;
	ghostlyHand->movementCtrl.currentFrame = 0;
	
	ghostlyHand->spriteDisplay.spriteSet = &ghosthand_hidden;

}

void ghostlyHand_doAppear(CharacterAttr* ghostlyHand, const MapInfo *mapInfo, 
    const CharacterCollection *characterCollection) {
    CharacterBaseControl *baseControl;
	//FreeTypeUnion *freeControl;
    bool isLastFrame = false;
	ghostlyHand->spriteDisplay.imageUpdateStatus = ENoUpdate;
	ghostlyHand->spriteDisplay.palleteUpdateStatus = ENoUpdate;
	if (commonUpdateAnimation(ghostlyHand) == EUpdate) {
		ghostlyHand->spriteDisplay.imageUpdateStatus = EUpdate;
		ghostlyHand->spriteDisplay.palleteUpdateStatus = EUpdate;
	}
	
	//mprinter_printf("current frame %d\n", ghostlyHand->spriteDisplay.currentAnimationFrame);
	//mprinter_printf("current DISPLAY frame %d\n", ghostlyHand->spriteDisplay.numberOfFramesPassed);
	ghostlyHand->action = ghostlyHand->nextAction;
	ghostlyHand->direction = ghostlyHand->nextDirection;
	
	baseControl = ghostlyHand->free;
	if (ghostlyHand->spriteDisplay.numberOfFramesPassed == 0 && ghostlyHand->spriteDisplay.currentAnimationFrame > 0) {
	    int distance = baseControl->target->x - ghostlyHand->position.x, rightPhaseDelay, leftPhaseDelay;
		msound_process3dSound(&distance, &rightPhaseDelay, &leftPhaseDelay);
	    msound_setChannel3d(&soundeffect_window_hit, false, rightPhaseDelay, leftPhaseDelay, distance);
	}
	
	ghostlyHand->spriteDisplay.spriteSet = &ghosthand_appear;
}
