#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageWerewolf.h"

const SpriteLayer werewolf_stand_down_layerSet0[] = {
    {werewolffeet_stand_down_image0,0,19,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {werewolfhead_down_image0,4,0,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0},
    {werewolfarm_down_image0,12,4,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,1,0},
    {werewolfarm_down_image0,-4,4,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolfupperbody_run_down_image0,0,3,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0}};
const SpriteLayer werewolf_stand_down_layerSet1[] = {
    {werewolffeet_stand_down_image0,0,19,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {werewolfhead_down_image1,3,0,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0},
    {werewolfarm_down_image0,-4,4,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,1,0},
    {werewolfarm_down_image0,12,4,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolfupperbody_run_down_image0,0,3,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0}};
const SpriteLayer werewolf_stand_down_layerSet2[] = {
    {werewolffeet_stand_down_image0,0,19,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {werewolfhead_down_image0,4,0,SQUARE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0},
    {werewolfarm_down_image0,-4,4,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,1,0},
    {werewolfarm_down_image0,12,4,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolfupperbody_run_down_image0,0,3,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0}};
const SpriteLayer werewolf_stand_down_layerSet3[] = {
    {werewolffeet_stand_down_image0,0,19,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {werewolfhead_down_image1,5,0,SQUARE,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0},
    {werewolfarm_down_image0,-4,4,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,1,0},
    {werewolfarm_down_image0,12,4,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolfupperbody_run_down_image0,0,3,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0}};

const SpriteLayerSet werewolf_stand_down_layerSet[] = {
    {werewolf_stand_down_layerSet0,20,5},
    {werewolf_stand_down_layerSet1,30,5},
    {werewolf_stand_down_layerSet2,10,5},
    {werewolf_stand_down_layerSet3,30,5},
};

const SpriteSet werewolf_stand_down = {werewolf_stand_down_layerSet,4};
