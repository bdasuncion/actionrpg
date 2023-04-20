#include "GBAObject.h"
#include "GBABG.h"
#include "GBADMA.h"
#include "GBACharacterActionEvent.h"
#include "ManagerOAM.h"
#include "ManagerPrinter.h"
#include "UtilCommonValues.h"
#include "CharacterCommon.h"

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

//for test only
/*extern const unsigned short testmap_pal[48];
extern const unsigned int testmap_tiles[2336];
extern const unsigned int testmap_collisionEntry[288];
extern const unsigned short testmap_mapEntry[2][2304];
extern const unsigned int testmap_width;
extern const unsigned int testmap_height;*/

extern const FuncCharacterInit chacterInit[];
//extern const FuncCharacterSet characterSet[];
//end test const

void mbg_checkCollision(
	const MapInfo *mapInfo,
	const CharBoundingBox *charBoundingBox,
	const EDirections direction);

void mbg_init(const ScreenAttr *scrAtt, const MapInfo *mapInfo, CharacterCollection *characterCollection,
    ControlTypePool *controlPool, CharacterActionCollection *charActionCollection) {
	int i, j, currentvramIdx = 1;
	
	for (i = 0; i < mapInfo->palletteCnt; ++i) {
	    dma3_cpy16(PALETTE_MEMORY_BG->data[i], mapInfo->pallette[i], COUNT_PER_PALLETTE);
	}
	
	for (i = 0; i < mapInfo->tileSetCount; ++i) {
		dma3_cpy32(&VRAM->block[0].tile[currentvramIdx],
		    mapInfo->tileSet[i]->tileData, mapInfo->tileSet[i]->size*WORDS_PER_TILE);
		currentvramIdx += mapInfo->tileSet[i]->size;
	}
	
	mbg_initializeMapOnScreen(scrAtt, mapInfo, 
	    &SCR_ENTRY->entry[ETileMap0], &SCR_ENTRY->entry[ETileMap1]);

    mbg_initializeCharacters(mapInfo, characterCollection, controlPool, charActionCollection);

	*REG_BG_CNT0 = BG_PRIO(2)|BG_CBB(0)|BG_SBB(ETileMap0)|BG_SIZE(0);
	*REG_BG_CNT1 = BG_PRIO(3)|BG_CBB(0)|BG_SBB(ETileMap1)|BG_SIZE(0);
}

void mbg_initializeMapOnScreen(const ScreenAttr *scrAtt, const MapInfo *mapInfo, 
    u16 *screntryBG0, u16 *screntryBG1) {
	int i, j, bgIdx, mapIdx, mapStartXIdx = DIVIDE_BY_TILE_WIDTH(scrAtt->position.x);
    int mapStartYIdx = DIVIDE_BY_TILE_HEIGHT(scrAtt->position.y);
	int bgStartXIdx = mapStartXIdx & MAPBLOCK_WIDTH_MAXIDX;
	int bgStartYIdx = mapStartYIdx & MAPBLOCK_HEIGHT_MAXIDX;
	int widthInTiles = DIVIDE_BY_TILE_WIDTH(mapInfo->width);
	
	for(i = 0; i < MAPBLOCK_HEIGHT; ++i) {
		for (j = 0; j < MAPBLOCK_WIDTH; ++j) {
			bgIdx = ((j + bgStartXIdx) & MAPBLOCK_WIDTH_MAXIDX) + 
			    (((bgStartYIdx + i) & MAPBLOCK_WIDTH_MAXIDX)*MAPBLOCK_WIDTH);
			mapIdx = (mapStartXIdx + j) + ((mapStartYIdx + i)*widthInTiles);
			screntryBG0[bgIdx] = mapInfo->mapEntry[0][mapIdx];
			screntryBG1[bgIdx] = mapInfo->mapEntry[1][mapIdx];
		}
	}
}

void mbg_initializeCharacters(const MapInfo *mapInfo, CharacterCollection *characterCollection, 
    ControlTypePool* controlPool, CharacterActionCollection *charActionCollection) {
    int i;
	
	for ( i = 0; i < mapInfo->characterCount; ++characterCollection->currentSize, ++i) {
		CharacterAttr *character = characterCollection->characters[characterCollection->currentSize];
	    chacterInit[mapInfo->characterInit[i].type](character, controlPool);
		commonCharacterSetPosition(character, mapInfo->characterInit[i].x, mapInfo->characterInit[i].y,
		mapInfo->characterInit[i].z, EDown);
		character->doAction(character, mapInfo, characterCollection, charActionCollection);
		character->checkMapCollision(character, mapInfo);
		if (mapInfo->characterInit[i].eventControl) {
		    commonSetCharacterEvent(character, mapInfo->characterInit[i].eventControl);
			character->controller = &commonTriggerCharacterEvent;
		}
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
	
	s32 i,layeridx;
	for (layeridx = 0; layeridx < mapInfo->mapEntryCount; ++layeridx) {
		u16 *mapblock = &SCR_ENTRY->entry[mapblock_id + layeridx];
		for (i = 0; i < count; ++i) {
			mapblock[mapblock_xidx + 
				((mapblock_yidx + i)&MAPBLOCK_HEIGHT_MAXIDX)*
				(mapblock_width)] =
			mapInfo->mapEntry[layeridx]
					[(bg_width_tile_count*(bg_tile_y_idx + i)) + bg_tile_x_idx];
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
	s32 i,layeridx;
	for (layeridx = 0; layeridx < mapInfo->mapEntryCount; ++layeridx) {
		u16 *mapblock = &SCR_ENTRY->entry[mapblock_id + layeridx];
		for (i = 0; i < count; ++i) {
			mapblock[((mapblock_xidx + i)&MAPBLOCK_WIDTH_MAXIDX) +
				(mapblock_yidx*mapblock_width)] =
			mapInfo->mapEntry[layeridx]
					[bg_width_tile_count*(bg_tile_y_idx) + 
					bg_tile_x_idx + i];
		}
	}
}

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
}
//TODO Remove?
void mbg_checkCollision(
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
	
}

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