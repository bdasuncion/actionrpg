#ifndef GBACharacterActionEvent
#define GBACharacterActionEvent
#include "GBAObject.h"
#include "GBACharacter.h"

typedef enum CharacterActionTypes {
    EActionNone,
	EActionAttack,
	EActionCount
}CharacterActionTypes;

typedef struct CharacterActionEvent {
    CharacterActionTypes type;
	CharacterAttr *source;
	//BoundingBox position;
	s16 value:8;
	s16 dummy1:5;
	u16 count:3;
	Position collisionPoints[5];
} ALIGN4 CharacterActionEvent;

typedef struct CharacterActionCollection {
    u8 count;
	u8 max;
	u16 dummy1;
	CharacterActionEvent *currentActions;
} ALIGN4 CharacterActionCollection ;
#endif