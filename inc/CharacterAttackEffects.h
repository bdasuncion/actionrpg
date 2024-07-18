#ifndef CHARACTER_ATTACK_EFFECTS
#define CHARACTER_ATTACK_EFFECTS

void charAttackEffect_UpdateAnimation(AttackEffectCollection* attackEffectCollection);
int charAttackEffect_setToOAMBuffer(AttackEffectCollection* attackEffectCollection, OAMCollection *oamCollection,
	const int currentOAMIdx, const Position *scr_pos, const ScreenDimension *scr_dim);
int charAttackEffect_setPosition(AttackEffect *effect, OBJ_ATTR *oamBuf, const Position *scr_pos,
	const ScreenDimension *scr_dim);
void charAttackEffect_Add(Position *position, CharacterActionType type, AttackEffectCollection* attackEffectCollection);
void charAttackEffect_getPosition(BoundingBox *attack, BoundingBox *collisiontTarget, Position *position);
void charAttackEffect_Init(AttackEffectCollection* attackEffects);
#endif