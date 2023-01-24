#ifndef GBAObjects
#define GBAObjects

#include "GBATypes.h"
#include <stdbool.h>

typedef enum SEARCH_STAT {
	FOUND,
	NOT_FOUND
}SEARCH_STAT;

typedef enum SCREENPOSITION {
	ONSCREEN,
	OFFSCREEN
}SCREENPOSITION;

typedef enum VRAMIDBLOCKSTATUS {
	VRAM_FREE,
	VRAM_TAKEN
} VRAMIDBLOCKSTATUS;

typedef enum PALETTESTATUS {
	PAL_FREE,
	PAL_TAKEN
} PALETTESTATUS;

//typedef enum ACTION
//{
//	STAND,
//	RUN,
//	GOTOSTAND
//}ACTION;

typedef enum BoundingBoxConversionMeasurement {
	EBBCnvrtLength,
	EBBCnvrtWidth,
	EBBCnvrtHeight,
	EBBCnvrtMeasurementCount
}BoundingBoxMeasurement;

typedef enum ScreenConversionMeasurement {
	EScrCnvrtWidth,
	EScrCnvrtHeight,
	EScrCnvrtMeasureCount
}ScreenConversionMeasurement;


typedef enum ECollisionStatus
{
	ECollide,
	ENoCollide
}ECollisionStatus;

typedef enum TYPE
{
	CHAR_PLAYER,
	AI_ALLY,
	AI_ENEMY
}TYPE;

typedef enum EDirections {
	EUnknown = -1,
	EDown,
	EDownright,
	ERight,
	EUpright,
	EUp,
	EUpleft,
	ELeft,
	EDownleft,
	EDirectionsMax = EDownleft,
	EDirectionsCount
}EDirections;

typedef enum EButtons {
	EButtonUnknown = -1,
	EButtonB,
	EButtonA,
	EButtonL,
	EButtonR,
	EButtonSelect,
	EButtonStart,
	EButtonsCount
}EButtons;

typedef enum RANGE {
	TOOFAR = -1,
	OUTOFRANGE,
	INRANGE
}RANGE;

typedef enum STATS {
	COLLISIONLENGTH,
	COLLISIONWIDTH,
	FULLLENGTH,
	FULLWIDTH,
	FULLHEIGHT
}STATS;

typedef enum SPRITESIZE {
	SMALL_A,//8x16, 16x8
	SMALL_B,//8x32, 32x8
	MEDIUM,//16x32, 32x16
	LARGE, //32x64, 64x32
	SPRITESIZE_COUNT
}SPRITESIZE;

typedef enum SPRITESHAPE {
	SQUARE,
	WIDE,
	TALL,
	SPRITESHAPE_COUNT
}SPRITESHAPE;

typedef enum VERTICALFLIP {
	NO_VFLIP,
	DO_VFLIP
}VERTICALFLIP;

typedef enum HORIZONTALFLIP {
	NO_HFLIP,
	DO_HFLIP
}HORIZONTALFLIP;

typedef enum COMPRESSION_TYPE {
	NO_COMPRESSION,
	LZSS_COMPRESSION
}COMPRESSION_TYPE;

typedef enum CONTROLTYPE {
	AI,
	PLAYER
}CONTROLTYPE;

typedef struct OBJ_ATT0 {
	u16 yCoordinate:8;
	u16 objectMode:2;
	u16 renderMode:2;
	u16 mosaic:1;
	u16 colorMode:1;
	u16 shape:2;
}ALIGN2 OBJ_ATT0;

typedef struct OBJ_ATT1
{
	u16 xCoordinate:9;
	u16 padding:3;
	u16 horizontalFlip:1;
	u16 verticalFlip:1;
	u16 size:2;
}ALIGN2 OBJ_ATT1;

typedef struct OBJ_ATT1_AFF {
	u16 xCoordinate:9;
	u16 affineIndex:5;
	u16 size:2;
}ALIGN2 OBJ_ATT1_AFF;

typedef struct OBJ_ATT2 {
	u16 tileIndex:10;
	u16 drawPriority:2;
	u16 paletteBank:4;
}ALIGN2 OBJ_ATT2;

typedef struct STRUCT_OBJ_ATT {
	OBJ_ATT0 att0;
	OBJ_ATT1 att1;
	OBJ_ATT2 att2;
	s16 fill;
}ALIGN4 STRUCT_OBJ_ATT;

typedef struct OBJ_ATTR {
	u16 attr0;
	u16 attr1;
	u16 attr2;
	s16 fill;
}ALIGN4 OBJ_ATTR;

typedef struct OBJ_AFFINE
{
    u16 fill0[3];
    s16 pa;
    u16 fill1[3];
    s16 pb;
    u16 fill2[3];
    s16 pc;
    u16 fill3[3];
    s16 pd;
}ALIGN4 OBJ_AFFINE;

typedef struct Position {
	s32 x;
	s32 y;
	s32 z;
} ALIGN4 Position;

typedef struct ScreenPosition {
	u16 x;
	u16 y;
}ALIGN4 ScreenPosition;

typedef struct ScreenDimension {
	u16 width;
	u16 height;
} ScreenDimension;

typedef struct OAMCollection {
	u32 size:8;
	u32 previousSize:8;
	OBJ_ATTR *data;
}ALIGN4 OAMCollection;

typedef struct BoundingBox {
	s16 startX;
	s16 startY;
	s16 endX;
	s16 endY;
	s16 startZ;
	s16 endZ;
	u8 direction:3;
	u8 dummy:3;
	bool isMoving:1;
	bool isMovable:1;
}ALIGN4 BoundingBox;

typedef struct OffsetPoints {
    s16 x;
	s16 y;
}ALIGN4  OffsetPoints;
typedef struct Control {
    CONTROLTYPE type:1;
} Control;

typedef struct PlayerControl {
    CONTROLTYPE type:1;
	u8 currentFrame;
}ALIGN4 PlayerControl;

typedef struct VramIdControl {
	u16 id;
	VRAMIDBLOCKSTATUS status:1;
}ALIGN4 VramIdControl;

typedef struct ActionCharacters {
    u32 action:8;
    u32 doActionForNFrames:24;
}ALIGN4 ActionCharacters;

typedef struct ScreenBoundingBox {
	u16 offset_x;
	u16 offset_y;
	u16 width;
	u16 height;
} ScreenBoundingBox;

typedef void (*BgCollisionCheck)(const void *mapInfo, 
	const void *CharBoundingBox, int direction);

typedef enum EventType {
    EEventTransfer,
	EEventAction
} EventType;

typedef enum EventTriggerType {
    ETriggerAuto,
	ETriggerButton
} EventTriggerType ;

typedef void (*EventFunc)(void *character, void *mapInfo);

/*typedef union Event {
  EventType type;
  EventTriggerType trigger;
  EventBase base;
  EventTransfer transfer;
} ALIGN4 Event;*/

typedef struct EventBase {	
	EventType type;
	EventTriggerType trigger;
	u16 width:6;
	u16 height:6;
	u16 x;
	u16 y;
} EventBase;

typedef void (*ScreenFunc)(void* scrAtt, void *mapInfo);

typedef struct ScreenAttr
{
	ScreenFunc controller;
	void *moveReference;
	ScreenBoundingBox moveRefBox;
	Position position;
	ScreenDimension dimension;
}ScreenAttr;

//full* variables used to convert from game world postion to screen postion
//collision* variables used for collision with other objects and background
typedef struct CHARACTER_STATS
{
	s32 collisionLength;
	s32 collisionWidth;
	s32 fullLength;
	s32 fullWidth;
	s32 fullHeight;
}ALIGN4 CHARACTER_STATS;

typedef struct WINDOWSPRITE
{
	OBJ_ATTR OAM;
	u32 sprite_id;
//	SpritePlanePosition *reference_pos;
}ALIGN4 WINDOWSPRITE;

typedef struct BG_object2Layers
{
	u16 CNT0;
	u16 CNT1;	
	u16 CNT2;
	u16 CNT3;
	u16 H0;
	u16 V0;
	u16 H1;
	u16 V1;
	u16 H2;
	u16 V2;
	u16 H3;
	u16 V3;
	u16 *BG0;
	u16 *BG1;
	s32 xChange;
	s32 yChange;
	u32 xScroll_MAX;
	u32 yScroll_MAX;
	//pointer to collision background data
	u32 *collision;
	//number of collision entries with respect to the BG width
	u32 collisionWidth;
	//width and height measured in tiles
	u32 width;
	u32 height;
	//used for checking previous screen movement
	//0 = no movement 1 = left/up 2 = right/down
	u32 left_right;
	u32	up_down;
//	SpritePlanePosition prevPos;
}ALIGN4 BG_object2Layers;

#define ATTR0_Y(n)			(n)
#define ATTR0_SPRITE_REG	0
#define ATTR0_SPRITE_AFF	(1<<8)
#define ATTR0_SPRITE_HIDE	(2<<8)
#define	ATTR0_SPRITE_DBL	(3<<8)
#define ATTR0_BLEND			(1<<10)
#define ATTR0_WIN			(2<<10)
#define ATTR0_MOSAIC		BIT12
#define	ATTR0_4BPP			0
#define ATTR0_8BPP			BIT13
#define	ATTR0_SQUARE		0
#define	ATTR0_WIDE			(1<<14)
#define	ATTR0_TALL			(2<<14)
#define	ATTR0_SHAPE(n)		(n<<14)

#define ATTR0_SET(yPos, shape) (ATTR0_Y(yPos) | ATTR0_SHAPE(shape) | ATTR0_BLEND)

#define ATTR0_SETASWINOBJ(yPos, shape) (ATTR0_Y(yPos) | ATTR0_SHAPE(shape) | ATTR0_WIN)

#define ATTR1_X(n)          (n)
#define ATTR1_AFF(n)		(n<<9)
#define	ATTR1_HFLIP			BITC
#define	ATTR1_VFLIP			BITD
#define	ATTR1_SETHFLIP(n)		(n<<12)
#define	ATTR1_SETVFLIP(n)		(n<<13)
#define	ATTR1_SIZE(n)		(n<<14)


#define ATTR1_SET(xPos, size, hflip, vflip) ( ATTR1_X(xPos) | ATTR1_SIZE(size) | ATTR1_SETHFLIP(hflip) | ATTR1_SETVFLIP(vflip) )

#define	ATTR2_ID(n)			(n)
#define	ATTR2_PRIO(n)		(n<<10)
#define	ATTR2_PAL(n)		(n<<12)
#define ATTR2_SET(spriteid, palleteid, priority)     ( ATTR2_ID(spriteid) | ATTR2_PRIO(priority) | ATTR2_PAL(palleteid) )	

#define ARM_IWRAM __attribute__((noinline, target("arm"), section(".iwram"), long_call))
#endif
