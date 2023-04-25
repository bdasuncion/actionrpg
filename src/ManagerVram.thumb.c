#include"GBAVideo.h"
#include "GBATypes.h"
#include"GBADMA.h"
#include"GBAObject.h"
#include "GBACharacterType.h"

#define BLOCKSPERCHARACTER 32 //1KB(1024) for every character
#define BLOCKSPERCHARACTERSMALL 16 //(512B) for every small character
#define BLOCKSPERCHARACTERMEDIUM 24 //(768B) for every medium character
#define BLOCKSPERCHARACTERLARGE 32 //(1024B) for every large character
#define BLOCKSPERCHARACTERVLARGE 64 //(1024B) for every large character
//#define BLOCKSPERCHARACTER 40 //1KB(1024) for every character
#define MAXNCHARACTER 15
#define MAXNCHARACTERSMALL 10
#define MAXNCHARACTERMEDIUM 5
#define MAXNCHARACTERLARGE 3

#define MAXNPALETTE 15
#define PALLETTEERROR -1

u32	sprite_memory_bank = 0;
u32 BG_memory_bank = 0;
u32 palette_memory_bank = 0;
VramIdControl idCollection[MAXNCHARACTER + BLOCKSPERCHARACTERMEDIUM + BLOCKSPERCHARACTERLARGE];
PaletteIdControl paletteIdCollection[MAXNPALETTE];

void sprite_vram_init() {
    int i;
    for (i = 0; i < MAXNCHARACTER; ++i) {
	    VramIdControl idCtrl;
		idCtrl.id = BLOCKSPERCHARACTER * i;
		idCtrl.status = VRAM_FREE;
	    idCollection[i] = idCtrl;
	}
}

void sprite_vram_init_sections() {
    int i, j, currentID = 0;
    for (i = 0; i < MAXNCHARACTERSMALL; ++i) {
	    VramIdControl idCtrl;
		idCtrl.id = currentID; ;
		currentID += BLOCKSPERCHARACTERSMALL;
		idCtrl.status = VRAM_FREE;
	    idCollection[i] = idCtrl;
	}
	
	for (j = 0; j < MAXNCHARACTERMEDIUM; ++i, ++j) {
	    VramIdControl idCtrl;
		idCtrl.id = currentID;
		currentID += BLOCKSPERCHARACTERMEDIUM;
		idCtrl.status = VRAM_FREE;
	    idCollection[i] = idCtrl;
	}
	
	for (j = 0; j < MAXNCHARACTERLARGE; ++i, ++j) {
	    VramIdControl idCtrl;
		idCtrl.id = currentID;
		currentID += BLOCKSPERCHARACTERLARGE;
		idCtrl.status = VRAM_FREE;
	    idCollection[i] = idCtrl;
	}
}

u32 sprite_vram_findId() {
    int i;
    for (i = 0; i < MAXNCHARACTER; ++i) {
        if (idCollection[i].status == VRAM_FREE) {
		    idCollection[i].status = VRAM_TAKEN;
		    return idCollection[i].id;
		}
	}
}

u32 sprite_vram_findIdByType(CharacterSizeType type) {
    int i;
	if (type == ECharSizeSmall) {
		for (i = 0; i < MAXNCHARACTERSMALL; ++i) {
			if (idCollection[i].status == VRAM_FREE) {
				idCollection[i].status = VRAM_TAKEN;
				return idCollection[i].id;
			}
		}
	} else if (type == ECharSizeMedium) {
		for (i = MAXNCHARACTERSMALL; i < MAXNCHARACTERMEDIUM; ++i) {
			if (idCollection[i].status == VRAM_FREE) {
				idCollection[i].status = VRAM_TAKEN;
				return idCollection[i].id;
			}
		}
	} else if (type == ECharSizeLarge) {
		for (i = MAXNCHARACTERSMALL + MAXNCHARACTERMEDIUM; i < MAXNCHARACTERLARGE; ++i) {
			if (idCollection[i].status == VRAM_FREE) {
				idCollection[i].status = VRAM_TAKEN;
				return idCollection[i].id;
			}
		}
	}
  
}

void sprite_vram_freeId(u32 id) {
    int i;
    for (i = 0; i < MAXNCHARACTER; ++i) {
        if (idCollection[i].id == id) {
		    return idCollection[i].status = VRAM_FREE;
		}
	}
}

void sprite_vram_copy32_ID(const void* src, u32 count, u32 id) {
	void *dest = &VRAM->block[4].tile[id];
	dma3_cpy32(dest, src, count);
}

u32 sprite_getID(u32 width, u32 height) {
	u32 id = sprite_memory_bank;
	sprite_memory_bank += width*height >> 6;
	return id;
}

void sprite_vram_reset() {
	sprite_memory_bank = 0;
}

void sprite_palette_init() {
    int i;
    for (i = 0; i < MAXNPALETTE; ++i) {
	    PaletteIdControl idCtrl;
		idCtrl.id = i;
		idCtrl.status = PAL_FREE;
		idCtrl.type = NONE;
		paletteIdCollection[i] = idCtrl;
	}
}

int sprite_palette_findId(CHARACTERTYPE type, int nPalette) {
	int i,j;
    for (i = 0; i < MAXNPALETTE; ++i) {
	    if (paletteIdCollection[i].status == PAL_FREE) {
		    for(j = 0; j < nPalette; ++j) {
			    paletteIdCollection[i + j].status = PAL_TAKEN;
				paletteIdCollection[i + j].type = type;
			}
		    return paletteIdCollection[i].id;
		} else if (paletteIdCollection[i].type == type) {
		    return paletteIdCollection[i].id;
		}
	}
	return PALLETTEERROR;
}

void sprite_palette_copy32(const void* src) {
	dma_mem[3].cnt = 0;
	dma_mem[3].src = src;
	dma_mem[3].dest = &PALETTE_MEMORY_SP[palette_memory_bank];
	dma_mem[3].cnt = 8|DMA_32|DMA_ON;
	
	palette_memory_bank += 8;
}

void sprite_palette_copy32_ID(const void* src, u32 id) {
	void *dest = &PALETTE_OBJMAP->palette[id];
	dma3_cpy32(dest, src, 8);
}

u32 sprite_palette_getID()
{
	return palette_memory_bank>>3;
}

void sprite_palette_reset()
{
	palette_memory_bank = 0;
}

void tiles_vram_copy32(const void* src, u32 count)
{
	dma_mem[3].cnt = 0;
	dma_mem[3].src = src;
	dma_mem[3].dest = &VRAM->block[0].tile[BG_memory_bank];
	dma_mem[3].cnt = count|DMA_32|DMA_ON;
	
	count = count<<6;
	BG_memory_bank += count;
}

void map_vram_copy32(const void* src, u32 count)
{
	dma_mem[3].cnt = 0;
	dma_mem[3].src = src;
	dma_mem[3].dest = &VRAM->block[0].tile[BG_memory_bank];
	dma_mem[3].cnt = count|DMA_32|DMA_ON;
	
	count = count<<6;
	BG_memory_bank += count;
}

u32 getBGMemoryCurrent()
{
	return BG_memory_bank;
}

void memFill16(const void* src, void* dst, u32 count)
{
	dma_mem[3].cnt = 0;
	dma_mem[3].src = src;
	dma_mem[3].dest = dst;
	dma_mem[3].cnt = count|DMA_16|DMA_ON|DMA_SRC_FIXED;
}

u16* sprite_get_palette_ID(u32 id) {
	return &PALETTE_OBJMAP->palette[id];
}