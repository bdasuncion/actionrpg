#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageSkullDemon.h"

const SpriteLayer skull_demon_hurt_left_layerSet0[] = {
    {skull_demon_head_down_image0,1,-5,SQUARE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {skull_demon_arm_side_image1,4,0,TALL,SMALL_B,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {skull_demon_upper_side_image0,0,0,SQUARE,SMALL_B,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0},
    {skull_demon_walking_side_image1,0,16,SQUARE,SMALL_B,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0},
    {skull_demon_arm_side_image2,1,0,TALL,SMALL_B,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};

const SpriteLayerSet skull_demon_hurt_left_layerSet[] = {
    {skull_demon_hurt_left_layerSet0,10,5},
};

const SpriteSet skull_demon_hurt_left = {skull_demon_hurt_left_layerSet,1};
