#include <stdbool.h>
#include <stdlib.h>
#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacterActionEvent.h"
#include "ManagerPrinter.h"
#include "CharacterCommon.h"
#include "GBATimer.h"

const CharacterActionEvent defaultCharacterActionEvent = {NULL, NULL, EActionNone, 0, 0, 0, {0, 0, 0, 0, 0, 0, 0}};

void mchar_actione_init(CharacterActionCollection *charActionCollection, int maxActions) {
    int i;
    charActionCollection->max = maxActions;
    charActionCollection->count = 0;
	charActionCollection->currentActions = malloc(sizeof(CharacterActionEvent)*maxActions);
	
	for (i = 0; i < maxActions; ++i) {
	    charActionCollection->currentActions[i] = defaultCharacterActionEvent;
	}
}

void mchar_actione_reinit(CharacterActionCollection *charActionCollection) {
    int i;
    for (i = 0; i < charActionCollection->count; ++i) {
	    charActionCollection->currentActions[i] = defaultCharacterActionEvent;
	}
	
	charActionCollection->count = 0;
}

CharacterAttr* getCloserCharacter(const Position *reference, 
		const CharacterAttr* char1, const CharacterAttr* char2) {
	int dist1, dist2;
	int xDist, yDist, zDist;
	xDist = reference->x - char1->position.x;
	xDist *= xDist;
	yDist = reference->y - char1->position.y;
	yDist *= yDist;
	zDist = reference->z - char1->position.z;
	zDist *= zDist;
	dist1 = xDist + yDist + zDist;
	xDist = reference->x - char2->position.x;
	xDist *= xDist;
	yDist = reference->y - char2->position.y;
	yDist *= yDist;
	zDist = reference->z - char2->position.z;
	zDist *= zDist;
	dist2 = xDist + yDist + zDist;
	if (dist1 < dist2) {
		return char1;
	} 
	return char2;
} 

void mchar_actione_resolveonetarget(CharacterActionEvent *actionEvent, CharacterCollection *charCollection,
		AttackEffectCollection *attackEffects) {
	if (actionEvent->maxHit > 0) {
		int i, count;
		BoundingBox charBoundingBox;
		CharacterAttr *characterTarget = NULL;
		bool isHit = false;
		for (i = 0; i < charCollection->currentSize; ++i) {
			CharacterAttr *character = charCollection->characters[i];
			if (actionEvent->source == character) {
				continue;
			}
			character->getBounds(character, &count, &charBoundingBox);
			isHit = hasCollision(&actionEvent->collisionBox, &charBoundingBox);
			if (isHit) {
				if (!characterTarget) {
					characterTarget = character;
				}
				characterTarget = getCloserCharacter(&actionEvent->source->position, characterTarget, character);
			}
		}
		if (characterTarget) {
			Position pos;
			actionEvent->maxHit = 0;
			if (characterTarget->isHit(characterTarget, actionEvent)) {
				charAttackEffect_getPosition(&actionEvent->collisionBox, &charBoundingBox, &pos);
				charAttackEffect_Add(&pos, actionEvent->type, attackEffects);
			}
		}
	}
	
}

bool mchar_actione_update(CharacterAttr *source, CharacterActionCollection *charActionCollection, 
    CharacterActionType type, s16 value, s16 maxHit, BoundingBox *collisionBox) {
	int i;
	for (i = 0; i < charActionCollection->count; ++i) {
		CharacterActionEvent *charAction = &charActionCollection->currentActions[i];
		if (charAction->source == source) {
			charAction->type = type;
			charAction->value = value;
			charAction->collisionBox = *collisionBox;
			return true;
		}
	}
	return false;
}

void mchar_actione_add(CharacterAttr *source, CharacterActionCollection *charActionCollection, 
    CharacterActionType type, s16 value, s16 maxHit, BoundingBox *collisionBox) {
	
	if (mchar_actione_update(source, charActionCollection, type, value, maxHit, collisionBox)) {
		return;
	}

	CharacterActionEvent *charAction = &charActionCollection->currentActions[charActionCollection->count];
	charAction->type = type;
	charAction->value = value;
	charAction->maxHit = maxHit;
	charAction->collisionBox = *collisionBox;
	charAction->source = source;
	if (maxHit == 1) {
		charAction->resolve = &mchar_actione_resolveonetarget;
	}
	
	++charActionCollection->count;
}

void mchar_actione_remove(CharacterAttr *source, CharacterActionCollection *charActionCollection) {
	int i;
	for (i = 0; i < charActionCollection->count; ++i) {
		CharacterActionEvent *charAction = &charActionCollection->currentActions[i];
		if (charAction->source == source) {
			--charActionCollection->count;
			*charAction = charActionCollection->currentActions[charActionCollection->count];
			charActionCollection->currentActions[charActionCollection->count] = defaultCharacterActionEvent;
			
			break;
		}
	}
}