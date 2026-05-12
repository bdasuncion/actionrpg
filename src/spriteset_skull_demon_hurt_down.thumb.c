#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageSkullDemon.h"

const SpriteLayer skull_demon_hurt_down_layerSet0[] = {
    {skull_demon_head_side_image0,2,-7,SQUARE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {skull_demon_arm_down_image0,9,3,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {skull_demon_arm_down_image4,-3,2,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {skull_demon_walking_down_image1,0,16,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {skull_demon_upper_down_image0,0,0,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};

const SpriteLayerSet skull_demon_hurt_down_layerSet[] = {
    {skull_demon_hurt_down_layerSet0,10,5},
};

const SpriteSet skull_demon_hurt_down = {skull_demon_hurt_down_layerSet,1};
