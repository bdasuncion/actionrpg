#include <stdlib.h>
#include "GBAObject.h"
#include "GBACharacter.h"
#include "GBACharacterType.h"

void alisa_init(CharacterAttr *character, ControlTypePool* controlPool);
void alisa_setCharacter(CharacterAttr *character);
void werewolf_init(CharacterAttr *character, ControlTypePool* controlPool);
void werewolf_setCharacter(CharacterAttr *character);
void ghostlyHand_init(CharacterAttr *character, ControlTypePool* controlPool);
void ghostMan_init(CharacterAttr *character, ControlTypePool* controlPool);
void ghostlyHand_setCharacter(CharacterAttr *character);
void ghostMan_setCharacter(CharacterAttr *character);
void crow_init(CharacterAttr *character, ControlTypePool* controlPool);
void crow_setCharacter(CharacterAttr *character);
void zombie_init(CharacterAttr* character, ControlTypePool* controlPool);
void zombie_setCharacter(CharacterAttr* character);

const FuncCharacterInit chacterInit[] = { &alisa_init, /*NULL, &ghostlyHand_init, &ghostMan_init, NULL,*/ &werewolf_init, /*&crow_init,*/ &zombie_init };
const FuncCharacterSet characterSet[] = { &alisa_setCharacter, /*NULL, &ghostlyHand_setCharacter, &ghostMan_setCharacter, NULL, */
	&werewolf_setCharacter,  /*&crow_setCharacter,*/ &zombie_setCharacter };