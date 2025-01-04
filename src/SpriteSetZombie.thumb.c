#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"

extern const SpriteSet zombie_walk_up;
extern const SpriteSet zombie_walk_right;
extern const SpriteSet zombie_walk_left;
extern const SpriteSet zombie_walk_down;
extern const SpriteSet zombie_attack_up;
extern const SpriteSet zombie_attack_right;
extern const SpriteSet zombie_attack_left;
extern const SpriteSet zombie_attack_down;
extern const SpriteSet zombie_chase_up;
extern const SpriteSet zombie_chase_right;
extern const SpriteSet zombie_chase_left;
extern const SpriteSet zombie_chase_down;
extern const SpriteSet zombie_stunned_up;
extern const SpriteSet zombie_stunned_right;
extern const SpriteSet zombie_stunned_left;
extern const SpriteSet zombie_stunned_down;

const SpriteSet * const zombieWalk[] = {&zombie_walk_down, &zombie_walk_down, &zombie_walk_right, &zombie_walk_up,
    &zombie_walk_up, &zombie_walk_up, &zombie_walk_left, &zombie_walk_down};
const SpriteSet * const zombieAttack[] = {&zombie_attack_down, &zombie_attack_down, &zombie_attack_right, &zombie_attack_up,
    &zombie_attack_up, &zombie_attack_up, &zombie_attack_left, &zombie_attack_down};
const SpriteSet * const zombieChase[] = {&zombie_chase_down, &zombie_chase_down, &zombie_chase_right, &zombie_chase_up,
    &zombie_chase_up, &zombie_chase_up, &zombie_chase_left, &zombie_chase_down};
const SpriteSet * const zombieStunned[] = {&zombie_stunned_down, &zombie_stunned_down, &zombie_stunned_right, &zombie_stunned_up,
    &zombie_stunned_up, &zombie_stunned_up, &zombie_stunned_left, &zombie_stunned_down};