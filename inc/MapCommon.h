#include "GBAObject.h"
#include "GBAMap.h"

#ifndef MapCommon
#define MapCommon
#include "GBACharacterActionEvent.h"

void mapCommon_transferToMap(ScreenAttr *screenAttribute, CharacterCollection *characterCollection, 
MapInfo *mapInfo, ControlTypePool* controlPool, CharacterActionCollection *charActionCollection,
	Track *track);
void fadeToBlack(ScreenAttr *screenAttribute, CharacterCollection *characterCollection, MapInfo *mapInfo);
void returnToScreen(ScreenAttr *screenAttribute, CharacterCollection *characterCollection, MapInfo *mapInfo);
void mapCommon_initFlashScreen(MapInfo *mapInfo);
void mapCommon_defaultEffect(void *screenAttribute, void *characterCollection, MapInfo *mapInfo);
#endif