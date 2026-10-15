#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageMouthDemon.h"

const SpriteLayer mouth_demon_floating_left_layerSet0[] = {
    {mouthdemon_image0,0,0,WIDE,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0}};

const SpriteLayerSet mouth_demon_floating_left_layerSet[] = {
    {mouth_demon_floating_left_layerSet0,5,1},
};

const SpriteSet mouth_demon_floating_left = {mouth_demon_floating_left_layerSet,1};
