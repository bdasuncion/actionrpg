#include "GBATypes.h"
#include "GBAObject.h"
#include "ImageAlisa.h"

const SpriteLayer alisa_swordslash_down_layerSet0[] = {
    {alisa_swordslash_down_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {sword_side_image0,-8,12,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,8,1}};
const SpriteLayer alisa_swordslash_down_layerSet1[] = {
    {alisa_swordslash_down_image1,0,1,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {sword_side_image1,-10,10,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,8,1}};
const SpriteLayer alisa_swordslash_down_layerSet2[] = {
    {alisa_swordslash_down_image2,0,1,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {sword_side_image0,-8,16,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,8,1}};
const SpriteLayer alisa_swordslash_down_layerSet3[] = {
    {sword_vertical_image0,1,21,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,1},
    {alisa_swordslash_down_image3,0,1,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0}};
const SpriteLayer alisa_swordslash_down_layerSet4[] = {
    {sword_vertical_image1,11,19,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,1},
    {alisa_swordslash_down_image4,0,1,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0}};

const SpriteLayerSet alisa_swordslash_down_layerSet[] = {
    {alisa_swordslash_down_layerSet0,5,2},
    {alisa_swordslash_down_layerSet1,7,2},
    {alisa_swordslash_down_layerSet2,1,2},
    {alisa_swordslash_down_layerSet3,1,2},
    {alisa_swordslash_down_layerSet4,10,2},
};

const SpriteSet alisa_swordslash_down = {alisa_swordslash_down_layerSet,5};
