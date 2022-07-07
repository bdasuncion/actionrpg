#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageAlisa.h"

const SpriteLayer alisa_standwithsword_up_layerSet0[] = {
    {sword_side_image2,9,13,WIDE,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,1},
    {alisa_standwithsword_up_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0}};

const SpriteLayerSet alisa_standwithsword_up_layerSet[] = {
    {alisa_standwithsword_up_layerSet0,5,2},
};

const SpriteSet alisa_standwithsword_up = {alisa_standwithsword_up_layerSet,1};
