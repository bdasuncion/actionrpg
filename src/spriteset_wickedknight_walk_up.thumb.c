#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageWickedKnight.h"

const SpriteLayer wickedknight_walk_up_layerSet0[] = {
    {wickedknight_armsholdingsword_up_image0,-1,0,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {wickedknight_body_walk_up_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {wickedknight_head_up_image0,4,-7,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,8,0},
    {wickedknight_sword_vertical_image0,7,-27,TALL,SMALL_B,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0}};
const SpriteLayer wickedknight_walk_up_layerSet1[] = {
    {wickedknight_armsholdingsword_up_image0,-1,0,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {wickedknight_body_walk_up_image1,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {wickedknight_head_up_image0,4,-7,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,8,0},
    {wickedknight_sword_vertical_image0,7,-26,TALL,SMALL_B,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0}};
const SpriteLayer wickedknight_walk_up_layerSet2[] = {
    {wickedknight_armsholdingsword_up_image0,-1,0,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {wickedknight_body_walk_up_image2,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {wickedknight_head_up_image0,4,-7,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,8,0},
    {wickedknight_sword_vertical_image0,7,-28,TALL,SMALL_B,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0}};
const SpriteLayer wickedknight_walk_up_layerSet3[] = {
    {wickedknight_armsholdingsword_up_image0,-1,0,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {wickedknight_body_walk_up_image3,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {wickedknight_head_up_image0,4,-7,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,8,0},
    {wickedknight_sword_vertical_image0,7,-27,TALL,SMALL_B,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0}};

const SpriteLayerSet wickedknight_walk_up_layerSet[] = {
    {wickedknight_walk_up_layerSet0,10,4},
    {wickedknight_walk_up_layerSet1,15,4},
    {wickedknight_walk_up_layerSet2,10,4},
    {wickedknight_walk_up_layerSet3,15,4},
};

const SpriteSet wickedknight_walk_up = {wickedknight_walk_up_layerSet,4};
