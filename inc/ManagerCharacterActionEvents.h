#ifndef MANAGER_CHARACTERACTION_EVENTS
#define MANAGER_CHARACTERACTION_EVENTS

#include "GBACharacterActionEvent.h"

void mchar_actione_init(CharacterActionCollection *charActionCollection, int maxActions);
void mchar_actione_reinit(CharacterActionCollection *charActionCollection);
//void mchar_actione_add(CharacterActionCollection *charActionCollection, 
//    CharacterActionTypes type, s16 value, BoundingBox *position);
void mchar_actione_add(CharacterAttr *source, CharacterActionCollection *charActionCollection, 
    CharacterActionType type, s16 value, s16 maxHit, BoundingBox *collisionBox);
void mchar_actione_update(CharacterAttr *source, CharacterActionCollection *charActionCollection, 
    CharacterActionType type, s16 value, s16 maxHit, BoundingBox *collisionBox);
void mchar_actione_remove(CharacterAttr *source, CharacterActionCollection *charActionCollection);
#endif