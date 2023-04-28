#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageZombie.h"

const SpriteLayer zombie_walk_right_layerSet0[] = {
    {zombie_walk_side_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0}};
const SpriteLayer zombie_walk_right_layerSet1[] = {
    {zombie_walk_side_image1,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0}};
const SpriteLayer zombie_walk_right_layerSet2[] = {
    {zombie_walk_side_image2,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0}};
const SpriteLayer zombie_walk_right_layerSet3[] = {
    {zombie_walk_side_image3,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0}};

const SpriteLayerSet zombie_walk_right_layerSet[] = {
    {zombie_walk_right_layerSet0,15,1},
    {zombie_walk_right_layerSet1,15,1},
    {zombie_walk_right_layerSet2,15,1},
    {zombie_walk_right_layerSet3,15,1},
};

const SpriteSet zombie_walk_right = {zombie_walk_right_layerSet,4};
