#include "GBATypes.h"

#ifndef GBABG
#define	GBABG

#define	REG_BG_CNT0		((vu16*)0x4000008)
#define	REG_BG_CNT1		((vu16*)0x400000A)
#define	REG_BG_CNT2		((vu16*)0x400000C)
#define	REG_BG_CNT3		((vu16*)0x400000E)


#define	REG_BG_H0		((vu16*)0x4000010)
#define	REG_BG_V0		((vu16*)0x4000012)
#define	REG_BG_H1		((vu16*)0x4000014)
#define	REG_BG_V1		((vu16*)0x4000016)
#define	REG_BG_H2		((vu16*)0x4000018)
#define	REG_BG_V2		((vu16*)0x400001A)
#define	REG_BG_H3		((vu16*)0x400001C)
#define	REG_BG_V3		((vu16*)0x400001E)

#define	BG_PRIO(n)		(n)

#define BG_CBB(n)		((n)<<2)

#define	BG_MOSAIC		BIT6

#define	BG_4BPP			0

#define BG_8BPP			BIT7

#define	BG_SBB(n)		((n)<<8)

#define	BG_WRAP			BIT13

#define	BG_SIZE(n)		((n)<<14)


#define SE_ID(n)		(n)

#define	SE_HFLIP		BIT10

#define	SE_VFLIP		BIT11

#define SE_PALBANK(n)			((n)<<12)

typedef struct BgControl {
	u16 priority:2;
	u16 screenBlock:2;
	u16 unused:2;
	u16 mosaic:1;
	u16 colorMode:1;
	u16 tileBlock:5;
	u16 affineWrap:1;
	u16 size:2;
} ALIGN2 BgControl;

typedef enum BGColorMode
{
	EBgColor16,
	EBgColor256
}BGColorMode;

typedef enum BGMosaic {
	EMosaicInactive,
	EMosaicActive
}BGMosaic;

typedef enum BGSize {
	EBgSize32x32,
	EBgSize64x32,
	EBgSize32x64,
	EBgSize64x64,
} BGSize;

static inline void setBGControl(int bgId, const BgControl *bgc)
{
	REG_BG_CNT0[bgId] = *((u16*)bgc);
}

static inline void setBGControlAttr(int bgId, int priority, 
	int screenBlk, BGMosaic mosaic, BGColorMode colorMode, int tileBlock, 
	BGSize size)
{
	BgControl bgc;
	bgc.priority = priority;
	bgc.screenBlock = screenBlk;
	bgc.mosaic = mosaic;
	bgc.colorMode = colorMode;
	bgc.tileBlock = tileBlock;
	bgc.size = size;
	setBGControl(bgId, &bgc);
}

static inline void setBGPosition(int bgId, u16 x, u16 y) {
	REG_BG_H0[2*bgId] = x;
	REG_BG_V0[2*bgId] = y;
}


#endif
