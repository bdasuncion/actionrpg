#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "sprite_ghostlyman.h"

const SpriteLayer ghosltyman_layerSet0[] = {
    {ghostlyman_image0,0,0,SQUARE,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0}};

const SpriteLayerSet ghosltyman_layerSet[] = {
    {ghosltyman_layerSet0,1,1},
};

const SpriteLayerSet ghosltymantransition_layerSet[] = {
    {ghosltyman_layerSet0, 120, 1},
};

const SpriteSet ghosltyman = {ghosltyman_layerSet,1};

const SpriteSet ghosltymantransition = {ghosltymantransition_layerSet,1};
