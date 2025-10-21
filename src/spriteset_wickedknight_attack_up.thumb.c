#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageWickedKnight.h"

const SpriteLayer wickedknight_attack_up_layerSet0[] = {
    {wickedknight_body_attack_up_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {wickedknight_head_up_image0,4,-3,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,8,0},
    {wickedknight_armsholdingswordattack_up_image0,-1,3,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {wickedknight_swordattack_image1,12,6,TALL,SMALL_A,DO_HFLIP,DO_VFLIP,NO_COMPRESSION,2,0}};
const SpriteLayer wickedknight_attack_up_layerSet1[] = {
    {wickedknight_body_attack_up_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {wickedknight_head_up_image0,4,-3,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,8,0},
    {wickedknight_armsholdingswordattack_up_image1,-1,3,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {wickedknight_swordattack_image1,11,4,TALL,SMALL_A,DO_HFLIP,DO_VFLIP,NO_COMPRESSION,2,0}};
const SpriteLayer wickedknight_attack_up_layerSet2[] = {
    {wickedknight_body_attack_up_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {wickedknight_head_up_image0,4,-3,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,8,0},
    {wickedknight_armsholdingswordattack_up_image2,-1,3,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {wickedknight_swordprepareattack_side_image2,11,2,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0}};
const SpriteLayer wickedknight_attack_up_layerSet3[] = {
    {wickedknight_body_attack_up_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {wickedknight_head_up_image0,4,-3,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,8,0},
    {wickedknight_armsholdingswordattack_up_image3,-1,3,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {wickedknight_sword_image1,3,-13,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0}};
const SpriteLayer wickedknight_attack_up_layerSet4[] = {
    {wickedknight_body_attack_up_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {wickedknight_head_up_image0,4,-3,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,8,0},
    {wickedknight_armsholdingswordattack_up_image0,0,3,WIDE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {wickedknight_swordprepareattack_side_image0,-9,-1,WIDE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0}};

const SpriteLayerSet wickedknight_attack_up_layerSet[] = {
    {wickedknight_attack_up_layerSet0,15,4},
    {wickedknight_attack_up_layerSet1,20,4},
    {wickedknight_attack_up_layerSet2,5,4},
    {wickedknight_attack_up_layerSet3,3,4},
    {wickedknight_attack_up_layerSet4,20,4},
};

const SpriteSet wickedknight_attack_up = {wickedknight_attack_up_layerSet,5};
