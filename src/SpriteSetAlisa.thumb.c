#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"

extern const SpriteSet alisa_standwithsword_down;
extern const SpriteSet alisa_standwithsword_left;
extern const SpriteSet alisa_standwithsword_right;
extern const SpriteSet alisa_standwithsword_up;
extern const SpriteSet alisa_standwithsword_big_right;

const SpriteSet *alisaStandWithSwordSet[] = {&alisa_standwithsword_down, &alisa_standwithsword_down, &alisa_standwithsword_right, &alisa_standwithsword_up,
    &alisa_standwithsword_up, &alisa_standwithsword_up, &alisa_standwithsword_left, &alisa_standwithsword_down};
//const SpriteSet *alisaStandWithSwordSet[] = {&alisa_standwithsword_down, &alisa_standwithsword_down, &alisa_standwithsword_big_right, &alisa_standwithsword_up,
//    &alisa_standwithsword_up, &alisa_standwithsword_up, &alisa_standwithsword_left, &alisa_standwithsword_down};
	
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
	
extern const SpriteSet alisa_stunnedwithsword_down;
extern const SpriteSet alisa_stunnedwithsword_right;
extern const SpriteSet alisa_stunnedwithsword_left;
extern const SpriteSet alisa_stunnedwithsword_up;

const SpriteSet *alisaStunnedSet[] = { &alisa_stunnedwithsword_down, &alisa_stunnedwithsword_down, &alisa_stunnedwithsword_right, 
    &alisa_stunnedwithsword_up, &alisa_stunnedwithsword_up, &alisa_stunnedwithsword_up, &alisa_stunnedwithsword_left, &alisa_stunnedwithsword_down };
	
extern const SpriteSet alisa_dashforwardwithsword_down;
extern const SpriteSet alisa_dashforwardwithsword_right;
extern const SpriteSet alisa_dashforwardwithsword_left;
extern const SpriteSet alisa_dashforwardwithsword_up;

const SpriteSet *alisaDashForwardSet[] = { &alisa_dashforwardwithsword_down, &alisa_dashforwardwithsword_down, &alisa_dashforwardwithsword_right, 
    &alisa_dashforwardwithsword_up, &alisa_dashforwardwithsword_up, &alisa_dashforwardwithsword_up, &alisa_dashforwardwithsword_left, &alisa_dashforwardwithsword_down };

extern const SpriteSet alisa_preparedash_down;
extern const SpriteSet alisa_preparedash_left;
extern const SpriteSet alisa_preparedash_right;
extern const SpriteSet alisa_preparedash_up;

const SpriteSet *alisaPrepareDashSet[] = { &alisa_preparedash_down, &alisa_preparedash_down, &alisa_preparedash_right, 
    &alisa_preparedash_up, &alisa_preparedash_up, &alisa_preparedash_up, &alisa_preparedash_left, &alisa_preparedash_down };

extern const SpriteSet alisa_dashbackwardwithsword_down;
extern const SpriteSet alisa_dashbackwardwithsword_left;
extern const SpriteSet alisa_dashbackwardwithsword_right;
extern const SpriteSet alisa_dashbackwardwithsword_up;

const SpriteSet *alisaDashBackwardWithSwordSet[] = { &alisa_dashbackwardwithsword_down, &alisa_dashbackwardwithsword_down, &alisa_dashbackwardwithsword_right, 
    &alisa_dashbackwardwithsword_up, &alisa_dashbackwardwithsword_up, &alisa_dashbackwardwithsword_up, &alisa_dashbackwardwithsword_left, &alisa_dashbackwardwithsword_down };
	
extern const SpriteSet alisa_jumpwithsword_down;
extern const SpriteSet alisa_jumpwithsword_left;
extern const SpriteSet alisa_jumpwithsword_right;
extern const SpriteSet alisa_jumpwithsword_up;

const SpriteSet *alisaJumpWithSwordSet[] = { &alisa_jumpwithsword_down, &alisa_jumpwithsword_down, &alisa_jumpwithsword_right, 
    &alisa_jumpwithsword_up, &alisa_jumpwithsword_up, &alisa_jumpwithsword_up, &alisa_jumpwithsword_left, &alisa_jumpwithsword_down };
	
extern const SpriteSet alisa_fallingdown_down;
extern const SpriteSet alisa_fallingdown_left;
extern const SpriteSet alisa_fallingdown_right;
extern const SpriteSet alisa_fallingdown_up;

const SpriteSet *alisaFallingDownSet[] = { &alisa_fallingdown_down, &alisa_fallingdown_down, &alisa_fallingdown_right, 
    &alisa_fallingdown_up, &alisa_fallingdown_up, &alisa_fallingdown_up, &alisa_fallingdown_left, &alisa_fallingdown_down };