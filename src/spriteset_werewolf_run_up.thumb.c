#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageWerewolf.h"

const SpriteLayer werewolf_run_up_layerSet0[] = {
    {werewolftail_up_image0,2,5,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {werewolfupperbody_run_up_image0,0,3,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolfhead_up_image0,4,0,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0},
    {werewolffeet_run_up_image0,0,19,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,1,0},
    {werewolfarm_up_image0,-4,5,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0},
    {werewolfarm_up_image0,12,5,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0}};
const SpriteLayer werewolf_run_up_layerSet1[] = {
    {werewolftail_up_image0,2,5,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {werewolfupperbody_run_up_image0,0,3,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolfarm_up_image1,-4,5,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0},
    {werewolfarm_up_image2,12,5,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolfhead_up_image0,4,0,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolffeet_run_up_image1,0,19,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,1,0}};
const SpriteLayer werewolf_run_up_layerSet2[] = {
    {werewolftail_up_image0,2,5,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {werewolfupperbody_run_up_image0,0,3,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolfarm_up_image2,12,5,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0},
    {werewolfarm_up_image1,-4,5,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolfhead_up_image0,4,0,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolffeet_run_up_image2,0,19,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,1,0}};
const SpriteLayer werewolf_run_up_layerSet3[] = {
    {werewolftail_up_image0,2,5,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {werewolfupperbody_run_up_image0,0,3,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolfarm_up_image1,-4,5,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0},
    {werewolfarm_up_image2,12,5,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolfhead_up_image0,4,0,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolffeet_run_up_image1,0,19,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,1,0}};
const SpriteLayer werewolf_run_up_layerSet4[] = {
    {werewolftail_up_image0,2,5,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {werewolfupperbody_run_up_image0,0,3,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolfhead_up_image0,4,0,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0},
    {werewolffeet_run_up_image0,0,19,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,1,0},
    {werewolfarm_up_image0,-4,5,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0},
    {werewolfarm_up_image0,12,5,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0}};
const SpriteLayer werewolf_run_up_layerSet5[] = {
    {werewolftail_up_image0,2,5,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {werewolfupperbody_run_up_image0,0,3,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolfarm_up_image2,-4,5,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0},
    {werewolfarm_up_image1,12,5,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolfhead_up_image0,4,0,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolffeet_run_up_image1,0,19,SQUARE,SMALL_B,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,1,0}};
const SpriteLayer werewolf_run_up_layerSet6[] = {
    {werewolftail_up_image0,2,5,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {werewolfupperbody_run_up_image0,0,3,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolfarm_up_image2,-4,5,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0},
    {werewolfarm_up_image1,12,5,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolfhead_up_image0,4,0,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolffeet_run_up_image2,0,19,SQUARE,SMALL_B,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,1,0}};
const SpriteLayer werewolf_run_up_layerSet7[] = {
    {werewolftail_up_image0,2,5,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {werewolfupperbody_run_up_image0,0,3,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolfarm_up_image1,12,5,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0},
    {werewolfarm_up_image2,-4,5,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolfhead_up_image0,4,0,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolffeet_run_up_image1,0,19,SQUARE,SMALL_B,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,1,0}};

const SpriteLayerSet werewolf_run_up_layerSet[] = {
    {werewolf_run_up_layerSet0,5,6},
    {werewolf_run_up_layerSet1,5,6},
    {werewolf_run_up_layerSet2,5,6},
    {werewolf_run_up_layerSet3,5,6},
    {werewolf_run_up_layerSet4,5,6},
    {werewolf_run_up_layerSet5,5,6},
    {werewolf_run_up_layerSet6,5,6},
    {werewolf_run_up_layerSet7,5,6},
};

const SpriteSet werewolf_run_up = {werewolf_run_up_layerSet,8};
