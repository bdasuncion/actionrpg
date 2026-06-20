#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageGhoul.h"

const SpriteLayer ghoul_hurt_down_layerSet0[] = {
    {ghoul_head_side_image1,1,3,SQUARE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {ghoul_head_side_image0,4,-3,SQUARE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_arm_down_image1,10,4,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,1,0},
    {ghoul_arm_down_image1,-2,4,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {ghoul_body_stun_down_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0}};

const SpriteLayerSet ghoul_hurt_down_layerSet[] = {
    {ghoul_hurt_down_layerSet0,5,5},
};

const SpriteSet ghoul_hurt_down = {ghoul_hurt_down_layerSet,1};
