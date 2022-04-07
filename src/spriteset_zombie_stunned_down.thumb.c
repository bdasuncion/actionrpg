#include "GBATypes.h"
#include "GBAObject.h"
#include "ImageZombie.h"

const SpriteLayer zombie_stunned_down_layerSet0[] = {
    {zombie_stunned_down_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0}};

const SpriteLayerSet zombie_stunned_down_layerSet[] = {
    {zombie_stunned_down_layerSet0,60,1},
};

const SpriteSet zombie_stunned_down = {zombie_stunned_down_layerSet,1};
