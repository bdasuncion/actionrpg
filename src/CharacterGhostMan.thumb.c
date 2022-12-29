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
#include "CharacterGhostMan.h"

#define GHOSTMAN_SCRCNVRTWIDTH 10
#define GHOSTMAN_SCRCNVRTHEIGHT 24

#define GHOSTMAN_LENGTH 12
#define GHOSTMAN_WIDTH 10
#define GHOSTMAN_HEIGHT 18

#define GHOSTMAN_PAL_CNT 1

#define GHOSTMAN_FRAMEPASSED_GROWL 5
#define GHOSTMAN_FRAMEPASSED_DARKEN 30
#define GHOSTMAN_FRAMEPASSED_DARKEN2 60
#define GHOSTMAN_FRAMEPASSED_DARKEN3 90
#define GHOSTMAN_FOLLOWDISTANCE 20

extern const unsigned short ghostlyman_pal[16];
extern const Sound soundeffect_ghost_moan;
extern const Sound soundeffect_ghost_moan2;
extern const Sound soundeffect_ghost_moan3;
extern const Sound soundeffect_ghost_moan4;
extern const Sound soundeffect_crow;

extern const SpriteSet ghosltyman;
extern const SpriteSet ghosltymantransition;
extern const SpriteSet ghostlyman_floating;

const u8 ghostMan_scrConversionMeasurements[EScrCnvrtMeasureCount] = {
	GHOSTMAN_SCRCNVRTWIDTH,
	GHOSTMAN_SCRCNVRTHEIGHT
};

const u8 ghostMan_boundingBoxMeasurements[EBBCnvrtMeasurementCount] = {
	GHOSTMAN_LENGTH,
	GHOSTMAN_WIDTH,
	GHOSTMAN_HEIGHT,
};

void ghostMan_doAction(CharacterAttr* ghostMan, const MapInfo *mapInfo, 
    const CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection);
void ghostMan_doSit(CharacterAttr* ghostMan, const MapInfo *mapInfo, 
    const CharacterCollection *characterCollection);
void ghostMan_doTransitionToFollow(CharacterAttr* ghostMan, const MapInfo *mapInfo, 
    const CharacterCollection *characterCollection);
void ghostMan_doFollow(CharacterAttr* ghostMan, const MapInfo *mapInfo, 
    const CharacterCollection *characterCollection);
void ghostMan_controller(CharacterAttr* ghostMan, const MapInfo *mapInfo, CharacterCollection *charCollection);
int ghostMan_setPosition(CharacterAttr* ghostMan, OBJ_ATTR *oamBuf, 
	const Position *scr_pos, const ScreenDimension *scr_dim);
void ghostMan_getBoundingBox(const CharacterAttr* ghostMan, int *count, BoundingBox *boundingBox);
void ghostMan_checkCollision(CharacterAttr* ghostMan, bool isOtherCharBelow,
	bool *checkNext, const CharacterAttr* otherCharacter);
void ghostMan_checkMapCollision(CharacterAttr* ghostMan, const MapInfo* mapInfo);

const CharFuncAction ghostMan_actions[] = {
	&ghostMan_doSit,
	&ghostMan_doTransitionToFollow,
	&ghostMan_doFollow
};

void ghostMan_init(CharacterAttr* ghostMan, ControlTypePool* controlPool) {	
	//use library to get id
	ghostMan->id = 0;
	//use enum of character type
	ghostMan->type = GHOSTMAN;
	
	ghostMan->spriteDisplay.baseImageId = sprite_vram_findId();
	ghostMan->spriteDisplay.imageUpdateStatus = EUpdate;
	ghostMan->spriteDisplay.basePalleteId = sprite_palette_findId(GHOSTMAN, GHOSTMAN_PAL_CNT);
	
	sprite_palette_copy32_ID(ghostlyman_pal, ghostMan->spriteDisplay.basePalleteId);
		
	commonCharacterInit(ghostMan, EGhostmanInitialize, EGhostmanSit, ELeft);
	commonCharacterSetPosition(ghostMan, 0, 0, 0, ELeft);
	ghostMan->controller = &ghostMan_controller;
	ghostMan->doAction = &ghostMan_doAction;
	ghostMan->setPosition = &ghostMan_setPosition;
	ghostMan->getBounds = &ghostMan_getBoundingBox;
	ghostMan->checkCollision = &ghostMan_checkCollision;
	ghostMan->checkMapCollision = &ghostMan_checkMapCollision;
	ghostMan->free = mchar_getControlType(controlPool);
}

void ghostMan_doAction(CharacterAttr* ghostMan, const MapInfo *mapInfo, 
    const CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection) {
    if (ghostMan->nextAction < EGhostmanActionCount) {
        ghostMan_actions[ghostMan->nextAction](ghostMan, mapInfo, characterCollection, charActionCollection);
	}
}

void ghostMan_doSit(CharacterAttr* ghostMan, const MapInfo *mapInfo, 
    const CharacterCollection *characterCollection) {
	CharacterBaseControl *baseControl;
    bool isLastFrame = false;
	
	ghostMan->spriteDisplay.imageUpdateStatus = ENoUpdate;
	ghostMan->spriteDisplay.palleteUpdateStatus = ENoUpdate;
	if (commonInitializeAction(ghostMan) == EUpdate) {
		ghostMan->spriteDisplay.imageUpdateStatus = EUpdate;
		ghostMan->spriteDisplay.palleteUpdateStatus = EUpdate;
	}
	
	ghostMan->action = ghostMan->nextAction;
	ghostMan->direction = ghostMan->nextDirection;
	
	/*baseControl = ghostMan->free;
	if (ghostMan->spriteDisplay.numberOfFramesPassed == 0 && ghostMan->spriteDisplay.currentAnimationFrame > 0) {
	    int distance = baseControl->target->x - ghostMan->position.x;
		int rightPhaseDelay; 
		int leftPhaseDelay;
		distance = distance >> 4;
		rightPhaseDelay = 6*(distance < 0);
		leftPhaseDelay = 6*(distance > 0);
		distance *= (distance < 0)*(-1) + (distance >= 0)*1;
		msound_setChannel3d(&soundeffect_ghost_moan3, false, rightPhaseDelay, leftPhaseDelay, distance);
	}*/
	ghostMan->movementCtrl.maxFrames = 0;
	ghostMan->movementCtrl.currentFrame = 0;
	
	ghostMan->spriteDisplay.spriteSet = &ghosltyman;
	//ghostMan->spriteDisplay.spriteSet = &ghostlyman_floating;
}

void ghostMan_doTransitionToFollow(CharacterAttr* ghostMan, const MapInfo *mapInfo, 
    const CharacterCollection *characterCollection) {
	CharacterAIControl *charControl = (CharacterAIControl*)ghostMan->free;
    bool isLastFrame = false;
	
	ghostMan->spriteDisplay.imageUpdateStatus = ENoUpdate;
	ghostMan->spriteDisplay.palleteUpdateStatus = ENoUpdate;
	if (commonUpdateAnimation(ghostMan) == EUpdate) {
		ghostMan->spriteDisplay.imageUpdateStatus = EUpdate;
		ghostMan->spriteDisplay.palleteUpdateStatus = EUpdate;
	}
	
	ghostMan->action = ghostMan->nextAction;
	ghostMan->direction = ghostMan->nextDirection;
	
	if (ghostMan->spriteDisplay.numberOfFramesPassed == GHOSTMAN_FRAMEPASSED_GROWL) {
		int distance = charControl->target.x - ghostMan->position.x, rightPhaseDelay, leftPhaseDelay;
		msound_process3dSound(&distance, &rightPhaseDelay, &leftPhaseDelay);
	    msound_setChannel3d(&soundeffect_ghost_moan3, false, rightPhaseDelay, leftPhaseDelay, distance);
	}
	
	if (ghostMan->spriteDisplay.numberOfFramesPassed == GHOSTMAN_FRAMEPASSED_DARKEN || 
		ghostMan->spriteDisplay.numberOfFramesPassed == GHOSTMAN_FRAMEPASSED_DARKEN2 ||
		ghostMan->spriteDisplay.numberOfFramesPassed == GHOSTMAN_FRAMEPASSED_DARKEN3) {
		mapCommon_initFlashScreen(mapInfo);
	}
	
	ghostMan->spriteDisplay.spriteSet = &ghosltymantransition;
}

void ghostMan_doFollow(CharacterAttr* ghostMan, const MapInfo *mapInfo, 
    const CharacterCollection *characterCollection) {
	CharacterAIControl *charControl = (CharacterAIControl*)ghostMan->free;
	
	ghostMan->spriteDisplay.imageUpdateStatus = ENoUpdate;
	ghostMan->spriteDisplay.palleteUpdateStatus = ENoUpdate;
	if (commonUpdateAnimation(ghostMan) == EUpdate) {
		ghostMan->spriteDisplay.imageUpdateStatus = EUpdate;
		ghostMan->spriteDisplay.palleteUpdateStatus = EUpdate;
	}
	
	ghostMan->action = ghostMan->nextAction;
	ghostMan->direction = ghostMan->nextDirection;
	
	ghostMan->position.x = charControl->target.x + GHOSTMAN_FOLLOWDISTANCE;
	
	++ghostMan->movementCtrl.currentFrame;
	if (ghostMan->movementCtrl.currentFrame >= ghostMan->movementCtrl.maxFrames) {
		int distance = charControl->target.x - ghostMan->position.x, rightPhaseDelay, leftPhaseDelay;
		ghostMan->movementCtrl.currentFrame = 0;
		distance = distance >> 4;
		rightPhaseDelay = 6*(distance < 0);
		leftPhaseDelay = 6*(distance > 0);
		distance *= (distance < 0)*(-1) + (distance >= 0)*1;
	    msound_setChannel3d(&soundeffect_ghost_moan4, false, rightPhaseDelay, leftPhaseDelay, distance);
	}
		
	ghostMan->spriteDisplay.spriteSet = &ghostlyman_floating;
}

int ghostMan_setPosition(CharacterAttr* ghostMan,
	OBJ_ATTR *oamBuf, 
	const Position *scr_pos,
	const ScreenDimension *scr_dim) {
	
	ghostMan->spriteDisplay.baseY = CONVERT_TO_SCRYPOS(ghostMan->position.y, 
		scr_pos->y, ghostMan_scrConversionMeasurements);
	ghostMan->spriteDisplay.baseX = CONVERT_TO_SCRXPOS(ghostMan->position.x, 
		scr_pos->x, ghostMan_scrConversionMeasurements);
	
	//TODO add in screen check
	commonSetToOamBuffer(&ghostMan->spriteDisplay, oamBuf);
	ghostMan->spriteDisplay.isInScreen = true;
	
    return ghostMan->spriteDisplay.spriteSet->set[ghostMan->spriteDisplay.currentAnimationFrame].numberOflayers;
}

void ghostMan_getBoundingBox(const CharacterAttr* ghostMan, int *count, BoundingBox *boundingBox) {
}

void ghostMan_checkCollision(CharacterAttr* ghostMan, bool isOtherCharBelow,
	bool *checkNext, const CharacterAttr* otherCharacter) {
}

void ghostMan_checkMapCollision(CharacterAttr* ghostMan, const MapInfo* mapInfo) {
}