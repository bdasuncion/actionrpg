#include "GBATypes.h"
#include "GBAObject.h"
#include "ImageAlisa.h"

const SpriteLayer alisa_swordslash_up_layerSet0[] = {
    {alisa_swordslash_up_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {sword_side_image1,10,15,WIDE,SMALL_A,DO_HFLIP,DO_VFLIP,LZSS_COMPRESSION,8,1}};
const SpriteLayer alisa_swordslash_up_layerSet1[] = {
    {sword_vertical_image1,9,16,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,1},
    {alisa_swordslash_up_image1,0,-1,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0}};
const SpriteLayer alisa_swordslash_up_layerSet2[] = {
    {alisa_swordslash_up_image2,0,-1,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {sword_side_image0,10,10,WIDE,SMALL_A,DO_HFLIP,DO_VFLIP,LZSS_COMPRESSION,8,1}};
const SpriteLayer alisa_swordslash_up_layerSet3[] = {
    {alisa_swordslash_up_image3,0,-1,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {sword_vertical_image1,4,-3,TALL,SMALL_A,DO_HFLIP,DO_VFLIP,LZSS_COMPRESSION,8,1}};
const SpriteLayer alisa_swordslash_up_layerSet4[] = {
    {alisa_swordslash_up_image4,0,-1,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {sword_vertical_image1,-2,-3,TALL,SMALL_A,DO_HFLIP,DO_VFLIP,LZSS_COMPRESSION,8,1}};

const SpriteLayerSet alisa_swordslash_up_layerSet[] = {
    {alisa_swordslash_up_layerSet0,5,2},
    {alisa_swordslash_up_layerSet1,7,2},
    {alisa_swordslash_up_layerSet2,1,2},
    {alisa_swordslash_up_layerSet3,1,2},
    {alisa_swordslash_up_layerSet4,10,2},
};

const SpriteSet alisa_swordslash_up = {alisa_swordslash_up_layerSet,5};
