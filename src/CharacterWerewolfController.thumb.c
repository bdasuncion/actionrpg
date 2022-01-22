#include "GBAObject.h"
#include "CharacterWerewolf.h"
#include  <stdbool.h>

void werewolf_scanSurroundings(CharacterAttr* character);

void werewolf_setCharacter(CharacterAttr* character) {
    character->controller = &werewolf_scanSurroundings; 
}

void werewolf_scanSurroundings(CharacterAttr* character) {
    character->nextAction = EWerewolfWalk;
	character->nextDirection = EDown;
}