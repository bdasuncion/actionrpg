#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageGhoul.h"

const SpriteLayer ghoul_attack_left_layerSet0[] = {
    {ghoul_arm_attack_side_image1,4,6,SQUARE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {ghoul_arm_attack_side_image0,5,4,SQUARE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_head_side_image1,0,-2,SQUARE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_head_side_image0,3,-6,SQUARE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_body_attack_side_image0,0,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0}};
const SpriteLayer ghoul_attack_left_layerSet1[] = {
    {ghoul_arm_attack_side_image2,5,4,SQUARE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {ghoul_head_side_image1,0,-2,SQUARE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_head_side_image0,3,-6,SQUARE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_body_attack_side_image0,0,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0}};
const SpriteLayer ghoul_attack_left_layerSet2[] = {
    {ghoul_arm_attack_side_image3,7,1,SQUARE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {ghoul_arm_attack_side_image0,5,3,SQUARE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_head_side_image1,3,-2,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_head_side_image0,3,-6,SQUARE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_body_attack_side_image0,0,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0}};
const SpriteLayer ghoul_attack_left_layerSet3[] = {
    {ghoul_arm_attack_side_image5,-3,3,SQUARE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {ghoul_arm_attack_side_image4,2,3,SQUARE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_head_side_image1,1,-2,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_head_side_image0,1,-6,SQUARE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_body_attack_side_image1,0,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0}};
const SpriteLayer ghoul_attack_left_layerSet4[] = {
    {ghoul_arm_attack_side_image5,-7,1,SQUARE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {ghoul_arm_attack_side_image4,1,2,SQUARE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_head_side_image1,1,-2,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_head_side_image0,1,-6,SQUARE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_body_attack_side_image1,0,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0}};
const SpriteLayer ghoul_attack_left_layerSet5[] = {
    {ghoul_arm_attack_side_image6,-5,0,SQUARE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {ghoul_arm_attack_side_image4,1,2,SQUARE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_head_side_image1,1,-2,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_head_side_image0,1,-6,SQUARE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_body_attack_side_image1,0,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0}};

const SpriteLayerSet ghoul_attack_left_layerSet[] = {
    {ghoul_attack_left_layerSet0,2,5},
    {ghoul_attack_left_layerSet1,15,4},
    {ghoul_attack_left_layerSet2,20,5},
    {ghoul_attack_left_layerSet3,3,5},
    {ghoul_attack_left_layerSet4,3,5},
    {ghoul_attack_left_layerSet5,3,5},
};

const SpriteSet ghoul_attack_left = {ghoul_attack_left_layerSet,6};
