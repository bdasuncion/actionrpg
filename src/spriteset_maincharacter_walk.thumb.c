#include "GBATypes.h"
#include "GBAObject.h"
#include "sprite_maincharacterupper_walk.h"
#include "sprite_maincharacterlower_walk.h"


const SpriteLayer maincharacter_walk_layerSet0[] = {
    {maincharacterlower_walk_image0,0,32,SQUARE,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    { maincharacterupper_walk_image0,0,0,SQUARE,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,16,0}};
const SpriteLayer maincharacter_walk_layerSet1[] = {
    {maincharacterlower_walk_image1,0,32,SQUARE,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    { maincharacterupper_walk_image1,0,0,SQUARE,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,16,0}};
const SpriteLayer maincharacter_walk_layerSet2[] = {
    {maincharacterlower_walk_image2,0,32,SQUARE,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    { maincharacterupper_walk_image2,0,0,SQUARE,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,16,0}};
const SpriteLayer maincharacter_walk_layerSet3[] = {
    {maincharacterlower_walk_image3,0,32,SQUARE,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    { maincharacterupper_walk_image3,0,0,SQUARE,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,16,0}};
const SpriteLayer maincharacter_walk_layerSet4[] = {
    {maincharacterlower_walk_image4,0,32,SQUARE,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    { maincharacterupper_walk_image4,0,0,SQUARE,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,16,0}};
const SpriteLayer maincharacter_walk_layerSet5[] = {
    {maincharacterlower_walk_image5,0,32,SQUARE,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    { maincharacterupper_walk_image5,0,0,SQUARE,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,16,0}};

const SpriteLayerSet maincharacter_walk_layerSet[] = {
    {maincharacter_walk_layerSet0,8,2},
    {maincharacter_walk_layerSet1,8,2},
    {maincharacter_walk_layerSet2,8,2},
    {maincharacter_walk_layerSet3,8,2},
    {maincharacter_walk_layerSet4,8,2},
    {maincharacter_walk_layerSet5,8,2},
};

const SpriteSet maincharacter_walk = {maincharacter_walk_layerSet,6};
