#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"

extern const SpriteSet wickedknight_walk_up;
extern const SpriteSet wickedknight_walk_right;
extern const SpriteSet wickedknight_walk_left;
extern const SpriteSet wickedknight_walk_down;

const SpriteSet *const wickedknightWalking[] = {&wickedknight_walk_down, &wickedknight_walk_down, &wickedknight_walk_right, &wickedknight_walk_up,
    &wickedknight_walk_up, &wickedknight_walk_up, &wickedknight_walk_left, &wickedknight_walk_down};
	
extern const SpriteSet wickedknight_attack_up;
extern const SpriteSet wickedknight_attack_right;
extern const SpriteSet wickedknight_attack_left;
extern const SpriteSet wickedknight_attack_down;

const SpriteSet *const wickedknightAttacking[] = {&wickedknight_attack_down, &wickedknight_attack_down, &wickedknight_attack_right, &wickedknight_attack_up,
    &wickedknight_attack_up, &wickedknight_attack_up, &wickedknight_attack_left, &wickedknight_attack_down};