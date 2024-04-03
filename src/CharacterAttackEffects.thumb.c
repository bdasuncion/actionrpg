#include "CharacterCommon.h"
#include "GBACharacter.h"
#include "ManagerVram.h"
#include <stdlib.h>

extern const SpriteSet slash_horizontalright;
extern const SpriteSet slash_horizontalleft;
const SpriteSet *attackEffectSpiteSets[EActionCount] = {&slash_horizontalright, &slash_horizontalleft, 
	&slash_horizontalright, &slash_horizontalleft};

extern const unsigned short slash_horizontal_pal[];

#define CHARATTACK_SCRCNVRTWIDTH 16
#define CHARATTACK_SCRCNVRTHEIGHT 8

const u8 charAttackEffect_scrConversionMeasurements[EScrCnvrtMeasureCount] = {
	CHARATTACK_SCRCNVRTWIDTH,
	CHARATTACK_SCRCNVRTHEIGHT
};

#define ATTACK_EFFECT_MAX 10
void charAttackEffect_Init(AttackEffectCollection* attackEffects) {
	int i;
	attackEffects->count = 0;
	attackEffects->collection = malloc(sizeof(AttackEffect*)*ATTACK_EFFECT_MAX);
	for (i = 0; i < ATTACK_EFFECT_MAX; ++i) {
		attackEffects->collection[i] = malloc(sizeof(AttackEffect));
		attackEffects->collection[i]->type = EActionNone;
	}
	
	sprite_palette_copy32_ID(slash_horizontal_pal, SHARED_PALETTEID);
}

void charAttackEffect_getPosition(BoundingBox *attack, BoundingBox *collisiontTarget, Position *position) {
	position->z = CONVERT_2MOVE((attack->startZ + attack->endZ + collisiontTarget->startZ + collisiontTarget->endZ) >> 2);
	position->x = CONVERT_2MOVE((attack->startX + attack->endX + collisiontTarget->startX + collisiontTarget->endX) >> 2);
	position->y = CONVERT_2MOVE((attack->startY + attack->endY + collisiontTarget->startY + collisiontTarget->endY) >> 2);
}

void charAttackEffect_Add(Position *position, CharacterActionType type, AttackEffectCollection* attackEffectCollection) {
	AttackEffect *effect = attackEffectCollection->collection[attackEffectCollection->count];
	effect->type = type;
	effect->display.baseImageId = EVramMapIdAttackEffects;
	effect->display.imageUpdateStatus = EUpdate;
	effect->display.basePalleteId = SHARED_PALETTEID;
	effect->display.spriteSet = attackEffectSpiteSets[type];
	effect->display.currentAnimationFrame = 0;
	effect->display.numberOfFramesPassed = 0;
	effect->position = *position;
	++attackEffectCollection->count;
}

int charAttackEffect_setPosition(
	AttackEffect *effect,
	OBJ_ATTR *oamBuf, 
	const Position *scr_pos,
	const ScreenDimension *scr_dim) {
	
	effect->display.baseY = CONVERT_TO_SCRYPOS(effect->position.y, 
		scr_pos->y, charAttackEffect_scrConversionMeasurements);
	effect->display.baseX = CONVERT_TO_SCRXPOS(effect->position.x, 
		scr_pos->x, charAttackEffect_scrConversionMeasurements);
	effect->display.baseY -= CONVERT_TO_SCRZPOS(effect->position.z);
		
	commonSetToOamBuffer(&effect->display, oamBuf);
	effect->display.isInScreen = true;
	
	return effect->display.spriteSet->set[effect->display.currentAnimationFrame].numberOflayers;
}

int charAttackEffect_setToOAMBuffer(AttackEffectCollection* attackEffectCollection, OAMCollection *oamCollection,
	const int currentOAMIdx,
	const Position *scr_pos,
	const ScreenDimension *scr_dim) {
	OBJ_ATTR *oamBuffer = oamCollection->data;
	int effectIdx, oamIdx;
	
	for (effectIdx = 0, oamIdx = currentOAMIdx; effectIdx < attackEffectCollection->count; ++effectIdx) {
		if (attackEffectCollection->collection[effectIdx]->type != EActionNone) {
			oamIdx += charAttackEffect_setPosition( attackEffectCollection->collection[effectIdx], 
				&oamBuffer[oamIdx], scr_pos, scr_dim);
		}
	}
	
	return oamIdx;
}

inline void charAttackEffect_Remove(int idx, AttackEffect *effect, AttackEffectCollection* attackEffectCollection) {
	--attackEffectCollection->count;
	effect->type = EActionNone;
	AttackEffect *lastActiveEffect = attackEffectCollection->collection[attackEffectCollection->count];
	attackEffectCollection->collection[attackEffectCollection->count] = effect;
	attackEffectCollection->collection[idx] = lastActiveEffect;
}

void charAttackEffect_UpdateAnimation(AttackEffectCollection* attackEffectCollection) {
	int i;
	for (i = 0; i < attackEffectCollection->count; ++i) {
		AttackEffect *effect = attackEffectCollection->collection[i];
		if (effect->type != EActionNone) {
			if (!commonAnimation_IsLastFrame(&effect->display)) {
				commonUpdateAnimation(&effect->display);
			} else {
				charAttackEffect_Remove(i, effect, attackEffectCollection);
			}
		}
	}
}