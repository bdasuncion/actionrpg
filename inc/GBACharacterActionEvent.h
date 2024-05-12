#ifndef GBACharacterActionEvent
#define GBACharacterActionEvent
#include "GBAObject.h"
#include "GBACharacter.h"

typedef void (*ActionEventResolve)(void *actionEvent, CharacterCollection *charCollection,
		AttackEffectCollection *attackEffects);

typedef struct CharacterActionEvent {
	ActionEventResolve resolve;
	CharacterAttr *source;
	CharacterActionType type;
	//BoundingBox position;
	s16 value:8;
	s16 dummy1:4;
	s16 maxHit:4;
	BoundingBox collisionBox;
} ALIGN4 CharacterActionEvent;

typedef struct CharacterActionCollection {
    u8 count;
	u8 max;
	u16 dummy1;
	CharacterActionEvent *currentActions;
} ALIGN4 CharacterActionCollection ;
#endif