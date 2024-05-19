#ifndef CHARACTER_PLAYER
#define CHARACTER_PLAYER

#include "GBAObject.h"
#include "GBACharacter.h"

typedef enum AlisaAction
{
	EAlisaInitialize = -1,
	EAlisaStand,
	EAlisaRun,
	EAlisaNormalSwordSlash,
	EAlisaStrongSwordSlash,
	EAlisaPrepareDash,
	EAlisaDashForward,
	EAlisaDashBackward,
	EAlisaJumpUp,
	EAlisaJumpForward,
	EAlisaFallingDown,
	EAlisaFallingDownForward,
	EAlisaStunned,
	EAlisaActionCount
} AlisaAction;

typedef enum AlisaStatus
{
	EAlisaStatusNormal,
	EAlisaStatusStunned,
	EAlisaStatusFalling,
} AlisaStatus;


void alisa_init(CharacterAttr* character, ControlTypePool* controlPool);
void alisa_setCharacter(CharacterAttr* character);
void alisa_controller(CharacterAttr* character);
void alisa_slashController(CharacterAttr* character);
void alisa_dashForwardController(CharacterAttr* character);
void alisa_prepareDashController(CharacterAttr* character);
void alisa_jumpController(CharacterAttr* character);
void alisa_getBoundingBoxStanding(const CharacterAttr* alisa, 
	int *count, BoundingBox *boundingBox);
void alisa_getBoundingBoxMoving(const CharacterAttr* alisa, 
	int *count, BoundingBox *boundingBox);
	
#define ALISA_DASH_STARTMOVE_FRAME 1
#endif