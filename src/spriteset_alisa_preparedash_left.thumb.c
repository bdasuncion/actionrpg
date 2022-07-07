#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageAlisa.h"

const SpriteLayer alisa_preparedash_left_layerSet0[] = {
    {sword_side_image0,8,16,WIDE,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,1},
    {alisa_dashbackwardwithsword_side_image0,0,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0}};

const SpriteLayerSet alisa_preparedash_left_layerSet[] = {
    {alisa_preparedash_left_layerSet0,10,2},
};

const SpriteSet alisa_preparedash_left = {alisa_preparedash_left_layerSet,1};
