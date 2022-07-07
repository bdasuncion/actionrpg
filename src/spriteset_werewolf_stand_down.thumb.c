#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageWerewolf.h"

const SpriteLayer werewolf_stand_down_layerSet0[] = {
    {werewolfupperbody_run_down_image0,0,0,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {werewolfarm_down_image0,12,3,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0},
    {werewolfarm_down_image0,-4,3,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolffeet_run_down_image0,0,16,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0}};
const SpriteLayer werewolf_stand_down_layerSet1[] = {
    {werewolffeet_run_down_image0,0,16,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {werewolfupperbody_run_down_image1,0,0,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0},
    {werewolfarm_down_image0,-4,3,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0},
    {werewolfarm_down_image0,12,3,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0}};
const SpriteLayer werewolf_stand_down_layerSet2[] = {
    {werewolffeet_run_down_image0,0,16,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {werewolfupperbody_run_down_image0,0,0,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0},
    {werewolfarm_down_image0,-4,3,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0},
    {werewolfarm_down_image0,12,3,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0}};
const SpriteLayer werewolf_stand_down_layerSet3[] = {
    {werewolffeet_run_down_image0,0,16,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {werewolfupperbody_run_down_image1,0,0,SQUARE,SMALL_B,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0},
    {werewolfarm_down_image0,-4,3,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0},
    {werewolfarm_down_image0,12,3,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0}};

const SpriteLayerSet werewolf_stand_down_layerSet[] = {
    {werewolf_stand_down_layerSet0,20,4},
    {werewolf_stand_down_layerSet1,30,4},
    {werewolf_stand_down_layerSet2,10,4},
    {werewolf_stand_down_layerSet3,30,4},
};

const SpriteSet werewolf_stand_down = {werewolf_stand_down_layerSet,4};
