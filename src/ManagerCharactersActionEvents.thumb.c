#include <stdbool.h>
#include <stdlib.h>
#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacterActionEvent.h"
#include "ManagerPrinter.h"
#include "CharacterCommon.h"
#include "GBATimer.h"

const CharacterActionEvent defaultCharacterActionEvent = {EActionNone, 0, NULL, {0, 0, 0, 0, 0, 0, 0}};

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

/*void mchar_actione_add(CharacterActionCollection *charActionCollection, 
    CharacterActionTypes type, s16 value, BoundingBox *position) {
	CharacterActionEvent *charAction = &charActionCollection->currentActions[charActionCollection->count];
	charAction->type = type;
	charAction->value = value;
	charAction->position = *position;
	
	++charActionCollection->count;
}*/

/*void mchar_actione_add(CharacterActionCollection *charActionCollection, 
    CharacterActionTypes type, s16 value, int countPoints, Position *collisionPoints) {
	int i;
	CharacterActionEvent *charAction = &charActionCollection->currentActions[charActionCollection->count];
	charAction->type = type;
	charAction->value = value;
	//charAction->position = *position;
	charAction->count = countPoints;
	for (i = 0; i < countPoints; ++i) {
		charAction->collisionPoints[i] = collisionPoints[i];
	}
	
	++charActionCollection->count;
}*/

void mchar_actione_add(CharacterActionCollection *charActionCollection, 
    CharacterActionTypes type, s16 value, s16 maxHit, BoundingBox *collisionBox) {
	int i;
	CharacterActionEvent *charAction = &charActionCollection->currentActions[charActionCollection->count];
	charAction->type = type;
	charAction->value = value;
	charAction->maxHit = maxHit;
	charAction->collisionBox = *collisionBox;
	
	++charActionCollection->count;
}
