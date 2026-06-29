#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageGhoul.h"

const SpriteLayer ghoul_walk_down_layerSet0[] = {
    {ghoul_head_down_image1,4,2,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {ghoul_head_down_image0,4,-5,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_arm_down_image0,9,3,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_arm_down_image0,-1,2,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {ghoul_body_walk_down_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0}};
const SpriteLayer ghoul_walk_down_layerSet1[] = {
    {ghoul_head_down_image1,4,2,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {ghoul_head_down_image0,4,-5,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_arm_down_image0,9,2,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_arm_down_image0,-1,3,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {ghoul_body_walk_down_image1,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0}};
const SpriteLayer ghoul_walk_down_layerSet2[] = {
    {ghoul_head_down_image1,5,2,SQUARE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {ghoul_head_down_image0,4,-5,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_arm_down_image0,9,2,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_arm_down_image0,-1,3,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {ghoul_body_walk_down_image0,0,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0}};
const SpriteLayer ghoul_walk_down_layerSet3[] = {
    {ghoul_head_down_image1,5,2,SQUARE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {ghoul_head_down_image0,4,-5,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_arm_down_image0,9,3,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_arm_down_image0,-1,2,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {ghoul_body_walk_down_image1,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0}};

const SpriteLayerSet ghoul_walk_down_layerSet[] = {
    {ghoul_walk_down_layerSet0,12,5},
    {ghoul_walk_down_layerSet1,12,5},
    {ghoul_walk_down_layerSet2,12,5},
    {ghoul_walk_down_layerSet3,12,5},
};

const SpriteSet ghoul_walk_down = {ghoul_walk_down_layerSet,4};
