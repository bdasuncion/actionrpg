#include "GBATypes.h"
#include "GBAObject.h"
#include "sprite_ghostly_hand.h"

const SpriteLayer ghosthand_hidden_layerSet0[] = {
    {ghostly_hand_image0,0,0,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0}};

const SpriteLayerSet ghosthand_hidden_layerSet[] = {
    {ghosthand_hidden_layerSet0,5,1},
};

const SpriteSet ghosthand_hidden = {ghosthand_hidden_layerSet,1};
