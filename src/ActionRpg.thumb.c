#include <stdlib.h>
#include "GBAObject.h"
#include "GBATransparency.h"
#include "UtilCommonValues.h"
#include "ManagerOAM.h"
#include "ManagerSound.h"
#include "ManagerScrDisplay.h"
#include "ManagerGame.h"
#include "ManagerVram.h"
#include "ManagerCharacterActionEvents.h"
#include "UpdategameStatus.h"
#include "MapCommon.h"
#include "ManagerPrinter.h"
#include "ManagerCharacters.h"
#include "CharacterAttackEffects.h"
#include "CharacterCommon.h"

//TODO move this somewhere else
#include "CharacterAlisa.h"

#define DEFAULT_SCREEN_BOUNDING_BOX 0

#define MAX_CHARCOUNT 28
#define MAX_CHARACTIONEVENT 20
	
//TODO: Temporay only
//extern const MapInfo mapsnowfield;
//extern const MapInfo mapforest;
extern const MapInfo mapheighttest;
extern const MapInfo mapdungeonsample;
extern const EventTransfer transfer_mapforest[];
extern const MusicTrack musickankandara_end;
extern const EventTransfer startAt;
extern const EventTransfer startAt_dungeonSample;

inline void waitForVBlank() {
	asm("swi 0x05");
}

void gameloop(MapInfo *mapInfo, CharacterCollection *characterCollection,
 OAMCollection *oamCollection, ControlTypePool *controlPool, ScreenAttr *screenAttribute, 
    CharacterActionCollection *charActionCollection, AttackEffectCollection *attackEffects, Track *track) {
	
	//mapInfo->transferTo =  &mapInfo->tranfers[0];
	//mapInfo->mapFunction = &fadeToBlack;
	mapInfo->screenEffect.processScreenEffect = &mapCommon_goDark;
	setSpriteMasking();
	commonInitShadow();
	while(1) {
		setUpdateGameState(false);
		mprinter_clear();

		//mprinter_printf("action %d\n", charActionCollection->count);
        //mchar_actione_reinit(charActionCollection);
		//quicksort_oam();
		
		if (!mapInfo->transferTo) {
		    mchar_action(characterCollection);
		    mchar_resolveAction(characterCollection, mapInfo, charActionCollection, attackEffects);
		}
		
		screenAttribute->controller(screenAttribute, mapInfo);
		
		commonReverseDisplayShadow();
		mchar_setPosition(characterCollection,
			attackEffects, oamCollection,
			&screenAttribute->position, &screenAttribute->dimension);
			
		charAttackEffect_UpdateAnimation(attackEffects);
		
		mchar_setDraw(characterCollection, attackEffects);
		
		moam_setUpdate(oamCollection);
		
		mscr_setDraw(screenAttribute);
		
		if (mapInfo->mapFunction) {
		    mapInfo->mapFunction(screenAttribute, characterCollection, mapInfo, 
			    controlPool, charActionCollection, track);
		}
		
		mapInfo->screenEffect.processScreenEffect(screenAttribute, characterCollection, 
		    mapInfo, controlPool, charActionCollection, track);

		msound_updateTrack(track);
		msound_mixSound();
		
		setUpdateGameState(true);
		waitForVBlank();
	}
}

void setWaitState() {
	WAITCNT = STDWAIT;
}

int main() {
	CharacterCollection characterCollection;
	OAMCollection oamCollection;
	ControlTypePool controlPool;
	MapInfo mapInfo;
	ScreenAttr screenAttribute;
	CharacterActionCollection charActionCollection;
	AttackEffectCollection *attackEffects;
	CharacterAttr *alisa;
	
	attackEffects = malloc(sizeof(AttackEffectCollection));
	charAttackEffect_Init(attackEffects);
	Track track = {&musickankandara_end,0,0};
	sprite_vram_init_sections();
	sprite_palette_init();
	setWaitState();
	
	mapInfo.screenEffect.processScreenEffect = &mapCommon_defaultEffect;
	
	oamCollection.size = 128;
	oamCollection.previousSize = 0;
	oamCollection.data = malloc(sizeof(OBJ_ATTR)*
		oamCollection.size);
	
	mchar_initControlType(&controlPool);
	
	moam_initBuffer(&oamCollection);
	
	mchar_init(&characterCollection, MAX_CHARCOUNT);
	mchar_initTransferableCharacters(&characterCollection, 1);
	mchar_addTransferableCharacters(&characterCollection, &alisa_init);
	
	mchar_actione_init(&charActionCollection, MAX_CHARACTIONEVENT);
	
	mchar_getPlayerCharacter(&characterCollection, &alisa, &controlPool);
	
	mscr_initCharMoveRef(&screenAttribute, &mapInfo,
		&alisa->position, DEFAULT_SCREEN_BOUNDING_BOX);
	
	//mapInfo.transferTo =  &startAt;
	mapInfo.transferTo =  &startAt_dungeonSample;
	mapCommon_transferToMap(&screenAttribute,  &characterCollection, &mapInfo, &controlPool,
		&charActionCollection, &track);
	
	mgame_setUpdater(&updateGameStatus);
	//Initalize display for 2 backgrounds and 1-d sprites
	initDisplay2BG();
	
	msound_init();
	msound_setUpMono(EMidHighQ);

	mprinter_init();
	gameloop(&mapInfo, &characterCollection, &oamCollection, &controlPool, 
	   &screenAttribute, &charActionCollection, attackEffects, &track);
	
	return 0;
}