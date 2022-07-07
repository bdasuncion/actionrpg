#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageAlisa.h"

const SpriteLayer alisa_dashbackwardwithsword_right_layerSet0[] = {
    {sword_side_image0,-7,15,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,1},
    {alisa_dashbackwardwithsword_side_image1,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0}};
const SpriteLayer alisa_dashbackwardwithsword_right_layerSet1[] = {
    {sword_side_image0,-7,16,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,1},
    {alisa_dashbackwardwithsword_side_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0}};

const SpriteLayerSet alisa_dashbackwardwithsword_right_layerSet[] = {
    {alisa_dashbackwardwithsword_right_layerSet0,8,2},
    {alisa_dashbackwardwithsword_right_layerSet1,10,2},
};

const SpriteSet alisa_dashbackwardwithsword_right = {alisa_dashbackwardwithsword_right_layerSet,2};
