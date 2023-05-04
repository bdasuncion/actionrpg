#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageAlisa.h"

const SpriteLayer alisa_preparedash_left_layerSet0[] = {
    {sword_side_set_image0,9,16,WIDE,SMALL_B,DO_HFLIP,DO_VFLIP,NO_COMPRESSION,0,1},
    {alisa_dashbackwardwithsword_side_image0,0,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};

const SpriteLayerSet alisa_preparedash_left_layerSet[] = {
    {alisa_preparedash_left_layerSet0,5,2},
};

const SpriteSet alisa_preparedash_left = {alisa_preparedash_left_layerSet,1};
