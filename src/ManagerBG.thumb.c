#include<string.h>
#include<stdio.h>
#include "DebugLogMgba.h"


#include "GBAObject.h"
#include "GBABG.h"
#include "GBADMA.h"
#include "GBACharacterActionEvent.h"
#include "ManagerOAM.h"
#include "ManagerPrinter.h"
#include "ManagerBG.h"
#include "ManagerVram.h"
#include "UtilCommonValues.h"
#include "CharacterCommon.h"
#include "CharacterSpriteMask.h"


#define MAP_BLOCK_WIDTH 256
#define MAP_BLOCK_HEIGHT 256
#define MAPBLOCK_WIDTH_TILE_COUNT DIVIDE_BY_TILE_WIDTH(MAP_BLOCK_WIDTH)
#define MAPBLOCK_HEIGHT_TILE_COUNT DIVIDE_BY_TILE_HEIGHT(MAP_BLOCK_HEIGHT);
#define MAPBLOCK_WIDTH_MAXIDX 31
#define MAPBLOCK_HEIGHT_MAXIDX 31
#define TILE_WIDTH 8
#define TILE_HEIGHT 8
#define COUNT_PER_PALLETTE 16
#define WORDS_PER_TILE 8

#define MAPBLOCK_WIDTH 32
#define MAPBLOCK_HEIGHT 32

/*void mbg_checkCollision(
	const MapInfo *mapInfo,
	const CharBoundingBox *charBoundingBox,
	const EDirections direction);
*/	
void mbg_copySpriteMaskImageToVram(const MapInfo *mapInfo);
void mbg_initializeSpriteMasks(const MapInfo *mapInfo, CharacterCollection *characterCollection);

void mbg_init(const ScreenAttr *scrAtt, const MapInfo *mapInfo, CharacterCollection *characterCollection,
    ControlTypePool *controlPool, CharacterActionCollection *charActionCollection) {
	int i, j, currentvramIdx = 1;
	
	for (i = 0; i < mapInfo->palletteCnt; ++i) {
	    dma3_cpy16(PALETTE_MEMORY_BG->data[i], mapInfo->pallette[i], COUNT_PER_PALLETTE);
	}
	
	/*for (i = 0; i < mapInfo->tileSetCount; ++i) {
		dma3_cpy32(&VRAM->block[0].tile[currentvramIdx],
		    mapInfo->tileSet[i]->tileData, mapInfo->tileSet[i]->size*WORDS_PER_TILE);
		currentvramIdx += mapInfo->tileSet[i]->size;
	}*/
	
	for (i = 0; i < mapInfo->tilesCount; ++i) {
		dma3_cpy32(&VRAM->block[0].tile[currentvramIdx],
		    mapInfo->tiles[i], WORDS_PER_TILE);
		currentvramIdx += 1;
	}
	
	mbg_initializeMapOnScreen(scrAtt, mapInfo, 
	    (u16*)&SCR_ENTRY->entry[ETileMap0], (u16*)&SCR_ENTRY->entry[ETileMap1]);

    mbg_initializeCharacters(mapInfo, characterCollection, controlPool, charActionCollection);
	mbg_copySpriteMaskImageToVram(mapInfo);
	mbg_initializeSpriteMasks(mapInfo, characterCollection);

	*REG_BG_CNT0 = BG_PRIO(2)|BG_CBB(0)|BG_SBB(ETileMap0)|BG_SIZE(0);
	*REG_BG_CNT1 = BG_PRIO(3)|BG_CBB(0)|BG_SBB(ETileMap1)|BG_SIZE(0);
}

void mbg_initializeMapOnScreen(const ScreenAttr *scrAtt, const MapInfo *mapInfo, 
    u16 *screntryBG0, u16 *screntryBG1) {
	int i, j, bgIdx, mapIdx, mapIdx2, mapStartXIdx = DIVIDE_BY_TILE_WIDTH(scrAtt->position.x);
    int mapStartYIdx = DIVIDE_BY_TILE_HEIGHT(scrAtt->position.y);
	int bgStartXIdx = mapStartXIdx & MAPBLOCK_WIDTH_MAXIDX;
	int bgStartYIdx = mapStartYIdx & MAPBLOCK_HEIGHT_MAXIDX;
	int widthInTiles = DIVIDE_BY_TILE_WIDTH(mapInfo->width);
	
	for(i = 0; i < MAPBLOCK_HEIGHT; ++i) {
		mgba_log("\n", 1);
		for (j = 0; j < MAPBLOCK_WIDTH; ++j) {
			int xIdx = mapStartXIdx + j;
			int yIdx = mapStartYIdx + i;
			
			bgIdx = ((j + bgStartXIdx) & MAPBLOCK_WIDTH_MAXIDX) + 
			    (((bgStartYIdx + i) & MAPBLOCK_WIDTH_MAXIDX)*MAPBLOCK_WIDTH);
			if (xIdx >= 0 && xIdx < DIVIDE_BY_TILE_WIDTH(mapInfo->width) && 
				yIdx >= 0 && yIdx < DIVIDE_BY_TILE_HEIGHT(mapInfo->height)) {
				
				mapIdx = xIdx + (yIdx*widthInTiles);
				mapIdx2 = mapIdx + widthInTiles*DIVIDE_BY_TILE_HEIGHT(mapInfo->height);
				screntryBG0[bgIdx] = mapInfo->mapEntry[0][mapIdx];
				screntryBG1[bgIdx] = mapInfo->mapEntry[0][mapIdx2];
			} else {
				screntryBG0[bgIdx] = 0;
				screntryBG1[bgIdx] = 0;
			}
		}
	}
}

void mbg_initializeCharacters(const MapInfo *mapInfo, CharacterCollection *characterCollection, 
    ControlTypePool* controlPool, CharacterActionCollection *charActionCollection) {
    int i;
	
	for ( i = 0; i < mapInfo->characterCount; ++characterCollection->currentSize, ++characterCollection->displaySize,++i) {
		CharacterAttr *character = characterCollection->charactersForDisplay[characterCollection->displaySize];
	    
		Position position = {mapInfo->characterInit[i].x, mapInfo->characterInit[i].y, mapInfo->characterInit[i].z};
		commonSetCharType(&position, mapInfo, mapInfo->characterInit[i].type, characterCollection, 
			charActionCollection, character, controlPool, mapInfo->characterInit[i].charWaypoints);
		characterCollection->characters[characterCollection->currentSize] = character;
		//if (mapInfo->characterInit[i].eventControl) {
		//    commonSetCharacterEvent(character, mapInfo->characterInit[i].eventControl);
		//	character->controller = &commonTriggerCharacterEvent;
		//}
	}
}

extern const unsigned int spritemask_standard_image0[];

void mbg_copySpriteMaskImageToVram(const MapInfo *mapInfo) {
	int i, id = 16;
	spritemask_vram_copy32_ID(spritemask_standard_image0, 
			spriteMaskImageSize[EMask32x32], 0);
			
	for ( i = 0; i < mapInfo->spriteMaskImageCount; ++i) {
		spritemask_vram_copy32_ID(mapInfo->spriteMaskImage[i].image, 
			spriteMaskImageSize[mapInfo->spriteMaskImage[i].type], id);
		id += spriteMaskImageSize[mapInfo->spriteMaskImage[i].type] >> 3;
	}
}

void mbg_initializeSpriteMasks(const MapInfo *mapInfo, CharacterCollection *characterCollection) {
    int i;
	
	for ( i = 0; i < mapInfo->spriteMaskCount; ++characterCollection->displaySize,++i) {
		CharacterAttr *character = characterCollection->charactersForDisplay[characterCollection->displaySize];
		spritemask_init(character, &mapInfo->spriteMaskInit[i]);
	}
}

void mbg_setVerticalTiles(const MapInfo *mapInfo, 
	u16 mapblock_id, 
	u16 x,
	u16 y,
	u16 count)
{
	u16 bg_tile_x_idx = DIVIDE_BY_TILE_WIDTH(x);
	u16 bg_tile_y_idx = DIVIDE_BY_TILE_HEIGHT(y);
	
	u16 mapblock_width = MAPBLOCK_WIDTH_TILE_COUNT;
	u16 mapblock_height = MAPBLOCK_HEIGHT_TILE_COUNT;
	u16 mapblock_xidx = bg_tile_x_idx & MAPBLOCK_WIDTH_MAXIDX;
	u16 mapblock_yidx = bg_tile_y_idx & MAPBLOCK_HEIGHT_MAXIDX;
	u16 bg_width_tile_count = DIVIDE_BY_TILE_WIDTH(mapInfo->width);
	u16 layeroffset = DIVIDE_BY_TILE_HEIGHT(mapInfo->height)*bg_width_tile_count;
	
	s16 limit = DIVIDE_BY_TILE_HEIGHT(mapInfo->height);
	s16 xS = x;
	
	s32 i,layeridx;

	for (layeridx = 0; layeridx < mapInfo->mapEntryCount; ++layeridx) {
		u16 *mapblock = (u16*)&SCR_ENTRY->entry[mapblock_id + layeridx];
		s16 yCheck = y;
		yCheck = DIVIDE_BY_TILE_HEIGHT(yCheck);
		for (i = 0; i < count; ++i) {
			if (yCheck >= 0 && yCheck < limit && x < mapInfo->width) {
				mapblock[mapblock_xidx + 
					((mapblock_yidx + i)&MAPBLOCK_HEIGHT_MAXIDX)*
					(mapblock_width)] =
				mapInfo->mapEntry[0]
						[(layeridx*layeroffset) + (bg_width_tile_count*(yCheck)) + bg_tile_x_idx];
			} else {
				mapblock[mapblock_xidx + 
					((mapblock_yidx + i)&MAPBLOCK_HEIGHT_MAXIDX)*
					(mapblock_width)] = 0;
			}
			++yCheck;
		}
	}
}

void mbg_setHorizontalTiles(const MapInfo *mapInfo, 
	u16 mapblock_id, 
	u16 x,
	u16 y,
	u16 count)
{	
	u16 bg_tile_x_idx = DIVIDE_BY_TILE_WIDTH(x);
	u16 bg_tile_y_idx = DIVIDE_BY_TILE_HEIGHT(y);
	
	u16 mapblock_width = MAPBLOCK_WIDTH_TILE_COUNT;
	u16 mapblock_height = MAPBLOCK_HEIGHT_TILE_COUNT;
	u16 mapblock_xidx = bg_tile_x_idx & MAPBLOCK_WIDTH_MAXIDX;
	u16 mapblock_yidx = bg_tile_y_idx & MAPBLOCK_HEIGHT_MAXIDX;
	u16 bg_width_tile_count = DIVIDE_BY_TILE_WIDTH(mapInfo->width);
	u16 layeroffset = DIVIDE_BY_TILE_HEIGHT(mapInfo->height)*bg_width_tile_count;
	s32 i,layeridx;
	
	s16 limit = DIVIDE_BY_TILE_WIDTH(mapInfo->width);
	s16 yS = y;
	
	bool doprint = true;
	bool doprint2 = true;
	for (layeridx = 0; layeridx < mapInfo->mapEntryCount; ++layeridx) {
		u16 *mapblock = (u16*)&SCR_ENTRY->entry[mapblock_id + layeridx];
		s16 xCheck = x;
		xCheck = DIVIDE_BY_TILE_WIDTH(xCheck);
		//if (doprint) {
		//	mprinter_printf("y:%d mapHeight:%d\n", y, mapInfo->height);
		//	doprint = false;
		//}
		
		for (i = 0; i < count; ++i) {
			//mprinter_printf("xCheck:%d y:%d ", xCheck, y);
			//mprinter_printf("xCheck: y: ");
			if (xCheck >= 0 && xCheck < limit && y < mapInfo->height) {
				//if (doprint2) {
				//	mprinter_printf("y");
				//}
				mapblock[((mapblock_xidx + i)&MAPBLOCK_WIDTH_MAXIDX) +
					(mapblock_yidx*mapblock_width)] =
				mapInfo->mapEntry[0]
						[(layeridx*layeroffset) + bg_width_tile_count*(bg_tile_y_idx) + xCheck];
			} else {
				mapblock[((mapblock_xidx + i)&MAPBLOCK_WIDTH_MAXIDX) +
					(mapblock_yidx*mapblock_width)] = 0;
			}
			++xCheck;
		}
		doprint2 = false;
	}
}