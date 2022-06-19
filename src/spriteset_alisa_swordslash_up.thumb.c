#include "GBATypes.h"
#include "GBAObject.h"
#include "ImageAlisa.h"

const SpriteLayer alisa_swordslash_up_layerSet0[] = {
    {alisa_swordslash_up_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {sword_vertical_image1,9,16,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,8,1}};
const SpriteLayer alisa_swordslash_up_layerSet1[] = {
    {alisa_swordslash_up_image1,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {sword_side_image0,10,10,WIDE,SMALL_A,DO_HFLIP,DO_VFLIP,LZSS_COMPRESSION,8,1}};
const SpriteLayer alisa_swordslash_up_layerSet2[] = {
    {alisa_swordslash_up_image2,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {sword_vertical_image1,4,-2,TALL,SMALL_A,DO_HFLIP,DO_VFLIP,LZSS_COMPRESSION,8,1}};
const SpriteLayer alisa_swordslash_up_layerSet3[] = {
    {alisa_swordslash_up_image3,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {sword_vertical_image1,-2,-2,TALL,SMALL_A,DO_HFLIP,DO_VFLIP,LZSS_COMPRESSION,8,1}};

const SpriteLayerSet alisa_swordslash_up_layerSet[] = {
    {alisa_swordslash_up_layerSet0,2,2},
    {alisa_swordslash_up_layerSet1,2,2},
    {alisa_swordslash_up_layerSet2,2,2},
    {alisa_swordslash_up_layerSet3,20,2},
};

const SpriteSet alisa_swordslash_up = {alisa_swordslash_up_layerSet,4};
