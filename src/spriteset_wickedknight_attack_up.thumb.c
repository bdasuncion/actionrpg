#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageWickedKnight.h"

const SpriteLayer wickedknight_attack_up_layerSet0[] = {
    {wickedknight_body_attack_up_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {wickedknight_head_up_image0,4,-7,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,8,0},
    {wickedknight_armsholdingswordattack_up_image0,-1,-1,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {wickedknight_sword_vertical_image3,13,2,TALL,SMALL_B,NO_HFLIP,DO_VFLIP,NO_COMPRESSION,2,0}};
const SpriteLayer wickedknight_attack_up_layerSet1[] = {
    {wickedknight_armsholdingswordattack_up_image1,-1,-1,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {wickedknight_sword_vertical_image3,13,0,TALL,SMALL_B,NO_HFLIP,DO_VFLIP,NO_COMPRESSION,2,0},
    {wickedknight_body_attack_up_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0},
    {wickedknight_head_up_image0,4,-7,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,8,0}};
const SpriteLayer wickedknight_attack_up_layerSet2[] = {
    {wickedknight_sword_horizontal_image0,15,0,WIDE,SMALL_B,NO_HFLIP,DO_VFLIP,NO_COMPRESSION,0,0},
    {wickedknight_body_attack_up_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0},
    {wickedknight_head_up_image0,4,-7,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,8,0},
    {wickedknight_armsholdingswordattack_up_image2,-1,-1,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0}};
const SpriteLayer wickedknight_attack_up_layerSet3[] = {
    {wickedknight_body_attack_up_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {wickedknight_head_up_image0,4,-7,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,8,0},
    {wickedknight_armsholdingswordattack_up_image3,-1,-1,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {wickedknight_sword_vertical_image1,3,-30,TALL,SMALL_B,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0}};
const SpriteLayer wickedknight_attack_up_layerSet4[] = {
    {wickedknight_body_attack_up_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {wickedknight_head_up_image0,4,-7,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,8,0},
    {wickedknight_armsholdingswordattack_up_image0,0,-1,WIDE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {wickedknight_sword_horizontal_image0,-26,-4,WIDE,SMALL_B,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0}};

const SpriteLayerSet wickedknight_attack_up_layerSet[] = {
    {wickedknight_attack_up_layerSet0,8,4},
    {wickedknight_attack_up_layerSet1,10,4},
    {wickedknight_attack_up_layerSet2,5,4},
    {wickedknight_attack_up_layerSet3,3,4},
    {wickedknight_attack_up_layerSet4,20,4},
};

const SpriteSet wickedknight_attack_up = {wickedknight_attack_up_layerSet,5};
