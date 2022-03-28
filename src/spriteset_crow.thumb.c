#include "GBATypes.h"
#include "GBAObject.h"
#include "sprite_crow.h"

const SpriteLayer crow_layerSet0[] = {
    {crow_image0,0,0,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0}};

const SpriteLayerSet crow_layerSet[] = {
    {crow_layerSet0,5,1},
};

const SpriteSet crow_standing = {crow_layerSet,1};
