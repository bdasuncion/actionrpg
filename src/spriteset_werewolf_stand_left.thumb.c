#include "GBATypes.h"
#include "GBAObject.h"
#include "ImageWerewolf.h"

const SpriteLayer werewolf_stand_left_layerSet0[] = {
    {werewolftail_side_image0,14,13,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {werewolfarm_side_image0,6,4,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolffeet_run_side_image2,0,16,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolfupperbody_run_side_image0,0,0,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0}};
const SpriteLayer werewolf_stand_left_layerSet1[] = {
    {werewolftail_side_image0,14,13,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {werewolfarm_side_image0,7,4,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolffeet_run_side_image2,0,16,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolfupperbody_run_side_image1,0,0,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0}};
const SpriteLayer werewolf_stand_left_layerSet2[] = {
    {werewolftail_side_image0,14,13,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {werewolfarm_side_image0,6,4,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolffeet_run_side_image2,0,16,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolfupperbody_run_side_image0,0,0,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0}};
const SpriteLayer werewolf_stand_left_layerSet3[] = {
    {werewolftail_side_image0,14,13,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {werewolfarm_side_image0,5,4,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolffeet_run_side_image2,0,16,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolfupperbody_run_side_image2,0,0,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0}};

const SpriteLayerSet werewolf_stand_left_layerSet[] = {
    {werewolf_stand_left_layerSet0,20,4},
    {werewolf_stand_left_layerSet1,30,4},
    {werewolf_stand_left_layerSet2,10,4},
    {werewolf_stand_left_layerSet3,30,4},
};

const SpriteSet werewolf_stand_left = {werewolf_stand_left_layerSet,4};
