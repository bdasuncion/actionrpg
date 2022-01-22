#include <stdlib.h>
#include "GBAObject.h"
#include "GBABG.h"
#include "GBAVideo.h"
#include "GBADMA.h"

//for test only
extern const unsigned short testmap_pal[48];
extern const unsigned int testmap_tiles[2336];
extern const unsigned int testmap_collisionEntry[288];
extern const unsigned short testmap_mapEntry[2][2304];
//extern const unsigned int testmap_width;
//extern const unsigned int testmap_height;

const TileSet genericTileSet = { 292, NO_COMPRESSION, testmap_tiles };
const TileSet *allTiles[] = { &genericTileSet };
const u16 *allPalletes[] = { &testmap_pal[0], &testmap_pal[16], &testmap_pal[32] };
const u16 *mapTestEntry[] = { &testmap_mapEntry[0], &testmap_mapEntry[1]};
extern const MapInfo mapgraveyard;

void test_checkCollision(
	const MapInfo *mapInfo,
	const CharBoundingBox *charBoundingBox,
	const EDirections direction);

const CharacterInit testMapCharacters[] = { {80, 70, GHOSTHAND}, {230, 105, GHOSTHAND}, 
    {110, 140, GHOSTHAND}, {160, 175, GHOSTHAND}, {176, 182, GHOSTHAND}, 
	{160, 245, GHOSTHAND}, {176, 237, GHOSTHAND}, {230, 330, GHOSTHAND} };

const EventTransfer mapTestEvents[] = { { 0, 0, 32, 64, &mapgraveyard, 16, 16, ELeft } };

const MapInfo mapTest = { 384, 384, 2, 1, 3, 1, 8, NULL, mapTestEntry, allTiles, allPalletes, mapTestEvents, NULL, testMapCharacters, NULL };

void map_test_init() {
}

void test_checkCollision(
	const MapInfo *mapInfo,
	const CharBoundingBox *charBoundingBox,
	const EDirections direction){
}