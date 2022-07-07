#ifndef CHARACTER_GHOSTMAN
#define CHARACTER_GHOSTMAN

#include "GBAObject.h"
#include "GBACharacter.h"
#include "GBAMap.h"

typedef enum GhostmanAction {
	EGhostmanInitialize = -1,
	EGhostmanSit,
	EGhostmanTransitionToFollow,
	EGhostmanFollow,
	EGhostmanActionCount
} GhostmanAction;

void ghostMan_init(CharacterAttr* character, ControlTypePool* controlPool);
void ghostMan_setCharacter(CharacterAttr* character);
void ghostMan_controller(CharacterAttr* character, const MapInfo *mapInfo, CharacterCollection *charCollection);
#endif