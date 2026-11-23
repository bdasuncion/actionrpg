#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageAlisa.h"

const SpriteLayer alisa_jumpdownwardslash_down_layerSet0[] = {
    {alisa_jumpdownwardslash_down_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0}};
const SpriteLayer alisa_jumpdownwardslash_down_layerSet1[] = {
    {alisa_jumpdownwardslash_down_image1,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {sword_vertical_set_image3,3,-1,TALL,SMALL_B,DO_HFLIP,DO_VFLIP,NO_COMPRESSION,8,1}};
const SpriteLayer alisa_jumpdownwardslash_down_layerSet2[] = {
    {alisa_jumpdownwardslash_down_image2,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {sword_vertical_set_image3,6,-27,TALL,SMALL_B,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,8,1}};
const SpriteLayer alisa_jumpdownwardslash_down_layerSet3[] = {
    {sword_vertical_set_image3,6,-23,TALL,SMALL_B,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,1},
    {alisa_jumpdownwardslash_down_image3,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};
const SpriteLayer alisa_jumpdownwardslash_down_layerSet4[] = {
    {sword_vertical_set_image3,3,9,TALL,SMALL_B,DO_HFLIP,DO_VFLIP,NO_COMPRESSION,0,1},
    {alisa_jumpdownwardslash_down_image4,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};

const SpriteLayerSet alisa_jumpdownwardslash_down_layerSet[] = {
    {alisa_jumpdownwardslash_down_layerSet0,2,1},
    {alisa_jumpdownwardslash_down_layerSet1,2,2},
    {alisa_jumpdownwardslash_down_layerSet2,2,2},
    {alisa_jumpdownwardslash_down_layerSet3,2,2},
    {alisa_jumpdownwardslash_down_layerSet4,10,2},
};

const SpriteSet alisa_jumpdownwardslash_down = {alisa_jumpdownwardslash_down_layerSet,5};
