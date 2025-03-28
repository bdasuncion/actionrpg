#include <stdlib.h>
#include  <stdarg.h>
#include  <stdbool.h>
#include "GBAObject.h"
#include "GBAMap.h"
#include "GBATransparency.h"
#include "GBACharacterActionEvent.h"

#include "ManagerScrDisplay.h"
#include "ManagerBG.h"
#include "ManagerVram.h"
#include "ManagerCharacters.h"
#include "ManagerCharacterActionEvents.h"

#include "MapCommon.h"
//#include "CharacterAlisa.h"
//#include "CharacterNameless.h"
#include "CharacterCommon.h"

#define DEFAULT_SCREEN_BOUNDING_BOX 0
//#define DELAY 2
#define DELAY 1
#define BLENDVAL_MAX 16

EWRAM int blendVal = 0;
EWRAM int current = 0;
EWRAM bool update = true;

//extern const MapInfo mapTest;

//void fadeToBlack(ScreenAttr *screenAttribute, CharacterCollection *characterCollection, MapInfo *mapInfo,
//	ControlTypePool* controlPool, CharacterActionCollection *charActionCollection,
//	Track *track);
void returnToScreen(ScreenAttr *screenAttribute, CharacterCollection *characterCollection, MapInfo *mapInfo,
	ControlTypePool* controlPool, CharacterActionCollection *charActionCollection,
	Track *track);
//void mapCommon_defaultEffect(void *screenAttribute, void *characterCollection, void *mapInfo, 
//	void *dummy1, void *dummy2, void *dummy3);
void mapCommon_effectSpriteMasking(ScreenAttr *screenAttribute, CharacterCollection *characterCollection, MapInfo *mapInfo, 
	ControlTypePool* controlPool, CharacterActionCollection *charActionCollection, Track *track);

void map_nofunction(ScreenAttr *screenAttribute, CharacterCollection *characterCollection, MapInfo *mapInfo) {
}

void mapCommon_transferToMap(ScreenAttr *screenAttribute, CharacterCollection *characterCollection, 
        MapInfo *mapInfo, ControlTypePool* controlPool, CharacterActionCollection *charActionCollection,
		Track *track) {
	CharacterAttr *character;
	EventTransfer *eventTransfer = mapInfo->transferTo;
	int i;

	mchar_actione_reinit(charActionCollection);
	if (mapInfo->onExitMap) {
		mapInfo->onExitMap(screenAttribute, characterCollection, 
        mapInfo, controlPool, charActionCollection, track);
	}

	sprite_vram_init_sections();
	sprite_palette_init();
	mchar_reinit(characterCollection, &character);
	
	mchar_resetControlTypeAndSetCount(controlPool, characterCollection->countCharacterTransfer + 
		((MapInfo*)eventTransfer->mapInfo)->characterCount);
	for (i = 0; i < characterCollection->countCharacterTransfer; ++i) {
		characterCollection->characterTransfer[i](character, controlPool, NULL);
	}
	
    commonCharacterSetPosition(character, 
	   eventTransfer->transferToX, eventTransfer->transferToY, eventTransfer->transferToZ, eventTransfer->directionOnTransfer);
	character->doAction(character, mapInfo, characterCollection, charActionCollection);
	
	*mapInfo = *((MapInfo*)eventTransfer->mapInfo);
	mscr_initCharMoveRef(screenAttribute, mapInfo,
		&character->position, DEFAULT_SCREEN_BOUNDING_BOX);

	mapInfo->transferTo = eventTransfer;
	
	character->checkMapCollision(character, mapInfo);

	if (mapInfo->music && track->musicTrack != mapInfo->music) {
		track->musicTrack = mapInfo->music;
		track->trackIndex = 0;
		track->framesPassed = 0;
	} else if (!mapInfo->music) {
		track->musicTrack = NULL;
		track->trackIndex = 0;
		track->framesPassed = 0;
	}
	
	if (mapInfo->onInitMap) {
		mapInfo->onInitMap(screenAttribute, characterCollection, 
        mapInfo, controlPool, charActionCollection, track);
	}

	mbg_init(screenAttribute, mapInfo, characterCollection, controlPool, charActionCollection);
	
	mapInfo->mapFunction = &returnToScreen;
	
	mapInfo->screenEffect.processScreenEffect = &mapCommon_defaultEffect;
}

void fadeToBlack(ScreenAttr *screenAttribute, CharacterCollection *characterCollection, MapInfo *mapInfo,
	ControlTypePool* controlPool, CharacterActionCollection *charActionCollection,
	Track *track) {
    ++current;
	if (current >= DELAY) {
	    current = 0;
        ++blendVal;
	}
    if (blendVal >= BLENDVAL_MAX) {
		mapInfo->mapFunction = &mapCommon_transferToMap;
	}
    //blendBlack(blendVal);
	blendBlack(BLENDVAL_MAX);
}

void returnToScreen(ScreenAttr *screenAttribute, CharacterCollection *characterCollection, MapInfo *mapInfo,
	ControlTypePool* controlPool, CharacterActionCollection *charActionCollection,
	Track *track) {
    
	++current;
	if (current >= DELAY) {
	    current = 0;
		--blendVal;
	}
	
	if (blendVal <= 0) {
		mapInfo->mapFunction = ((MapInfo*)mapInfo->transferTo->mapInfo)->mapFunction;
		mapInfo->screenEffect.processScreenEffect = &mapCommon_defaultEffect;
	    mapInfo->transferTo = NULL;
		blendBlack(0);
		mapCommon_effectSpriteMasking(screenAttribute, characterCollection, mapInfo, controlPool, charActionCollection, track);
	}
}

void mapCommon_effectSpriteMasking(ScreenAttr *screenAttribute, CharacterCollection *characterCollection, 
	MapInfo *mapInfo, ControlTypePool* controlPool, CharacterActionCollection *charActionCollection,
	Track *track) {
	setSpriteMasking();
}

void mapCommon_defaultEffect(ScreenAttr *screenAttribute, CharacterCollection *characterCollection, 
	MapInfo *mapInfo, ControlTypePool* controlPool, CharacterActionCollection *charActionCollection,
	Track *track) {
}

void mapCommon_returnToNormal(ScreenAttr *screenAttribute, CharacterCollection *characterCollection, 
	MapInfo *mapInfo, ControlTypePool* controlPool, CharacterActionCollection *charActionCollection,
	Track *track) {
    blendBlack(0);
	++mapInfo->screenEffect.currentFrame;
	if (mapInfo->screenEffect.currentFrame >= mapInfo->screenEffect.durationFrames) {
	    //mapInfo->screenEffect.durationFrames = 3;
		mapInfo->screenEffect.durationFrames = 1;
		mapInfo->screenEffect.currentFrame = 0;
		mapInfo->screenEffect.processScreenEffect = &mapCommon_defaultEffect;
	}
}

void mapCommon_goDark(ScreenAttr *screenAttribute, CharacterCollection *characterCollection, 
	MapInfo *mapInfo, ControlTypePool* controlPool, CharacterActionCollection *charActionCollection,
	Track *track) {
    blendBlack(BLENDVAL_MAX);
	++mapInfo->screenEffect.currentFrame;
	if (mapInfo->screenEffect.currentFrame >= mapInfo->screenEffect.durationFrames) {
	    //mapInfo->screenEffect.durationFrames = 5;
		mapInfo->screenEffect.durationFrames = 1;
		mapInfo->screenEffect.currentFrame = 0;
		mapInfo->screenEffect.processScreenEffect = &mapCommon_returnToNormal;
	}
}

void mapCommon_initFlashScreen(MapInfo *mapInfo) {
    //mapInfo->screenEffect.durationFrames = 5;
	mapInfo->screenEffect.durationFrames = 1;
    mapInfo->screenEffect.currentFrame = 0;
    mapInfo->screenEffect.processScreenEffect = &mapCommon_goDark;
}

