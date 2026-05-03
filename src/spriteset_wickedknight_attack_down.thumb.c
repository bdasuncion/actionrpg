#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageWickedKnight.h"

const SpriteLayer wickedknight_attack_down_layerSet0[] = {
    {wickedknight_sword_vertical_image3,-2,-29,TALL,SMALL_B,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {wickedknight_head_down_image0,4,-6,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0},
    {wickedknight_armsholdingswordattack_down_image0,0,1,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {wickedknight_body_attack_down_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0}};
const SpriteLayer wickedknight_attack_down_layerSet1[] = {
    {wickedknight_sword_vertical_image3,-3,-29,TALL,SMALL_B,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {wickedknight_armsholdingswordattack_down_image1,-1,1,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0},
    {wickedknight_head_down_image0,4,-6,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {wickedknight_body_attack_down_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0}};
const SpriteLayer wickedknight_attack_down_layerSet2[] = {
    {wickedknight_sword_horizontal_image1,-30,2,WIDE,SMALL_B,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {wickedknight_armsholdingswordattack_down_image2,1,1,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0},
    {wickedknight_head_down_image0,4,-6,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {wickedknight_body_attack_down_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0}};
const SpriteLayer wickedknight_attack_down_layerSet3[] = {
    {wickedknight_sword_vertical_image1,4,8,TALL,SMALL_B,NO_HFLIP,DO_VFLIP,NO_COMPRESSION,0,0},
    {wickedknight_armsholdingswordattack_down_image3,0,2,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0},
    {wickedknight_head_down_image0,4,-6,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {wickedknight_body_attack_down_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0}};
const SpriteLayer wickedknight_attack_down_layerSet4[] = {
    {wickedknight_sword_horizontal_image0,14,2,WIDE,SMALL_B,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {wickedknight_armsholdingswordattack_down_image2,-1,2,WIDE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0},
    {wickedknight_head_down_image0,4,-6,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {wickedknight_body_attack_down_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0}};

const SpriteLayerSet wickedknight_attack_down_layerSet[] = {
    {wickedknight_attack_down_layerSet0,8,4},
    {wickedknight_attack_down_layerSet1,10,4},
    {wickedknight_attack_down_layerSet2,5,4},
    {wickedknight_attack_down_layerSet3,3,4},
    {wickedknight_attack_down_layerSet4,20,4},
};

const SpriteSet wickedknight_attack_down = {wickedknight_attack_down_layerSet,5};
