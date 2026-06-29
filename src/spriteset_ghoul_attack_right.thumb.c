
#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageGhoul.h"
const SpriteLayer ghoul_attack_right_layerSet0[] = {
    {ghoul_arm_attack_side_image1,4,6,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {ghoul_arm_attack_side_image0,3,4,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_head_side_image1,8,-2,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_head_side_image0,5,-6,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_body_attack_side_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0}};
const SpriteLayer ghoul_attack_right_layerSet1[] = {
    {ghoul_arm_attack_side_image2,3,4,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {ghoul_head_side_image1,8,-2,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_head_side_image0,5,-6,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_body_attack_side_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0}};
const SpriteLayer ghoul_attack_right_layerSet2[] = {
    {ghoul_arm_attack_side_image3,1,1,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {ghoul_arm_attack_side_image0,3,3,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_head_side_image1,6,-2,SQUARE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_head_side_image0,5,-6,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_body_attack_side_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0}};
const SpriteLayer ghoul_attack_right_layerSet3[] = {
    {ghoul_arm_attack_side_image5,12,3,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {ghoul_arm_attack_side_image4,6,3,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_head_side_image1,8,-2,SQUARE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_head_side_image0,7,-6,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_body_attack_side_image1,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0}};
const SpriteLayer ghoul_attack_right_layerSet4[] = {
    {ghoul_arm_attack_side_image5,15,1,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {ghoul_arm_attack_side_image4,7,2,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_head_side_image1,8,-2,SQUARE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_head_side_image0,7,-6,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_body_attack_side_image1,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0}};
const SpriteLayer ghoul_attack_right_layerSet5[] = {
    {ghoul_arm_attack_side_image6,14,0,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {ghoul_arm_attack_side_image4,7,2,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_head_side_image1,8,-2,SQUARE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_head_side_image0,7,-6,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_body_attack_side_image1,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0}};

const SpriteLayerSet ghoul_attack_right_layerSet[] = {
    {ghoul_attack_right_layerSet0,2,5},
    {ghoul_attack_right_layerSet1,12,4},
    {ghoul_attack_right_layerSet2,15,5},
    {ghoul_attack_right_layerSet3,3,5},
    {ghoul_attack_right_layerSet4,3,5},
    {ghoul_attack_right_layerSet5,3,5},
};

const SpriteSet ghoul_attack_right = {ghoul_attack_right_layerSet,6};
