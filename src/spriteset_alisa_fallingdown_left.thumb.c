#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageAlisa.h"

const SpriteLayer alisa_fallingdown_left_layerSet0[] = {
    {sword_side_set_image0,9,-4,WIDE,SMALL_B,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,1},
    {alisa_jumpwithsword_side_image2,0,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};

const SpriteLayerSet alisa_fallingdown_left_layerSet[] = {
    {alisa_fallingdown_left_layerSet0,5,2},
};

const SpriteSet alisa_fallingdown_left = {alisa_fallingdown_left_layerSet,1};
