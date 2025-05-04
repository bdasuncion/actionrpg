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
#include "ManagerPrinter.h"

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
EWRAM ScreenCharPosition transferToScrPos[1];
EWRAM MoveScrPosition moveCharacter[1];

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

void mapCommon_calculateMovement(const ScreenCharPosition *from, const ScreenCharPosition *to, 
	CharacterAttr *character, MoveScrPosition *move) {
	s8 xDiff = to->y - from->x;
	s8 yDiff = to->y - from->y;
	int xdiffAbs = abs(xDiff), ydiffAbs = abs(yDiff);
	if (xdiffAbs > ydiffAbs) {
		move->offsetY = (MOVE_STR*ydiffAbs)/xdiffAbs;
		move->offsetX = MOVE_STR;
		move->count = xdiffAbs;
	} else {
		move->offsetX = (MOVE_STR*xdiffAbs)/ydiffAbs;
		move->offsetY = MOVE_STR;
		move->count = ydiffAbs;
	}
	
	mprinter_printf("xdiff:%d ydiff:%d\n", xDiff, yDiff);
	
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

	ScreenCharPosition from, to;
	from.x = character->spriteDisplay.baseX;
	from.y = character->spriteDisplay.baseY;
	mprinter_printf("POS X:%d Y:%d\n", from.x, from.y);
	
	mchar_resetControlTypeAndSetCount(controlPool, characterCollection->countCharacterTransfer + 
		((MapInfo*)eventTransfer->mapInfo)->characterCount);

	//mprinter_printf("BEFORE ACTION current %d next %d\n", character->action, character->nextAction);
    commonCharacterSetPosition(character, 
	   eventTransfer->transferToX, eventTransfer->transferToY, eventTransfer->transferToZ, 
	   eventTransfer->directionOnTransfer);
	
   
	for (i = 0; i < characterCollection->countCharacterTransfer; ++i) {
		characterCollection->characterTransfer[i].init(character, controlPool, NULL);
	}

	character->doAction(character, mapInfo, characterCollection, charActionCollection);
	
	//mprinter_printf("ACTION current %d next %d\n", character->action, character->nextAction);
	
	*mapInfo = *((MapInfo*)eventTransfer->mapInfo);
	mscr_initCharMoveRef(screenAttribute, mapInfo,
		&character->position, DEFAULT_SCREEN_BOUNDING_BOX);
		
	characterCollection->characterTransfer[0].getScreenPos(character, 
			&screenAttribute->position, &to);
			
	mapCommon_calculateMovement(&from, &to, character, moveCharacter);
			
	mprinter_printf("NEXT POS X:%d Y:%d\n", to.x, to.y);
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
	if (blendVal == 0) {
		common_removeSpriteMask(characterCollection);
	}
	
    ++current;
	if (current >= DELAY) {
	    current = 0;
        ++blendVal;
	}
    if (blendVal >= BLENDVAL_MAX) {
		mapInfo->mapFunction = &mapCommon_transferToMap;
	}
    //blendBlack(blendVal);
	blendBlackBGOnly(blendVal);
}

void returnToScreen(ScreenAttr *screenAttribute, CharacterCollection *characterCollection, MapInfo *mapInfo,
	ControlTypePool* controlPool, CharacterActionCollection *charActionCollection,
	Track *track) {
    
	++current;
	if (current >= DELAY) {
	    current = 0;
		--blendVal;
	}
	blendBlackBGOnly(blendVal);
	if (blendVal <= 0) {
		mapInfo->mapFunction = ((MapInfo*)mapInfo->transferTo->mapInfo)->mapFunction;
		mapInfo->screenEffect.processScreenEffect = &mapCommon_defaultEffect;
	    mapInfo->transferTo = NULL;
		blendBlackBGOnly(0);
		//blendBlackBGOnly(blendVal);
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
    blendBlackBGOnly(0);
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
    blendBlackBGOnly(BLENDVAL_MAX);
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

