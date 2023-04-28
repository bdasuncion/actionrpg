#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageZombie.h"

const SpriteLayer zombie_stunned_right_layerSet0[] = {
    {zombie_stunned_side_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0}};

const SpriteLayerSet zombie_stunned_right_layerSet[] = {
    {zombie_stunned_right_layerSet0,60,1},
};

const SpriteSet zombie_stunned_right = {zombie_stunned_right_layerSet,1};
