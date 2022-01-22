#ifndef CHARACTER_NAMELESS
#define CHARACTER_NAMELESS

#include "GBAObject.h"

typedef enum NamelessAction
{
	ENamelessInitialize = -1,
	ENamelessStand,
	ENamelessWalk,
	ENamelessActionCount
} NamelessAction;

void nameless_init(CharacterAttr* character);
void nameless_setCharacter(CharacterAttr* character);
void nameless_controller(CharacterAttr* character);
#endif