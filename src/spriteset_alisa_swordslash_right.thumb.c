#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageAlisa.h"

const SpriteLayer alisa_swordslash_right_layerSet0[] = {
    {sword_side_image1,-26,13,WIDE,SMALL_B,NO_HFLIP,DO_VFLIP,LZSS_COMPRESSION,0,1},
    {alisa_swordslash_side_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0}};
const SpriteLayer alisa_swordslash_right_layerSet1[] = {
    {sword_vertical_image2,0,15,TALL,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,1},
    {alisa_swordslash_side_image1,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0}};
const SpriteLayer alisa_swordslash_right_layerSet2[] = {
    {sword_vertical_image1,10,16,TALL,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,1},
    {alisa_swordslash_side_image2,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0}};
const SpriteLayer alisa_swordslash_right_layerSet3[] = {
    {alisa_swordslash_side_image3,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {sword_side_image0,13,7,WIDE,SMALL_B,DO_HFLIP,DO_VFLIP,LZSS_COMPRESSION,8,1}};

const SpriteLayerSet alisa_swordslash_right_layerSet[] = {
    {alisa_swordslash_right_layerSet0,2,2},
    {alisa_swordslash_right_layerSet1,2,2},
    {alisa_swordslash_right_layerSet2,2,2},
    {alisa_swordslash_right_layerSet3,20,2},
};

const SpriteSet alisa_swordslash_right = {alisa_swordslash_right_layerSet,4};

