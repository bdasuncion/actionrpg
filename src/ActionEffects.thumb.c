#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"

const unsigned short slash_horizontal_pal[16] = 
{
	0x7FFF,0x0000,0x03FF,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
};
const unsigned int slash_horizontal_image0[16] = 
{
	0x00000000,0x00000000,0x00222200,0x02222220,0x00222200,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,

};
const unsigned int slash_horizontal_image1[16] = 
{
	0x00000000,0x00000000,0x22220000,0x22222220,0x22220000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000022,0x00000222,0x00000022,0x00000000,0x00000000,0x00000000,

};
const unsigned int slash_horizontal_image2[16] = 
{
	0x00000000,0x00000000,0x22000000,0x22222220,0x22000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00222222,0x02222222,0x00222222,0x00000000,0x00000000,0x00000000
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
