#ifndef CHARACTER_PLAYER
#define CHARACTER_PLAYER

#include "GBAObject.h"

typedef enum AlisaAction
{
	EAlisaInitialize = -1,
	EAlisaStand,
	EAlisaRun,
	EAlisaNormalSwordSlash,
	EAlisaStrongSwordSlash,
	EAlisaDashForward,
	EAlisaStunned,
	EAlisaActionCount
} AlisaAction;

typedef enum AlisaStatus
{
	EAlisaStatusNormal,
	EAlisaStatusStunned,
} AlisaStatus;


void alisa_init(CharacterAttr* character, ControlTypePool* controlPool);
void alisa_setCharacter(CharacterAttr* character);
void alisa_controller(CharacterAttr* character);
void alisa_slashController(CharacterAttr* character);
void alisa_dashForwardController(CharacterAttr* character);
void alisa_getBoundingBoxStanding(const CharacterAttr* alisa, 
	int *count, BoundingBox *boundingBox);
void alisa_getBoundingBoxMoving(const CharacterAttr* alisa, 
	int *count, BoundingBox *boundingBox);
#endif