#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageAlisa.h"

const SpriteLayer alisa_dashbackwardwithsword_up_layerSet0[] = {
    {alisa_dashbackwardwithsword_up_image1,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {sword_side_image0,10,10,WIDE,SMALL_B,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,8,1}};
const SpriteLayer alisa_dashbackwardwithsword_up_layerSet1[] = {
    {alisa_dashbackwardwithsword_up_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {sword_side_image0,10,12,WIDE,SMALL_B,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,8,1}};

const SpriteLayerSet alisa_dashbackwardwithsword_up_layerSet[] = {
    {alisa_dashbackwardwithsword_up_layerSet0,10,2},
    {alisa_dashbackwardwithsword_up_layerSet1,5,2},
};

const SpriteSet alisa_dashbackwardwithsword_up = {alisa_dashbackwardwithsword_up_layerSet,2};
