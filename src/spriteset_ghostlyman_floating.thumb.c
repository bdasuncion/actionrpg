#include "GBATypes.h"
#include "GBAObject.h"
#include "sprite_ghostlyman_lower_float.h"
#include "sprite_ghostlyman_upper_float.h"

const SpriteLayer ghostlyman_floating_layerSet0[] = {
    {ghostlyman_lower_float_image0,0,32,SQUARE,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {ghostlyman_upper_float_image0,0,0,SQUARE,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,16,0}};

const SpriteLayerSet ghostlyman_floating_layerSet[] = {
    {ghostlyman_floating_layerSet0,1,2},
};

const SpriteSet ghostlyman_floating = {ghostlyman_floating_layerSet,1};
