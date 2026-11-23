#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageAlisa.h"

const SpriteLayer alisa_jumpdownwardslash_right_layerSet0[] = {
    {sword_vertical_set_image0,-2,-1,TALL,SMALL_B,NO_HFLIP,DO_VFLIP,NO_COMPRESSION,0,1},
    {alisa_jumpdownwardslash_side_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};
const SpriteLayer alisa_jumpdownwardslash_right_layerSet1[] = {
    {sword_side_set_image2,-25,0,WIDE,SMALL_B,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,1},
    {alisa_jumpdownwardslash_side_image1,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};
const SpriteLayer alisa_jumpdownwardslash_right_layerSet2[] = {
    {sword_side_set_image0,-20,-5,WIDE,SMALL_B,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,1},
    {alisa_jumpdownwardslash_side_image2,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};
const SpriteLayer alisa_jumpdownwardslash_right_layerSet3[] = {
    {sword_vertical_set_image0,13,-24,TALL,SMALL_B,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,1},
    {alisa_jumpdownwardslash_side_image3,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};
const SpriteLayer alisa_jumpdownwardslash_right_layerSet4[] = {
    {sword_side_set_image0,12,12,WIDE,SMALL_B,DO_HFLIP,DO_VFLIP,NO_COMPRESSION,0,1},
    {alisa_jumpdownwardslash_side_image4,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};

const SpriteLayerSet alisa_jumpdownwardslash_right_layerSet[] = {
    {alisa_jumpdownwardslash_right_layerSet0,2,2},
    {alisa_jumpdownwardslash_right_layerSet1,2,2},
    {alisa_jumpdownwardslash_right_layerSet2,2,2},
    {alisa_jumpdownwardslash_right_layerSet3,2,2},
    {alisa_jumpdownwardslash_right_layerSet4,10,2},
};

const SpriteSet alisa_jumpdownwardslash_right = {alisa_jumpdownwardslash_right_layerSet,5};
