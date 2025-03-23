#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageAlisa.h"

const SpriteLayer alisa_reverseswordslash_left_layerSet0[] = {
    {alisa_reverseswordslash_side_image0,0,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {sword_side_set_image2,7,11,WIDE,SMALL_B,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,8,1}};
const SpriteLayer alisa_reverseswordslash_left_layerSet1[] = {
    {alisa_reverseswordslash_side_image1,0,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {sword_side_set_image2,4,9,WIDE,SMALL_B,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,8,1}};
const SpriteLayer alisa_reverseswordslash_left_layerSet2[] = {
    {sword_side_set_image1,-29,6,WIDE,SMALL_B,NO_HFLIP,DO_VFLIP,NO_COMPRESSION,0,1},
    {alisa_reverseswordslash_side_image2,0,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};
const SpriteLayer alisa_reverseswordslash_left_layerSet3[] = {
    {sword_side_set_image0,-26,12,WIDE,SMALL_B,NO_HFLIP,DO_VFLIP,NO_COMPRESSION,0,1},
    {alisa_reverseswordslash_side_image3,0,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};

const SpriteLayerSet alisa_reverseswordslash_left_layerSet[] = {
    {alisa_reverseswordslash_left_layerSet0,10,2},
    {alisa_reverseswordslash_left_layerSet1,2,2},
    {alisa_reverseswordslash_left_layerSet2,2,2},
    {alisa_reverseswordslash_left_layerSet3,10,2},
};

const SpriteSet alisa_reverseswordslash_left = {alisa_reverseswordslash_left_layerSet,4};
