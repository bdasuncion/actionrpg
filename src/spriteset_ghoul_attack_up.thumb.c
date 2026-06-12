#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageGhoul.h"

const SpriteLayer ghoul_attack_up_layerSet0[] = {
    {ghoul_arm_attack_down_image1,11,10,SQUARE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {ghoul_head_up_image0,4,-4,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_body_attack_up_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_arm_attack_down_image0,10,2,SQUARE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,8,0},
    {ghoul_arm_down_image0,-1,3,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0}};
const SpriteLayer ghoul_attack_up_layerSet1[] = {
    {ghoul_arm_attack_down_image3,19,0,SQUARE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {ghoul_head_up_image0,4,-4,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_body_attack_up_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_arm_down_image0,-1,4,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,8,0},
    {ghoul_arm_attack_down_image2,11,1,SQUARE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0}};
const SpriteLayer ghoul_attack_up_layerSet2[] = {
    {ghoul_arm_attack_down_image4,17,-2,SQUARE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {ghoul_head_up_image0,4,-4,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_body_attack_up_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_arm_down_image0,-1,4,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,8,0},
    {ghoul_arm_attack_down_image2,11,1,SQUARE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0}};
const SpriteLayer ghoul_attack_up_layerSet3[] = {
    {ghoul_arm_attack_down_image6,11,-8,SQUARE,SMALL_A,DO_HFLIP,DO_VFLIP,NO_COMPRESSION,0,0},
    {ghoul_head_up_image0,4,-5,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_arm_down_image0,-1,2,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_body_attack_up_image1,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {ghoul_arm_attack_down_image5,10,-3,SQUARE,SMALL_A,DO_HFLIP,DO_VFLIP,NO_COMPRESSION,8,0}};
const SpriteLayer ghoul_attack_up_layerSet4[] = {
    {ghoul_arm_attack_down_image6,9,-11,SQUARE,SMALL_A,DO_HFLIP,DO_VFLIP,NO_COMPRESSION,0,0},
    {ghoul_arm_down_image0,-1,2,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_head_up_image0,4,-5,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {ghoul_body_attack_up_image1,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_arm_attack_down_image5,9,-3,SQUARE,SMALL_A,DO_HFLIP,DO_VFLIP,NO_COMPRESSION,8,0}};
const SpriteLayer ghoul_attack_up_layerSet5[] = {
    {ghoul_arm_down_image0,-1,2,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {ghoul_head_up_image0,4,-5,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {ghoul_body_attack_up_image1,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_arm_attack_down_image7,7,2,SQUARE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,8,0}};

const SpriteLayerSet ghoul_attack_up_layerSet[] = {
    {ghoul_attack_up_layerSet0,2,5},
    {ghoul_attack_up_layerSet1,15,5},
    {ghoul_attack_up_layerSet2,20,5},
    {ghoul_attack_up_layerSet3,3,5},
    {ghoul_attack_up_layerSet4,3,5},
    {ghoul_attack_up_layerSet5,3,4},
};

const SpriteSet ghoul_attack_up = {ghoul_attack_up_layerSet,6};
