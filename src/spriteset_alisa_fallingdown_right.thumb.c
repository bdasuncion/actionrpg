#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageAlisa.h"

const SpriteLayer alisa_fallingdown_right_layerSet0[] = {
    {sword_side_set_image0,-25,-4,WIDE,SMALL_B,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,1},
    {alisa_jumpwithsword_side_image2,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};

const SpriteLayerSet alisa_fallingdown_right_layerSet[] = {
    {alisa_fallingdown_right_layerSet0,5,2},
};

const SpriteSet alisa_fallingdown_right = {alisa_fallingdown_right_layerSet,1};

