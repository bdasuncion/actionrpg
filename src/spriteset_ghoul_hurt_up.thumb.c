#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageGhoul.h"

const SpriteLayer ghoul_hurt_up_layerSet0[] = {
    {ghoul_arm_down_image1,10,3,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {ghoul_arm_down_image1,-2,3,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {ghoul_body_stun_up_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {ghoul_head_side_image0,4,-4,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,8,0}};

const SpriteLayerSet ghoul_hurt_up_layerSet[] = {
    {ghoul_hurt_up_layerSet0,5,4},
};

const SpriteSet ghoul_hurt_up = {ghoul_hurt_up_layerSet,1};
