
#ifndef CHARACTER_WEREWOLF
#define CHARACTER_WEREWOLF

#include "GBAObject.h"

typedef enum WerewolfAction
{
	EWerewolfInitialize = -1,
	EWerewolfStand,
	EWerewolfWalk,
	EWerewolfActionCount
} WerewolfAction;

void werewolf_init(CharacterAttr* character, ControlTypePool* controlPool);
void werewolf_setCharacter(CharacterAttr* character);

#endif