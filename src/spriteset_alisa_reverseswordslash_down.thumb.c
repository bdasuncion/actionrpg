#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageAlisa.h"

const SpriteLayer alisa_reverseswordslash_down_layerSet0[] = {
    {sword_vertical_set_image0,11,-16,TALL,SMALL_B,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,1},
    {alisa_reverseswordslash_down_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};
const SpriteLayer alisa_reverseswordslash_down_layerSet1[] = {
    {alisa_reverseswordslash_down_image1,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {sword_side_set_image2,9,11,WIDE,SMALL_B,DO_HFLIP,DO_VFLIP,NO_COMPRESSION,8,1}};
const SpriteLayer alisa_reverseswordslash_down_layerSet2[] = {
    {sword_vertical_set_image2,6,14,TALL,SMALL_B,NO_HFLIP,DO_VFLIP,NO_COMPRESSION,0,1},
    {alisa_reverseswordslash_down_image2,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};
const SpriteLayer alisa_reverseswordslash_down_layerSet3[] = {
    {sword_vertical_set_image0,-2,11,TALL,SMALL_B,NO_HFLIP,DO_VFLIP,NO_COMPRESSION,0,1},
    {alisa_reverseswordslash_down_image3,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};

const SpriteLayerSet alisa_reverseswordslash_down_layerSet[] = {
    {alisa_reverseswordslash_down_layerSet0,10,2},
    {alisa_reverseswordslash_down_layerSet1,2,2},
    {alisa_reverseswordslash_down_layerSet2,2,2},
    {alisa_reverseswordslash_down_layerSet3,10,2},
};

const SpriteSet alisa_reverseswordslash_down = {alisa_reverseswordslash_down_layerSet,4};
