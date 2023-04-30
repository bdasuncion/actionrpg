#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageAlisa.h"

const SpriteLayer alisa_jumpwithsword_down_layerSet0[] = {
    {sword_side_set_image2,-25,11,WIDE,SMALL_B,NO_HFLIP,DO_VFLIP,NO_COMPRESSION,0,1},
    {alisa_jumpwithsword_down_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};
const SpriteLayer alisa_jumpwithsword_down_layerSet1[] = {
    {sword_side_set_image2,-25,11,WIDE,SMALL_B,NO_HFLIP,DO_VFLIP,NO_COMPRESSION,0,1},
    {alisa_jumpwithsword_down_image1,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};
const SpriteLayer alisa_jumpwithsword_down_layerSet2[] = {
    {sword_frontback_set_image0,4,-11,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,1},
    {alisa_jumpwithsword_down_image2,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0}};

const SpriteLayerSet alisa_jumpwithsword_down_layerSet[] = {
    {alisa_jumpwithsword_down_layerSet0,8,2},
    {alisa_jumpwithsword_down_layerSet1,8,2},
    {alisa_jumpwithsword_down_layerSet2,8,2},
};

const SpriteSet alisa_jumpwithsword_down = {alisa_jumpwithsword_down_layerSet,3};
