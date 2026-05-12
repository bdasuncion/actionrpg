#include <stdlib.h>
#include <stdbool.h>
#include "GBATypes.h"
#include "GBAObject.h"
#include "GBAVideo.h"
#include "GBADMA.h"
#include "CharacterSkullDemon.h"
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

const EDirections skulldemon_walkDirections[] = {
    EDown, EDownright, ERight, EUpright,
	EUp, EUpleft, ELeft, EDownleft
};

void skulldemon_walkAroundController(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection);

void skulldemon_huntController(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection);
	
void skulldemon_stunnedController(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection);
	
void skulldemon_hurtController(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection);
	
void skulldemon_getBoundingBoxMoving(const CharacterAttr* character, 
	int *count, BoundingBox *boundingBox);
	

void skulldemon_setCharacter(CharacterAttr* character) {
    character->controller = &skulldemon_walkAroundController; 
}

#define SKULLDEMON_MOVACT_INRANGE_ARRAYWIDTH 13
#define SKULLDEMON_MOVACT_INRANGE_DIST 52

const EDirections SKULLDEMON_ATTACKRANGE_TARGET_8x8[SKULLDEMON_MOVACT_INRANGE_ARRAYWIDTH][SKULLDEMON_MOVACT_INRANGE_ARRAYWIDTH] = {
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

const SkullDemonAction SKULLDEMON_INRANGE_ACTION_8x8[SKULLDEMON_MOVACT_INRANGE_ARRAYWIDTH][SKULLDEMON_MOVACT_INRANGE_ARRAYWIDTH] = {
	{ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget},
	{ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget},
	{ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget},
	{ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget},
	{ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonAttack      , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget},
	{ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonAttack      , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget},
	{ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonAttack      , ESkullDemonAttack      , ESkullDemonAttack      , ESkullDemonAttack      , ESkullDemonAttack      , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget},
	{ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonAttack      , ESkullDemonChaseTarget ,ESkullDemonChaseTarget  , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget},
	{ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonAttack      , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget},
	{ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget},
	{ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget},
	{ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget},
	{ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget , ESkullDemonChaseTarget}
};





#define SKULLDEMON_INSCREEN_DIST 84
#define SKULLDEMON_INSCREEN_ARRAYWIDTH 21

const EDirections FAR_TARGET_SKULLDEMON_8x8[SKULLDEMON_INSCREEN_ARRAYWIDTH][SKULLDEMON_INSCREEN_ARRAYWIDTH] = {
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




void skulldemon_doWalk(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection, CharacterAIControl *charControl) {
	Position *position = &character->position;
	BoundingBox searchArea;
	searchArea.startX = CONVERT_2POS(position->x) + skulldemon_scanSurroundingOffset[character->direction][0].x;
	searchArea.startY = CONVERT_2POS(position->y) + skulldemon_scanSurroundingOffset[character->direction][0].y;
	searchArea.endX = CONVERT_2POS(position->x) + skulldemon_scanSurroundingOffset[character->direction][1].x;
	searchArea.endY = CONVERT_2POS(position->y) + skulldemon_scanSurroundingOffset[character->direction][1].y;

	charControl->target = *commonFindCharTypeInBoundingBox(characterCollection, &searchArea, 
		STARTPLAYABLECHARTYPE, ENDPLAYABLECHARACTERTYPE);
		
	if (commonIsFoundPosition(&charControl->target)) {
		charControl->currentStatus = ESkullDemonAIStateHuntTarget;
		character->nextAction = ESkullDemonChaseTarget;
		//return;
	}
}

void skulldemon_walkAroundController(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection) {
	CharacterAIControl *charControl = (CharacterAIControl*)character->free;
	int i;
	//EDirections goDirection;
   
	if (charControl->currentStatus == ESkullDemonAIStateHuntTarget) {
		charControl->currentAction = MAXACTIONS;
		character->controller = &skulldemon_huntController;
		character->controller(character, mapInfo, characterCollection);
		return;
	}
			
	if (common_shouldDoIntializeActions(character)) {
		character->getBounds = &skulldemon_getBoundingBoxMoving;
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
	character->nextAction = ESkullDemonWalk;
	character->nextDirection = direction;
	
	if (charControl->leftBlocked | charControl->rightBlocked | 
		charControl->upBlocked | charControl->downBlocked) {
		common_doGoAroundObstacle(&character->position, &charControl->target, charControl, 
			ESkullDemonWalk, 15);
	}
	
	common_doSetActions(charControl, character);
	
	if (charControl->currentAction >= charControl->countAction) {
		//charControl->countAction = 0;
		commonInitializeAISetActions(charControl);
		charControl->currentAction = MAXACTIONS;
		//character->nextDirection = direction;
		//return;
	}
		
	skulldemon_doWalk(character, mapInfo, characterCollection, charControl);
}

void skulldemon_doChaseTarget(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection, CharacterAIControl *charControl) {
	bool isNear;
	EDirections goDirection, faceDirection;
	s8 doAction;

	charControl->target = *commonFindCharTypePositionByDistance(characterCollection,
		&character->position, MAX_DIST_FOR_CHASE, STARTPLAYABLECHARTYPE, ENDPLAYABLECHARACTERTYPE);
	
	if (!commonIsFoundPosition(&charControl->target)) {
		charControl->currentStatus = ESkullDemonAIStateWalkAround;
		character->nextAction = ESkullDemonWalk;
		return;
	}
	
	//common_findDirectionOfTargetCharacterInScreen(&character->position, 
	//	&charControl->target, &goDirection, &isNear);
		
	common_findDirectionOfTargetCharacterInScreenCustom(&character->position,
		&charControl->target, 
		&FAR_TARGET_SKULLDEMON_8x8[0][0], SKULLDEMON_INSCREEN_DIST, SKULLDEMON_INSCREEN_ARRAYWIDTH,
		&SKULLDEMON_ATTACKRANGE_TARGET_8x8[0][0], (s8*)&SKULLDEMON_INRANGE_ACTION_8x8[0][0],
			SKULLDEMON_MOVACT_INRANGE_DIST, SKULLDEMON_MOVACT_INRANGE_ARRAYWIDTH,
		&goDirection, &doAction, &isNear);
	
		if (charControl->currentAction < charControl->countAction && 
		doAction != ESkullDemonAttack) {
		mprinter_printf("CONTINUE ACTION\n");
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
			charControl->currentStatus = ESkullDemonAIStateWalkAround;
			character->nextAction = ESkullDemonWalk;
			return;
		}
		mprinter_printf("CHASE ACTION\n");
		character->nextAction = ESkullDemonChaseTarget;
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
		mprinter_printf("ACTION %d\n", character->nextAction);
		common_faceTarget(&character->position, &charControl->target, 
				&faceDirection);

		if (character->faceDirection != faceDirection) {
			character->hasNewFaceDirection = true;
			character->faceDirection = faceDirection;
		}
		//return;
	}
	
	if (character->nextAction == ESkullDemonAttack) {
		mprinter_printf("ATTACK\n");
		return;
	}
	//character->nextAction = ESkullDemonChaseTarget;
	
	if (charControl->leftBlocked | charControl->rightBlocked | 
		charControl->upBlocked | charControl->downBlocked) {
		common_doGoAroundObstacle(&character->position, &charControl->target, charControl, 
			ESkullDemonChaseTarget, 15);
		common_doSetActions(charControl, character);
		mprinter_printf("MOVE AROUND SET\n");
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

void skulldemon_doAttack(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection, CharacterAIControl *charControl) {
}

void skulldemon_huntController(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection) {
	CharacterAIControl *charControl = (CharacterAIControl*)character->free;
	int distanceX, distanceY, i;
	
	if (charControl->currentStatus == ESkullDemonAIStateWalkAround) {
		charControl->currentAction = MAXACTIONS;
		character->controller = &skulldemon_walkAroundController;
		character->controller(character, mapInfo, characterCollection);
		return;
	}
	
	if (common_shouldDoIntializeActions(character)) {
		mprinter_printf("INIT HUNT\n");
		commonInitializeAISetActions(charControl);
		character->nextAction = ESkullDemonChaseTarget;
		skulldemon_doChaseTarget(character, mapInfo, characterCollection, charControl);
		return;
	}
	
	if (character->action == ESkullDemonChaseTarget) {
		mprinter_printf("CHASE\n");
		skulldemon_doChaseTarget(character, mapInfo, characterCollection, charControl);
	} else if (character->action == ESkullDemonAttack) {
		mprinter_printf("ATTACk\n");
		skulldemon_doAttack(character, mapInfo, characterCollection, charControl);
	}
	//++charControl->actions[charControl->currentAction].currentFrame;
}

void skulldemon_doStun(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection, CharacterAIControl *charControl) {
}

void skulldemon_stunnedController(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection) {
	CharacterAIControl *charControl = (CharacterAIControl*)character->free;
	int distanceX, distanceY, i;
	
	if (charControl->currentStatus == ESkullDemonAIStateHuntTarget) {
		charControl->currentAction = MAXACTIONS;
		character->controller = &skulldemon_huntController;
		character->controller(character, mapInfo, characterCollection);
		return;
	}
	
	if (common_shouldDoIntializeActions(character)) {
		charControl->countAction = 1;
		charControl->currentAction = 0;
		charControl->actions[0] = ((ActionControl){30, 0, character->direction, ESkullDemonStunned});
		character->nextAction = ESkullDemonStunned;
	}
	
	/*if (character->nextAction == ESkullDemonStunned) {
		skulldemon_doStun(character, mapInfo, characterCollection, charControl);
	} else {
		charControl->currentStatus = ESkullDemonAIStateHuntTarget;
		charControl->currentAction = MAXACTIONS;
		character->controller = &skulldemon_huntController;
		character->controller(character, mapInfo, characterCollection);
	}*/
}

void skulldemon_hurtController(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection) {
	CharacterAIControl *charControl = (CharacterAIControl*)character->free;
	int distanceX, distanceY, i;
	
	//mgba_logs("ACTION HURT CONTOLLER");
	//mprinter_printf("ACTION HURT CONTOLLER\n");
	if (charControl->currentStatus == ESkullDemonAIStateHuntTarget) {
		charControl->currentAction = MAXACTIONS;
		character->controller = &skulldemon_huntController;
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
	//mprinter_printf("DO HURT: %d %d\n", character->nextAction, ESkullDemonHurt);
	/*if (character->nextAction == ESkullDemonStunned) {
		skulldemon_doStun(character, mapInfo, characterCollection, charControl);
	} else {
		charControl->currentStatus = ESkullDemonAIStateHuntTarget;
		charControl->currentAction = MAXACTIONS;
		character->controller = &skulldemon_huntController;
		character->controller(character, mapInfo, characterCollection);
	}*/
}