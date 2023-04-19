#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageAlisa.h"

const SpriteLayer alisa_jumpwithsword_up_layerSet0[] = {
    {alisa_jumpwithsword_up_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0}};
const SpriteLayer alisa_jumpwithsword_up_layerSet1[] = {
    {alisa_jumpwithsword_up_image1,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0}};

const SpriteLayerSet alisa_jumpwithsword_up_layerSet[] = {
    {alisa_jumpwithsword_up_layerSet0,10,1},
    {alisa_jumpwithsword_up_layerSet1,20,1},
};

const SpriteSet alisa_jumpwithsword_up = {alisa_jumpwithsword_up_layerSet,2};
