#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageZombie.h"

const SpriteLayer zombie_chase_down_layerSet0[] = {
    {zombie_walk_down_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0}};
const SpriteLayer zombie_chase_down_layerSet1[] = {
    {zombie_walk_down_image1,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0}};
const SpriteLayer zombie_chase_down_layerSet2[] = {
    {zombie_walk_down_image2,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0}};
const SpriteLayer zombie_chase_down_layerSet3[] = {
    {zombie_walk_down_image3,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0}};

const SpriteLayerSet zombie_chase_down_layerSet[] = {
    {zombie_chase_down_layerSet0,15,1},
    {zombie_chase_down_layerSet1,5,1},
    {zombie_chase_down_layerSet2,15,1},
    {zombie_chase_down_layerSet3,5,1},
};

const SpriteSet zombie_chase_down = {zombie_chase_down_layerSet,4};
