#ifndef CHARACTER_SKULLDEMON
#define CHARACTER_SKULLDEMON
#include "GBAObject.h"
typedef enum SkullDemonAction {
	ESkullDemonInitialize = -1,
	ESkullDemonWalk,
	//ESkullDemonChaseTarget,
	//ESkullDemonAttack,
	//ESkullDemonStunned,
	ESkullDemonActionCount
} SkullDemonAction;
typedef enum SkullDemonAIState {
	ESkullDemonAIStateWalkAround,
	//ESkullDemonAIStateHuntTarget,
	ESkullDemonAIStateStunned
} SkullDemonAIState;
#endif