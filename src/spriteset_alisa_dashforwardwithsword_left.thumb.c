#include "GBATypes.h"
#include "GBAObject.h"
#include "ImageAlisa.h"

const SpriteLayer alisa_dashforwardwithsword_left_layerSet0[] = {
    {sword_side_image2,8,14,WIDE,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,1},
    {alisa_dashforwardwithsword_side_image0,0,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0}};
const SpriteLayer alisa_dashforwardwithsword_left_layerSet1[] = {
    {sword_side_image2,8,14,WIDE,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,1},
    {alisa_dashforwardwithsword_side_image1,0,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0}};
const SpriteLayer alisa_dashforwardwithsword_left_layerSet2[] = {
    {sword_side_image2,8,15,WIDE,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,1},
    {alisa_dashforwardwithsword_side_image2,0,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0}};

const SpriteLayerSet alisa_dashforwardwithsword_left_layerSet[] = {
    {alisa_dashforwardwithsword_left_layerSet0,5,2},
    {alisa_dashforwardwithsword_left_layerSet1,8,2},
    {alisa_dashforwardwithsword_left_layerSet2,3,2},
};

const SpriteSet alisa_dashforwardwithsword_left = {alisa_dashforwardwithsword_left_layerSet,3};
