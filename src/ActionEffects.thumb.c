#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"

const unsigned short slash_horizontal_pal[16] = 
{
	0x7FFF,0x7FE0,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
};
const unsigned int slash_horizontal_image0[16] = 
{
	0x00000000,0x00000000,0x00111100,0x01111110,0x00111100,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,

};
const unsigned int slash_horizontal_image1[16] = 
{
	0x00000000,0x00000000,0x11110000,0x11111110,0x11110000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000011,0x00000111,0x00000011,0x00000000,0x00000000,0x00000000,

};
const unsigned int slash_horizontal_image2[16] = 
{
	0x00000000,0x00000000,0x11000000,0x11111110,0x11000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00111111,0x01111111,0x00111111,0x00000000,0x00000000,0x00000000
};

const SpriteLayer slash_horizontalleft_layerSet0[] = {
    {slash_horizontal_image0,12,0,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0}};
const SpriteLayer slash_horizontalleft_layerSet1[] = {
    {slash_horizontal_image1,4,0,WIDE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0}};
const SpriteLayer slash_horizontalleft_layerSet2[] = {
    {slash_horizontal_image2,4,0,WIDE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0}};
const SpriteLayer slash_horizontalleft_layerSet3[] = {
    {slash_horizontal_image2,0,0,WIDE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0}};
const SpriteLayer slash_horizontalleft_layerSet4[] = {
    {slash_horizontal_image1,-4,0,WIDE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0}};
const SpriteLayer slash_horizontalleft_layerSet5[] = {
    {slash_horizontal_image0,0,0,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0}};

const SpriteLayerSet slash_horizontalleft_layerSet[] = {
    {slash_horizontalleft_layerSet0,2,1},
    {slash_horizontalleft_layerSet1,2,1},
    {slash_horizontalleft_layerSet2,2,1},
    {slash_horizontalleft_layerSet3,2,1},
    {slash_horizontalleft_layerSet4,2,1},
    {slash_horizontalleft_layerSet5,2,1},
};

const SpriteSet slash_horizontalleft = {slash_horizontalleft_layerSet,6};

const SpriteLayer slash_horizontalright_layerSet0[] = {
    {slash_horizontal_image0,0,0,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0}};
const SpriteLayer slash_horizontalright_layerSet1[] = {
    {slash_horizontal_image1,0,0,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0}};
const SpriteLayer slash_horizontalright_layerSet2[] = {
    {slash_horizontal_image2,0,0,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0}};
const SpriteLayer slash_horizontalright_layerSet3[] = {
    {slash_horizontal_image2,4,0,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0}};
const SpriteLayer slash_horizontalright_layerSet4[] = {
    {slash_horizontal_image1,8,0,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0}};
const SpriteLayer slash_horizontalright_layerSet5[] = {
    {slash_horizontal_image0,12,0,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0}};

const SpriteLayerSet slash_horizontalright_layerSet[] = {
    {slash_horizontalright_layerSet0,2,1},
    {slash_horizontalright_layerSet1,2,1},
    {slash_horizontalright_layerSet2,2,1},
    {slash_horizontalright_layerSet3,2,1},
    {slash_horizontalright_layerSet4,2,1},
    {slash_horizontalright_layerSet5,2,1},
};

const SpriteSet slash_horizontalright = {slash_horizontalright_layerSet,6};
