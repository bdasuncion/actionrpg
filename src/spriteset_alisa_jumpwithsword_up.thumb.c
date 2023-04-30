#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageAlisa.h"

const SpriteLayer alisa_jumpwithsword_up_layerSet0[] = {
    {sword_side_set_image2,8,11,WIDE,SMALL_B,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,1},
    {alisa_jumpwithsword_up_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};
const SpriteLayer alisa_jumpwithsword_up_layerSet1[] = {
    {sword_side_set_image2,8,11,WIDE,SMALL_B,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,1},
    {alisa_jumpwithsword_up_image1,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};
const SpriteLayer alisa_jumpwithsword_up_layerSet2[] = {
    {sword_frontback_set_image1,4,-11,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,1},
    {alisa_jumpwithsword_up_image2,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0}};

const SpriteLayerSet alisa_jumpwithsword_up_layerSet[] = {
    {alisa_jumpwithsword_up_layerSet0,8,2},
    {alisa_jumpwithsword_up_layerSet1,8,2},
    {alisa_jumpwithsword_up_layerSet2,8,2},
};

const SpriteSet alisa_jumpwithsword_up = {alisa_jumpwithsword_up_layerSet,3};

