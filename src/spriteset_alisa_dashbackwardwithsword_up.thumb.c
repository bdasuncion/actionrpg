#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageAlisa.h"

const SpriteLayer alisa_dashbackwardwithsword_up_layerSet0[] = {
    {alisa_dashbackwardwithsword_up_image1,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {sword_side_image0,9,14,WIDE,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,8,1}};
const SpriteLayer alisa_dashbackwardwithsword_up_layerSet1[] = {
    {alisa_dashbackwardwithsword_up_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {sword_side_image0,9,15,WIDE,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,8,1}};

const SpriteLayerSet alisa_dashbackwardwithsword_up_layerSet[] = {
    {alisa_dashbackwardwithsword_up_layerSet0,8,2},
    {alisa_dashbackwardwithsword_up_layerSet1,10,2},
};

const SpriteSet alisa_dashbackwardwithsword_up = {alisa_dashbackwardwithsword_up_layerSet,2};
