#include <stdbool.h>
#include <stdlib.h>
#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacterActionEvent.h"
#include "ManagerPrinter.h"
#include "CharacterCommon.h"
#include "GBATimer.h"

const CharacterActionEvent defaultCharacterActionEvent = {EActionNone, NULL, 0, 0, 0, {0, 0, 0, 0, 0, 0, 0}};

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

void mchar_actione_onetarget(CharacterActionEvent *actionEvent, CharacterCollection *charCollection) {
	if (actionEvent->maxHit > 0) {
		int i, count;
		BoundingBox charBoundingBox;
		bool isHit = false;
		for (i = 0; i < charCollection->currentSize; ++i) {
			CharacterAttr *character = charCollection->characters[i];
			character->getBounds(character, &count, &charBoundingBox);
		}
	}
}
