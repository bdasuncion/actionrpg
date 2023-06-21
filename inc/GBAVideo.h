#include "GBATypes.h"

#ifndef GBAVideo
#define	GBAVideo

#define DCNT_MODE0			0
#define DCNT_MODE1			1
#define DCNT_MODE2			2
#define DCNT_MODE3			3
#define DCNT_MODE4			4
#define DCNT_MODE5			5

#define DCNT_OAM_HBL		BIT(0x5)
#define DCNT_PAGE 			BIT(0x6)
#define DCNT_OBJ_2D			0
#define DCNT_OBJ_1D			BIT(0x6)
#define DCNT_BLANK			BIT(0x7)
#define DCNT_BG0			BIT(0x8)
#define DCNT_BG1			BIT(0x9)
#define DCNT_BG2			BIT(0xA)
#define DCNT_BG3			BIT(0xB)
#define DCNT_OBJENB			BIT(0xC)
#define DCNT_WIN0			BIT(0xD)
#define DCNT_WIN1			BIT(0xE)
#define DCNT_WINOBJ			BIT(0xF)


#define REG_DISPCNT		((vu16*)0x4000000)

#define SetMode(mode) 	REG_DISPCNT(mode)

#define DSTAT_VBL_IRQ 	BIT3
#define DSTAT_HBL_IRQ	BIT4
#define DSTAT_VCT_IRQ	BIT5
#define DSTAT_VCT(n)	((n)<<8)

#define REG_DSTAT			((vu16*)0x4000004)

#define REG_VCOUNT			((vu16*)0x4000006)

#define	VRAM_ADDR			((vu32*)0x6000000)


typedef struct PALLETTE_BANK { u16 data[16][16]; } PALLETTE_BANK;

//#define PALETTE_MEMORY_BG	((vu32*)0x5000000)
#define PALETTE_MEMORY_BG	((PALLETTE_BANK*)0x5000000)

#define PALETTE_MEMORY_SP	((vu32*)0x5000200)

#define OAM_MEMORY			((vu32*)0x7000000)

#define SIZE_MAP_BLOCK 2048
#define COUNT_MAP_BLOCK 32
#define MAPBLOCK_MAX 16
#define TILECOUNTPERBLOCK 512
#define TILECOUNTPERBLOCK8BPP 256
#define WORDSPERTILE 8
#define WORDSPERTILE8BPP 16

typedef struct TILE4 {u32 data[WORDSPERTILE];} TILE4; //8x8 4bpp(1 tile)
typedef struct TILE8 {u32 data[WORDSPERTILE8BPP];} TILE8; // 8x8 8bpp(1 tile)
typedef struct BLOCK_4BPP { TILE4 tile[TILECOUNTPERBLOCK];} BLOCK_4BPP; //512 4bpp tiles in one block of memory(around 16K)
typedef struct BLOCK_8BPP { TILE4 tile[TILECOUNTPERBLOCK8BPP];} BLOCK_8BPP;
typedef struct VRAM_MAP { BLOCK_4BPP block[6]; } VRAM_MAP;
typedef struct VRAM_MAP_8BPP { BLOCK_8BPP block[6]; } VRAM_MAP_8BPP;

typedef struct PALETTE_ENTRY { u16 RGB[16]; } PALETTE_ENTRY;
typedef struct PALETTE_MAP { PALETTE_ENTRY palette[16]; } PALETTE_MAP;

typedef struct SCREEN { u8 screen[SIZE_MAP_BLOCK]; } SCREEN;
typedef struct SCREEN_ENTRY { SCREEN entry[COUNT_MAP_BLOCK]; } SCREEN_ENTRY;

typedef struct VRAMMAP_BG {
    SCREEN screen[MAPBLOCK_MAX];
	BLOCK_4BPP tiles[2];
} VRAMMAP_BG;

typedef struct DisplayStatus {
	u16 isInVBlank:1;
	u16 isInHBlank:1;
	u16 isVcountTrigger:1;
	u16 vBlankInterrupt:1;
	u16 hBlankInterrupt:1;
	u16 vCountInterrupt:1;
	u16 pad:2;
	u16 vCountTigger:8;
}ALIGN2 DisplayStatus;

#define STRUCT_REG_DSTAT 		((DisplayStatus*)REG_DSTAT)

static inline int gbavid_isVBlank() {
	return STRUCT_REG_DSTAT->isInVBlank;
}

static inline int gbavid_isHBlank() {
	return STRUCT_REG_DSTAT->isInHBlank;
}

static inline int gbavid_isVCountTrigger() {
	return STRUCT_REG_DSTAT->isVcountTrigger;
}

static inline void gbavid_vBlankInterrupt(ERegStatus s) {
	STRUCT_REG_DSTAT->vBlankInterrupt = s;
}

static inline void gbavid_hBlankInterrupt(ERegStatus s) {
	STRUCT_REG_DSTAT->hBlankInterrupt = s;
}

static inline void gbavid_vCountInterrupt(ERegStatus s, int trigger) {
	STRUCT_REG_DSTAT->vCountInterrupt = s;
	if (s) {
		STRUCT_REG_DSTAT->vCountTigger = trigger;
	}
}

#define SPRITE_BLOCK 4
#define VRAM		((VRAM_MAP*)VRAM_ADDR)
#define TILE_MAP_BLOCK 28
#define SCR_ENTRY   ((SCREEN_ENTRY*)VRAM_ADDR)
#define PALETTE_BGMAP	((PALETTE_MAP*)PALETTE_MEMORY_BG)
#define PALETTE_OBJMAP	((PALETTE_MAP*)PALETTE_MEMORY_SP)
#define VRAM_BG ((VRAMMAP_BG)VRAM_ADDR)

typedef enum ETileMapId
{
	ETileMapPrinter = TILE_MAP_BLOCK - 1,
	ETileMap0,
	ETileMap1,
	ETileMap2,
	ETileMap3
}ETileMapId;


#define REG_WINOUT ((vu16*)0x0400004A)
#endif
