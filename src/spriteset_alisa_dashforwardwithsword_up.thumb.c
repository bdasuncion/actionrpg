#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageAlisa.h"

const SpriteLayer alisa_dashforwardwithsword_up_layerSet0[] = {
    {alisa_runwithsword_up_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {sword_side_image2,8,13,WIDE,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,8,1}};
const SpriteLayer alisa_dashforwardwithsword_up_layerSet1[] = {
    {alisa_runwithsword_up_image1,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {sword_side_image2,8,13,WIDE,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,8,1}};
const SpriteLayer alisa_dashforwardwithsword_up_layerSet2[] = {
    {alisa_runwithsword_up_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {sword_side_image2,8,13,WIDE,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,8,1}};
const SpriteLayer alisa_dashforwardwithsword_up_layerSet3[] = {
    {sword_side_image0,10,16,WIDE,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,1},
    {alisa_dashbackwardwithsword_up_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0}};

const SpriteLayerSet alisa_dashforwardwithsword_up_layerSet[] = {
    {alisa_dashforwardwithsword_up_layerSet0,2,2},
    {alisa_dashforwardwithsword_up_layerSet1,8,2},
    {alisa_dashforwardwithsword_up_layerSet2,2,2},
    {alisa_dashforwardwithsword_up_layerSet3,10,2},
};

const SpriteSet alisa_dashforwardwithsword_up = {alisa_dashforwardwithsword_up_layerSet,4};

