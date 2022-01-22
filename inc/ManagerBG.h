#ifndef MANAGER_BG
#define MANAGER_BG
#include "GBAObject.h"

void mbg_init(const ScreenAttr *scrAtt, const MapInfo *mapInfo, CharacterCollection *characterCollection, 
    ControlTypePool* controlPool);
void mbg_setVerticalTiles(MapInfo *mapInfo, u16 mapblock_id, 
	u16 x, u16 y, u16 count);
void mbg_setHorizontalTiles(MapInfo *mapInfo, u16 mapblock_id, 
	u16 x, u16 y, u16 count);
	
ECollisionStatus mbg_checkCollision(MapInfo *mapInfor, CharacterAttr *charAttr);

//extern inline BG_object2Layers* getBackground();
//extern inline CHARACTER_ATTR* getbgReference();
//extern void setReference(CHARACTER_ATTR* ref, BG_object2Layers* bg);
//extern void updateBGPos(u32 spriteDir, SpritePlanePosition* spriteCurrent,
//SpritePlanePosition* spritePrevious);
//extern inline void checkBoundary(SpritePlanePosition* newPos,
//	SpritePlanePosition* currPos);
#endif
