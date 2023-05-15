#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageAlisa.h"

const SpriteLayer alisa_stunnedwithsword_up_layerSet0[] = {
    {sword_vertical_set_image2,9,13,TALL,SMALL_B,NO_HFLIP,DO_VFLIP,NO_COMPRESSION,0,1},
    {alisa_stunnedwithsword_up_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};

const SpriteLayerSet alisa_stunnedwithsword_up_layerSet[] = {
    {alisa_stunnedwithsword_up_layerSet0,60,2},
};

const SpriteSet alisa_stunnedwithsword_up = {alisa_stunnedwithsword_up_layerSet,1};

