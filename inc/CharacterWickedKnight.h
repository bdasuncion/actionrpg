#ifndef CHARACTER_SKULLDEMON
#define CHARACTER_SKULLDEMON
#include "GBAObject.h"
typedef enum WickedKnightAction {
	EWickedKnightInitialize = -1,
	EWickedKnightWalk,
	EWickedKnightChaseTarget,
	EWickedKnightAttack,
	EWickedKnightStunned,
	EWickedKnightActionCount
} WickedKnightAction;
typedef enum WickedKnightAIState {
	EWickedKnightAIStateWalkAround,
	EWickedKnightAIStateHuntTarget,
	EWickedKnightAIStateStunned
} WickedKnightAIState;

extern const OffsetPoints wickedknight_scanSurroundingOffset[8][2];
#endif