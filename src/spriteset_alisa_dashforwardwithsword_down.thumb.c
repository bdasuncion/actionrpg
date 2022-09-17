#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageAlisa.h"

const SpriteLayer alisa_dashforwardwithsword_down_layerSet0[] = {
    {alisa_runwithsword_down_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {sword_side_image2,-8,13,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,8,1}};
const SpriteLayer alisa_dashforwardwithsword_down_layerSet1[] = {
    {alisa_runwithsword_down_image1,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {sword_side_image0,-8,13,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,8,1}};
const SpriteLayer alisa_dashforwardwithsword_down_layerSet2[] = {
    {alisa_runwithsword_down_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {sword_side_image0,-8,13,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,8,1}};
const SpriteLayer alisa_dashforwardwithsword_down_layerSet3[] = {
    {sword_side_image0,-9,15,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,1},
    {alisa_dashbackwardwithsword_down_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0}};

const SpriteLayerSet alisa_dashforwardwithsword_down_layerSet[] = {
    {alisa_dashforwardwithsword_down_layerSet0,2,2},
    {alisa_dashforwardwithsword_down_layerSet1,8,2},
    {alisa_dashforwardwithsword_down_layerSet2,2,2},
    {alisa_dashforwardwithsword_down_layerSet3,10,2},
};

const SpriteSet alisa_dashforwardwithsword_down = {alisa_dashforwardwithsword_down_layerSet,4};
