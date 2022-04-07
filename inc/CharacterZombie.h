#ifndef CHARACTER_ZOMBIE
#define CHARACTER_ZOMBIE

#include "GBAObject.h"

typedef enum ZombieAction {
	EZombieInitialize = -1,
	EZombieWalk,
	EZombieChaseTarget,
	EZombieAttack,
	EZombieStunned,
	EZombieActionCount
} ZombiefAction;

typedef enum ZombieStatus {
	EZombieStatusWalkAround,
	EZombieStatusHuntTarget,
	EZombieStatusStunned
} ZombieStatus;

#endif