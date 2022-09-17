#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageAlisa.h"

const SpriteLayer alisa_standwithsword_big_right_layerSet0[] = {
    {alisa_standwithsword_upper_side_image0,0,0,WIDE,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {alisa_standwithsword_lower_side_image0,0,16,SQUARE,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,8,0}};

const SpriteLayerSet alisa_standwithsword_big_right_layerSet[] = {
    {alisa_standwithsword_big_right_layerSet0,5,2},
};

const SpriteSet alisa_standwithsword_big_right = {alisa_standwithsword_big_right_layerSet,1};
