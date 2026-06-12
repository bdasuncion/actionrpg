#ifndef CHARACTER_GHOUL
#define CHARACTER_GHOUL
#include "GBAObject.h"
typedef enum GhoulAction {
	EGhoulInitialize = -1,
	EGhoulWalk,
	EGhoulChaseTarget,
	EGhoulAttack,
	EGhoulStunned,
	EGhoulHurt,
	EGhoulActionCount
} GhoulAction;

typedef enum GhoulAIState {
	EGhoulAIStateWalkAround,
	EGhoulAIStateHuntTarget,
	EGhoulAIStateStunned
} GhoulAIState;

extern const OffsetPoints ghoul_scanSurroundingOffset[8][2];
#endif