#ifndef MANAGER_VRAM
#define MANAGER_VRAM

#include "GBATypes.h"

void sprite_vram_copy32_ID(const void* src, u32 count, u32 id);
u32 sprite_getID(u32 width, u32 height);
void sprite_vram_reset();
void sprite_palette_copy32(const void* src);
void sprite_palette_copy32_ID(const void* src, u32 id);
u32 sprite_palette_getID();
void sprite_palette_reset();
void memFill(const void* src, void* dst, u32 count);
u32 lzss2vram(const u32* src, u32 id);
void sprite_vram_init();
u32 sprite_vram_findId();
void sprite_vram_freeId(u32 id);
int sprite_palette_findId(CHARACTERTYPE type, int nPalette);

#endif