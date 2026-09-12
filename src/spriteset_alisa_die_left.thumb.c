#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageAlisa.h"

const SpriteLayer alisa_die_left_layerSet0[] = {
    {alisa_die_image0,0,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0}};
const SpriteLayer alisa_die_left_layerSet1[] = {
    {alisa_die_image1,0,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0}};
const SpriteLayer alisa_die_left_layerSet2[] = {
    {alisa_die_image2,0,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0}};
const SpriteLayer alisa_die_left_layerSet3[] = {
    {alisa_die_image3,0,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0}};
const SpriteLayer alisa_die_left_layerSet4[] = {
    {alisa_die_final_image0,-15,18,WIDE,MEDIUM,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0}};

const SpriteLayerSet alisa_die_left_layerSet[] = {
    {alisa_die_left_layerSet0,8,1},
    {alisa_die_left_layerSet1,8,1},
    {alisa_die_left_layerSet2,8,1},
    {alisa_die_left_layerSet3,8,1},
    {alisa_die_left_layerSet4,20,1},
};

const SpriteSet alisa_die_left = {alisa_die_left_layerSet,5};
