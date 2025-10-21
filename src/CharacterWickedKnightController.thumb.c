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

	charControl->target = *commonFindCharTypePositionByDistance(characterCollection,
		&character->position, MAX_DIST_FOR_CHASE, STARTPLAYABLECHARTYPE, ENDPLAYABLECHARACTERTYPE);
	
	if (!commonIsFoundPosition(&charControl->target)) {
		charControl->currentStatus = EWickedKnightAIStateWalkAround;
		character->nextAction = EWickedKnightWalk;
		return;
	}
	
	common_findDirectionOfTargetCharacterInScreen(&character->position, 
		&charControl->target, &goDirection, &isNear);
	if (!isNear && goDirection == EUnknown) {
		charControl->currentAction = MAXACTIONS;
		charControl->currentStatus = EWickedKnightAIStateWalkAround;
		character->nextAction = EWickedKnightWalk;
		return;
	} else if (isNear) {
		character->nextAction = EWickedKnightAttack;
		character->nextDirection = goDirection;
		return;
	}
	
	character->nextAction = EWickedKnightChaseTarget;
	
	if (charControl->leftBlocked | charControl->rightBlocked | 
		charControl->upBlocked | charControl->downBlocked) {
		common_doGoAroundObstacle(&character->position, &charControl->target, charControl, 
			EWickedKnightChaseTarget, 60);
		common_doSetActions(charControl, character);
		return;
	} else if (charControl->currentAction >= charControl->countAction) {
		//charControl->countAction = 0;
		commonInitializeAISetActions(charControl);
		charControl->currentAction = MAXACTIONS;
		character->nextDirection = goDirection;
		return;
	}
	
	character->nextDirection = goDirection;
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