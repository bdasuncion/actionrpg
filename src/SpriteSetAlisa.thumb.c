#include "GBATypes.h"
#include "GBAObject.h"

extern const SpriteSet alisa_standwithsword_down;
extern const SpriteSet alisa_standwithsword_left;
extern const SpriteSet alisa_standwithsword_right;
extern const SpriteSet alisa_standwithsword_up;

const SpriteSet *alisaStandWithSwordSet[] = {&alisa_standwithsword_down, &alisa_standwithsword_down, &alisa_standwithsword_right, &alisa_standwithsword_up,
    &alisa_standwithsword_up, &alisa_standwithsword_up, &alisa_standwithsword_left, &alisa_standwithsword_down};
	
extern const SpriteSet alisa_runwithsword_down;
extern const SpriteSet alisa_runwithsword_right;
extern const SpriteSet alisa_runwithsword_left;
extern const SpriteSet alisa_runwithsword_up;

const SpriteSet *alisaRunSet[] = { &alisa_runwithsword_down, &alisa_runwithsword_down, &alisa_runwithsword_right, 
    &alisa_runwithsword_up, &alisa_runwithsword_up, &alisa_runwithsword_up, &alisa_runwithsword_left, &alisa_runwithsword_down };

extern const SpriteSet alisa_swordslash_down;
extern const SpriteSet alisa_swordslash_left;
extern const SpriteSet alisa_swordslash_right;
extern const SpriteSet alisa_swordslash_up;

const SpriteSet *alisaSlashSet[] = { &alisa_swordslash_down, &alisa_swordslash_down, &alisa_swordslash_right, 
    &alisa_swordslash_up, &alisa_swordslash_up, &alisa_swordslash_up, &alisa_swordslash_left, &alisa_swordslash_down };