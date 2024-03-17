#include "CharacterCommon.h"
#include "GBACharacter.h"
#include "ManagerVram.h"

extern const SpriteSet slash_horizontalright;
extern const SpriteSet slash_horizontalleft;
const SpriteSet *attackEffectSpiteSets[EActionCount] = {&slash_horizontalright, &slash_horizontalleft, 
	&slash_horizontalright, &slash_horizontalleft};

void charAttackEffect_getPosition(BoundingBox *attack, BoundingBox *collisiontTarget, Position *position) {
	position->z = (attack->startZ + attack->startZ + collisiontTarget->startZ + collisiontTarget->endZ) >> 2;
	position->x = (attack->startX + attack->endX + collisiontTarget->startX + collisiontTarget->endX) >> 2;
	position->x = (attack->startY + attack->endY + collisiontTarget->startY + collisiontTarget->endY) >> 2;
}

void charAttackEffect_Add(Position *position, CharacterActionType type, AttackEffectCollection* attackEffectCollection) {
	AttackEffect *effect = &attackEffectCollection->collection[0];
	effect->display.baseImageId = EVramMapIdAttackEffects;
	effect->display.imageUpdateStatus = EUpdate;
	effect->display.basePalleteId = 15;
	effect->display.spriteSet = attackEffectSpiteSets[type];
	effect->position = *position;
}