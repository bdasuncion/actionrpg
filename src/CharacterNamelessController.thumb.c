#include "GBAObject.h"
#include "GBAKey.h"
#include "CharacterNameless.h"
#include  <stdbool.h>

void nameless_setCharacter(CharacterAttr* character) {
	character->controller = &nameless_controller; 
}

void nameless_controller(CharacterAttr* character) {	
	EDirections direction = KEYPRESS_DIRECTION;
		
	if (direction == ELeft) {
		character->nextAction = ENamelessWalk;
		character->nextDirection = direction;
		return;
	}
	
	character->nextAction = ENamelessStand;
}
