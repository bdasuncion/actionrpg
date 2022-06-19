#include "GBATypes.h"
#include "GBAObject.h"
#include "ImageAlisa.h"

const SpriteLayer alisa_dashforwardwithsword_down_layerSet0[] = {
    {sword_side_image2,-8,13,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,1},
    {alisa_dashforwardwithsword_down_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0}};
const SpriteLayer alisa_dashforwardwithsword_down_layerSet1[] = {
    {sword_side_image2,-8,13,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,1},
    {alisa_dashforwardwithsword_down_image1,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0}};
const SpriteLayer alisa_dashforwardwithsword_down_layerSet2[] = {
    {sword_side_image2,-8,14,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,1},
    {alisa_dashforwardwithsword_down_image2,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0}};

const SpriteLayerSet alisa_dashforwardwithsword_down_layerSet[] = {
    {alisa_dashforwardwithsword_down_layerSet0,5,2},
    {alisa_dashforwardwithsword_down_layerSet1,8,2},
    {alisa_dashforwardwithsword_down_layerSet2,3,2},
};

const SpriteSet alisa_dashforwardwithsword_down = {alisa_dashforwardwithsword_down_layerSet,3};
