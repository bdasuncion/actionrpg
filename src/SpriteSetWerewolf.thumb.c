#include "GBATypes.h"
#include "GBAObject.h"

extern const SpriteSet werewolf_run_down;
extern const SpriteSet werewolf_run_right;
extern const SpriteSet werewolf_run_up;
extern const SpriteSet werewolf_run_left;

const SpriteSet *werewolfRun[] = {&werewolf_run_down, &werewolf_run_down, &werewolf_run_right, &werewolf_run_up,
    &werewolf_run_up, &werewolf_run_up, &werewolf_run_left, &werewolf_run_down};

extern const SpriteSet werewolf_stand_down;
extern const SpriteSet werewolf_stand_left;
extern const SpriteSet werewolf_stand_right;
extern const SpriteSet werewolf_stand_up;

const SpriteSet *werewolfStand[] = {&werewolf_stand_down, &werewolf_stand_down, &werewolf_stand_right, &werewolf_stand_up,
    &werewolf_stand_up, &werewolf_stand_up, &werewolf_stand_left, &werewolf_stand_down};