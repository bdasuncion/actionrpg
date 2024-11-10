#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageSkullDemon.h"

const SpriteLayer skull_demon_walking_up_layerSet0[] = {
    {skull_demon_arm_down_image1,9,3,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {skull_demon_arm_down_image0,-1,3,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {skull_demon_walking_up_image0,0,16,SQUARE,SMALL_B,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {skull_demon_upper_up_image0,0,0,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0},
    {skull_demon_head_up_image0,4,-4,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,1}};
const SpriteLayer skull_demon_walking_up_layerSet1[] = {
    {skull_demon_arm_down_image1,9,3,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {skull_demon_arm_down_image0,-1,3,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {skull_demon_walking_up_image1,0,16,SQUARE,SMALL_B,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {skull_demon_upper_up_image0,0,0,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0},
    {skull_demon_head_up_image0,4,-4,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,1}};
const SpriteLayer skull_demon_walking_up_layerSet2[] = {
    {skull_demon_arm_down_image1,-1,2,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {skull_demon_arm_down_image0,9,3,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {skull_demon_walking_up_image0,0,16,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {skull_demon_upper_up_image0,0,0,SQUARE,SMALL_B,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0},
    {skull_demon_head_up_image0,4,-4,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,1}};
const SpriteLayer skull_demon_walking_up_layerSet3[] = {
    {skull_demon_arm_down_image1,-1,2,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {skull_demon_arm_down_image0,9,3,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {skull_demon_walking_up_image1,0,16,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {skull_demon_upper_up_image0,0,0,SQUARE,SMALL_B,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0},
    {skull_demon_head_up_image0,4,-4,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,1}};

const SpriteLayerSet skull_demon_walking_up_layerSet[] = {
    {skull_demon_walking_up_layerSet0,10,5},
    {skull_demon_walking_up_layerSet1,10,5},
    {skull_demon_walking_up_layerSet2,10,5},
    {skull_demon_walking_up_layerSet3,10,5},
};

const SpriteSet skull_demon_walking_up = {skull_demon_walking_up_layerSet,4};
