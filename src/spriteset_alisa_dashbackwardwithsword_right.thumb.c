#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageAlisa.h"

const SpriteLayer alisa_dashbackwardwithsword_right_layerSet0[] = {
    {sword_side_image0,-24,11,WIDE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,1},
    {alisa_dashbackwardwithsword_side_image1,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0}};
const SpriteLayer alisa_dashbackwardwithsword_right_layerSet1[] = {
    {sword_side_image0,-26,13,WIDE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,1},
    {alisa_dashbackwardwithsword_side_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0}};

const SpriteLayerSet alisa_dashbackwardwithsword_right_layerSet[] = {
    {alisa_dashbackwardwithsword_right_layerSet0,10,2},
    {alisa_dashbackwardwithsword_right_layerSet1,5,2},
};

const SpriteSet alisa_dashbackwardwithsword_right = {alisa_dashbackwardwithsword_right_layerSet,2};
