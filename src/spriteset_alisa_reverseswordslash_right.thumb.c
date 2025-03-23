#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageAlisa.h"

const SpriteLayer alisa_reverseswordslash_right_layerSet0[] = {
    {alisa_reverseswordslash_side_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {sword_side_set_image2,-23,11,WIDE,SMALL_B,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,8,1}};
const SpriteLayer alisa_reverseswordslash_right_layerSet1[] = {
    {alisa_reverseswordslash_side_image1,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {sword_side_set_image2,-20,9,WIDE,SMALL_B,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,8,1}};
const SpriteLayer alisa_reverseswordslash_right_layerSet2[] = {
    {alisa_reverseswordslash_side_image2,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {sword_side_set_image1,13,6,WIDE,SMALL_B,DO_HFLIP,DO_VFLIP,NO_COMPRESSION,8,1}};
const SpriteLayer alisa_reverseswordslash_right_layerSet3[] = {
    {sword_side_set_image0,10,12,WIDE,SMALL_B,DO_HFLIP,DO_VFLIP,NO_COMPRESSION,0,1},
    {alisa_reverseswordslash_side_image3,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};

const SpriteLayerSet alisa_reverseswordslash_right_layerSet[] = {
    {alisa_reverseswordslash_right_layerSet0,10,2},
    {alisa_reverseswordslash_right_layerSet1,2,2},
    {alisa_reverseswordslash_right_layerSet2,2,2},
    {alisa_reverseswordslash_right_layerSet3,10,2},
};

const SpriteSet alisa_reverseswordslash_right = {alisa_reverseswordslash_right_layerSet,4};
