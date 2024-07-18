#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageAlisa.h"

const SpriteLayer alisa_dashforwardwithsword_up_layerSet0[] = {
    {sword_side_set_image2,8,11,WIDE,SMALL_B,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,1},
    {alisa_runwithsword_up_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};
const SpriteLayer alisa_dashforwardwithsword_up_layerSet1[] = {
    {sword_side_set_image2,8,11,WIDE,SMALL_B,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,1},
    {alisa_runwithsword_up_image1,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};
const SpriteLayer alisa_dashforwardwithsword_up_layerSet2[] = {
    {sword_side_set_image2,8,11,WIDE,SMALL_B,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,1},
    {alisa_runwithsword_up_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};
const SpriteLayer alisa_dashforwardwithsword_up_layerSet3[] = {
    {sword_side_set_image2,9,13,WIDE,SMALL_B,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,1},
    {alisa_dashbackwardwithsword_up_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};

const SpriteLayerSet alisa_dashforwardwithsword_up_layerSet[] = {
    {alisa_dashforwardwithsword_up_layerSet0,3,2},
    {alisa_dashforwardwithsword_up_layerSet1,7,2},
    {alisa_dashforwardwithsword_up_layerSet2,3,2},
    {alisa_dashforwardwithsword_up_layerSet3,10,2},
};

const SpriteSet alisa_dashforwardwithsword_up = {alisa_dashforwardwithsword_up_layerSet,4};
