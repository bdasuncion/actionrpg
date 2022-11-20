#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageAlisa.h"

const SpriteLayer alisa_standwithsword_right_layerSet0[] = {
    {sword_side_image0,-25,11,WIDE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,1},
    {alisa_standwithsword_side_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0}};

const SpriteLayerSet alisa_standwithsword_right_layerSet[] = {
    {alisa_standwithsword_right_layerSet0,5,2},
};

const SpriteSet alisa_standwithsword_right = {alisa_standwithsword_right_layerSet,1};
