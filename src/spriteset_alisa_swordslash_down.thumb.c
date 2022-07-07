#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageAlisa.h"

const SpriteLayer alisa_swordslash_down_layerSet0[] = {
    {alisa_swordslash_down_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {sword_side_image1,-10,10,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,8,1}};
const SpriteLayer alisa_swordslash_down_layerSet1[] = {
    {alisa_swordslash_down_image1,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {sword_side_image0,-8,16,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,8,1}};
const SpriteLayer alisa_swordslash_down_layerSet2[] = {
    {sword_vertical_image0,1,20,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,1},
    {alisa_swordslash_down_image2,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0}};
const SpriteLayer alisa_swordslash_down_layerSet3[] = {
    {alisa_swordslash_down_image3,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {sword_vertical_image1,11,17,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,8,1}};

const SpriteLayerSet alisa_swordslash_down_layerSet[] = {
    {alisa_swordslash_down_layerSet0,2,2},
    {alisa_swordslash_down_layerSet1,2,2},
    {alisa_swordslash_down_layerSet2,2,2},
    {alisa_swordslash_down_layerSet3,20,2},
};

const SpriteSet alisa_swordslash_down = {alisa_swordslash_down_layerSet,4};

