#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageWickedKnight.h"

const SpriteLayer wickedknight_walk_left_layerSet0[] = {
    {wickedknight_sword_vertical_image1,6,-27,TALL,SMALL_B,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {wickedknight_armsholdingsword_side_image0,-1,1,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0},
    {wickedknight_head_side_image0,2,-7,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {wickedknight_body_walk_side_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0}};
const SpriteLayer wickedknight_walk_left_layerSet1[] = {
    {wickedknight_sword_vertical_image1,6,-27,TALL,SMALL_B,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {wickedknight_armsholdingsword_side_image0,-1,1,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0},
    {wickedknight_head_side_image0,2,-7,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {wickedknight_body_walk_side_image1,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0}};
const SpriteLayer wickedknight_walk_left_layerSet2[] = {
    {wickedknight_sword_vertical_image1,6,-27,TALL,SMALL_B,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {wickedknight_armsholdingsword_side_image0,-1,1,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0},
    {wickedknight_head_side_image0,2,-7,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {wickedknight_body_walk_side_image2,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0}};
const SpriteLayer wickedknight_walk_left_layerSet3[] = {
    {wickedknight_sword_vertical_image1,6,-27,TALL,SMALL_B,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {wickedknight_armsholdingsword_side_image0,-1,1,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0},
    {wickedknight_head_side_image0,2,-7,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {wickedknight_body_walk_side_image3,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0}};

const SpriteLayerSet wickedknight_walk_left_layerSet[] = {
    {wickedknight_walk_left_layerSet0,10,4},
    {wickedknight_walk_left_layerSet1,15,4},
    {wickedknight_walk_left_layerSet2,10,4},
    {wickedknight_walk_left_layerSet3,15,4},
};

const SpriteSet wickedknight_walk_left = {wickedknight_walk_left_layerSet,4};
