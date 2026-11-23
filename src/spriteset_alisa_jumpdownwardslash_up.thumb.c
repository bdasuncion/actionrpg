#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageAlisa.h"

const SpriteLayer alisa_jumpdownwardslash_up_layerSet0[] = {
    {sword_vertical_set_image1,4,0,TALL,SMALL_B,NO_HFLIP,DO_VFLIP,NO_COMPRESSION,0,1},
    {alisa_jumpdownwardslash_up_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};
const SpriteLayer alisa_jumpdownwardslash_up_layerSet1[] = {
    {sword_vertical_set_image3,4,2,TALL,SMALL_B,NO_HFLIP,DO_VFLIP,NO_COMPRESSION,0,1},
    {alisa_jumpdownwardslash_up_image1,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};
const SpriteLayer alisa_jumpdownwardslash_up_layerSet2[] = {
    {sword_vertical_set_image3,4,0,TALL,SMALL_B,NO_HFLIP,DO_VFLIP,NO_COMPRESSION,0,1},
    {alisa_jumpdownwardslash_up_image2,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};
const SpriteLayer alisa_jumpdownwardslash_up_layerSet3[] = {
    {alisa_jumpdownwardslash_up_image3,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {sword_vertical_set_image3,3,-20,TALL,SMALL_B,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,8,1}};
const SpriteLayer alisa_jumpdownwardslash_up_layerSet4[] = {
    {alisa_jumpdownwardslash_up_image3,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0}};

const SpriteLayerSet alisa_jumpdownwardslash_up_layerSet[] = {
    {alisa_jumpdownwardslash_up_layerSet0,2,2},
    {alisa_jumpdownwardslash_up_layerSet1,2,2},
    {alisa_jumpdownwardslash_up_layerSet2,2,2},
    {alisa_jumpdownwardslash_up_layerSet3,2,2},
    {alisa_jumpdownwardslash_up_layerSet4,10,1},
};

const SpriteSet alisa_jumpdownwardslash_up = {alisa_jumpdownwardslash_up_layerSet,5};
