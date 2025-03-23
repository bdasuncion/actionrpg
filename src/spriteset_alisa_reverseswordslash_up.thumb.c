#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageAlisa.h"

const SpriteLayer alisa_reverseswordslash_up_layerSet0[] = {
    {sword_vertical_set_image2,0,12,TALL,SMALL_B,NO_HFLIP,DO_VFLIP,NO_COMPRESSION,0,1},
    {alisa_reverseswordslash_up_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};
const SpriteLayer alisa_reverseswordslash_up_layerSet1[] = {
    {alisa_reverseswordslash_up_image1,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {sword_side_set_image2,-27,9,WIDE,SMALL_B,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,8,1}};
const SpriteLayer alisa_reverseswordslash_up_layerSet2[] = {
    {alisa_reverseswordslash_up_image2,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {sword_vertical_set_image2,0,-23,TALL,SMALL_B,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,8,1}};
const SpriteLayer alisa_reverseswordslash_up_layerSet3[] = {
    {alisa_reverseswordslash_up_image3,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {sword_vertical_set_image0,12,-24,TALL,SMALL_B,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,8,1}};

const SpriteLayerSet alisa_reverseswordslash_up_layerSet[] = {
    {alisa_reverseswordslash_up_layerSet0,10,2},
    {alisa_reverseswordslash_up_layerSet1,2,2},
    {alisa_reverseswordslash_up_layerSet2,2,2},
    {alisa_reverseswordslash_up_layerSet3,10,2},
};

const SpriteSet alisa_reverseswordslash_up = {alisa_reverseswordslash_up_layerSet,4};
