#include <stdlib.h>
#include <stdbool.h>
#include "GBATypes.h"
#include "GBAObject.h"
#include "GBAVideo.h"
#include "GBADMA.h"
#include "CharacterWickedKnight.h"
#include "GBACharacterActionEvent.h"
#include "UtilCommonValues.h"
#include "ManagerVram.h"
#include "ManagerSound.h"
#include "ManagerCharacterActionEvents.h"
#include "CharacterAlisa.h"
#include "CharacterCommon.h"
#include "MapCommon.h"
#include "GBAMap.h"
#include "ManagerCharacters.h"
#include "ManagerPrinter.h"

#include "DebugLogMgba.h"

#define MAX_DIST_FOR_CHASE 120

const EDirections wickedknight_walkDirections[] = {
    EDown, EDownright, ERight, EUpright,
	EUp, EUpleft, ELeft, EDownleft
};

//#define INSCREEN_DIST 80
//#define INSCREEN_ARRAYWIDTH 20

#define INSCREEN_DIST 120
#define INSCREEN_ARRAYWIDTH 30

const EDirections FAR_TARGET_WICKEDKNIGHT_8x8[INSCREEN_ARRAYWIDTH][INSCREEN_ARRAYWIDTH] = {
{ EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUp,       EUp,       EUp,       EUp,       EUp,       EUp,       EUp,       EUp,       EUp,       EUp,       EUp,        EUp,        EUp,        EUp,        EUpright,   EUpright,   EUpright,   EUpright,   EUpright,   EUpright,   EUpright,   EUpright },
{ EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUp,       EUp,       EUp,       EUp,       EUp,       EUp,       EUp,       EUp,       EUp,       EUp,       EUp,        EUp,        EUp,        EUp,        EUpright,   EUpright,   EUpright,   EUpright,   EUpright,   EUpright,   EUpright,   EUpright },
{ EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUp,       EUp,       EUp,       EUp,       EUp,       EUp,       EUp,       EUp,       EUp,       EUp,        EUp,        EUp,        EUpright,   EUpright,   EUpright,   EUpright,   EUpright,   EUpright,   EUpright,   EUpright,   EUpright },
{ EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUp,       EUp,       EUp,       EUp,       EUp,       EUp,       EUp,       EUp,       EUp,       EUp,        EUp,        EUp,        EUpright,   EUpright,   EUpright,   EUpright,   EUpright,   EUpright,   EUpright,   EUpright,   EUpright },
{ EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUp,       EUp,       EUp,       EUp,       EUp,       EUp,       EUp,       EUp,       EUp,        EUp,        EUpright,   EUpright,   EUpright,   EUpright,   EUpright,   EUpright,   EUpright,   EUpright,   EUpright,   EUpright },

{ EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUp,       EUp,       EUp,       EUp,       EUp,       EUp,       EUp,       EUp,        EUpright,   EUpright,   EUpright,   EUpright,   EUpright,   EUpright,   EUpright,   EUpright,   EUpright,   EUpright,   EUpright },
{ EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUp,       EUp,       EUp,       EUp,       EUp,       EUp,       EUp,       EUp,        EUpright,   EUpright,   EUpright,   EUpright,   EUpright,   EUpright,   EUpright,   EUpright,   EUpright,   EUpright,   EUpright },
{ EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUp,       EUp,       EUp,       EUp,       EUp,       EUp,       EUpright,   EUpright,   EUpright,   EUpright,   EUpright,   EUpright,   EUpright,   EUpright,   EUpright,   EUpright,   EUpright,   EUpright },
{ EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUp,       EUp,       EUp,       EUp,       EUp,       EUp,       EUpright,   EUpright,   EUpright,   EUpright,   EUpright,   EUpright,   EUpright,   EUpright,   EUpright,   EUpright,   EUpright,   EUpright },
{ ELeft,     EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,   EUnknown,   EUnknown,   EUpright,   EUpright,   EUpright,   EUpright,   EUpright,   EUpright,   EUpright,   EUpright,   ERight   },
{ ELeft,     ELeft,     ELeft,     EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,   EUnknown,   EUnknown,   EUpright,   EUpright,   EUpright,   EUpright,   EUpright,   EUpright,   ERight,     ERight,     ERight   },
{ ELeft,     ELeft,     ELeft,     ELeft,     ELeft,     ELeft,     ELeft,     EUpleft,   EUpleft,   EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,   EUnknown,   EUnknown,   EUpright,   EUpright,   ERight,     ERight,     ERight,     ERight,     ERight,     ERight,     ERight   },
{ ELeft,     ELeft,     ELeft,     ELeft,     ELeft,     ELeft,     ELeft,     ELeft,     ELeft,     EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,   EUnknown,   EUnknown,   ERight,     ERight,     ERight,     ERight,     ERight,     ERight,     ERight,     ERight,     ERight   },
{ ELeft,     ELeft,     ELeft,     ELeft,     ELeft,     ELeft,     ELeft,     ELeft,     ELeft,     EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,   EUnknown,   EUnknown,   ERight,     ERight,     ERight,     ERight,     ERight,     ERight,     ERight,     ERight,     ERight   },
{ ELeft,     ELeft,     ELeft,     ELeft,     ELeft,     ELeft,     ELeft,     ELeft,     ELeft,     EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,   EUnknown,   EUnknown,   ERight,     ERight,     ERight,     ERight,     ERight,     ERight,     ERight,     ERight,     ERight   },
{ ELeft,     ELeft,     ELeft,     ELeft,     ELeft,     ELeft,     ELeft,     ELeft,     ELeft,     EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,   EUnknown,   EUnknown,   ERight,     ERight,     ERight,     ERight,     ERight,     ERight,     ERight,     ERight,     ERight   },
{ ELeft,     ELeft,     ELeft,     ELeft,     ELeft,     ELeft,     ELeft,     ELeft,     ELeft,     EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,   EUnknown,   EUnknown,   ERight,     ERight,     ERight,     ERight,     ERight,     ERight,     ERight,     ERight,     ERight   },
{ ELeft,     ELeft,     ELeft,     ELeft,     ELeft,     ELeft,     ELeft,     ELeft,     ELeft,     EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,   EUnknown,   EUnknown,   ERight,     ERight,     ERight,     ERight,     ERight,     ERight,     ERight,     ERight,     ERight   },
{ ELeft,     ELeft,     ELeft,     ELeft,     ELeft,     ELeft,     ELeft,     EDownleft, EDownleft, EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,   EUnknown,   EUnknown,   EDownright, EDownright, ERight,     ERight,     ERight,     ERight,     ERight,     ERight,     ERight   },
{ ELeft,     ELeft,     ELeft,     EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,   EUnknown,   EUnknown,   EDownright, EDownright, EDownright, EDownright, EDownright, EDownright, ERight,     ERight,     ERight   },
{ ELeft,     EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,  EUnknown,   EUnknown,   EUnknown,   EDownright, EDownright, EDownright, EDownright, EDownright, EDownright, EDownright, EDownright, ERight   },
{ EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDown,     EDown,     EDown,     EDown,     EDown,     EDown,     EDownright, EDownright, EDownright, EDownright, EDownright, EDownright, EDownright, EDownright, EDownright, EDownright, EDownright, EDownright },
{ EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDown,     EDown,     EDown,     EDown,     EDown,     EDown,     EDownright, EDownright, EDownright, EDownright, EDownright, EDownright, EDownright, EDownright, EDownright, EDownright, EDownright, EDownright },
{ EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDown,     EDown,     EDown,     EDown,     EDown,     EDown,     EDown,     EDown,      EDownright, EDownright, EDownright, EDownright, EDownright, EDownright, EDownright, EDownright, EDownright, EDownright, EDownright },
{ EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDown,     EDown,     EDown,     EDown,     EDown,     EDown,     EDown,     EDown,      EDownright, EDownright, EDownright, EDownright, EDownright, EDownright, EDownright, EDownright, EDownright, EDownright, EDownright },

{ EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDown,     EDown,     EDown,     EDown,     EDown,     EDown,     EDown,     EDown,     EDown,      EDown,      EDownright, EDownright, EDownright, EDownright, EDownright, EDownright, EDownright, EDownright, EDownright, EDownright },
{ EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDown,     EDown,     EDown,     EDown,     EDown,     EDown,     EDown,     EDown,     EDown,     EDown,      EDown,      EDown,      EDownright, EDownright, EDownright, EDownright, EDownright, EDownright, EDownright, EDownright, EDownright },
{ EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDown,     EDown,     EDown,     EDown,     EDown,     EDown,     EDown,     EDown,     EDown,     EDown,      EDown,      EDown,      EDownright, EDownright, EDownright, EDownright, EDownright, EDownright, EDownright, EDownright, EDownright },
{ EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDown,     EDown,     EDown,     EDown,     EDown,     EDown,     EDown,     EDown,     EDown,     EDown,     EDown,      EDown,      EDown,      EDown,      EDownright, EDownright, EDownright, EDownright, EDownright, EDownright, EDownright, EDownright },
{ EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDown,     EDown,     EDown,     EDown,     EDown,     EDown,     EDown,     EDown,     EDown,     EDown,     EDown,      EDown,      EDown,      EDown,      EDownright, EDownright, EDownright, EDownright, EDownright, EDownright, EDownright, EDownright },

};

// L  L  L  L  L  L  L  L  L  L  UL U
// DL DL L  L  L  L  L  L  L  L  UL U
// D  D  DL DL DL DL DL DL DL UL U  U 
// D  D  DR O  O  =  =  O  O  UL U  U
// D  D  DR O  O  =  =  O  O  UL U  U
// D  D  DR =  =  =  =  =  =  UL U  U
// D  D  DR =  =  =  =  =  =  UL U  U
// D  D  DR O  O  =  =  O  O  UL U  U
// D  D  DR O  O  =  =  O  O  UL U  U
// D  D  DR UR UR UR UR UR UR UR U  U
// D  DR R  R  R  R  R  R  R  R  UR UR
// D  DR R  R  R  R  R  R  R  R  R  R

#define MOVACT_INRANGE_ARRAYWIDTH 12
#define MOVACT_INRANGE_DIST 48
const EDirections CIRCLE_TARGET_CLOCKWISE_8x8[MOVACT_INRANGE_ARRAYWIDTH][MOVACT_INRANGE_ARRAYWIDTH] = {
	{ELeft,     ELeft,      ELeft,      ELeft,      ELeft,      ELeft,      ELeft,     ELeft,     ELeft,     ELeft,     ELeft,    EUp},
	{EDownleft, EDownleft,  EDownleft,  EDownleft,  EDownleft,  EDownleft,  EDownleft, EDownleft, EDownleft, EDownleft, EUpleft,  EUp},
	{EDown,     EDownright, EDownleft,  EDownleft,  EDownleft,  EDownleft,  EDownleft, EDownleft, EDownleft, EUpleft,   EUpleft,  EUp},
	{EDown,     EDownright, EDownright, EDownright, EDownleft,  EDownleft,  EDownleft, EDownleft, EUpleft,   EUpleft,   EUpleft,  EUp},
	{EDown,     EDownright, EDownright, EDownright, EDownright, EDownleft,  EDownleft, EUpleft,   EUpleft,   EUpleft,   EUpleft,  EUp},
	{EDown,     EDownright, EDownright, EDownright, EDownright, EDownright, EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,  EUp},
	{EDown,     EDownright, EDownright, EDownright, EDownright, EDownright, EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,  EUp},
	{EDown,     EDownright, EDownright, EDownright, EDownright, EUpright,   EUpright,  EUpleft,   EUpleft,   EUpleft,   EUpleft,  EUp},
	{EDown,     EDownright, EDownright, EDownright, EUpright,   EUpright,   EUpright,  EUpright,  EUpleft,   EUpleft,   EUpleft,  EUp},
	{EDown,     EDownright, EUpright,   EUpright,   EUpright,   EUpright,   EUpright,  EUpright,  EUpright,  EUpright,  EUpleft,  EUp},
	{EDown,     EDownright, EUpright,   EUpright,   EUpright,   EUpright,   EUpright,  EUpright,  EUpright,  EUpright,  EUpright, EUpright},
	{EDown,     EDownright, ERight,     ERight,     ERight,     ERight,     ERight,    ERight,    ERight,    ERight,    ERight,   ERight},
};

const WickedKnightAction CIRCLE_ACTION_CLOCKWISE_8x8[MOVACT_INRANGE_ARRAYWIDTH][MOVACT_INRANGE_ARRAYWIDTH] = {
{EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget},
{EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget},
{EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightAttack, EWickedKnightAttack, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget},
{EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightAttack, EWickedKnightAttack, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget},
{EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightAttack, EWickedKnightAttack, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget},
{EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightAttack, EWickedKnightAttack, EWickedKnightAttack, EWickedKnightAttack, EWickedKnightAttack, EWickedKnightAttack, EWickedKnightAttack, EWickedKnightAttack, EWickedKnightChaseTarget, EWickedKnightChaseTarget},
{EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightAttack, EWickedKnightAttack, EWickedKnightAttack, EWickedKnightAttack, EWickedKnightAttack, EWickedKnightAttack, EWickedKnightAttack, EWickedKnightAttack, EWickedKnightChaseTarget, EWickedKnightChaseTarget},
{EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightAttack, EWickedKnightAttack, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget},
{EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightAttack, EWickedKnightAttack, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget},
{EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightAttack, EWickedKnightAttack, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget},
{EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget},
{EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget},
};

const EDirections ATTACKRANGE_TARGET_8x8[MOVACT_INRANGE_ARRAYWIDTH][MOVACT_INRANGE_ARRAYWIDTH] = {
 {EUpleft,   EUpleft,   EUpleft,   EUp,       EUp,       EUp,       EUp,       EUp,       EUp,       EUpright,   EUpright,   EUpright},
 {EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUp,       EUp,       EUp,       EUp,       EUpright,  EUpright,   EUpright,   EUpright},
 {EUpleft,   EUpleft,   EUpleft,   EUpleft,   ELeft,     EUp,       EUp,       ERight,    EUpright,  EUpright,   EUpright,   EUpright},
 {ELeft,     EUpleft,   EUpleft,   EUpleft,   EDownleft, EUp,       EUp,       EDownright,EUpright,  EUpright,   EUpright,   ERight},
 {ELeft,     ELeft,     EUp,       EUpright,  ERight,    EUp,       EUp,       ELeft,     EUpleft,   EUp,        ERight,     ERight},
 {ELeft,     ELeft,     ELeft,     ELeft,     ELeft,     ERight,    EDown,     ERight,    ERight,    ERight,     ERight,     ERight},
 {ELeft,     ELeft,     ELeft,     ELeft,     ELeft,     EUp,       ELeft,     ERight,    ERight,    ERight,     ERight,     ERight},
 {ELeft,     ELeft,     EDown,     EDownright,ERight,    EDown,     EDown,     ELeft,     EDownleft, EDown,      ERight,     ERight},
 {ELeft,     EDownleft, EDownleft, EDownleft, EUpleft,   EDown,     EDown,     EUpright,  EDownright,EDownright, EDownright, ERight},
 {EDownleft, EDownleft, EDownleft, EDownleft, ELeft,     EDown,     EDown,     ERight,    EDownright,EDownright, EDownright, EDownright},
 {EDownleft, EDownleft, EDownleft, EDownleft, EDown,     EDown,     EDown,     EDown,     EDownright,EDownright, EDownright, EDownright},
 {EDownleft, EDownleft, EDownleft, EDown,     EDown,     EDown,     EDown,     EDown,     EDown,     EDownright, EDownright, EDownright}
};

const WickedKnightAction ACTION_MOVEONLY_8x8[MOVACT_INRANGE_ARRAYWIDTH][MOVACT_INRANGE_ARRAYWIDTH] = {
{EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget},
{EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget},
{EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget},
{EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightAttack, EWickedKnightAttack, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget},
{EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightAttack, EWickedKnightAttack, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget},
{EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightAttack, EWickedKnightAttack, EWickedKnightAttack, EWickedKnightAttack, EWickedKnightAttack, EWickedKnightAttack, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget},
{EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightAttack, EWickedKnightAttack, EWickedKnightAttack, EWickedKnightAttack, EWickedKnightAttack, EWickedKnightAttack, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget},
{EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightAttack, EWickedKnightAttack, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget},
{EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightAttack, EWickedKnightAttack, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget},
{EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget},
{EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget},
{EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget},
};

const EDirections BACKOFF_TARGET_8x8[MOVACT_INRANGE_ARRAYWIDTH][MOVACT_INRANGE_ARRAYWIDTH] = {
 {EDownright, EDownright, EDownright, EDown,     EDown,     EDown,     EDown,     EDown,     EDown,     EDownleft,  EDownleft,  EDownleft},
 {EDownright, EDownright, EDownright, EDownright,EDown,     EDown,     EDown,     EDown,     EDownleft, EDownleft,  EDownleft,  EDownleft},
 {EDownright, EDownright, EDownright, EDownright,EDownright,EDown,     EDown,     EDownleft, EDownleft, EDownleft,  EDownleft,  EDownleft},
 {ERight,     EDownright, EDownright, EDownright,EDownright,EDown,     EDown,     EDownleft, EDownleft, EDownleft,  EDownleft,  ELeft},
 {ERight,     ERight,     EDownright, EDownright,EDownright,EDown,     EDown,     EDownleft, EDownleft, EDownleft,  ELeft,      ELeft},
 {ERight,     ERight,     ERight,     ERight,    ERight,    ERight,    EDown,     ELeft,     ELeft,     ELeft,      ELeft,      ELeft},
 {ERight,     ERight,     ERight,     ERight,    ERight,    EUp,       ELeft,     ELeft,     ELeft,     ELeft,      ELeft,      ELeft},
 {ERight,     ERight,     EUpright,   EUpright,  EUpright,  EUp,       EUp,       EUpleft,   EUpleft,   EUpleft,    ELeft,      ELeft},
 {ERight,     EUpright,   EUpright,   EUpright,  EUpright,  EUp,       EUp,       EUpleft,   EUpleft,   EUpleft,    EUpleft,    ELeft},
 {EUpright,  EUpright,   EUpright,   EUpright,  EUpright,  EUp,       EUp,       EUpleft,   EUpleft,   EUpleft,    EUpleft,    EUpleft},
 {EUpright,  EUpright,   EUpright,   EUpright,  EUp,       EUp,       EUp,       EUp,       EUpleft,   EUpleft,    EUpleft,    EUpleft},
 {EUpright,  EUpright,   EUpright,   EUp,       EUp,       EUp,       EUp,       EUp,       EUp,       EUpleft,    EUpleft,    EUpleft}
};


void wickedknight_walkAroundController(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection);

void wickedknight_huntController(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection);
	
void wickedknight_backoffController(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection);
	
void wickedknight_stunnedController(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection);
	
void wickedknight_getBoundingBoxMoving(const CharacterAttr* character, 
	int *count, BoundingBox *boundingBox);
	

void wickedknight_setCharacter(CharacterAttr* character) {
    character->controller = &wickedknight_walkAroundController; 
}

#define WICKEDKNIGHT_HEIGHT_SEARCH 24
void wickedknight_doWalk(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection, CharacterAIControl *charControl) {
	Position *position = &character->position;
	BoundingBox searchArea;
	searchArea.startX = CONVERT_2POS(position->x) + wickedknight_scanSurroundingOffset[character->direction][0].x;
	searchArea.startY = CONVERT_2POS(position->y) + wickedknight_scanSurroundingOffset[character->direction][0].y;
	searchArea.endX = CONVERT_2POS(position->x) + wickedknight_scanSurroundingOffset[character->direction][1].x;
	searchArea.endY = CONVERT_2POS(position->y) + wickedknight_scanSurroundingOffset[character->direction][1].y;
	searchArea.startZ = CONVERT_2POS(position->z);
	searchArea.endZ = CONVERT_2POS(position->z) + WICKEDKNIGHT_HEIGHT_SEARCH;
	
	charControl->target = *commonFindCharTypeInBoundingBox(characterCollection, &searchArea, 
		STARTPLAYABLECHARTYPE, ENDPLAYABLECHARACTERTYPE);
		
	if (commonIsFoundPosition(&charControl->target)) {
		charControl->currentStatus = EWickedKnightAIStateHuntTarget;
		character->nextAction = EWickedKnightChaseTarget;
		//return;
	}
}

void wickedknight_walkAroundController(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection) {
	CharacterAIControl *charControl = (CharacterAIControl*)character->free;
	int i;
	//EDirections goDirection;
	//mprinter_printf("WALK AROUND CONTROLLER\n");
	if (charControl->currentStatus == EWickedKnightAIStateHuntTarget) {
		charControl->currentAction = MAXACTIONS;
		character->controller = &wickedknight_huntController;
		character->controller(character, mapInfo, characterCollection);
		return;
	}
	
	if (common_shouldDoIntializeActions(character)) {
		commonInitializeAISetActions(charControl);
		character->getBounds = &wickedknight_getBoundingBoxMoving;
		//mprinter_printf("INITIALIZE ACT\n");
		charControl->currentAction = 0;
		charControl->countAction = 0;
		//charControl->countAction = 0;
		//charControl->actions[charControl->currentAction] = ((ActionControl){25, 0, character->direction, character->direction, EWickedKnightWalk});
	}
	
	int count;
	BoundingBox boundingBox;
	character->getBounds(character, &count, &boundingBox);
	bool hasArrived = commonHasReachedWaypoint(&charControl->wayPoints[charControl->wayPointCurrent], &boundingBox);
	
	if (hasArrived) {
		++charControl->wayPointCurrent;
		if (charControl->wayPointCurrent >= charControl->wayPointCnt) {
			charControl->wayPointCurrent= 0;
		}
	}
		
	EDirections direction = EDown;
	common_findDirectionOfPosition(&character->position, &charControl->wayPoints[charControl->wayPointCurrent], &direction);
	
	character->nextDirection = direction;
	character->faceDirection = direction;
	character->nextAction = EWickedKnightWalk;
	/*if (charControl->leftBlocked | charControl->rightBlocked | 
		charControl->upBlocked | charControl->downBlocked) {
		common_doGoAroundObstacle(&character->position, &charControl->target, charControl, 
			EWickedKnightWalk, 60);
	}*/
	//mprinter_printf("CURRENT ACTION %d WAY POINT %d\n", charControl->currentAction, charControl->wayPointCurrent);
	common_doSetActions(charControl, character);
	
	/*if (charControl->currentAction >= charControl->countAction) {
		//charControl->countAction = 0;
		commonInitializeAISetActions(charControl);
		charControl->currentAction = MAXACTIONS;
		//character->nextDirection = direction;
		//return;
	}*/
		
	wickedknight_doWalk(character, mapInfo, characterCollection, charControl);
}

void wickedknight_doCircleTarget(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection, CharacterAIControl *charControl) {
	bool isNear = false;
	EDirections goDirection = EUnknown;
	s8 doAction = EWickedKnightChaseTarget;

	charControl->target = *commonFindCharTypePositionByDistance(characterCollection,
		&character->position, MAX_DIST_FOR_CHASE, STARTPLAYABLECHARTYPE, ENDPLAYABLECHARACTERTYPE);
	
	if (!commonIsFoundPosition(&charControl->target)) {
		//mprinter_printf("NOT FOUND\n!");
		charControl->currentStatus = EWickedKnightAIStateWalkAround;
		character->nextAction = EWickedKnightWalk;
		return;
	}
	
	common_findDirectionOfTargetCharacterInScreenCustom(&character->position,
		&charControl->target, 
		&FAR_TARGET_WICKEDKNIGHT_8x8[0][0], INSCREEN_DIST, INSCREEN_ARRAYWIDTH,
		&CIRCLE_TARGET_CLOCKWISE_8x8[0][0], (s8*)&CIRCLE_ACTION_CLOCKWISE_8x8[0][0],
			MOVACT_INRANGE_DIST, MOVACT_INRANGE_ARRAYWIDTH,
		&goDirection, &doAction, &isNear);
	
	
	if (!isNear) {
		if (goDirection == EUnknown) {
			charControl->currentAction = MAXACTIONS;
			charControl->currentStatus = EWickedKnightAIStateWalkAround;
			character->nextAction = EWickedKnightWalk;
			return;
		}
		charControl->actions[charControl->currentAction].direction = goDirection;
		if (character->faceDirection != goDirection) {
			character->hasNewFaceDirection = true;
		}
		character->faceDirection = goDirection;
		charControl->actions[charControl->currentAction].action = EWickedKnightChaseTarget;
	} else {
		EDirections faceDirection;
		
		common_faceTarget(&character->position, &charControl->target, 
				&faceDirection);
				
		charControl->actions[charControl->currentAction].direction = goDirection;
		if (character->faceDirection != faceDirection) {
			character->hasNewFaceDirection = true;
		}
		//character->faceDirection = faceDirection;
		charControl->actions[charControl->currentAction].faceDirection = faceDirection;
	}
	
	charControl->actions[charControl->currentAction].action = doAction;
	
	/*if (charControl->leftBlocked | charControl->rightBlocked | 
		charControl->upBlocked | charControl->downBlocked) {
		mprinter_printf("XXX BLOCKED %d %d %d %d\n", charControl->leftBlocked, charControl->rightBlocked,
			charControl->upBlocked, charControl->downBlocked);
		common_doGoAroundObstacle(&character->position, &charControl->target, charControl, 
			EWickedKnightChaseTarget, 20);
		common_doSetActions(charControl, character);
		return;
	} /*else if (charControl->currentAction >= charControl->countAction) {
		//charControl->countAction = 0;
		commonInitializeAISetActions(charControl);
		charControl->currentAction = MAXACTIONS;
		character->nextDirection = goDirection;
		character->faceDirection = goDirection;
		mprinter_printf("???2 %d\n", character->faceDirection);
		return;
	}*/
	
	//mprinter_printf("???1 %d\n", character->faceDirection);
	common_doSetActions(charControl, character);
}

void wickedknight_doAttack(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection, CharacterAIControl *charControl) {
	bool isNear;
	EDirections goDirection, faceDirection;
	s8 doAction = EWickedKnightChaseTarget;
	charControl->target = *commonFindCharTypePositionByDistance(characterCollection,
	&character->position, MAX_DIST_FOR_CHASE, STARTPLAYABLECHARTYPE, ENDPLAYABLECHARACTERTYPE);
	//mprinter_printf("DO ATTACK\n");
	if (!commonIsFoundPosition(&charControl->target)) {
		charControl->currentStatus = EWickedKnightAIStateWalkAround;
		character->nextAction = EWickedKnightWalk;
		return;
	}
	//mprinter_printf("IN SCREEN POS\n");
	common_findDirectionOfTargetCharacterInScreenCustom(&character->position,
		&charControl->target, 
		&FAR_TARGET_WICKEDKNIGHT_8x8[0][0], INSCREEN_DIST, INSCREEN_ARRAYWIDTH,
		&ATTACKRANGE_TARGET_8x8[0][0], (s8*)&CIRCLE_ACTION_CLOCKWISE_8x8[0][0],
			MOVACT_INRANGE_DIST, MOVACT_INRANGE_ARRAYWIDTH,
		&goDirection, &doAction, &isNear);
		
	if (charControl->currentAction < charControl->countAction && 
		doAction != EWickedKnightAttack && goDirection != EUnknown) {
		common_doSetActions(charControl, character);
		
		faceDirection = goDirection;
		common_faceTarget(&character->position, &charControl->target, 
			&faceDirection);

		if (character->faceDirection != faceDirection) {
			character->hasNewFaceDirection = true;
			character->faceDirection = faceDirection;
		}

		return;
	}
		
	if (!isNear) {
		if (goDirection == EUnknown) {
			charControl->currentAction = MAXACTIONS;
			charControl->currentStatus = EWickedKnightAIStateWalkAround;
			character->nextAction = EWickedKnightWalk;
			return;
		}
		character->nextAction = EWickedKnightChaseTarget;
		character->nextDirection = goDirection;
		
		common_faceTarget(&character->position, &charControl->target, 
			&faceDirection);

		if (character->faceDirection != faceDirection) {
			character->hasNewFaceDirection = true;
			character->faceDirection = faceDirection;
		}
		
		
	} else if (isNear) {
		character->nextAction = doAction;
		character->nextDirection = goDirection;
		if (character->faceDirection != goDirection) {
			character->hasNewFaceDirection = true;
			character->faceDirection = goDirection;
		}
		
		//++charControl->actions[0].currentFrame;
		//return;
	}
	if (character->nextAction == EWickedKnightAttack) {
		charControl->currentAction = 0;
		charControl->countAction = 2;
		charControl->actions[charControl->currentAction] = ((ActionControl){DOACTIONUNTILEND, 0, character->nextDirection, character->faceDirection, EWickedKnightAttack});
		charControl->actions[charControl->currentAction + 1] = ((ActionControl){DOACTIONUNTILEND, 0, character->nextDirection, character->faceDirection, EWickedKnightAttack});
		common_doSetActions(charControl, character);
		return;
	}
	
	if (charControl->leftBlocked | charControl->rightBlocked | 
		charControl->upBlocked | charControl->downBlocked) {
		
		common_doGoAroundObstacle(&character->position, &charControl->target, charControl, 
			EWickedKnightChaseTarget, 16);
		common_doSetActions(charControl, character);
		return;
	} /*else if (charControl->currentAction >= charControl->countAction) {
		//charControl->countAction = 0;
		commonInitializeAISetActions(charControl);
		charControl->currentAction = MAXACTIONS;
		character->nextDirection = goDirection;
		return;
	}*/
	
	//character->nextDirection = goDirection;
	//common_doSetActions(charControl, character);
}

void wickedknight_attackController(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection) {
	CharacterAIControl *charControl = (CharacterAIControl*)character->free;
	int distanceX, distanceY, i;
	
	mprinter_printf("ATTACK CONTROLLER\n");
	
	if (charControl->currentStatus == EWickedKnightAIStateWalkAround) {
		charControl->currentAction = MAXACTIONS;
		character->controller = &wickedknight_walkAroundController;
		character->controller(character, mapInfo, characterCollection);
		return;
	}
	
	if (common_shouldDoIntializeActions(character)) {
		mprinter_printf("ATTACK INIT %d %d\n", charControl->currentAction, charControl->countAction);		
		commonInitializeAISetActions(charControl);
		//charControl->actions[0].currentFrame = 0;
		//charControl->actions[0].doForNumFrames = 20;
		charControl->currentAction = 0;
		charControl->countAction = 0;
		character->nextAction = EWickedKnightChaseTarget;
		wickedknight_doAttack(character, mapInfo, characterCollection, charControl);
		return;
	}
	
	if (character->nextAction == EWickedKnightChaseTarget) {
		if (character->action == EWickedKnightAttack) {
			charControl->currentAction = MAXACTIONS;
			character->controller = &wickedknight_backoffController;
			character->controller(character, mapInfo, characterCollection);
			mprinter_printf("BACK OFF\n");
			return;
		}
		/*if (charControl->actions[charControl->currentAction].currentFrame >= MAXCNTFRAMES) {
			charControl->currentAction = MAXACTIONS;
			character->controller = &wickedknight_backoffController;
			character->controller(character, mapInfo, characterCollection);
			mprinter_printf("BACK OFF\n");
			return;
		}*/
		wickedknight_doAttack(character, mapInfo, characterCollection, charControl);
	}
	
	//++charControl->actions[charControl->currentAction].currentFrame;
}

void wickedknight_huntController(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection) {
	CharacterAIControl *charControl = (CharacterAIControl*)character->free;
	int distanceX, distanceY, i;
	
	mprinter_printf("HUNT CONTROLLER\n");
	if (charControl->currentStatus == EWickedKnightAIStateWalkAround) {
		charControl->currentAction = MAXACTIONS;
		character->controller = &wickedknight_walkAroundController;
		character->controller(character, mapInfo, characterCollection);
		return;
	}
	
	/*if (charControl->currentStatus == EWickedKnightAIStateStunned) {
		charControl->currentAction = MAXACTIONS;
		if (character->nextAction == EWickedKnightAttack) {
			charControl->previousActionType = character->nextAction;
			charControl->previousSpriteDisplay = character->spriteDisplay;
		} else {
			charControl->previousActionType = EWickedKnightChaseTarget;
		}
		character->controller = &wickedknight_stunnedController;
		character->controller(character, mapInfo, characterCollection);
		return;
	}*/
	
	if (common_shouldDoIntializeActions(character)) {
		commonInitializeAISetActions(charControl);
		character->nextAction = EWickedKnightChaseTarget;
		charControl->countAction = 1;
		charControl->currentAction = 0;
		//charControl->actions[charControl->currentAction].doForNumFrames = MAXCNTFRAMES;
		charControl->actions[charControl->currentAction].doForNumFrames = 64 + rand()&127;
		charControl->actions[charControl->currentAction].currentFrame = 0;
		wickedknight_doCircleTarget(character, mapInfo, characterCollection, charControl);
		return;
	}
	
	if (charControl->actions[charControl->currentAction].currentFrame >= 
		charControl->actions[charControl->currentAction].doForNumFrames) {
		charControl->currentAction = MAXACTIONS;
		character->controller = &wickedknight_attackController;
		character->controller(character, mapInfo, characterCollection);
		return;
	}
	
	if (character->action == EWickedKnightChaseTarget) {
		mprinter_printf("DO CHASE\n");
		wickedknight_doCircleTarget(character, mapInfo, characterCollection, charControl);
	} /*else if (character->action == EWickedKnightAttack) {
		wickedknight_doAttack(character, mapInfo, characterCollection, charControl);
	}*/ else if (character->action == EWickedKnightAttack){
		mprinter_printf("ATTACK FROM CHASE\n");
	}
	//++charControl->actions[charControl->currentAction].currentFrame;
}

void wickedknight_doStun(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection, CharacterAIControl *charControl) {
}

void wickedknight_stunnedController(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection) {
	CharacterAIControl *charControl = (CharacterAIControl*)character->free;
	int distanceX, distanceY, i;
	if (charControl->currentStatus == EWickedKnightAIStateHuntTarget) {
		if (charControl->previousActionType == EWickedKnightAttack) {
			//mprinter_printf("STUNNED TO ATTACK DIRECTION %d\n", character->faceDirection);
			character->controller = &wickedknight_attackController;
			charControl->currentAction = 0;
			character->nextAction = charControl->previousActionType;
			charControl->previousActionType = EWickedKnightChaseTarget;
			character->spriteDisplay = charControl->previousSpriteDisplay;
		} else {
			charControl->currentAction = MAXACTIONS;
			character->controller = &wickedknight_huntController;
		}
		character->controller(character, mapInfo, characterCollection);
		return;
	}
		
	/*if (common_shouldDoIntializeActions(character)) {
		character->hasNewFaceDirection = true;
		charControl->countAction = 1;
		charControl->currentAction = 0;
		charControl->actions[charControl->currentAction] = ((ActionControl){25, 0, character->direction, character->faceDirection, EWickedKnightStunned});
	}*/
	common_doSetActions(charControl, character);
	/*if (character->nextAction == EWickedKnightStunned) {
		wickedknight_doStun(character, mapInfo, characterCollection, charControl);
	} else {
		charControl->currentStatus = EWickedKnightAIStateHuntTarget;
		charControl->currentAction = MAXACTIONS;
		character->controller = &wickedknight_huntController;
		character->controller(character, mapInfo, characterCollection);
	}*/
}

void wickedknight_doBackOff(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection, CharacterAIControl *charControl) {
	bool isNear = false;
	EDirections goDirection = EUnknown;
	s8 doAction;
	charControl->target = *commonFindCharTypePositionByDistance(characterCollection,
		&character->position, MAX_DIST_FOR_CHASE, STARTPLAYABLECHARTYPE, ENDPLAYABLECHARACTERTYPE);
	
	if (!commonIsFoundPosition(&charControl->target)) {
		charControl->currentStatus = EWickedKnightAIStateWalkAround;
		character->nextAction = EWickedKnightWalk;
		return;
	}
	
	common_findDirectionOfTargetCharacterInScreenCustom(&character->position,
		&charControl->target, 
		&FAR_TARGET_WICKEDKNIGHT_8x8[0][0], INSCREEN_DIST, INSCREEN_ARRAYWIDTH,
		&BACKOFF_TARGET_8x8[0][0], (s8*)&ACTION_MOVEONLY_8x8[0][0],
			MOVACT_INRANGE_DIST, MOVACT_INRANGE_ARRAYWIDTH,
		&goDirection, &doAction, &isNear);
	
	//mprinter_printf("NEAR %s DIRECTION %d\n", isNear ? "TRUE":"FALSE", goDirection);
	if (!isNear && goDirection == EUnknown) {
		//mprinter_printf("NOT NEAR\n");
		charControl->currentAction = MAXACTIONS;
		charControl->currentStatus = EWickedKnightAIStateWalkAround;
		character->nextAction = EWickedKnightWalk;
		return;
	} else if (isNear) {
		EDirections faceDirection;
		//mprinter_printf("NEAR\n");
		//character->nextAction = EWickedKnightAttack;
		//character->nextAction = doAction;
		charControl->actions[charControl->currentAction].action = doAction;
		common_faceTarget(&character->position, &charControl->target, 
				&faceDirection);

		//character->nextDirection = goDirection;
		charControl->actions[charControl->currentAction].direction = goDirection;
		if (character->faceDirection != faceDirection) {
			character->hasNewFaceDirection = true;
		}
		charControl->actions[charControl->currentAction].faceDirection = faceDirection;
	}
	
	//character->nextAction = EWickedKnightChaseTarget;
	charControl->actions[charControl->currentAction].action = EWickedKnightChaseTarget;
	
	/*if (charControl->leftBlocked | charControl->rightBlocked | 
		charControl->upBlocked | charControl->downBlocked) {
		common_doGoAroundObstacle(&character->position, &charControl->target, charControl, 
			EWickedKnightChaseTarget, 60);
		common_doSetActions(charControl, character);
		mprinter_printf("???3 %d\n", character->nextAction);
		return;
	} else if (charControl->currentAction >= charControl->countAction) {
		//charControl->countAction = 0;
		commonInitializeAISetActions(charControl);
		charControl->currentAction = MAXACTIONS;
		character->nextDirection = goDirection;
		character->faceDirection = goDirection;
		mprinter_printf("???2 %d\n", character->faceDirection);
		return;
	}*/
	
	//mprinter_printf("???1 %d\n", character->faceDirection);
	common_doSetActions(charControl, character);
	//mprinter_printf("ACTION AFTER SET %d\n", character->nextAction);
}

void wickedknight_backoffController(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection) {
	CharacterAIControl *charControl = (CharacterAIControl*)character->free;
	int distanceX, distanceY, i;
	
	if (charControl->currentStatus == EWickedKnightAIStateWalkAround) {
		charControl->currentAction = MAXACTIONS;
		character->controller = &wickedknight_walkAroundController;
		character->controller(character, mapInfo, characterCollection);
		return;
	}
	
	if (common_shouldDoIntializeActions(character)) {
		commonInitializeAISetActions(charControl);
		character->nextAction = EWickedKnightChaseTarget;
		charControl->countAction = 1;
		charControl->currentAction = 0;
		charControl->actions[charControl->currentAction].doForNumFrames = 20;
		charControl->actions[charControl->currentAction].currentFrame = 0;
		wickedknight_doBackOff(character, mapInfo, characterCollection, charControl);
		return;
	}
	
	if (charControl->actions[charControl->currentAction].currentFrame >= 
		charControl->actions[charControl->currentAction].doForNumFrames) {
		//mprinter_printf("GO TO HUNT CONTROLLER\n");
		charControl->currentAction = MAXACTIONS;
		character->controller = &wickedknight_huntController;
		character->controller(character, mapInfo, characterCollection);
		return;
	}
	
	if (character->action == EWickedKnightChaseTarget) {
		mprinter_printf("DO BACK OFF\n");
		wickedknight_doBackOff(character, mapInfo, characterCollection, charControl);
	}
}