#include "GBATypes.h"
#include "GBAObject.h"

extern const u32 GBASCREENWIDTH;
extern const u32 GBASCREENHEIGHT;
extern const u32 TOLERANCE_LR;
extern const u32 TOLERANCE_TB;
extern const u32 TOLERANCE_MOVE;
extern const s32 MAPBLOCK;
extern const s32 MAPBLOCKCHK;
extern const s32 HALFMAPBLOCK;
extern const s32 QUARTERMAPBLOCK;
extern const s32 TILEWIDTH;
extern const s32 TILEHEIGHT;
extern const s32 OBJONSCRXMAX;
extern const s32 OBJONSCRYMAX;
extern const s32 SCREENEDGELEFT;
extern const s32 SCREENEDGERIGHT;
extern const s32 SCREENEDGETOP;
extern const s32 SCREENEDGEBOTTOM;
extern const s32 SYMMETRICDIR;
extern const s32 ASYMMETRICDIR;
extern const s32 MAXBITSHIFT;
extern const EDirections directions[8];
extern const u32 h_flipOnDirection[8];
//profiling code
extern s32 timeTotal;
extern s32 sizeTotal;