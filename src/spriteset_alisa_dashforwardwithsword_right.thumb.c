#include "GBATypes.h"
#include "GBAObject.h"
#include "ImageAlisa.h"

const SpriteLayer alisa_dashforwardwithsword_right_layerSet0[] = {
    {sword_side_image2,-7,14,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,1},
    {alisa_dashforwardwithsword_side_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0}};
const SpriteLayer alisa_dashforwardwithsword_right_layerSet1[] = {
    {sword_side_image2,-7,14,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,1},
    {alisa_dashforwardwithsword_side_image1,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0}};
const SpriteLayer alisa_dashforwardwithsword_right_layerSet2[] = {
    {sword_side_image2,-7,15,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,1},
    {alisa_dashforwardwithsword_side_image2,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0}};

const SpriteLayerSet alisa_dashforwardwithsword_right_layerSet[] = {
    {alisa_dashforwardwithsword_right_layerSet0,5,2},
    {alisa_dashforwardwithsword_right_layerSet1,8,2},
    {alisa_dashforwardwithsword_right_layerSet2,3,2},
};

const SpriteSet alisa_dashforwardwithsword_right = {alisa_dashforwardwithsword_right_layerSet,3};
