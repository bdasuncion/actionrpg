#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageZombie.h"

const SpriteLayer zombie_attack_right_layerSet0[] = {
    {zombie_attack_side_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0}};
const SpriteLayer zombie_attack_right_layerSet1[] = {
    {zombie_attack_side_image1,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0}};
const SpriteLayer zombie_attack_right_layerSet2[] = {
    {zombie_attack_side_image2,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0}};
const SpriteLayer zombie_attack_right_layerSet3[] = {
    {zombie_attack_side_image3,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0}};
const SpriteLayer zombie_attack_right_layerSet4[] = {
    {zombie_attack_side_image4,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0}};
const SpriteLayer zombie_attack_right_layerSet5[] = {
    {zombie_attack_side_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0}};

const SpriteLayerSet zombie_attack_right_layerSet[] = {
    {zombie_attack_right_layerSet0,5,1},
    {zombie_attack_right_layerSet1,5,1},
    {zombie_attack_right_layerSet2,12,1},
    {zombie_attack_right_layerSet3,1,1},
    {zombie_attack_right_layerSet4,1,1},
    {zombie_attack_right_layerSet5,25,1},
};

const SpriteSet zombie_attack_right = {zombie_attack_right_layerSet,6};
