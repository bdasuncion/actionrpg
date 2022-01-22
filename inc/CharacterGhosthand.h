#ifndef CHARACTER_GHOSTHAND
#define CHARACTER_GHOSTHAND

#include "GBAObject.h"

typedef enum GhosthandAction {
	EGhosthandInitialize = -1,
	EGhosthandHidden,
	EGhosthandAppear,
	EGhosthandActionCount
} GhosthandAction;

void ghostlyHand_init(CharacterAttr* character, ControlTypePool* controlPool);
void ghostlyHand_setCharacter(CharacterAttr* character);
void ghostlyHand_controller(CharacterAttr* character, const MapInfo *mapInfo, CharacterCollection *charCollection);
#endif