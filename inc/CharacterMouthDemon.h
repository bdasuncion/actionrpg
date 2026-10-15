#ifndef CHARACTER_GHOUL
#define CHARACTER_MOUTHDEMON
#include "GBAObject.h"
typedef enum MouthDemonAction {
	EMouthDemonInitialize = -1,
	EMouthDemonFloat,
	EMouthDemonFloatUp,
	EMouthDemonFloatDown,
	EMouthDemonActionCount
} MouthDemonAction;

typedef enum MouthDemonAIState {
	EMouthDemonAIStateFloat
} MouthDemonAIState;

extern const OffsetPoints ghoul_scanSurroundingOffset[8][2];
#endif