#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageWickedKnight.h"

const SpriteLayer wickedknight_attack_right_layerSet0[] = {
    {wickedknight_sword_horizontal_image0,-29,-2,WIDE,SMALL_B,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {wickedknight_head_side_image0,6,-7,SQUARE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0},
    {wickedknight_armsholdingswordattack_side_image0,1,1,WIDE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {wickedknight_body_attack_side_image0,0,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0}};
const SpriteLayer wickedknight_attack_right_layerSet1[] = {
    {wickedknight_sword_horizontal_image0,-29,-1,WIDE,SMALL_B,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {wickedknight_head_side_image0,6,-7,SQUARE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0},
    {wickedknight_armsholdingswordattack_side_image1,1,1,WIDE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {wickedknight_body_attack_side_image0,0,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0}};
const SpriteLayer wickedknight_attack_right_layerSet2[] = {
    {wickedknight_sword_vertical_image2,5,5,TALL,SMALL_B,NO_HFLIP,DO_VFLIP,NO_COMPRESSION,0,0},
    {wickedknight_armsholdingswordattack_side_image2,1,1,WIDE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0},
    {wickedknight_head_side_image0,6,-7,SQUARE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {wickedknight_body_attack_side_image0,0,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0}};
const SpriteLayer wickedknight_attack_right_layerSet3[] = {
    {wickedknight_sword_horizontal_image1,20,0,WIDE,SMALL_B,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {wickedknight_armsholdingswordattack_side_image3,4,1,WIDE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0},
    {wickedknight_head_side_image0,6,-7,SQUARE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {wickedknight_body_attack_side_image0,0,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0}};
const SpriteLayer wickedknight_attack_right_layerSet4[] = {
    {wickedknight_armsholdingswordattack_side_image4,5,1,WIDE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {wickedknight_head_side_image0,6,-7,SQUARE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {wickedknight_body_attack_side_image0,0,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {wickedknight_sword_horizontal_image1,-19,0,WIDE,SMALL_B,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,8,0}};

const SpriteLayerSet wickedknight_attack_right_layerSet[] = {
    {wickedknight_attack_right_layerSet0,8,4},
    {wickedknight_attack_right_layerSet1,10,4},
    {wickedknight_attack_right_layerSet2,5,4},
    {wickedknight_attack_right_layerSet3,3,4},
    {wickedknight_attack_right_layerSet4,20,4},
};

const SpriteSet wickedknight_attack_right = {wickedknight_attack_right_layerSet,5};
