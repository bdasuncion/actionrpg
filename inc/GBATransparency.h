#include "GBATypes.h"

#ifndef GBATransparency
#define	GBATransparency


#define REG_BLDMOD	    ((vu16*)0x4000050)
#define REG_BLDALPHA    ((vu16*)0x4000052)
#define REG_BLDY        ((vu16*)0x4000054)

#define BLENDMODE_BLACK  (3 << 6)
#define BLENDMODE_WHITE  (2 << 6)
#define BLENDMODE_NORMAL (1 << 6)
#define BGB_0            BIT8
#define BGB_1            BIT9
#define BGB_2            BITA
#define BGB_3            BITB
#define OBJB             BITC
#define BDB              BITD
#define BGF_0            BIT0
#define BGF_1            BIT1
#define BGF_2            BIT2
#define BGF_3            BIT3
#define OBJF             BIT4
#define BDF              BIT5

typedef void (*BlendFunc)(void *blend);

typedef struct BlendToBlack {
    u32 blendVal;
	bool increasing;
	BlendFunc blendFunc;
} BlendToBlack;

static void blendBlack(u32 blendVal) {
    *REG_BLDMOD = BLENDMODE_BLACK | BGF_0 |  BGF_1 | OBJF | BDF;
	*REG_BLDY = blendVal;
}

static void setBlendTest2(u32 blendVal) {
    *REG_BLDMOD = BLENDMODE_NORMAL |  BGF_0 |  BGF_1  | OBJB | BDB;
	*REG_BLDALPHA = blendVal | 8 << 8;
}

//TODO analyse how this works
static void setSpriteMasking() {
	*REG_BLDMOD =  BGB_0 |  BGB_1  | BGF_1 |BLENDMODE_NORMAL ;
	*REG_BLDALPHA = (16 << 8);
}

#endif