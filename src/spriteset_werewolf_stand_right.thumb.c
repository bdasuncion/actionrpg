#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageWerewolf.h"

const SpriteLayer werewolf_stand_right_layerSet0[] = {
    {werewolftail_side_image0,-6,13,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {werewolfarm_side_image0,2,4,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolffeet_run_side_image2,0,16,SQUARE,SMALL_B,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolfupperbody_run_side_image0,0,0,SQUARE,SMALL_B,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0}};
const SpriteLayer werewolf_stand_right_layerSet1[] = {
    {werewolftail_side_image0,-6,13,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {werewolfarm_side_image0,1,4,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolffeet_run_side_image2,0,16,SQUARE,SMALL_B,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolfupperbody_run_side_image1,0,0,SQUARE,SMALL_B,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0}};
const SpriteLayer werewolf_stand_right_layerSet2[] = {
    {werewolftail_side_image0,-6,13,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {werewolfarm_side_image0,2,4,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolffeet_run_side_image2,0,16,SQUARE,SMALL_B,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolfupperbody_run_side_image0,0,0,SQUARE,SMALL_B,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0}};
const SpriteLayer werewolf_stand_right_layerSet3[] = {
    {werewolftail_side_image0,-6,13,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {werewolfarm_side_image0,3,4,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolffeet_run_side_image2,0,16,SQUARE,SMALL_B,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolfupperbody_run_side_image2,0,0,SQUARE,SMALL_B,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0}};

const SpriteLayerSet werewolf_stand_right_layerSet[] = {
    {werewolf_stand_right_layerSet0,20,4},
    {werewolf_stand_right_layerSet1,30,4},
    {werewolf_stand_right_layerSet2,10,4},
    {werewolf_stand_right_layerSet3,30,4},
};

const SpriteSet werewolf_stand_right = {werewolf_stand_right_layerSet,4};
