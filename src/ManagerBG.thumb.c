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
		for (j = 0; j < MAPBLOCK_WIDTH; ++j) {
			bgIdx = ((j + bgStartXIdx) & MAPBLOCK_WIDTH_MAXIDX) + 
			    (((bgStartYIdx + i) & MAPBLOCK_WIDTH_MAXIDX)*MAPBLOCK_WIDTH);
			mapIdx = (mapStartXIdx + j) + ((mapStartYIdx + i)*widthInTiles);
			mapIdx2 = mapIdx + widthInTiles*DIVIDE_BY_TILE_HEIGHT(mapInfo->height);
			screntryBG0[bgIdx] = mapInfo->mapEntry[0][mapIdx];
			screntryBG1[bgIdx] = mapInfo->mapEntry[0][mapIdx2];
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
	
	s32 i,layeridx;
	
	for (layeridx = 0; layeridx < mapInfo->mapEntryCount; ++layeridx) {
		u16 *mapblock = (u16*)&SCR_ENTRY->entry[mapblock_id + layeridx];
		for (i = 0; i < count; ++i) {
			mapblock[mapblock_xidx + 
				((mapblock_yidx + i)&MAPBLOCK_HEIGHT_MAXIDX)*
				(mapblock_width)] =
			mapInfo->mapEntry[0]
					[(layeridx*layeroffset) + (bg_width_tile_count*(bg_tile_y_idx + i)) + bg_tile_x_idx];
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
	
	for (layeridx = 0; layeridx < mapInfo->mapEntryCount; ++layeridx) {
		u16 *mapblock = (u16*)&SCR_ENTRY->entry[mapblock_id + layeridx];
		for (i = 0; i < count; ++i) {
			mapblock[((mapblock_xidx + i)&MAPBLOCK_WIDTH_MAXIDX) +
				(mapblock_yidx*mapblock_width)] =
			mapInfo->mapEntry[0]
					[(layeridx*layeroffset) + bg_width_tile_count*(bg_tile_y_idx) + 
					bg_tile_x_idx + i];
		}
	}
}
/*
ECollisionStatus mbg_checkBoundary(
	const MapInfo *mapInfo,
	const CharacterAttr *charAttr)
{
	int boundBoxCount = 0, i = 0;
	CharBoundingBox boundingBox[3];
	mapInfo->width;
	mapInfo->height;
	//mapInfo->collisionTable;
	charAttr->getBounds(charAttr, &boundBoxCount, boundingBox);
	
	return ENoCollide;
}*/
//TODO Remove?
/*void mbg_checkCollision(
	const MapInfo *mapInfo,
	const CharBoundingBox *charBoundingBox,
	const EDirections direction)
{
	Position point;
	int collisionValueOnPosition;
	
	if (direction == ERight) {
		int i;
		int total = DIVIDE_BY_8(charBoundingBox->width);
		int x_move = 0;
		point.x = charBoundingBox->upperLeftPt.x + charBoundingBox->length;
		point.y = charBoundingBox->upperLeftPt.y;

		for (i = 0; i < total; ++i) {
			point.y += i*TILE_HEIGHT;
			mbg_collisionAtPosition(mapInfo, &point, &collisionValueOnPosition);
			if (collisionValueOnPosition) {
				GET_REMAINDER_8(charBoundingBox->upperLeftPt.x);
			}
		}
	}
	//mbg_collisionAtPosition(mapInfo, &centerPt, &collisionValueOnPosition);
	
})*/

#define BITS_PER_COLLISION_ENTRY 4
/*/8 bits per entry
#define TILE_IDX(x) (DIVIDE_BY_8(GET_REMAINDER_16(x)))
#define GET_COLLISION_FROM_ENTRY(entry, xpos)\
 ((entry >> (TILE_IDX(xpos)*BITS_PER_COLLISION_ENTRY))&0xF)
#define DIVIDE_BY_TILES_PER_ENTRY(x) DIVIDE_BY_2(x)
//*/

//*/32 bits per entry
//Thanks to the weird way I built my collision table,
//we need to complement the tile idx. Visually, the table makes sense
//to a person but not to a computer.
//This should e fixed in the map tool
#define TILE_IDX(x) ((~DIVIDE_BY_8(GET_REMAINDER_64(x)))&0x7)
#define GET_COLLISION_FROM_ENTRY(entry, xpos)\
 ((entry >> (TILE_IDX(xpos)*BITS_PER_COLLISION_ENTRY))&0xF)
#define DIVIDE_BY_TILES_PER_ENTRY(x) DIVIDE_BY_8(x)
//*/


void mbg_collisionAtPosition(const MapInfo *mapInfo, 
	const Position * position, int *collisionValueOnPosition) {
	u32 arrayWidth = 
		DIVIDE_BY_TILES_PER_ENTRY(DIVIDE_BY_TILE_WIDTH(mapInfo->width));
	u32 horizontalIdx = 
		DIVIDE_BY_TILES_PER_ENTRY(DIVIDE_BY_TILE_WIDTH(position->x));
	u32 verticaloffsetIdx = 
		DIVIDE_BY_TILE_HEIGHT(position->y)*arrayWidth;
}