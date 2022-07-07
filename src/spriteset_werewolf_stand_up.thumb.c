#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageWerewolf.h"

const SpriteLayer werewolf_stand_up_layerSet0[] = {
    {werewolffeet_run_up_image0,0,16,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {werewolfupperbody_run_up_image0,0,0,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0},
    {werewolfarm_up_image0,-4,3,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0},
    {werewolfarm_up_image0,12,3,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0}};
const SpriteLayer werewolf_stand_up_layerSet1[] = {
    {werewolfupperbody_run_up_image1,0,0,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {werewolfarm_up_image0,-4,3,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0},
    {werewolfarm_up_image0,12,3,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolffeet_run_up_image0,0,16,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0}};
const SpriteLayer werewolf_stand_up_layerSet2[] = {
    {werewolfupperbody_run_up_image0,0,0,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {werewolfarm_up_image0,-4,3,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0},
    {werewolfarm_up_image0,12,3,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolffeet_run_up_image0,0,16,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0}};
const SpriteLayer werewolf_stand_up_layerSet3[] = {
    {werewolfupperbody_run_up_image2,0,0,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {werewolfarm_up_image0,-4,3,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,4,0},
    {werewolfarm_up_image0,12,3,TALL,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0},
    {werewolffeet_run_up_image0,0,16,SQUARE,SMALL_B,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0}};

const SpriteLayerSet werewolf_stand_up_layerSet[] = {
    {werewolf_stand_up_layerSet0,20,4},
    {werewolf_stand_up_layerSet1,30,4},
    {werewolf_stand_up_layerSet2,10,4},
    {werewolf_stand_up_layerSet3,30,4},
};

const SpriteSet werewolf_stand_up = {werewolf_stand_up_layerSet,4};
