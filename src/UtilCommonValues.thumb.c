#include "GBATypes.h"
#include "GBAObject.h"

//should be converted to defines
const u32 GBASCREENWIDTH = 240;
const u32 GBASCREENHEIGHT = 160;
const u32 TOLERANCE_LR = 64;
const u32 TOLERANCE_TB = 40;
const u32 TOLERANCE_MOVE = 10;
const s32 MAPBLOCK = 256;
const s32 MAPBLOCKCHK = 255;
const s32 HALFMAPBLOCK = 128;
const s32 QUARTERMAPBLOCK = 64;
const s32 TILEWIDTH = 8;
const s32 TILEHEIGHT = 8;
const s32 OBJONSCRXMAX = 511;
const s32 OBJONSCRYMAX = 255;
const s32 SCREENEDGELEFT = 5;
const s32 SCREENEDGERIGHT = 235;
const s32 SCREENEDGETOP = 5;
const s32 SCREENEDGEBOTTOM = 155;
const s32 SYMMETRICDIR = 5;
const s32 ASYMMETRICDIR = 8;
//for profiling code
s32 timeTotal = 0;
s32 sizeTotal = 0;

const EDirections dir_from_key[16] = 
{
	EUnknown,ERight,ELeft,EUnknown,
	EUp,EUpright,EUpleft,EUnknown,
	EDown,EDownright,EDownleft,EUnknown,
	EUnknown,EUnknown,EUnknown,EUnknown
};

//32 bits - 4bits = 28
//maximum shift allowable to get 4 bit values from 32 bit variable
const s32 MAXBITSHIFT = 28;

const EDirections directions[8] = {EDown,EDownright,ERight,EUpright,
	EUp,EUpright,ERight,EDownright};
//const DIRECTION directionsAS[8] = {DOWN,DOWNRIGHT,RIGHT,UPRIGHT,UP,UPLEFT,LEFT,DOWNLEFT};
const u32 h_flipOnDirection[8] = {0,0,0,0,0,ATTR1_HFLIP,ATTR1_HFLIP,ATTR1_HFLIP};
