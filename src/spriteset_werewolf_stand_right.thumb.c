#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageWerewolf.h"

const SpriteLayer werewolf_stand_right_layerSet0[] = {
    {werewolftail_side_image0,-4,15,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {werewolfarm_side_image0,5,5,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {werewolffeet_run_side_image2,2,19,SQUARE,SMALL_B,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {werewolfupperbody_run_side_image0,0,3,SQUARE,SMALL_B,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0},
    {werewolfhead_side_image0,10,0,SQUARE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};
const SpriteLayer werewolf_stand_right_layerSet1[] = {
    {werewolftail_side_image0,-4,15,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {werewolfarm_side_image0,4,5,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {werewolffeet_run_side_image2,2,19,SQUARE,SMALL_B,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {werewolfupperbody_run_side_image0,0,3,SQUARE,SMALL_B,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0},
    {werewolfhead_side_image1,10,0,SQUARE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};
const SpriteLayer werewolf_stand_right_layerSet2[] = {
    {werewolftail_side_image0,-4,15,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {werewolfarm_side_image0,5,5,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {werewolffeet_run_side_image2,2,19,SQUARE,SMALL_B,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {werewolfupperbody_run_side_image0,0,3,SQUARE,SMALL_B,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0},
    {werewolfhead_side_image0,10,0,SQUARE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};
const SpriteLayer werewolf_stand_right_layerSet3[] = {
    {werewolftail_side_image0,-4,15,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,0,0},
    {werewolfarm_side_image0,6,5,TALL,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {werewolffeet_run_side_image2,2,19,SQUARE,SMALL_B,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,2,0},
    {werewolfupperbody_run_side_image0,0,3,SQUARE,SMALL_B,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0},
    {werewolfhead_side_image2,9,0,SQUARE,SMALL_A,DO_HFLIP,NO_VFLIP,NO_COMPRESSION,4,0}};

const SpriteLayerSet werewolf_stand_right_layerSet[] = {
    {werewolf_stand_right_layerSet0,20,5},
    {werewolf_stand_right_layerSet1,30,5},
    {werewolf_stand_right_layerSet2,10,5},
    {werewolf_stand_right_layerSet3,30,5},
};

const SpriteSet werewolf_stand_right = {werewolf_stand_right_layerSet,4};
