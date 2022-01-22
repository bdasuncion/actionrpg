#include "GBATypes.h"
#include "GBAObject.h"
#include "ImageAlisa.h"

const SpriteLayer alisa_swordslash_left_layerSet0[] = {
    {sword_side_image0,6,15,WIDE,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,1},
    {alisa_swordslash_side_image0,0,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0}};
const SpriteLayer alisa_swordslash_left_layerSet1[] = {
    {sword_side_image1,8,13,WIDE,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,1},
    {alisa_swordslash_side_image1,-2,1,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0}};
const SpriteLayer alisa_swordslash_left_layerSet2[] = {
    {sword_vertical_image0,6,18,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,2},
    {alisa_swordslash_side_image2,-2,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0}};
const SpriteLayer alisa_swordslash_left_layerSet3[] = {
    {sword_side_image1,-12,16,WIDE,SMALL_A,NO_HFLIP,DO_VFLIP,LZSS_COMPRESSION,0,1},
    {alisa_swordslash_side_image3,-2,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0}};
const SpriteLayer alisa_swordslash_left_layerSet4[] = {
    {sword_side_image0,-15,10,WIDE,SMALL_A,NO_HFLIP,DO_VFLIP,LZSS_COMPRESSION,0,1},
    {alisa_swordslash_side_image4,-2,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0}};

const SpriteLayerSet alisa_swordslash_left_layerSet[] = {
    {alisa_swordslash_left_layerSet0,5,2},
    {alisa_swordslash_left_layerSet1,7,2},
    {alisa_swordslash_left_layerSet2,1,2},
    {alisa_swordslash_left_layerSet3,1,2},
    {alisa_swordslash_left_layerSet4,10,2},
};

const SpriteSet alisa_swordslash_left = {alisa_swordslash_left_layerSet,5};
