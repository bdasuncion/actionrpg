#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageAlisa.h"

const SpriteLayer alisa_fallingdown_left_layerSet0[] = {
    {alisa_jumpwithsword_side_image2,0,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0}};

const SpriteLayerSet alisa_fallingdown_left_layerSet[] = {
    {alisa_fallingdown_left_layerSet0,5,1},
};

const SpriteSet alisa_fallingdown_left = {alisa_fallingdown_left_layerSet,1};
