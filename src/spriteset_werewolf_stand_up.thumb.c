#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageWerewolf.h"

const SpriteLayer werewolf_stand_up_layerSet0[] = {
    {werewolffeet_stand_up_image0,0,19,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {werewolftail_up_image0,2,5,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0},
    {werewolfupperbody_run_up_image0,0,3,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolfhead_up_image0,4,0,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0},
    {werewolfarm_up_image0,-4,5,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,1,0},
    {werewolfarm_up_image0,12,5,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0}};
const SpriteLayer werewolf_stand_up_layerSet1[] = {
    {werewolffeet_stand_up_image0,0,19,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {werewolftail_up_image0,2,5,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0},
    {werewolfupperbody_run_up_image0,0,3,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolfhead_up_image2,5,0,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0},
    {werewolfarm_up_image0,-4,5,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,1,0},
    {werewolfarm_up_image0,12,5,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0}};
const SpriteLayer werewolf_stand_up_layerSet2[] = {
    {werewolffeet_stand_up_image0,0,19,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {werewolftail_up_image0,2,5,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0},
    {werewolfupperbody_run_up_image0,0,3,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolfhead_up_image0,4,0,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0},
    {werewolfarm_up_image0,-4,5,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,1,0},
    {werewolfarm_up_image0,12,5,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0}};
const SpriteLayer werewolf_stand_up_layerSet3[] = {
    {werewolffeet_stand_up_image0,0,19,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {werewolftail_up_image0,2,5,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0},
    {werewolfupperbody_run_up_image0,0,3,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolfhead_up_image1,3,0,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0},
    {werewolfarm_up_image0,-4,5,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,1,0},
    {werewolfarm_up_image0,12,5,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0}};

const SpriteLayerSet werewolf_stand_up_layerSet[] = {
    {werewolf_stand_up_layerSet0,20,6},
    {werewolf_stand_up_layerSet1,30,6},
    {werewolf_stand_up_layerSet2,10,6},
    {werewolf_stand_up_layerSet3,30,6},
};

const SpriteSet werewolf_stand_up = {werewolf_stand_up_layerSet,4};
