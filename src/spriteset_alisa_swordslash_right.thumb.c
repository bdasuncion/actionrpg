#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageAlisa.h"

const SpriteLayer alisa_swordslash_right_layerSet0[] = {
    {sword_side_set_image0,-26,13,WIDE,SMALL_B,NO_HFLIP,DO_VFLIP,NO_COMPRESSION,0,1},
    {alisa_swordslash_side_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};
const SpriteLayer alisa_swordslash_right_layerSet1[] = {
    {sword_vertical_set_image2,1,14,TALL,SMALL_B,DO_HFLIP,DO_VFLIP,NO_COMPRESSION,0,1},
    {alisa_swordslash_side_image1,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};
const SpriteLayer alisa_swordslash_right_layerSet2[] = {
    {sword_vertical_set_image0,12,15,TALL,SMALL_B,DO_HFLIP,DO_VFLIP,NO_COMPRESSION,0,1},
    {alisa_swordslash_side_image2,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};
const SpriteLayer alisa_swordslash_right_layerSet3[] = {
    {sword_side_set_image0,13,4,WIDE,SMALL_B,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,1},
    {alisa_swordslash_side_image3,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};

const SpriteLayerSet alisa_swordslash_right_layerSet[] = {
    {alisa_swordslash_right_layerSet0,2,2},
    {alisa_swordslash_right_layerSet1,2,2},
    {alisa_swordslash_right_layerSet2,2,2},
    {alisa_swordslash_right_layerSet3,20,2},
};

const SpriteSet alisa_swordslash_right = {alisa_swordslash_right_layerSet,4};
