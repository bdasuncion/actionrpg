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

#define MAX_DIST_FOR_CHASE 120

const EDirections wickedknight_walkDirections[] = {
    EDown, EDownright, ERight, EUpright,
	EUp, EUpleft, ELeft, EDownleft
};

#define INSCREEN_DIST 80
#define INSCREEN_ARRAYWIDTH 20

const EDirections FAR_TARGET_WICKEDKNIGHT_8x8[INSCREEN_ARRAYWIDTH][INSCREEN_ARRAYWIDTH] = {
 {EUpleft, EUpleft, EUpleft, EUpleft, EUpleft, EUpleft, EUp, EUp, EUp, EUp, EUp, EUp, EUp, EUp, EUpright, EUpright, EUpright, EUpright, EUpright, EUpright},
 {EUpleft, EUpleft, EUpleft, EUpleft, EUpleft, EUpleft, EUp, EUp, EUp, EUp, EUp, EUp, EUp, EUp, EUpright, EUpright, EUpright, EUpright, EUpright, EUpright},
 {EUpleft, EUpleft, EUpleft, EUpleft, EUpleft, EUpleft, EUpleft, EUp, EUp, EUp, EUp, EUp, EUp, EUpright, EUpright, EUpright, EUpright, EUpright, EUpright, EUpright},
 {EUpleft, EUpleft, EUpleft, EUpleft, EUpleft, EUpleft, EUpleft, EUp, EUp, EUp, EUp, EUp, EUp, EUpright, EUpright, EUpright, EUpright, EUpright, EUpright, EUpright},
 {EUpleft, EUpleft, EUpleft, EUpleft, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUpright, EUpright, EUpright, EUpright},
 {EUpleft, EUpleft, EUpleft, EUpleft, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUpright, EUpright, EUpright, EUpright},
 {ELeft, ELeft, EUpleft, EUpleft, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUpright, EUpright, ERight, ERight},
 {ELeft, ELeft, ELeft, ELeft, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, ERight, ERight, ERight, ERight},
 {ELeft, ELeft, ELeft, ELeft, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, ERight, ERight, ERight, ERight},
 {ELeft, ELeft, ELeft, ELeft, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, ERight, ERight, ERight, ERight},
 {ELeft, ELeft, ELeft, ELeft, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, ERight, ERight, ERight, ERight},
 {ELeft, ELeft, ELeft, ELeft, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, ERight, ERight, ERight, ERight},
 {ELeft, ELeft, ELeft, ELeft, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, ERight, ERight, ERight, ERight},
 {ELeft, ELeft, EDownleft, EDownleft, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EDownright, EDownright, ERight, ERight},
 {EDownleft, EDownleft, EDownleft, EDownleft, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EDownright, EDownright, EDownright, EDownright},
 {EDownleft, EDownleft, EDownleft, EDownleft, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EUnknown, EDownright, EDownright, EDownright, EDownright},
 {EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDown, EDown,  EDown, EDown, EDown, EDown, EDownright, EDownright, EDownright, EDownright, EDownright, EDownright, EDownright},
 {EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDown, EDown,  EDown, EDown, EDown, EDown, EDownright, EDownright, EDownright, EDownright, EDownright, EDownright, EDownright},
 {EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDown, EDown, EDown, EDown, EDown, EDown, EDown, EDown, EDownright, EDownright, EDownright, EDownright, EDownright, EDownright},
 {EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDown, EDown, EDown, EDown, EDown, EDown, EDown, EDown, EDownright, EDownright, EDownright, EDownright, EDownright, EDownright}
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
{ELeft, ELeft, ELeft, ELeft, ELeft, ELeft, ELeft, ELeft, ELeft, ELeft, ELeft, EUp},
{EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EDownleft, EUpleft, EUp},
{EDown, EDownright, EDownleft, EDownleft, EDownleft, EUp, EUp, EDownleft, EDownleft, EUpleft, EUpleft, EUp},
{EDown, EDownright, EDownright, EDownright, EDownright, EUp, EUp, EUpleft, EUpleft, EUpleft, EUpleft, EUp},
{EDown, EDownright, EDownright, EDownright, EDownright, EUp, EUp, EUpleft, EUpleft, EUpleft, EUpleft, EUp},
{EDown, EDownright, ELeft, ELeft, ELeft, EUp, ELeft, ERight, ERight, ERight, EUpleft, EUp},
{EDown, EDownright, ELeft, ELeft, ELeft, ERight, EDown, ERight, ERight, ERight, EUpleft, EUp},
{EDown, EDownright, EDownright, EDownright, EDownright, EDown, EDown, EUpleft, EUpleft, EUpleft, EUpleft, EUp},
{EDown, EDownright, EDownright, EDownright, EDownright, EDown, EDown, EUpleft, EUpleft, EUpleft, EUpleft, EUp},
{EDown, EDownright, EUpright, EUpright, EUpright, EDown, EDown, EUpright, EUpright, EUpright, EUpleft, EUp},
{EDown, EDownright, EUpright, EUpright, EUpright, EUpright, EUpright, EUpright, EUpright, EUpright, EUpright, EUpright},
{EDown, EDownright, ERight, ERight, ERight, ERight, ERight, ERight, ERight, ERight, ERight, ERight},
};

const WickedKnightAction CIRCLE_ACTION_CLOCKWISE_8x8[MOVACT_INRANGE_ARRAYWIDTH][MOVACT_INRANGE_ARRAYWIDTH] = {
{EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget},
{EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget},
{EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget},
{EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightAttack, EWickedKnightAttack, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget},
{EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightAttack, EWickedKnightAttack, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget},
{EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightAttack, EWickedKnightAttack, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightAttack, EWickedKnightAttack, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget},
{EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightAttack, EWickedKnightAttack, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightAttack, EWickedKnightAttack, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget},
{EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightAttack, EWickedKnightAttack, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget},
{EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightAttack, EWickedKnightAttack, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget},
{EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget},
{EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget},
{EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget, EWickedKnightChaseTarget},
};

void wickedknight_walkAroundController(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection);

void wickedknight_huntController(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection);
	
void wickedknight_stunnedController(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection);
	
void wickedknight_getBoundingBoxMoving(const CharacterAttr* character, 
	int *count, BoundingBox *boundingBox);
	

void wickedknight_setCharacter(CharacterAttr* character) {
    character->controller = &wickedknight_walkAroundController; 
}

void wickedknight_doWalk(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection, CharacterAIControl *charControl) {
	Position *position = &character->position;
	BoundingBox searchArea;
	searchArea.startX = CONVERT_2POS(position->x) + wickedknight_scanSurroundingOffset[character->direction][0].x;
	searchArea.startY = CONVERT_2POS(position->y) + wickedknight_scanSurroundingOffset[character->direction][0].y;
	searchArea.endX = CONVERT_2POS(position->x) + wickedknight_scanSurroundingOffset[character->direction][1].x;
	searchArea.endY = CONVERT_2POS(position->y) + wickedknight_scanSurroundingOffset[character->direction][1].y;

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
   
	if (charControl->currentStatus == EWickedKnightAIStateHuntTarget) {
		charControl->currentAction = MAXACTIONS;
		character->controller = &wickedknight_huntController;
		character->controller(character, mapInfo, characterCollection);
		return;
	}
	
	if (charControl->currentStatus == EWickedKnightAIStateStunned) {
		charControl->currentAction = MAXACTIONS;
		character->controller = &wickedknight_stunnedController;
		character->controller(character, mapInfo, characterCollection);
		return;
	}
		
	if (common_shouldDoIntializeActions(character)) {
		character->getBounds = &wickedknight_getBoundingBoxMoving;
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
	character->nextAction = EWickedKnightWalk;
	character->nextDirection = direction;
	character->faceDirection = direction;
	
	if (charControl->leftBlocked | charControl->rightBlocked | 
		charControl->upBlocked | charControl->downBlocked) {
		common_doGoAroundObstacle(&character->position, &charControl->target, charControl, 
			EWickedKnightWalk, 60);
	}
	
	common_doSetActions(charControl, character);
	
	if (charControl->currentAction >= charControl->countAction) {
		//charControl->countAction = 0;
		commonInitializeAISetActions(charControl);
		charControl->currentAction = MAXACTIONS;
		//character->nextDirection = direction;
		//return;
	}
		
	wickedknight_doWalk(character, mapInfo, characterCollection, charControl);
}

void wickedknight_doChaseTarget(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection, CharacterAIControl *charControl) {
	bool isNear;
	EDirections goDirection;
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
		&CIRCLE_TARGET_CLOCKWISE_8x8[0][0], (s8*)&CIRCLE_ACTION_CLOCKWISE_8x8[0][0],
			MOVACT_INRANGE_DIST, MOVACT_INRANGE_ARRAYWIDTH,
		&goDirection, &doAction, &isNear);
	if (!isNear && goDirection == EUnknown) {
		charControl->currentAction = MAXACTIONS;
		charControl->currentStatus = EWickedKnightAIStateWalkAround;
		character->nextAction = EWickedKnightWalk;
		return;
	} else if (isNear) {
		EDirections faceDirection;
		//character->nextAction = EWickedKnightAttack;
		character->nextAction = doAction;
		if (goDirection == ELeft || goDirection == ERight) {
			common_findDirectionOfTargetUpDown(&character->position, &charControl->target, 
			&faceDirection);
		} else if  (goDirection == EUp || goDirection == EDown){
			common_findDirectionOfTargetLeftRight(&character->position, &charControl->target, 
				&faceDirection);		
		} else {
			common_findDirectionOfTarget(&character->position, &charControl->target, 
				&faceDirection);
		}

		character->nextDirection = goDirection;
		if (character->faceDirection != faceDirection) {
			character->hasNewFaceDirection = true;
		}
		character->faceDirection = faceDirection;
		return;
	}
	
	character->nextAction = EWickedKnightChaseTarget;
	
	if (charControl->leftBlocked | charControl->rightBlocked | 
		charControl->upBlocked | charControl->downBlocked) {
		common_doGoAroundObstacle(&character->position, &charControl->target, charControl, 
			EWickedKnightChaseTarget, 60);
		common_doSetActions(charControl, character);
		mprinter_printf("???3 %d\n", character->faceDirection);
		return;
	} else if (charControl->currentAction >= charControl->countAction) {
		//charControl->countAction = 0;
		commonInitializeAISetActions(charControl);
		charControl->currentAction = MAXACTIONS;
		character->nextDirection = goDirection;
		character->faceDirection = goDirection;
		mprinter_printf("???2 %d\n", character->faceDirection);
		return;
	}
	
	character->nextDirection = goDirection;
	character->faceDirection = goDirection;
	mprinter_printf("???1 %d\n", character->faceDirection);
	common_doSetActions(charControl, character);
}

void wickedknight_doAttack(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection, CharacterAIControl *charControl) {
}

void wickedknight_huntController(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection) {
	CharacterAIControl *charControl = (CharacterAIControl*)character->free;
	int distanceX, distanceY, i;
	
	if (charControl->currentStatus == EWickedKnightAIStateWalkAround) {
		charControl->currentAction = MAXACTIONS;
		character->controller = &wickedknight_walkAroundController;
		character->controller(character, mapInfo, characterCollection);
		return;
	}
	
	if (charControl->currentStatus == EWickedKnightAIStateStunned) {
		charControl->currentAction = MAXACTIONS;
		character->controller = &wickedknight_stunnedController;
		character->controller(character, mapInfo, characterCollection);
		return;
	}
	
	if (common_shouldDoIntializeActions(character)) {
		commonInitializeAISetActions(charControl);
		character->nextAction = EWickedKnightChaseTarget;
		wickedknight_doChaseTarget(character, mapInfo, characterCollection, charControl);
	}
	
	if (character->action == EWickedKnightChaseTarget) {
		wickedknight_doChaseTarget(character, mapInfo, characterCollection, charControl);
	} else if (character->action == EWickedKnightAttack) {
		wickedknight_doAttack(character, mapInfo, characterCollection, charControl);
	}
	++charControl->actions[charControl->currentAction].currentFrame;
}

void wickedknight_doStun(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection, CharacterAIControl *charControl) {
}

void wickedknight_stunnedController(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection) {
	CharacterAIControl *charControl = (CharacterAIControl*)character->free;
	int distanceX, distanceY, i;
	
	if (charControl->currentStatus == EWickedKnightAIStateHuntTarget) {
		charControl->currentAction = MAXACTIONS;
		character->controller = &wickedknight_huntController;
		character->controller(character, mapInfo, characterCollection);
		return;
	}
	
	if (common_shouldDoIntializeActions(character)) {
		charControl->countAction = 1;
		charControl->currentAction = 0;
		charControl->actions[0] = ((ActionControl){30, 0, character->direction, EWickedKnightStunned});
		character->nextAction = EWickedKnightStunned;
	}
	
	/*if (character->nextAction == EWickedKnightStunned) {
		wickedknight_doStun(character, mapInfo, characterCollection, charControl);
	} else {
		charControl->currentStatus = EWickedKnightAIStateHuntTarget;
		charControl->currentAction = MAXACTIONS;
		character->controller = &wickedknight_huntController;
		character->controller(character, mapInfo, characterCollection);
	}*/
}

void wickedknight_circleAroundController(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection) {
}