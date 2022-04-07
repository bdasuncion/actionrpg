#include "GBATypes.h"
#include "GBAObject.h"
#include "ImageZombie.h"

const SpriteLayer zombie_stunned_left_layerSet0[] = {
    {zombie_stunned_side_image0,0,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0}};

const SpriteLayerSet zombie_stunned_left_layerSet[] = {
    {zombie_stunned_left_layerSet0,60,1},
};

const SpriteSet zombie_stunned_left = {zombie_stunned_left_layerSet,1};
