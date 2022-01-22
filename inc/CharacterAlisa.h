#ifndef CHARACTER_PLAYER
#define CHARACTER_PLAYER

#include "GBAObject.h"

typedef enum AlisaAction
{
	EAlisaInitialize = -1,
	EAlisaStand,
	EAlisaRun,
	EAlisaNormalSwordSlash,
	EAlisaActionCount
} AlisaAction;

void alisa_init(CharacterAttr* character);
void alisa_setCharacter(CharacterAttr* character);
void alisa_controller(CharacterAttr* character);
void alisa_slashController(CharacterAttr* character);
#endif