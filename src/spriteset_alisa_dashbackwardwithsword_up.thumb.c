#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageAlisa.h"

const SpriteLayer alisa_dashbackwardwithsword_up_layerSet0[] = {
    {sword_side_set_image2,9,11,WIDE,SMALL_B,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,1},
    {alisa_dashbackwardwithsword_up_image1,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};
const SpriteLayer alisa_dashbackwardwithsword_up_layerSet1[] = {
    {sword_side_set_image2,9,13,WIDE,SMALL_B,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,1},
    {alisa_dashbackwardwithsword_up_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};

const SpriteLayerSet alisa_dashbackwardwithsword_up_layerSet[] = {
    {alisa_dashbackwardwithsword_up_layerSet0,10,2},
    {alisa_dashbackwardwithsword_up_layerSet1,5,2},
};

const SpriteSet alisa_dashbackwardwithsword_up = {alisa_dashbackwardwithsword_up_layerSet,2};
