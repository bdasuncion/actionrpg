#ifndef MANAGER_VRAM
#define MANAGER_VRAM

#include "GBATypes.h"
#include "GBACharacterType.h"
#include "GBAVideo.h"

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
void sprite_vram_init_sections();
u32 sprite_vram_findId();
void sprite_vram_freeId(u32 id);
int sprite_palette_findId(CHARACTERTYPE type, int nPalette);
u16* sprite_get_palette_ID(u32 id);
u32 sprite_vram_findIdByType(CharacterSizeType type);
#define SPRITEMASK_BLOCKSTART 384
#define SPRITEMASK_IDSTART TILECOUNTPERBLOCK + SPRITEMASK_BLOCKSTART
#define SHARED_PALETTEID 15
typedef enum EVramMapId{
	EVramMapIdChar = 0,
	EVramMapIdShadow = TILECOUNTPERBLOCK + SPRITEMASK_BLOCKSTART - 4,
	EVramMapIdMaskStandard = EVramMapIdShadow + 4,
	EVramMapIdMaskCustom = EVramMapIdMaskStandard + 4,
	EVramMapIdAttackEffects = EVramMapIdMaskCustom + 24
}EVramMapId;

#endif