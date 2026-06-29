#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageGhoul.h"

const SpriteLayer ghoul_attack_down_layerSet0[] = {
    {ghoul_arm_attack_down_image1,-2,11,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {ghoul_head_down_image1,3,1,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_head_down_image0,4,-5,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_arm_down_image0,9,3,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_arm_attack_down_image0,-1,3,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {ghoul_body_attack_down_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0}};
const SpriteLayer ghoul_attack_down_layerSet1[] = {
    {ghoul_arm_attack_down_image3,-10,2,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {ghoul_head_down_image1,3,1,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_head_down_image0,4,-5,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_arm_down_image0,9,3,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_body_attack_down_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {ghoul_arm_attack_down_image2,-2,1,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,8,0}};
const SpriteLayer ghoul_attack_down_layerSet2[] = {
    {ghoul_head_down_image1,4,1,SQUARE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {ghoul_head_down_image0,4,-5,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_arm_down_image0,9,3,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_body_attack_down_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {ghoul_arm_attack_down_image2,-2,0,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,8,0},
    {ghoul_arm_attack_down_image4,-9,-3,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0}};
const SpriteLayer ghoul_attack_down_layerSet3[] = {
    {ghoul_arm_attack_down_image6,-3,11,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {ghoul_head_down_image1,4,2,SQUARE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_head_down_image0,4,-4,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_arm_down_image0,9,4,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_body_attack_down_image1,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {ghoul_arm_attack_down_image5,-2,5,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,8,0}};
const SpriteLayer ghoul_attack_down_layerSet4[] = {
    {ghoul_head_down_image1,3,2,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {ghoul_arm_down_image0,9,4,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_head_down_image0,4,-4,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {ghoul_arm_attack_down_image6,-2,13,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_body_attack_down_image1,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_arm_attack_down_image5,-2,5,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,8,0}};
const SpriteLayer ghoul_attack_down_layerSet5[] = {
    {ghoul_head_down_image1,3,3,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {ghoul_arm_down_image0,9,4,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_arm_attack_down_image3,6,8,SQUARE,SMALL_A,DO_HFLIP,DO_VFLIP,NO_COMPRESSION,2,0},
    {ghoul_head_down_image0,4,-4,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_arm_attack_down_image7,0,4,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_body_attack_down_image1,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0}};

const SpriteLayerSet ghoul_attack_down_layerSet[] = {
    {ghoul_attack_down_layerSet0,2,6},
    {ghoul_attack_down_layerSet1,12,6},
    {ghoul_attack_down_layerSet2,15,6},
    {ghoul_attack_down_layerSet3,3,6},
    {ghoul_attack_down_layerSet4,3,6},
    {ghoul_attack_down_layerSet5,3,6},
};

const SpriteSet ghoul_attack_down = {ghoul_attack_down_layerSet,6};
