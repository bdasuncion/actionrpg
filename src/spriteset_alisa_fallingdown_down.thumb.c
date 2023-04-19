#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageAlisa.h"

const SpriteLayer alisa_fallingdown_down_layerSet0[] = {
    {alisa_jumpwithsword_down_image2,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0}};

const SpriteLayerSet alisa_fallingdown_down_layerSet[] = {
    {alisa_fallingdown_down_layerSet0,5,1},
};

const SpriteSet alisa_fallingdown_down = {alisa_fallingdown_down_layerSet,1};
