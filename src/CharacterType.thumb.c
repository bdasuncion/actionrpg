#include <stdlib.h>
#include "GBAObject.h"
#include "GBACharacter.h"
#include "GBACharacterType.h"

void alisa_init(CharacterAttr *character, ControlTypePool* controlPool);
void alisa_setCharacter(CharacterAttr *character);
void werewolf_init(CharacterAttr *character, ControlTypePool* controlPool);
void werewolf_setCharacter(CharacterAttr *character);
void zombie_init(CharacterAttr* character, ControlTypePool* controlPool);
void zombie_setCharacter(CharacterAttr* character);

const FuncCharacterInit character_InitFunctionsCollection[] = { &alisa_init, &werewolf_init, &zombie_init };
const FuncCharacterSet characterSet[] = { &alisa_setCharacter, &werewolf_setCharacter, &zombie_setCharacter };