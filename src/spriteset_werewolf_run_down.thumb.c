#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageWerewolf.h"

const SpriteLayer werewolf_run_down_layerSet0[] = {
    {werewolfhead_down_image0,4,0,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {werewolfarm_down_image0,-4,4,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,1,0},
    {werewolfarm_down_image0,12,4,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolfupperbody_run_down_image0,0,3,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolffeet_run_down_image0,0,19,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0}};
const SpriteLayer werewolf_run_down_layerSet1[] = {
    {werewolfarm_down_image2,12,4,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {werewolfarm_down_image1,-4,4,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolfhead_down_image0,4,0,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolfupperbody_run_down_image0,0,3,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,1,0},
    {werewolffeet_run_down_image1,0,19,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0}};
const SpriteLayer werewolf_run_down_layerSet2[] = {
    {werewolfarm_down_image1,-4,4,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {werewolfarm_down_image2,12,4,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolfhead_down_image0,4,0,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolfupperbody_run_down_image0,0,3,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,1,0},
    {werewolffeet_run_down_image2,0,19,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0}};
const SpriteLayer werewolf_run_down_layerSet3[] = {
    {werewolfarm_down_image1,-4,4,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {werewolfarm_down_image2,12,4,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolfhead_down_image0,4,0,SQUARE,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolfupperbody_run_down_image0,0,3,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,1,0},
    {werewolffeet_run_down_image1,0,19,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0}};
const SpriteLayer werewolf_run_down_layerSet4[] = {
    {werewolfhead_down_image0,4,0,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {werewolfarm_down_image0,-4,4,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,1,0},
    {werewolfarm_down_image0,12,4,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolfupperbody_run_down_image0,0,3,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolffeet_run_down_image0,0,19,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0}};
const SpriteLayer werewolf_run_down_layerSet5[] = {
    {werewolfarm_down_image1,12,4,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {werewolfarm_down_image2,-4,4,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolfhead_down_image0,4,0,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolfupperbody_run_down_image0,0,3,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,1,0},
    {werewolffeet_run_down_image1,0,19,SQUARE,SMALL_B,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0}};
const SpriteLayer werewolf_run_down_layerSet6[] = {
    {werewolfarm_down_image1,12,4,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {werewolfarm_down_image2,-4,4,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolfhead_down_image0,4,0,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolfupperbody_run_down_image0,0,3,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,1,0},
    {werewolffeet_run_down_image2,0,19,SQUARE,SMALL_B,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0}};
const SpriteLayer werewolf_run_down_layerSet7[] = {
    {werewolfarm_down_image1,12,4,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {werewolfarm_down_image2,-4,4,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolfhead_down_image0,4,0,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolfupperbody_run_down_image0,0,3,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,1,0},
    {werewolffeet_run_down_image1,0,19,SQUARE,SMALL_B,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0}};

const SpriteLayerSet werewolf_run_down_layerSet[] = {
    {werewolf_run_down_layerSet0,5,5},
    {werewolf_run_down_layerSet1,5,5},
    {werewolf_run_down_layerSet2,9,5},
    {werewolf_run_down_layerSet3,5,5},
    {werewolf_run_down_layerSet4,5,5},
    {werewolf_run_down_layerSet5,5,5},
    {werewolf_run_down_layerSet6,9,5},
    {werewolf_run_down_layerSet7,5,5},
};

const SpriteSet werewolf_run_down = {werewolf_run_down_layerSet,8};
