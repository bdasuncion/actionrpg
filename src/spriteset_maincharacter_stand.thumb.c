#include "GBATypes.h"
#include "GBAObject.h"
#include "sprite_maincharacterupper_stand.h"
#include "sprite_maincharacterlower_stand.h"

const SpriteLayer maincharacter_stand_layerSet0[] = {
    {maincharacterlower_stand_image0,0,32,SQUARE,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {maincharacterupper_stand_image0,0,0,SQUARE,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,16,0}};

const SpriteLayerSet maincharacter_stand_layerSet[] = {
    {maincharacter_stand_layerSet0,5,2},
};

const SpriteSet maincharacter_stand = {maincharacter_stand_layerSet,1};
