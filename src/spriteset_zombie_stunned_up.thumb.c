#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageZombie.h"

const SpriteLayer zombie_stunned_up_layerSet0[] = {
    {zombie_stunned_up_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0}};

const SpriteLayerSet zombie_stunned_up_layerSet[] = {
    {zombie_stunned_up_layerSet0,60,1},
};

const SpriteSet zombie_stunned_up = {zombie_stunned_up_layerSet,1};
