#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageAlisa.h"

const SpriteLayer alisa_dashbackwardwithsword_down_layerSet0[] = {
    {sword_side_image0,-8,14,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,1},
    {alisa_dashbackwardwithsword_down_image1,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0}};
const SpriteLayer alisa_dashbackwardwithsword_down_layerSet1[] = {
    {sword_side_image0,-8,15,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,1},
    {alisa_dashbackwardwithsword_down_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0}};

const SpriteLayerSet alisa_dashbackwardwithsword_down_layerSet[] = {
    {alisa_dashbackwardwithsword_down_layerSet0,8,2},
    {alisa_dashbackwardwithsword_down_layerSet1,10,2},
};

const SpriteSet alisa_dashbackwardwithsword_down = {alisa_dashbackwardwithsword_down_layerSet,2};
