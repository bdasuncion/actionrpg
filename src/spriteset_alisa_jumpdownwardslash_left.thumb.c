#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageAlisa.h"

const SpriteLayer alisa_jumpdownwardslash_left_layerSet0[] = {
    {sword_vertical_set_image0,10,-1,TALL,SMALL_B,DO_HFLIP,DO_VFLIP,NO_COMPRESSION,0,1},
    {alisa_jumpdownwardslash_side_image0,0,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};
const SpriteLayer alisa_jumpdownwardslash_left_layerSet1[] = {
    {sword_side_set_image2,9,0,WIDE,SMALL_B,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,1},
    {alisa_jumpdownwardslash_side_image1,0,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};
const SpriteLayer alisa_jumpdownwardslash_left_layerSet2[] = {
    {sword_side_set_image0,4,-5,WIDE,SMALL_B,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,1},
    {alisa_jumpdownwardslash_side_image2,0,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};
const SpriteLayer alisa_jumpdownwardslash_left_layerSet3[] = {
    {sword_vertical_set_image0,-5,-24,TALL,SMALL_B,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,1},
    {alisa_jumpdownwardslash_side_image3,0,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};
const SpriteLayer alisa_jumpdownwardslash_left_layerSet4[] = {
    {sword_side_set_image0,-28,12,WIDE,SMALL_B,NO_HFLIP,DO_VFLIP,NO_COMPRESSION,0,1},
    {alisa_jumpdownwardslash_side_image4,0,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};

const SpriteLayerSet alisa_jumpdownwardslash_left_layerSet[] = {
    {alisa_jumpdownwardslash_left_layerSet0,2,2},
    {alisa_jumpdownwardslash_left_layerSet1,2,2},
    {alisa_jumpdownwardslash_left_layerSet2,2,2},
    {alisa_jumpdownwardslash_left_layerSet3,2,2},
    {alisa_jumpdownwardslash_left_layerSet4,10,2},
};

const SpriteSet alisa_jumpdownwardslash_left = {alisa_jumpdownwardslash_left_layerSet,5};
