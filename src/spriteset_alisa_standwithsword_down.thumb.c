#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageAlisa.h"

const SpriteLayer alisa_standwithsword_down_layerSet0[] = {
    {sword_side_set_image2,-24,11,WIDE,SMALL_B,NO_HFLIP,DO_VFLIP,NO_COMPRESSION,0,1},
    {alisa_standwithsword_down_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};

const SpriteLayerSet alisa_standwithsword_down_layerSet[] = {
    {alisa_standwithsword_down_layerSet0,5,2},
};

const SpriteSet alisa_standwithsword_down = {alisa_standwithsword_down_layerSet,1};
