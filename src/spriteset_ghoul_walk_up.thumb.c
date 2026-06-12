#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageGhoul.h"

const SpriteLayer ghoul_walk_up_layerSet0[] = {
    {ghoul_body_walk_up_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {ghoul_arm_down_image0,9,4,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,8,0},
    {ghoul_arm_down_image0,-1,3,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {ghoul_head_up_image0,4,-4,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0}};
const SpriteLayer ghoul_walk_up_layerSet1[] = {
    {ghoul_body_walk_up_image1,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {ghoul_arm_down_image0,9,3,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,8,0},
    {ghoul_arm_down_image0,-1,4,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {ghoul_head_up_image0,4,-4,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0}};
const SpriteLayer ghoul_walk_up_layerSet2[] = {
    {ghoul_body_walk_up_image0,0,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {ghoul_arm_down_image0,9,3,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,8,0},
    {ghoul_arm_down_image0,-1,4,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {ghoul_head_up_image0,4,-4,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0}};
const SpriteLayer ghoul_walk_up_layerSet3[] = {
    {ghoul_body_walk_up_image1,0,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {ghoul_arm_down_image0,9,4,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,8,0},
    {ghoul_arm_down_image0,-1,3,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {ghoul_head_up_image0,4,-4,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0}};

const SpriteLayerSet ghoul_walk_up_layerSet[] = {
    {ghoul_walk_up_layerSet0,15,4},
    {ghoul_walk_up_layerSet1,15,4},
    {ghoul_walk_up_layerSet2,15,4},
    {ghoul_walk_up_layerSet3,15,4},
};

const SpriteSet ghoul_walk_up = {ghoul_walk_up_layerSet,4};
