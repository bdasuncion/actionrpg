#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageAlisa.h"

const SpriteLayer alisa_swordslash_down_layerSet0[] = {
    {sword_side_image3,-25,11,WIDE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,1},
    {alisa_swordslash_down_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0}};
const SpriteLayer alisa_swordslash_down_layerSet1[] = {
    {sword_side_image0,-25,13,WIDE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,1},
    {alisa_swordslash_down_image1,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0}};
const SpriteLayer alisa_swordslash_down_layerSet2[] = {
    {sword_vertical_image2,4,15,TALL,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,1},
    {alisa_swordslash_down_image2,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0}};
const SpriteLayer alisa_swordslash_down_layerSet3[] = {
    {sword_vertical_image1,9,14,TALL,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,1},
    {alisa_swordslash_down_image3,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0}};

const SpriteLayerSet alisa_swordslash_down_layerSet[] = {
    {alisa_swordslash_down_layerSet0,2,2},
    {alisa_swordslash_down_layerSet1,2,2},
    {alisa_swordslash_down_layerSet2,2,2},
    {alisa_swordslash_down_layerSet3,20,2},
};

const SpriteSet alisa_swordslash_down = {alisa_swordslash_down_layerSet,4};
