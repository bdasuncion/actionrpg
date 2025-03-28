#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"

extern const SpriteSet skull_demon_walking_up;
extern const SpriteSet skull_demon_walking_right;
extern const SpriteSet skull_demon_walking_left;
extern const SpriteSet skull_demon_walking_down;

const SpriteSet *const skulldemonWalking[] = {&skull_demon_walking_down, &skull_demon_walking_down, &skull_demon_walking_right, &skull_demon_walking_up,
    &skull_demon_walking_up, &skull_demon_walking_up, &skull_demon_walking_left, &skull_demon_walking_down};
	
extern const SpriteSet skull_demon_attacking_up;
extern const SpriteSet skull_demon_attacking_right;
extern const SpriteSet skull_demon_attacking_left;
extern const SpriteSet skull_demon_attacking_down;

const SpriteSet *const skulldemonAttacking[] = {&skull_demon_attacking_down, &skull_demon_attacking_down, &skull_demon_attacking_right, &skull_demon_attacking_up,
    &skull_demon_attacking_up, &skull_demon_attacking_up, &skull_demon_attacking_left, &skull_demon_attacking_down};