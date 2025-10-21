#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageWickedKnight.h"

const SpriteLayer wickedknight_attack_down_layerSet0[] = {
    {wickedknight_head_down_image0,4,-3,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {wickedknight_swordattack_image1,-4,-11,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {wickedknight_armsholdingswordattack_down_image0,-1,4,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {wickedknight_body_attack_down_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0}};
const SpriteLayer wickedknight_attack_down_layerSet1[] = {
    {wickedknight_swordattack_image1,-3,-10,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {wickedknight_armsholdingswordattack_down_image1,0,4,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {wickedknight_head_down_image0,4,-3,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {wickedknight_body_attack_down_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0}};
const SpriteLayer wickedknight_attack_down_layerSet2[] = {
    {wickedknight_swordprepareattack_side_image1,-14,6,WIDE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {wickedknight_armsholdingswordattack_down_image2,1,4,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {wickedknight_head_down_image0,4,-3,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {wickedknight_body_attack_down_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0}};
const SpriteLayer wickedknight_attack_down_layerSet3[] = {
    {wickedknight_sword_image1,4,10,TALL,SMALL_A,NO_HFLIP,DO_VFLIP,NO_COMPRESSION,0,0},
    {wickedknight_armsholdingswordattack_down_image3,0,5,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {wickedknight_head_down_image0,4,-3,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {wickedknight_body_attack_down_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0}};
const SpriteLayer wickedknight_attack_down_layerSet4[] = {
    {wickedknight_swordprepareattack_side_image0,14,6,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {wickedknight_armsholdingswordattack_down_image2,-1,5,WIDE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {wickedknight_head_down_image0,4,-3,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {wickedknight_body_attack_down_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0}};

const SpriteLayerSet wickedknight_attack_down_layerSet[] = {
    {wickedknight_attack_down_layerSet0,15,4},
    {wickedknight_attack_down_layerSet1,25,4},
    {wickedknight_attack_down_layerSet2,5,4},
    {wickedknight_attack_down_layerSet3,3,4},
    {wickedknight_attack_down_layerSet4,20,4},
};

const SpriteSet wickedknight_attack_down = {wickedknight_attack_down_layerSet,5};
