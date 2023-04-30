#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageAlisa.h"

const SpriteLayer alisa_fallingdown_up_layerSet0[] = {
    {sword_frontback_set_image1,4,-11,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,1},
    {alisa_jumpwithsword_up_image2,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0}};

const SpriteLayerSet alisa_fallingdown_up_layerSet[] = {
    {alisa_fallingdown_up_layerSet0,5,2},
};

const SpriteSet alisa_fallingdown_up = {alisa_fallingdown_up_layerSet,1};
