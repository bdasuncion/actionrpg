#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageAlisa.h"

const SpriteLayer alisa_dashforwardwithsword_left_layerSet0[] = {
    {sword_side_set_image0,7,14,WIDE,SMALL_B,DO_HFLIP,DO_VFLIP,NO_COMPRESSION,0,1},
    {alisa_runwithsword_side_image3,0,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};
const SpriteLayer alisa_dashforwardwithsword_left_layerSet1[] = {
    {sword_side_set_image0,7,14,WIDE,SMALL_B,DO_HFLIP,DO_VFLIP,NO_COMPRESSION,0,1},
    {alisa_runwithsword_side_image4,0,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};
const SpriteLayer alisa_dashforwardwithsword_left_layerSet2[] = {
    {sword_side_set_image0,7,14,WIDE,SMALL_B,DO_HFLIP,DO_VFLIP,NO_COMPRESSION,0,1},
    {alisa_runwithsword_side_image3,0,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};
const SpriteLayer alisa_dashforwardwithsword_left_layerSet3[] = {
    {sword_side_set_image0,9,16,WIDE,SMALL_B,DO_HFLIP,DO_VFLIP,NO_COMPRESSION,0,1},
    {alisa_dashbackwardwithsword_side_image0,0,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};

const SpriteLayerSet alisa_dashforwardwithsword_left_layerSet[] = {
    {alisa_dashforwardwithsword_left_layerSet0,3,2},
    {alisa_dashforwardwithsword_left_layerSet1,7,2},
    {alisa_dashforwardwithsword_left_layerSet2,3,2},
    {alisa_dashforwardwithsword_left_layerSet3,10,2},
};

const SpriteSet alisa_dashforwardwithsword_left = {alisa_dashforwardwithsword_left_layerSet,4};
