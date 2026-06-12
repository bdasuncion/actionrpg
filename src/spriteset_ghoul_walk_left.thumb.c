#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageGhoul.h"

const SpriteLayer ghoul_walk_left_layerSet0[] = {
    {ghoul_head_side_image1,1,-1,SQUARE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {ghoul_arm_side_image0,4,2,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_head_side_image0,3,-6,SQUARE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {ghoul_body_walk_side_image0,0,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0}};
const SpriteLayer ghoul_walk_left_layerSet1[] = {
    {ghoul_head_side_image1,1,-1,SQUARE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {ghoul_arm_side_image0,5,2,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_head_side_image0,3,-6,SQUARE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {ghoul_body_walk_side_image1,0,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0}};
const SpriteLayer ghoul_walk_left_layerSet2[] = {
    {ghoul_head_side_image1,4,-1,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {ghoul_arm_side_image0,5,2,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_head_side_image0,3,-6,SQUARE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {ghoul_body_walk_side_image2,0,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0}};
const SpriteLayer ghoul_walk_left_layerSet3[] = {
    {ghoul_head_side_image1,4,-1,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {ghoul_arm_side_image0,4,2,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_head_side_image0,3,-6,SQUARE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {ghoul_body_walk_side_image3,0,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0}};

const SpriteLayerSet ghoul_walk_left_layerSet[] = {
    {ghoul_walk_left_layerSet0,15,4},
    {ghoul_walk_left_layerSet1,15,4},
    {ghoul_walk_left_layerSet2,15,4},
    {ghoul_walk_left_layerSet3,15,4},
};

const SpriteSet ghoul_walk_left = {ghoul_walk_left_layerSet,4};
