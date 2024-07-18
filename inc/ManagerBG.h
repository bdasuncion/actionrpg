#ifndef MANAGER_BG
#define MANAGER_BG
#include "GBAObject.h"
#include "GBAMap.h"
#include "GBACharacterActionEvent.h"

void mbg_init(const ScreenAttr *scrAtt, const MapInfo *mapInfo, CharacterCollection *characterCollection, 
    ControlTypePool* controlPool, CharacterActionCollection *charActionCollection);
void mbg_setVerticalTiles(const MapInfo *mapInfo, u16 mapblock_id, 
	u16 x, u16 y, u16 count);
void mbg_setHorizontalTiles(const MapInfo *mapInfo, u16 mapblock_id, 
	u16 x, u16 y, u16 count);
	
//ECollisionStatus mbg_checkCollision(MapInfo *mapInfor, CharacterAttr *charAttr);
void mbg_initializeMapOnScreen(const ScreenAttr *scrAtt, const MapInfo *mapInfo, 
    u16 *screntryBG0, u16 *screntryBG1);
void mbg_initializeCharacters(const MapInfo *mapInfo, CharacterCollection *characterCollection, 
    ControlTypePool* controlPool, CharacterActionCollection *charActionCollection);
//extern inline BG_object2Layers* getBackground();
//extern inline CHARACTER_ATTR* getbgReference();
//extern void setReference(CHARACTER_ATTR* ref, BG_object2Layers* bg);
//extern void updateBGPos(u32 spriteDir, SpritePlanePosition* spriteCurrent,
//SpritePlanePosition* spritePrevious);
//extern inline void checkBoundary(SpritePlanePosition* newPos,
//	SpritePlanePosition* currPos);
#endif
