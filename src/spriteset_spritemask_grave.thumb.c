#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"

extern const unsigned int grave_image0[];

const SpriteLayer spritemask_grave_layerSet0[] = {
    {grave_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0}};

const SpriteLayerSet spritemask_grave_layerSet[] = {
    {spritemask_grave_layerSet0,5,1},
};

const SpriteSet spritemask_grave = {spritemask_grave_layerSet,1};
