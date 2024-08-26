#ifndef MANAGER_SCR_DISPLAY
#define MANAGER_SCR_DISPLAY

#include "GBATypes.h"
#include "GBAVideo.h"
#include "GBAObject.h"
#include "GBAMap.h"
#include "GBABG.h"

void initDisplay2BG();
void mscr_initCharMoveRef(ScreenAttr *scrAtt, const MapInfo *mapInfo,
	Position *moveReference, ScreenBoundingBox *moveRefCustomBox);
void mscr_initPosMoveRef(ScreenAttr *scrAtt, 
	Position *reference);
void mscr_moveScr(ScreenAttr *scrAtt, MapInfo *mapInfo);
void mscr_setDraw(ScreenAttr *scrAtt);
void mscr_draw();
void mscr_adjustScreenToMapLimits(ScreenAttr *scrAtt, const MapInfo *mapInfo);
//Transfer to ManagerGameStatus
void mscr_setUpdater(fnptr functionUpdater);

	
void initWindowObj();
void removeWindowObj();

#endif