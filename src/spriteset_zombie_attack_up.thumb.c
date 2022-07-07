#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageZombie.h"

const SpriteLayer zombie_attack_up_layerSet0[] = {
    {zombie_attack_up_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0}};
const SpriteLayer zombie_attack_up_layerSet1[] = {
    {zombie_attack_up_image1,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0}};
const SpriteLayer zombie_attack_up_layerSet2[] = {
    {zombie_attack_up_image2,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0}};
const SpriteLayer zombie_attack_up_layerSet3[] = {
    {zombie_attack_up_image3,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0}};
const SpriteLayer zombie_attack_up_layerSet4[] = {
    {zombie_attack_up_image4,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0}};
const SpriteLayer zombie_attack_up_layerSet5[] = {
    {zombie_attack_up_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0}};

const SpriteLayerSet zombie_attack_up_layerSet[] = {
    {zombie_attack_up_layerSet0,5,1},
    {zombie_attack_up_layerSet1,5,1},
    {zombie_attack_up_layerSet2,12,1},
    {zombie_attack_up_layerSet3,1,1},
    {zombie_attack_up_layerSet4,1,1},
    {zombie_attack_up_layerSet5,25,1},
};

const SpriteSet zombie_attack_up = {zombie_attack_up_layerSet,6};
