#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageSkullDemon.h"

const SpriteLayer skull_demon_walking_right_layerSet0[] = {
    {skull_demon_arm_side_image0,7,1,TALL,SMALL_B,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {skull_demon_head_side_image0,9,-5,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0},
    {skull_demon_upper_side_image0,0,0,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {skull_demon_walking_side_image0,0,16,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};
const SpriteLayer skull_demon_walking_right_layerSet1[] = {
    {skull_demon_arm_side_image0,7,1,TALL,SMALL_B,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {skull_demon_head_side_image0,9,-5,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0},
    {skull_demon_upper_side_image0,0,0,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {skull_demon_walking_side_image1,0,16,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};
const SpriteLayer skull_demon_walking_right_layerSet2[] = {
    {skull_demon_arm_side_image0,5,1,TALL,SMALL_B,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {skull_demon_walking_side_image0,0,16,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0},
    {skull_demon_head_side_image0,9,-5,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0},
    {skull_demon_upper_side_image0,0,0,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0}};
const SpriteLayer skull_demon_walking_right_layerSet3[] = {
    {skull_demon_arm_side_image0,5,1,TALL,SMALL_B,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {skull_demon_head_side_image0,9,-5,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0},
    {skull_demon_upper_side_image0,0,0,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {skull_demon_walking_side_image2,-1,16,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};

const SpriteLayerSet skull_demon_walking_right_layerSet[] = {
    {skull_demon_walking_right_layerSet0,10,4},
    {skull_demon_walking_right_layerSet1,10,4},
    {skull_demon_walking_right_layerSet2,10,4},
    {skull_demon_walking_right_layerSet3,10,4},
};

const SpriteSet skull_demon_walking_right = {skull_demon_walking_right_layerSet,4};
