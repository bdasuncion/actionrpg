#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageWickedKnight.h"

const SpriteLayer wickedknight_attack_left_layerSet0[] = {
    {wickedknight_head_side_image0,2,-4,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {wickedknight_swordprepareattack_side_image0,13,2,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {wickedknight_armsholdingswordattack_side_image0,-1,4,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {wickedknight_body_attack_side_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0}};
const SpriteLayer wickedknight_attack_left_layerSet1[] = {
    {wickedknight_swordprepareattack_side_image0,15,3,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {wickedknight_head_side_image0,2,-4,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {wickedknight_armsholdingswordattack_side_image1,0,4,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {wickedknight_body_attack_side_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0}};
const SpriteLayer wickedknight_attack_left_layerSet2[] = {
    {wickedknight_swordattack_image0,2,9,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {wickedknight_armsholdingswordattack_side_image2,-1,4,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {wickedknight_head_side_image0,2,-4,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {wickedknight_body_attack_side_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0}};
const SpriteLayer wickedknight_attack_left_layerSet3[] = {
    {wickedknight_swordprepareattack_side_image1,-20,3,WIDE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {wickedknight_armsholdingswordattack_side_image3,-4,4,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {wickedknight_head_side_image0,2,-4,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {wickedknight_body_attack_side_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0}};
const SpriteLayer wickedknight_attack_left_layerSet4[] = {
    {wickedknight_armsholdingswordattack_side_image4,-5,4,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {wickedknight_head_side_image0,2,-4,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {wickedknight_body_attack_side_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {wickedknight_swordprepareattack_side_image1,6,4,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,8,0}};

const SpriteLayerSet wickedknight_attack_left_layerSet[] = {
    {wickedknight_attack_left_layerSet0,15,4},
    {wickedknight_attack_left_layerSet1,25,4},
    {wickedknight_attack_left_layerSet2,5,4},
    {wickedknight_attack_left_layerSet3,3,4},
    {wickedknight_attack_left_layerSet4,20,4},
};

const SpriteSet wickedknight_attack_left = {wickedknight_attack_left_layerSet,5};
