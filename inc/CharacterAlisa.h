#ifndef CHARACTER_PLAYER
#define CHARACTER_PLAYER

#include "GBAObject.h"
#include "GBACharacter.h"
#include "GBAMap.h"

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


void alisa_init(CharacterAttr* character, ControlTypePool* controlPool, CharacterWaypoints *charWaypoints);
void alisa_setCharacter(CharacterAttr* character);
void alisa_controller(CharacterAttr* charAtt, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection);
void alisa_slashController(CharacterAttr* charAtt, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection);
void alisa_dashForwardController(CharacterAttr* charAtt, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection);
void alisa_prepareDashController(CharacterAttr* charAtt, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection);
void alisa_jumpController(CharacterAttr* charAtt, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection);
void alisa_getBoundingBoxStanding(const CharacterAttr* alisa, 
	int *count, BoundingBox *boundingBox);
void alisa_getBoundingBoxMoving(const CharacterAttr* alisa, 
	int *count, BoundingBox *boundingBox);
	
#define ALISA_DASH_STARTMOVE_FRAME 1
#endif