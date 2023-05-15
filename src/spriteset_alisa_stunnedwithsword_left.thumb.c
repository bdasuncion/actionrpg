#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageAlisa.h"

const SpriteLayer alisa_stunnedwithsword_left_layerSet0[] = {
    {sword_side_set_image0,11,15,WIDE,SMALL_B,DO_HFLIP,DO_VFLIP,NO_COMPRESSION,0,1},
    {alisa_stunnedwithsword_side_image0,0,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};

const SpriteLayerSet alisa_stunnedwithsword_left_layerSet[] = {
    {alisa_stunnedwithsword_left_layerSet0,60,2},
};

const SpriteSet alisa_stunnedwithsword_left = {alisa_stunnedwithsword_left_layerSet,1};