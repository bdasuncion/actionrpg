#include "GBATypes.h"
#include "GBAObject.h"
#include "ImageAlisa.h"

const SpriteLayer alisa_standwithsword_down_layerSet0[] = {
    {alisa_standwithsword_down_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {sword_side_image0,-8,12,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,8,1}};

const SpriteLayerSet alisa_standwithsword_down_layerSet[] = {
    {alisa_standwithsword_down_layerSet0,5,2},
};

const SpriteSet alisa_standwithsword_down = {alisa_standwithsword_down_layerSet,1};
