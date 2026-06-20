#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageGhoul.h"

const SpriteLayer ghoul_hurt_left_layerSet0[] = {
    {ghoul_head_down_image1,10,1,SQUARE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {ghoul_head_down_image0,10,-6,SQUARE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_arm_side_image1,12,2,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_body_stun_side_image0,0,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0}};

const SpriteLayerSet ghoul_hurt_left_layerSet[] = {
    {ghoul_hurt_left_layerSet0,5,4},
};

const SpriteSet ghoul_hurt_left = {ghoul_hurt_left_layerSet,1};
