#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageAlisa.h"

const SpriteLayer alisa_jumpwithsword_left_layerSet0[] = {
    {sword_side_set_image0,9,13,WIDE,SMALL_B,DO_HFLIP,DO_VFLIP,NO_COMPRESSION,0,1},
    {alisa_jumpwithsword_side_image0,0,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};
const SpriteLayer alisa_jumpwithsword_left_layerSet1[] = {
    {sword_side_set_image0,9,13,WIDE,SMALL_B,DO_HFLIP,DO_VFLIP,NO_COMPRESSION,0,1},
    {alisa_jumpwithsword_side_image1,0,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};
const SpriteLayer alisa_jumpwithsword_left_layerSet2[] = {
    {sword_side_set_image0,9,-4,WIDE,SMALL_B,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,1},
    {alisa_jumpwithsword_side_image2,0,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};

const SpriteLayerSet alisa_jumpwithsword_left_layerSet[] = {
    {alisa_jumpwithsword_left_layerSet0,8,2},
    {alisa_jumpwithsword_left_layerSet1,8,2},
    {alisa_jumpwithsword_left_layerSet2,8,2},
};

const SpriteSet alisa_jumpwithsword_left = {alisa_jumpwithsword_left_layerSet,3};
