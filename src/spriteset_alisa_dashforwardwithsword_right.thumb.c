#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageAlisa.h"

const SpriteLayer alisa_dashforwardwithsword_right_layerSet0[] = {
    {alisa_runwithsword_side_image3,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {sword_side_image2,-8,14,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,8,1}};
const SpriteLayer alisa_dashforwardwithsword_right_layerSet1[] = {
    {alisa_runwithsword_side_image4,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {sword_side_image0,-8,14,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,8,1}};
const SpriteLayer alisa_dashforwardwithsword_right_layerSet2[] = {
    {alisa_runwithsword_side_image3,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {sword_side_image2,-8,14,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,8,1}};
const SpriteLayer alisa_dashforwardwithsword_right_layerSet3[] = {
    {alisa_dashbackwardwithsword_side_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {sword_side_image0,-8,16,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,8,1}};

const SpriteLayerSet alisa_dashforwardwithsword_right_layerSet[] = {
    {alisa_dashforwardwithsword_right_layerSet0,3,2},
    {alisa_dashforwardwithsword_right_layerSet1,10,2},
    {alisa_dashforwardwithsword_right_layerSet2,3,2},
    {alisa_dashforwardwithsword_right_layerSet3,10,2},
};

const SpriteSet alisa_dashforwardwithsword_right = {alisa_dashforwardwithsword_right_layerSet,4};
