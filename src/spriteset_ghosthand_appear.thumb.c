#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "sprite_ghostly_hand.h"

const SpriteLayer ghosthand_appear_layerSet0[] = {
    {ghostly_hand_image0,0,0,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0}};
const SpriteLayer ghosthand_appear_layerSet1[] = {
    {ghostly_hand_image1,0,0,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0}};
const SpriteLayer ghosthand_appear_layerSet2[] = {
    {ghostly_hand_image2,0,0,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0}};
const SpriteLayer ghosthand_appear_layerSet3[] = {
    {ghostly_hand_image2,0,0,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {ghostly_hand_image1,0,0,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0}};
const SpriteLayer ghosthand_appear_layerSet4[] = {
    {ghostly_hand_image1,5,0,SQUARE,SMALL_B,DO_HFLIP,DO_VFLIP,LZSS_COMPRESSION,0,0},
    {ghostly_hand_image2,0,-3,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0},
    {ghostly_hand_image1,0,0,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0},
    {ghostly_hand_image0,0,0,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0}};
const SpriteLayer ghosthand_appear_layerSet5[] = {
    {ghostly_hand_image3,0,0,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0}};

const SpriteLayerSet ghosthand_appear_layerSet[] = {
    {ghosthand_appear_layerSet0,5,1},
    {ghosthand_appear_layerSet1,70,1},
    {ghosthand_appear_layerSet2,50,1},
    {ghosthand_appear_layerSet3,30,2},
    {ghosthand_appear_layerSet4,20,4},
    {ghosthand_appear_layerSet5,70,1},
};

const SpriteSet ghosthand_appear = {ghosthand_appear_layerSet,6};