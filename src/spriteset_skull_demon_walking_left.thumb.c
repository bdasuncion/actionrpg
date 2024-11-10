#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageSkullDemon.h"

const SpriteLayer skull_demon_walking_left_layerSet0[] = {
    {skull_demon_arm_side_image0,1,1,TALL,SMALL_B,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {skull_demon_head_side_image0,-1,-5,SQUARE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,1},
    {skull_demon_upper_side_image0,0,0,SQUARE,SMALL_B,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {skull_demon_walking_side_image0,0,16,SQUARE,SMALL_B,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};
const SpriteLayer skull_demon_walking_left_layerSet1[] = {
    {skull_demon_arm_side_image0,1,1,TALL,SMALL_B,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {skull_demon_head_side_image0,-1,-5,SQUARE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,1},
    {skull_demon_upper_side_image0,0,0,SQUARE,SMALL_B,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {skull_demon_walking_side_image1,0,16,SQUARE,SMALL_B,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};
const SpriteLayer skull_demon_walking_left_layerSet2[] = {
    {skull_demon_walking_side_image0,0,16,SQUARE,SMALL_B,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {skull_demon_arm_side_image0,2,1,TALL,SMALL_B,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0},
    {skull_demon_head_side_image0,-1,-5,SQUARE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,1},
    {skull_demon_upper_side_image0,0,0,SQUARE,SMALL_B,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0}};
const SpriteLayer skull_demon_walking_left_layerSet3[] = {
    {skull_demon_arm_side_image0,2,1,TALL,SMALL_B,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {skull_demon_head_side_image0,-1,-5,SQUARE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,1},
    {skull_demon_upper_side_image0,0,0,SQUARE,SMALL_B,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {skull_demon_walking_side_image2,1,16,SQUARE,SMALL_B,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};

const SpriteLayerSet skull_demon_walking_left_layerSet[] = {
    {skull_demon_walking_left_layerSet0,10,4},
    {skull_demon_walking_left_layerSet1,10,4},
    {skull_demon_walking_left_layerSet2,10,4},
    {skull_demon_walking_left_layerSet3,10,4},
};

const SpriteSet skull_demon_walking_left = {skull_demon_walking_left_layerSet,4};
