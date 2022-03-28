#include "GBATypes.h"
#include "GBAObject.h"
#include "ImageWerewolf.h"

const SpriteLayer werewolf_run_up_layerSet0[] = {
    {werewolfupperbody_run_up_image0,0,0,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {werewolffeet_run_up_image0,0,16,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0},
    {werewolfarm_up_image0,-3,4,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0},
    {werewolfarm_up_image0,11,4,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0}};
const SpriteLayer werewolf_run_up_layerSet1[] = {
    {werewolfupperbody_run_up_image0,0,0,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {werewolffeet_run_up_image1,0,16,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0},
    {werewolfarm_up_image0,-3,3,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0},
    {werewolfarm_up_image0,11,5,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0}};
const SpriteLayer werewolf_run_up_layerSet2[] = {
    {werewolfupperbody_run_up_image0,0,1,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {werewolfarm_up_image0,10,6,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0},
    {werewolffeet_run_up_image2,0,16,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolfarm_up_image0,-3,3,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0}};
const SpriteLayer werewolf_run_up_layerSet3[] = {
    {werewolfupperbody_run_up_image0,0,0,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {werewolffeet_run_up_image1,0,16,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0},
    {werewolfarm_up_image0,-3,3,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0},
    {werewolfarm_up_image0,11,5,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0}};
const SpriteLayer werewolf_run_up_layerSet4[] = {
    {werewolfupperbody_run_up_image0,0,0,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {werewolffeet_run_up_image0,0,16,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0},
    {werewolfarm_up_image0,-3,4,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0},
    {werewolfarm_up_image0,11,4,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0}};
const SpriteLayer werewolf_run_up_layerSet5[] = {
    {werewolfupperbody_run_up_image0,0,0,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {werewolfarm_up_image0,-3,5,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0},
    {werewolffeet_run_up_image1,0,16,SQUARE,SMALL_B,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolfarm_up_image0,11,3,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0}};
const SpriteLayer werewolf_run_up_layerSet6[] = {
    {werewolfupperbody_run_up_image0,0,1,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {werewolfarm_up_image0,-2,6,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0},
    {werewolffeet_run_up_image2,0,16,SQUARE,SMALL_B,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolfarm_up_image0,11,3,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0}};
const SpriteLayer werewolf_run_up_layerSet7[] = {
    {werewolfupperbody_run_up_image0,0,0,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {werewolfarm_up_image0,-3,5,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0},
    {werewolffeet_run_up_image1,0,16,SQUARE,SMALL_B,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolfarm_up_image0,11,3,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0}};

const SpriteLayerSet werewolf_run_up_layerSet[] = {
    {werewolf_run_up_layerSet0,5,4},
    {werewolf_run_up_layerSet1,5,4},
    {werewolf_run_up_layerSet2,5,4},
    {werewolf_run_up_layerSet3,5,4},
    {werewolf_run_up_layerSet4,5,4},
    {werewolf_run_up_layerSet5,5,4},
    {werewolf_run_up_layerSet6,5,4},
    {werewolf_run_up_layerSet7,5,4},
};

const SpriteSet werewolf_run_up = {werewolf_run_up_layerSet,8};
