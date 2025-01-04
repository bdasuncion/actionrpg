#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"

extern const SpriteSet werewolf_run_down;
extern const SpriteSet werewolf_run_right;
extern const SpriteSet werewolf_run_up;
extern const SpriteSet werewolf_run_left;

const SpriteSet * const werewolfRun[] = {&werewolf_run_down, &werewolf_run_down, &werewolf_run_right, &werewolf_run_up,
    &werewolf_run_up, &werewolf_run_up, &werewolf_run_left, &werewolf_run_down};

extern const SpriteSet werewolf_stand_down;
extern const SpriteSet werewolf_stand_left;
extern const SpriteSet werewolf_stand_right;
extern const SpriteSet werewolf_stand_up;

const SpriteSet * const werewolfStand[] = {&werewolf_stand_down, &werewolf_stand_down, &werewolf_stand_right, &werewolf_stand_up,
    &werewolf_stand_up, &werewolf_stand_up, &werewolf_stand_left, &werewolf_stand_down};