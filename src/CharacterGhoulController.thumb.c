#include <stdlib.h>
#include <stdbool.h>
#include "GBATypes.h"
#include "GBAObject.h"
#include "GBAVideo.h"
#include "GBADMA.h"
#include "CharacterGhoul.h"
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

const EDirections ghoul_walkDirections[] = {
    EDown, EDownright, ERight, EUpright,
	EUp, EUpleft, ELeft, EDownleft
};

void ghoul_walkAroundController(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection);

void ghoul_huntController(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection);
	
void ghoul_stunnedController(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection);
	
void ghoul_hurtController(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection);
	
void ghoul_getBoundingBoxMoving(const CharacterAttr* character, 
	int *count, BoundingBox *boundingBox);
	

void ghoul_setCharacter(CharacterAttr* character) {
    character->controller = &ghoul_walkAroundController; 
}

#define GHOUL_MOVACT_INRANGE_ARRAYWIDTH 13
#define GHOUL_MOVACT_INRANGE_DIST 52

const EDirections GHOUL_ATTACKRANGE_TARGET_8x8[GHOUL_MOVACT_INRANGE_ARRAYWIDTH][GHOUL_MOVACT_INRANGE_ARRAYWIDTH] = {
	{EUpleft,   EUpleft,   EUpleft,   EUp,       EUp,       EUp,        EUp,      EUp,        EUp,        EUp,        EUpright,   EUpright,   EUpright},
	{EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUp,       EUp,        EUp,      EUp,        EUp,        EUpright,   EUpright,   EUpright,   EUpright},
	{EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUp,        EUp,      EUp,        EUpright,   EUpright,   EUpright,   EUpright,   EUpright},
	{ELeft,     EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUp,        EUp,      EUp,        EUpright,   EUpright,   EUpright,   EUpright,   ERight},
	{ELeft,     ELeft,     EUpleft,   EUpleft,   EUpleft,   ELeft,      EUp,      ERight,     EUpright,   EUpright, EUpright,   ERight,     ERight},
	{ELeft,     ELeft,     ELeft,     ELeft,     EUp,       EUpright,   EUp,      EUpleft,    EUp,        ERight,     ERight,     ERight,     ERight},
	{ELeft,     ELeft,     ELeft,     ELeft,     ELeft,     ELeft,      EUnknown, ERight,     ERight,     ERight,     ERight,     ERight,     ERight},
	{ELeft,     ELeft,     ELeft,     ELeft,     EDown,     EDownright, EDown,    EDownleft,  EDown,      ERight,     ERight,     ERight,     ERight},
	{ELeft,     ELeft,     EDown,     EDownleft, ERight,    ELeft,      EDown,    ERight,     EDown,      EDownright, EDownright, ERight,     ERight},
	{ELeft,     EDownleft, EDownleft, EDownleft, EDownleft, EDown,      EDown,    EDown,      EDownright, EDownright, EDownright, EDownright, ERight},
	{EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDown,      EDown,    EDown,      EDownright, EDownright, EDownright, EDownright, EDownright},
	{EDownleft, EDownleft, EDownleft, EDownleft, EDown,     EDown,      EDown,    EDown,      EDown,      EDownright, EDownright, EDownright, EDownright},
	{EDownleft, EDownleft, EDownleft, EDown,     EDown,     EDown,      EDown,    EDown,      EDown,      EDown,      EDownright, EDownright, EDownright},
};

const GhoulAction GHOUL_INRANGE_ACTION_8x8[GHOUL_MOVACT_INRANGE_ARRAYWIDTH][GHOUL_MOVACT_INRANGE_ARRAYWIDTH] = {
	{EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget},
	{EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget},
	{EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget},
	{EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget},
	{EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulAttack      , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget},
	{EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulAttack      , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget},
	{EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulAttack      , EGhoulAttack      , EGhoulAttack      , EGhoulAttack      , EGhoulAttack      , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget},
	{EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulAttack      , EGhoulChaseTarget ,EGhoulChaseTarget  , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget},
	{EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulAttack      , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget},
	{EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget},
	{EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget},
	{EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget},
	{EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget , EGhoulChaseTarget}
};





#define GHOUL_INSCREEN_DIST 84
#define GHOUL_INSCREEN_ARRAYWIDTH 21

const EDirections FAR_TARGET_GHOUL_8x8[GHOUL_INSCREEN_ARRAYWIDTH][GHOUL_INSCREEN_ARRAYWIDTH] = {
	{EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUp,      EUp,      EUp,      EUp,      EUp,      EUp,      EUp,      EUp,      EUp,        EUpright,   EUpright,   EUpright,   EUpright,   EUpright,   EUpright},
	{EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUp,      EUp,      EUp,      EUp,      EUp,      EUp,      EUp,      EUp,      EUp,        EUpright,   EUpright,   EUpright,   EUpright,   EUpright,   EUpright},
	{EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,  EUp,      EUp,      EUp,      EUp,      EUp,      EUp,      EUp,      EUpright,   EUpright,   EUpright,   EUpright,   EUpright,   EUpright,   EUpright},
	{EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUpleft,  EUp,      EUp,      EUp,      EUp,      EUp,      EUp,      EUp,      EUpright,   EUpright,   EUpright,   EUpright,   EUpright,   EUpright,   EUpright},
	{EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUnknown,  EUnknown,  EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown,   EUnknown,   EUnknown,   EUpright,   EUpright,   EUpright,   EUpright},
	{EUpleft,   EUpleft,   EUpleft,   EUpleft,   EUnknown,  EUnknown,  EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown,   EUnknown,   EUnknown,   EUpright,   EUpright,   EUpright,   EUpright},
	{ELeft,     ELeft,     EUpleft,   EUpleft,   EUnknown,  EUnknown,  EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown,   EUnknown,   EUnknown,   EUpright,   EUpright,   ERight,     ERight},
	{ELeft,     ELeft,     ELeft,     ELeft,     EUnknown,  EUnknown,  EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown,   EUnknown,   EUnknown,   ERight,     ERight,     ERight,     ERight},
	{ELeft,     ELeft,     ELeft,     ELeft,     EUnknown,  EUnknown,  EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown,   EUnknown,   EUnknown,   ERight,     ERight,     ERight,     ERight},
	{ELeft,     ELeft,     ELeft,     ELeft,     EUnknown,  EUnknown,  EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown,   EUnknown,   EUnknown,   ERight,     ERight,     ERight,     ERight},
	{ELeft,     ELeft,     ELeft,     ELeft,     EUnknown,  EUnknown,  EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown,   EUnknown,   EUnknown,   ERight,     ERight,     ERight,     ERight},
	{ELeft,     ELeft,     ELeft,     ELeft,     EUnknown,  EUnknown,  EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown,   EUnknown,   EUnknown,   ERight,     ERight,     ERight,     ERight},
	{ELeft,     ELeft,     ELeft,     ELeft,     EUnknown,  EUnknown,  EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown,   EUnknown,   EUnknown,   ERight,     ERight,     ERight,     ERight},
	{ELeft,     ELeft,     ELeft,     ELeft,     EUnknown,  EUnknown,  EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown,   EUnknown,   EUnknown,   ERight,     ERight,     ERight,     ERight},
	{ELeft,     ELeft,     EDownleft, EDownleft, EUnknown,  EUnknown,  EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown,   EUnknown,   EUnknown,   EDownright, EDownright, ERight,     ERight},
	{EDownleft, EDownleft, EDownleft, EDownleft, EUnknown,  EUnknown,  EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown,   EUnknown,   EUnknown,   EDownright, EDownright, EDownright, EDownright},
	{EDownleft, EDownleft, EDownleft, EDownleft, EUnknown,  EUnknown,  EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown,   EUnknown,   EUnknown,   EDownright, EDownright, EDownright, EDownright},
	{EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft,EDown,    EDown,    EDown,    EDown,    EDown,    EDown,    EDown,    EDownright, EDownright, EDownright, EDownright, EDownright, EDownright, EDownright},
	{EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft,EDown,    EDown,    EDown,    EDown,    EDown,    EDown,    EDown,    EDownright, EDownright, EDownright, EDownright, EDownright, EDownright, EDownright},
	{EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDown,    EDown,    EDown,    EDown,    EDown,    EDown,    EDown,    EDown,    EDown,      EDownright, EDownright, EDownright, EDownright, EDownright, EDownright},
	{EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDown,    EDown,    EDown,    EDown,    EDown,    EDown,    EDown,    EDown,    EDown,      EDownright, EDownright, EDownright, EDownright, EDownright, EDownright}
};



#define GHOUL_HEIGHT_SEARCH 24
void ghoul_doWalk(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection, CharacterAIControl *charControl) {
	Position *position = &character->position;
	BoundingBox searchArea;
	searchArea.startX = CONVERT_2POS(position->x) + ghoul_scanSurroundingOffset[character->direction][0].x;
	searchArea.startY = CONVERT_2POS(position->y) + ghoul_scanSurroundingOffset[character->direction][0].y;
	searchArea.endX = CONVERT_2POS(position->x) + ghoul_scanSurroundingOffset[character->direction][1].x;
	searchArea.endY = CONVERT_2POS(position->y) + ghoul_scanSurroundingOffset[character->direction][1].y;
	searchArea.startZ = CONVERT_2POS(position->z);
	searchArea.endZ = CONVERT_2POS(position->z) + GHOUL_HEIGHT_SEARCH;
	charControl->target = *commonFindCharTypeInBoundingBox(characterCollection, &searchArea, 
		STARTPLAYABLECHARTYPE, ENDPLAYABLECHARACTERTYPE);
		
	if (commonIsFoundPosition(&charControl->target)) {
		charControl->currentStatus = EGhoulAIStateHuntTarget;
		character->nextAction = EGhoulChaseTarget;
		//return;
	}
}

void ghoul_walkAroundController(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection) {
	CharacterAIControl *charControl = (CharacterAIControl*)character->free;
	int i;
	//EDirections goDirection;
   
	if (charControl->currentStatus == EGhoulAIStateHuntTarget) {
		charControl->currentAction = MAXACTIONS;
		character->controller = &ghoul_huntController;
		character->controller(character, mapInfo, characterCollection);
		return;
	}
	
	if (common_shouldDoIntializeActions(character)) {
		character->getBounds = &ghoul_getBoundingBoxMoving;
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
		
	EDirections direction;
	common_findDirectionOfPosition(&character->position, &charControl->wayPoints[charControl->wayPointCurrent], &direction);
	character->nextAction = EGhoulWalk;
	character->nextDirection = direction;
	
	if (charControl->leftBlocked | charControl->rightBlocked | 
		charControl->upBlocked | charControl->downBlocked) {
		common_doGoAroundObstacle(&character->position, &charControl->target, charControl, 
			EGhoulWalk, 15);
	}
	
	common_doSetActions(charControl, character);
	
	if (charControl->currentAction >= charControl->countAction) {
		//charControl->countAction = 0;
		commonInitializeAISetActions(charControl);
		charControl->currentAction = MAXACTIONS;
		//character->nextDirection = direction;
		//return;
	}
		
	ghoul_doWalk(character, mapInfo, characterCollection, charControl);
}

void ghoul_doChaseTarget(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection, CharacterAIControl *charControl) {
	bool isNear;
	EDirections goDirection, faceDirection;
	s8 doAction;

	charControl->target = *commonFindCharTypePositionByDistance(characterCollection,
		&character->position, MAX_DIST_FOR_CHASE, STARTPLAYABLECHARTYPE, ENDPLAYABLECHARACTERTYPE);
	
	if (!commonIsFoundPosition(&charControl->target)) {
		charControl->currentStatus = EGhoulAIStateWalkAround;
		character->nextAction = EGhoulWalk;
		return;
	}
	
	//common_findDirectionOfTargetCharacterInScreen(&character->position, 
	//	&charControl->target, &goDirection, &isNear);
		
	common_findDirectionOfTargetCharacterInScreenCustom(&character->position,
		&charControl->target, 
		&FAR_TARGET_GHOUL_8x8[0][0], GHOUL_INSCREEN_DIST, GHOUL_INSCREEN_ARRAYWIDTH,
		&GHOUL_ATTACKRANGE_TARGET_8x8[0][0], (s8*)&GHOUL_INRANGE_ACTION_8x8[0][0],
			GHOUL_MOVACT_INRANGE_DIST, GHOUL_MOVACT_INRANGE_ARRAYWIDTH,
		&goDirection, &doAction, &isNear);
	
		if (charControl->currentAction < charControl->countAction && 
		doAction != EGhoulAttack) {
		common_doSetActions(charControl, character);
				
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
			charControl->currentStatus = EGhoulAIStateWalkAround;
			character->nextAction = EGhoulWalk;
			return;
		}
		character->nextAction = EGhoulChaseTarget;
		character->nextDirection = goDirection;
		
		common_faceTarget(&character->position, &charControl->target, 
			&faceDirection);

		if (character->faceDirection != faceDirection) {
			character->hasNewFaceDirection = true;
			character->faceDirection = faceDirection;
		}
		
		//return;
	} else if (isNear) {		
		character->nextAction = doAction;
		character->nextDirection = goDirection;
		common_faceTarget(&character->position, &charControl->target, 
				&faceDirection);

		if (character->faceDirection != faceDirection) {
			character->hasNewFaceDirection = true;
			character->faceDirection = faceDirection;
		}
		//return;
	}
	
	if (character->nextAction == EGhoulAttack) {
		return;
	}
	//character->nextAction = EGhoulChaseTarget;
	
	if (charControl->leftBlocked | charControl->rightBlocked | 
		charControl->upBlocked | charControl->downBlocked) {
		common_doGoAroundObstacle(&character->position, &charControl->target, charControl, 
			EGhoulChaseTarget, 15);
		common_doSetActions(charControl, character);
		return;
	} /*else if (charControl->currentAction >= charControl->countAction) {
		charControl->countAction = 0;
		commonInitializeAISetActions(charControl);
		charControl->currentAction = MAXACTIONS;
		//character->nextDirection = goDirection;
		return;
	}*/
	
	//character->nextDirection = goDirection;
	//common_doSetActions(charControl, character);
}

void ghoul_doAttack(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection, CharacterAIControl *charControl) {
}

void ghoul_huntController(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection) {
	CharacterAIControl *charControl = (CharacterAIControl*)character->free;
	int distanceX, distanceY, i;
	
	if (charControl->currentStatus == EGhoulAIStateWalkAround) {
		charControl->currentAction = MAXACTIONS;
		character->controller = &ghoul_walkAroundController;
		character->controller(character, mapInfo, characterCollection);
		return;
	}
	
	if (common_shouldDoIntializeActions(character)) {
		commonInitializeAISetActions(charControl);
		character->nextAction = EGhoulChaseTarget;
		ghoul_doChaseTarget(character, mapInfo, characterCollection, charControl);
		return;
	}
	
	if (character->action == EGhoulChaseTarget) {
		ghoul_doChaseTarget(character, mapInfo, characterCollection, charControl);
	} else if (character->action == EGhoulAttack) {
		ghoul_doAttack(character, mapInfo, characterCollection, charControl);
	}
	//++charControl->actions[charControl->currentAction].currentFrame;
}

void ghoul_doStun(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection, CharacterAIControl *charControl) {
}

void ghoul_stunnedController(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection) {
	CharacterAIControl *charControl = (CharacterAIControl*)character->free;
	int distanceX, distanceY, i;
	
	if (charControl->currentStatus == EGhoulAIStateHuntTarget) {
		charControl->currentAction = MAXACTIONS;
		character->controller = &ghoul_huntController;
		character->controller(character, mapInfo, characterCollection);
		return;
	}
	
	if (common_shouldDoIntializeActions(character)) {
		charControl->countAction = 1;
		charControl->currentAction = 0;
		charControl->actions[0] = ((ActionControl){30, 0, character->direction, EGhoulStunned});
		character->nextAction = EGhoulStunned;
	}
	
	/*if (character->nextAction == EGhoulStunned) {
		ghoul_doStun(character, mapInfo, characterCollection, charControl);
	} else {
		charControl->currentStatus = EGhoulAIStateHuntTarget;
		charControl->currentAction = MAXACTIONS;
		character->controller = &ghoul_huntController;
		character->controller(character, mapInfo, characterCollection);
	}*/
}

void ghoul_hurtController(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection) {
	CharacterAIControl *charControl = (CharacterAIControl*)character->free;
	int distanceX, distanceY, i;
	
	//mgba_logs("ACTION HURT CONTOLLER");
	//mprinter_printf("ACTION HURT CONTOLLER\n");
	if (charControl->currentStatus == EGhoulAIStateHuntTarget) {
		charControl->currentAction = MAXACTIONS;
		character->controller = &ghoul_huntController;
		character->controller(character, mapInfo, characterCollection);
		return;
	}
	
	if (common_shouldDoIntializeActions(character)) {		
		//commonInitializeAISetActions(charControl);
		//mgba_logs("INITIALIZE HURT\n");
		//mprinter_printf("INITIALIZE HURT\n");
	}
	
	//mgba_logs("ACTION HURT CONTOLLER DO ACTION");
	//mprinter_printf("BEFORE DO HURT: %d %d\n", character->nextAction);
	common_doSetActions(charControl, character);
	//mprinter_printf("DO HURT: %d %d\n", character->nextAction, EGhoulHurt);
	/*if (character->nextAction == EGhoulStunned) {
		ghoul_doStun(character, mapInfo, characterCollection, charControl);
	} else {
		charControl->currentStatus = EGhoulAIStateHuntTarget;
		charControl->currentAction = MAXACTIONS;
		character->controller = &ghoul_huntController;
		character->controller(character, mapInfo, characterCollection);
	}*/
}