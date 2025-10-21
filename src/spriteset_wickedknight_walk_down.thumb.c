#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageWickedKnight.h"

const SpriteLayer wickedknight_walk_down_layerSet0[] = {
    {wickedknight_sword_image0,-1,-8,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {wickedknight_armsholdingsword_down_image0,0,4,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {wickedknight_head_down_image0,4,-3,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {wickedknight_body_walk_down_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0}};
const SpriteLayer wickedknight_walk_down_layerSet1[] = {
    {wickedknight_sword_image0,-1,-8,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {wickedknight_armsholdingsword_down_image0,0,4,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {wickedknight_head_down_image0,4,-3,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {wickedknight_body_walk_down_image1,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0}};
const SpriteLayer wickedknight_walk_down_layerSet2[] = {
    {wickedknight_sword_image0,-1,-8,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {wickedknight_armsholdingsword_down_image0,0,4,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {wickedknight_head_down_image0,4,-3,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {wickedknight_body_walk_down_image2,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0}};
const SpriteLayer wickedknight_walk_down_layerSet3[] = {
    {wickedknight_sword_image0,-1,-8,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {wickedknight_armsholdingsword_down_image0,0,4,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {wickedknight_head_down_image0,4,-3,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {wickedknight_body_walk_down_image3,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0}};

const SpriteLayerSet wickedknight_walk_down_layerSet[] = {
    {wickedknight_walk_down_layerSet0,15,4},
    {wickedknight_walk_down_layerSet1,10,4},
    {wickedknight_walk_down_layerSet2,15,4},
    {wickedknight_walk_down_layerSet3,10,4},
};

const SpriteSet wickedknight_walk_down = {wickedknight_walk_down_layerSet,4};
