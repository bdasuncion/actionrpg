#include "GBATypes.h"
#include "GBAObject.h"
#include "ImageAlisa.h"

const SpriteLayer alisa_swordslash_right_layerSet0[] = {
    {sword_side_image0,-7,16,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,1},
    {alisa_swordslash_side_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0}};
const SpriteLayer alisa_swordslash_right_layerSet1[] = {
    {sword_side_image1,-8,13,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,1},
    {alisa_swordslash_side_image1,2,1,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0}};
const SpriteLayer alisa_swordslash_right_layerSet2[] = {
    {sword_vertical_image0,2,18,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,2},
    {alisa_swordslash_side_image2,2,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0}};
const SpriteLayer alisa_swordslash_right_layerSet3[] = {
    {sword_side_image1,13,16,WIDE,SMALL_A,DO_HFLIP,DO_VFLIP,LZSS_COMPRESSION,0,1},
    {alisa_swordslash_side_image3,2,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0}};
const SpriteLayer alisa_swordslash_right_layerSet4[] = {
    {sword_side_image0,15,10,WIDE,SMALL_A,DO_HFLIP,DO_VFLIP,LZSS_COMPRESSION,0,1},
    {alisa_swordslash_side_image4,2,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0}};

const SpriteLayerSet alisa_swordslash_right_layerSet[] = {
    {alisa_swordslash_right_layerSet0,5,2},
    {alisa_swordslash_right_layerSet1,7,2},
    {alisa_swordslash_right_layerSet2,1,2},
    {alisa_swordslash_right_layerSet3,1,2},
    {alisa_swordslash_right_layerSet4,10,2},
};

const SpriteSet alisa_swordslash_right = {alisa_swordslash_right_layerSet,5};
