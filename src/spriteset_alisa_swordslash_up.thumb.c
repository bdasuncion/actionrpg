#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageAlisa.h"

const SpriteLayer alisa_swordslash_up_layerSet0[] = {
    {alisa_swordslash_up_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {sword_side_set_image2,10,13,WIDE,SMALL_B,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,8,1}};
const SpriteLayer alisa_swordslash_up_layerSet1[] = {
    {alisa_swordslash_up_image1,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {sword_side_set_image2,11,8,WIDE,SMALL_B,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,8,1}};
const SpriteLayer alisa_swordslash_up_layerSet2[] = {
    {alisa_swordslash_up_image2,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {sword_vertical_set_image1,4,-22,TALL,SMALL_B,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,8,1}};
const SpriteLayer alisa_swordslash_up_layerSet3[] = {
    {sword_vertical_set_image0,-4,-24,TALL,SMALL_B,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,1},
    {alisa_swordslash_up_image3,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};

const SpriteLayerSet alisa_swordslash_up_layerSet[] = {
    {alisa_swordslash_up_layerSet0,2,2},
    {alisa_swordslash_up_layerSet1,2,2},
    {alisa_swordslash_up_layerSet2,2,2},
    {alisa_swordslash_up_layerSet3,20,2},
};

const SpriteSet alisa_swordslash_up = {alisa_swordslash_up_layerSet,4};
