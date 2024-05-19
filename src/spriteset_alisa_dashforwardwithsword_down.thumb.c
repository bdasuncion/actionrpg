#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageAlisa.h"

const SpriteLayer alisa_dashforwardwithsword_down_layerSet0[] = {
    {sword_side_set_image2,-25,11,WIDE,SMALL_B,NO_HFLIP,DO_VFLIP,NO_COMPRESSION,0,1},
    {alisa_runwithsword_down_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};
const SpriteLayer alisa_dashforwardwithsword_down_layerSet1[] = {
    {sword_side_set_image2,-25,11,WIDE,SMALL_B,NO_HFLIP,DO_VFLIP,NO_COMPRESSION,0,1},
    {alisa_runwithsword_down_image1,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};
const SpriteLayer alisa_dashforwardwithsword_down_layerSet2[] = {
    {sword_side_set_image2,-25,11,WIDE,SMALL_B,NO_HFLIP,DO_VFLIP,NO_COMPRESSION,0,1},
    {alisa_runwithsword_down_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};
const SpriteLayer alisa_dashforwardwithsword_down_layerSet3[] = {
    {sword_side_set_image2,-24,11,WIDE,SMALL_B,NO_HFLIP,DO_VFLIP,NO_COMPRESSION,0,1},
    {alisa_dashbackwardwithsword_down_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};

const SpriteLayerSet alisa_dashforwardwithsword_down_layerSet[] = {
    {alisa_dashforwardwithsword_down_layerSet0,3,2},
    {alisa_dashforwardwithsword_down_layerSet1,7,2},
    {alisa_dashforwardwithsword_down_layerSet2,3,2},
    {alisa_dashforwardwithsword_down_layerSet3,10,2},
};

const SpriteSet alisa_dashforwardwithsword_down = {alisa_dashforwardwithsword_down_layerSet,4};
