#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageAlisa.h"

const SpriteLayer alisa_jumpwithsword_left_layerSet0[] = {
    {alisa_jumpwithsword_side_image0,0,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0}};
const SpriteLayer alisa_jumpwithsword_left_layerSet1[] = {
    {alisa_jumpwithsword_side_image1,0,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0}};

const SpriteLayerSet alisa_jumpwithsword_left_layerSet[] = {
    {alisa_jumpwithsword_left_layerSet0,10,1},
    {alisa_jumpwithsword_left_layerSet1,20,1},
};

const SpriteSet alisa_jumpwithsword_left = {alisa_jumpwithsword_left_layerSet,2};
