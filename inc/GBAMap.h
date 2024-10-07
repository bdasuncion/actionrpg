#ifndef GBAMap
#define  GBAMap

#include "GBAStructDeclarations.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "GBASound.h"
#include "CharacterSpriteMask.h"

typedef enum MAPID {
    MapNoneID,
    MapTestID
} MAPID;

typedef enum COLLISIONTYPE {
	TYPE_SOLID,
	TYPE_CHANGE_LAYER
}COLLISIONTYPE;

typedef struct MapCollision {
    u16 x:3;
	u16 y:3;
	u16 type:2;
	u16 width:4;
	u16 height:4;
} ALIGN2 MapCollision;

typedef struct HeightCollision {
    u8 type:2;
	u8 height:6;
} HeightCollision;

typedef struct TileSet {
    const u32 size:16;
	const u32 compression:2;
	const u32* tileData;
} ALIGN4 TileSet;

typedef struct VramSet {
	const u32* tileData;
	const u32 index;
} ALIGN4 VramSet;

typedef struct EventTransfer {
	u16 x;
	u16 y;
	u16 transferToX;
	u16 transferToY;
	u16 transferToZ;
	//const void *mapInfo;
	const struct MapInfo *mapInfo;
	u16 width:8;
	u16 length:8;
	u16 zOffset:8;
	u16 directionOnTransfer:3;
} ALIGN4 EventTransfer;

//typedef void (*FuncMap)(void *screenAttribute, void *characterCollection, void *mapInfo, void *controlPool, void *charActionCollection, void *track);
typedef void (*FuncMap)(struct ScreenAttr *screenAttribute, struct CharacterCollection *characterCollection, 
	struct MapInfo *mapInfo, struct ControlTypePool* controlPool, struct CharacterActionCollection *charActionCollection, 
	struct Track *track);
typedef struct CharacterInit {
    u16 x;
	u16 y;
	u16 z;
	CHARACTERTYPE type;
	const struct CharacterEventControl *eventControl;
} CharacterInit;

typedef struct ScreenEffect {
	u32 durationFrames:8;
	u32 currentFrame:8;
	u32 type:8;
	u32 dummy:8;
	FuncMap processScreenEffect;
}ALIGN4 ScreenEffect;

typedef struct MapInfo {
	u16 width;
	u16 height;
	u16 mapEntryCount:2;
	//u16 tileSetCount:8;
	u16 tilesCount:10;
	u16 palletteCnt:4;
	u16 eventTransferCount:5;
	u16 characterCount:6;
	u16 spriteMaskCount:5;
	u16 spriteMaskImageCount:6;
	EventTransfer *transferTo;
	const u16 **mapEntry;
	//const TileSet **tileSet;
	const u32 **tiles;
	const u16 **pallette;
	const EventTransfer *tranfers;
	//const u8 *heightMap;
	const HeightCollision *heightMap; 
	const CharacterInit *characterInit;
	const SpriteMaskInit *spriteMaskInit;
	const SpriteMaskImage *spriteMaskImage;
	FuncMap mapFunction;
	FuncMap onInitMap;
	FuncMap onExitMap;
	const MusicTrack *music;
	ScreenEffect screenEffect;
} ALIGN4 MapInfo;
#endif