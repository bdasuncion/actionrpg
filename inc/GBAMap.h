#ifndef GBAMap
#define  GBAMap

#include "GBAObject.h"
#include "GBACharacter.h"
#include "GBACharacterType.h"
#include "GBASound.h"

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

typedef struct TileSet {
    const u32 size:16;
	const u32 compression:2;
	const u32* tileData;
} ALIGN4 TileSet;

typedef struct EventTransfer {
	u16 x;
	u16 y;
	u16 transferToX;
	u16 transferToY;
	u16 transferToZ;
	const void *mapInfo;
	u16 width:8;
	u16 length:8;
	u16 zOffset:8;
	u16 directionOnTransfer:3;
} ALIGN4 EventTransfer;

typedef void (*FuncMap)(void *screenAttribute, void *characterCollection, void *mapInfo, void *controlPool, void *charActionCollection, void *track);

typedef struct CharacterInit {
    u16 x;
	u16 y;
	u16 z;
	CHARACTERTYPE type;
	const CharacterEventControl *eventControl;
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
	u16 tileSetCount:8;
	u16 palletteCnt:4;
	u16 eventTransferCount:6;
	u16 characterCount:7;
	EventTransfer *transferTo;
	const u16 **mapEntry;
	const TileSet **tileSet;
	const u16 **pallette;
	const EventTransfer *tranfers;
	//const MapCollision *collisionMap;
	const u8 *heightMap; 
	const CharacterInit *characterInit;
	FuncMap mapFunction;
	FuncMap onInitMap;
	FuncMap onExitMap;
	const MusicTrack *music;
	ScreenEffect screenEffect;
} ALIGN4 MapInfo;
#endif