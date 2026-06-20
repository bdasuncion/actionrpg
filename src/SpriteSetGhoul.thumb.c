#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"

extern const SpriteSet ghoul_walk_up;
extern const SpriteSet ghoul_walk_right;
extern const SpriteSet ghoul_walk_left;
extern const SpriteSet ghoul_walk_down;

const SpriteSet *const ghoulWalking[] = {&ghoul_walk_down, &ghoul_walk_down, &ghoul_walk_right, &ghoul_walk_up,
    &ghoul_walk_up, &ghoul_walk_up, &ghoul_walk_left, &ghoul_walk_down};
	
extern const SpriteSet ghoul_attack_up;
extern const SpriteSet ghoul_attack_right;
extern const SpriteSet ghoul_attack_left;
extern const SpriteSet ghoul_attack_down;

const SpriteSet *const ghoulAttacking[] = {&ghoul_attack_down, &ghoul_attack_down, &ghoul_attack_right, &ghoul_attack_up,
    &ghoul_attack_up, &ghoul_attack_up, &ghoul_attack_left, &ghoul_attack_down};
	

extern const SpriteSet ghoul_hurt_up;
extern const SpriteSet ghoul_hurt_right;
extern const SpriteSet ghoul_hurt_left;
extern const SpriteSet ghoul_hurt_down;

const SpriteSet *const ghoulHurt[] = {&ghoul_hurt_down, &ghoul_hurt_down, &ghoul_hurt_right, &ghoul_hurt_up,
    &ghoul_hurt_up, &ghoul_hurt_up, &ghoul_hurt_left, &ghoul_hurt_down};
/*	
const SpriteSet *const ghoulHurt[] = {&ghoul_attack_down, &ghoul_attack_down, &ghoul_attack_right, &ghoul_attack_up,
    &ghoul_attack_up, &ghoul_attack_up, &ghoul_attack_left, &ghoul_attack_down};*/
