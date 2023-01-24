#include <stdlib.h>
#include "GBATypes.h"
#include "GBAVideo.h"
#include "GBAObject.h"
#include "GBABG.h"
#include "GBAMap.h"

#include "GBAInterrupt.h"
#include "ManagerBG.h"

#define OFFSET_X 100
#define OFFSET_Y 60
//#define OFFSET_Y 160
#define BOUND_LENGTH 40
//#define BOUND_HEIGHT 40
#define BOUND_HEIGHT 40
#define X_MOVE_LIMIT 8
#define Y_MOVE_LIMIT 8
#define SCR_VERTICAL_TILE_COUNT 20
#define SCR_HORIZONTAL_TILE_COUNT 30

ScreenAttr *mscr_vscrRef = NULL;

const ScreenBoundingBox default_scrBoundingBox = {
	OFFSET_X, OFFSET_Y, BOUND_LENGTH, BOUND_HEIGHT
};

void mscr_moveScr(ScreenAttr *scrAtt, MapInfo *mapInfo);
void mscr_checkMoveLeft(ScreenAttr *scrAtt, u16 x,
	s32 left_max);
void mscr_checkMoveRight(ScreenAttr *scrAtt, u16 x,
	s32 right_max);
void mscr_checkMoveUp(ScreenAttr *scrAtt, u16 y,
	s32 up_max);
void mscr_checkMoveDown(ScreenAttr *scrAtt, u16 y,
	s32 down_max);
void mscr_setHorizontalMove(ScreenAttr *scrAtt,
	MapInfo *mapInfo, u16 startXPos);
void mscr_setVerticalMove(ScreenAttr *scrAtt,
	MapInfo *mapInfo,
	u16 startYPos);

void initDisplay2BG(){
	*REG_DISPCNT = DCNT_MODE0|DCNT_OBJ_1D|DCNT_OBJENB|DCNT_BG0|DCNT_BG1|DCNT_BG2;
}

void mscr_initCharMoveRef(ScreenAttr *scrAtt, const MapInfo *mapInfo,
	Position *moveReference, ScreenBoundingBox *moveRefCustomBox) {
	
	scrAtt->position.x = CONVERT_2POS(moveReference->x) - DIVIDE_BY_2(GBA_SCREEN_WIDTH);
	scrAtt->position.y = CONVERT_2POS(moveReference->y) - DIVIDE_BY_2(GBA_SCREEN_HEIGHT);
	
	mscr_adjustScreenToMapLimits(scrAtt, mapInfo);
	
	scrAtt->moveReference = moveReference;
	scrAtt->controller = &mscr_moveScr;
	scrAtt->dimension.width = GBA_SCREEN_WIDTH;
	scrAtt->dimension.height = GBA_SCREEN_HEIGHT;
	if (moveRefCustomBox) {
		scrAtt->moveRefBox = 
			*moveRefCustomBox;
	} else {
		scrAtt->moveRefBox = 
			default_scrBoundingBox;
	}
}

void mscr_adjustScreenToMapLimits(ScreenAttr *scrAtt, const MapInfo *mapInfo) {
    s32 maxHorizontal = mapInfo->width - GBA_SCREEN_WIDTH;
	s32 maxVertical = mapInfo->height - GBA_SCREEN_HEIGHT;
	
	if (scrAtt->position.x < 0) {
	    scrAtt->position.x = 0;
	} else if (scrAtt->position.x > maxHorizontal) {
		scrAtt->position.x = maxHorizontal;
	}

	if (scrAtt->position.y < 0) {
	    scrAtt->position.y = 0;
	} else if (scrAtt->position.y > maxVertical) {
	    scrAtt->position.y = maxVertical;
	}
}

void mscr_moveScr(ScreenAttr *scrAtt, MapInfo *mapInfo) {
	Position *ref = scrAtt->moveReference;
	if (ref) {
		u16 x = CONVERT_2POS(ref->x);
		u16 y = CONVERT_2POS(ref->y);
		u16 startXPos = scrAtt->position.x;
		u16 startYPos = scrAtt->position.y;
		s32 maxHorizontal = mapInfo->width - GBA_SCREEN_WIDTH;
		s32 maxVertical = mapInfo->height - GBA_SCREEN_HEIGHT;

		mscr_checkMoveLeft(scrAtt, x, 0);
		mscr_checkMoveRight(scrAtt, x, maxHorizontal);
			
		mscr_checkMoveUp(scrAtt, y, 0);
		mscr_checkMoveDown(scrAtt, y, maxVertical);	
		
		mscr_setHorizontalMove(scrAtt, mapInfo, startXPos);
		mscr_setVerticalMove(scrAtt, mapInfo, startYPos);
	}
}

void mscr_initPosMoveRef(ScreenAttr *scrAtt, 
	Position *reference)
{
	scrAtt->position.x = 0;
	scrAtt->position.y = 0;
	scrAtt->moveReference = reference;
}

void mscr_checkMoveLeft(ScreenAttr *scrAtt, u16 x,
	s32 left_max)
{
	u16 leftLimit = scrAtt->position.x +
		scrAtt->moveRefBox.offset_x;
	
	if (x < leftLimit) {
		s32 movex = leftLimit - x;
		if (movex > X_MOVE_LIMIT) {
			movex = X_MOVE_LIMIT;
		}
		s32 newPositionx = scrAtt->position.x - movex;
		if (newPositionx < left_max) {
			newPositionx = left_max;
		}
		
		scrAtt->position.x = newPositionx;
	}
}

void mscr_checkMoveRight(ScreenAttr *scrAtt, u16 x,
	s32 right_max)
{
	u16 rightLimit = scrAtt->position.x +
		scrAtt->moveRefBox.offset_x +
		scrAtt->moveRefBox.width;
		
	if (x > rightLimit) {
		s32 movex = x - rightLimit;
		if (movex > X_MOVE_LIMIT) {
			movex = X_MOVE_LIMIT;
		}
		s32 newPositionx = scrAtt->position.x + movex;
		if (newPositionx > right_max) {
			newPositionx = right_max;
		}
		
		scrAtt->position.x = newPositionx;
	}
}

void mscr_checkMoveUp(ScreenAttr *scrAtt, u16 y,
	s32 up_max)
{
	u16 upLimit = scrAtt->position.y +
		scrAtt->moveRefBox.offset_y;
		
	if (y < upLimit) {
		s32 movey = upLimit - y;
		if (movey > Y_MOVE_LIMIT) {
			movey = Y_MOVE_LIMIT;
		}
		s32 newPositiony = scrAtt->position.y - movey;
		if (newPositiony < up_max) {
			newPositiony = up_max;
		}
		
		scrAtt->position.y = newPositiony;
	}
}

void mscr_checkMoveDown(ScreenAttr *scrAtt, u16 y,
	s32 down_max)
{
	u16 downLimit = scrAtt->position.y +
		scrAtt->moveRefBox.offset_y +
		scrAtt->moveRefBox.height;
		
	if (y > downLimit) {
		s32 movey = y - downLimit;
		if (movey > Y_MOVE_LIMIT) {
			movey = Y_MOVE_LIMIT;
		}
		s32 newPositiony = scrAtt->position.y + movey;
		if (newPositiony > down_max) {
			newPositiony = down_max;
		}
		
		scrAtt->position.y = newPositiony;
	}
}

void mscr_setHorizontalMove(ScreenAttr *scrAtt,
	MapInfo *mapInfo,
	u16 startXPos)
{
	u16 inital_xtileidx = DIVIDE_BY_TILE_WIDTH(startXPos);
	u16 new_xtileidx = DIVIDE_BY_TILE_WIDTH(scrAtt->position.x);
	s16 xtilemove = new_xtileidx - inital_xtileidx;
	
	if (xtilemove > 0) {
		mbg_setVerticalTiles(mapInfo, ETileMap0,
			scrAtt->position.x + scrAtt->dimension.width,
			scrAtt->position.y, SCR_VERTICAL_TILE_COUNT + 1);
	} else if (xtilemove < 0) {
		mbg_setVerticalTiles(mapInfo, ETileMap0,
			scrAtt->position.x,
			scrAtt->position.y, SCR_VERTICAL_TILE_COUNT + 1);
	}
}

void mscr_setVerticalMove(ScreenAttr *scrAtt,
	MapInfo *mapInfo,
	u16 startYPos)
{
	u16 inital_ytileidx = DIVIDE_BY_TILE_HEIGHT(startYPos);
	u16 new_ytileidx = DIVIDE_BY_TILE_HEIGHT(scrAtt->position.y);
	s16 ytilemove = new_ytileidx - inital_ytileidx;
	
	if (ytilemove > 0) {
		mbg_setHorizontalTiles(mapInfo, ETileMap0,
		scrAtt->position.x,
		scrAtt->position.y + scrAtt->dimension.height,
		SCR_HORIZONTAL_TILE_COUNT + 1);
	} else if (ytilemove < 0) {
		mbg_setHorizontalTiles(mapInfo, ETileMap0,
		scrAtt->position.x,
		scrAtt->position.y, 
		SCR_HORIZONTAL_TILE_COUNT + 1);
	}
}

void mscr_setDraw(ScreenAttr *scrAtt) {
	mscr_vscrRef = scrAtt;
}

void mscr_draw() {
	if (mscr_vscrRef) {
		*REG_BG_H0 = mscr_vscrRef->position.x;
		*REG_BG_V0 = mscr_vscrRef->position.y;
		*REG_BG_H1 = mscr_vscrRef->position.x;
		*REG_BG_V1 = mscr_vscrRef->position.y;
	}
}

void initWindowObj() {
	*REG_DISPCNT |= DCNT_WINOBJ;
//	*REG_WINOUT = BIT8|BIT9|BITC;
//	*REG_WINOUT = BIT8|BIT9|BITC|BIT5;
	*REG_WINOUT = BIT9|BITC|BIT4|BIT1|BIT0|BIT5;
}

void removeWindowObj() {
	*REG_DISPCNT &= ~DCNT_WINOBJ;
	*REG_WINOUT = 0;
}