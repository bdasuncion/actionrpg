#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ManagerVram.h"

extern const unsigned int shadow_image0[];

const SpriteLayer shadow_layerSet0[] = {
    {shadow_image0,0,0,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0}};

const SpriteLayerSet shadow_layerSet[] = {
    {shadow_layerSet0,5,1},
};

const SpriteSet shadow = {shadow_layerSet,1};

//const int shadow_palletteId = SHARED_PALETTEID;
//const int shadow_imageId = EVramMapIdShadow;

const SpriteDisplay common_shadowDisplay = { &shadow, EVramMapIdShadow, EUpdate, SHARED_PALETTEID, EUpdate,0,0,1,0,0,0 };
