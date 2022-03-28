#include "GBATypes.h"
#include "GBAObject.h"
#include "ImageZombie.h"

const SpriteLayer zombie_chase_left_layerSet0[] = {
    {zombie_walk_side_image0,0,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0}};
const SpriteLayer zombie_chase_left_layerSet1[] = {
    {zombie_walk_side_image1,0,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0}};
const SpriteLayer zombie_chase_left_layerSet2[] = {
    {zombie_walk_side_image2,0,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0}};
const SpriteLayer zombie_chase_left_layerSet3[] = {
    {zombie_walk_side_image3,0,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0}};

const SpriteLayerSet zombie_chase_left_layerSet[] = {
    {zombie_chase_left_layerSet0,15,1},
    {zombie_chase_left_layerSet1,10,1},
    {zombie_chase_left_layerSet2,15,1},
    {zombie_chase_left_layerSet3,10,1},
};

const SpriteSet zombie_chase_left = {zombie_chase_left_layerSet,4};
