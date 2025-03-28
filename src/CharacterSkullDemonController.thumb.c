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
	
void skulldemon_getBoundingBoxMoving(const CharacterAttr* character, 
	int *count, BoundingBox *boundingBox);
	

void skulldemon_setCharacter(CharacterAttr* character) {
    character->controller = &skulldemon_walkAroundController; 
}

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
	
	if (charControl->currentStatus == ESkullDemonAIStateStunned) {
		charControl->currentAction = MAXACTIONS;
		character->controller = &skulldemon_stunnedController;
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
			ESkullDemonWalk, 60);
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
	EDirections goDirection;

	charControl->target = *commonFindCharTypePositionByDistance(characterCollection,
		&character->position, MAX_DIST_FOR_CHASE, STARTPLAYABLECHARTYPE, ENDPLAYABLECHARACTERTYPE);
	
	if (!commonIsFoundPosition(&charControl->target)) {
		charControl->currentStatus = ESkullDemonAIStateWalkAround;
		character->nextAction = ESkullDemonWalk;
		return;
	}
	
	common_findDirectionOfTargetCharacterInScreen(&character->position, 
		&charControl->target, &goDirection, &isNear);
	if (!isNear && goDirection == EUnknown) {
		charControl->currentAction = MAXACTIONS;
		charControl->currentStatus = ESkullDemonAIStateWalkAround;
		character->nextAction = ESkullDemonWalk;
		return;
	} else if (isNear) {
		character->nextAction = ESkullDemonAttack;
		character->nextDirection = goDirection;
		return;
	}
	
	character->nextAction = ESkullDemonChaseTarget;
	
	if (charControl->leftBlocked | charControl->rightBlocked | 
		charControl->upBlocked | charControl->downBlocked) {
		common_doGoAroundObstacle(&character->position, &charControl->target, charControl, 
			ESkullDemonChaseTarget, 60);
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
	
	if (charControl->currentStatus == ESkullDemonAIStateStunned) {
		charControl->currentAction = MAXACTIONS;
		character->controller = &skulldemon_stunnedController;
		character->controller(character, mapInfo, characterCollection);
		return;
	}
	
	if (common_shouldDoIntializeActions(character)) {
		commonInitializeAISetActions(charControl);
		character->nextAction = ESkullDemonChaseTarget;
		skulldemon_doChaseTarget(character, mapInfo, characterCollection, charControl);
	}
	
	if (character->action == ESkullDemonChaseTarget) {
		skulldemon_doChaseTarget(character, mapInfo, characterCollection, charControl);
	} else if (character->action == ESkullDemonAttack) {
		skulldemon_doAttack(character, mapInfo, characterCollection, charControl);
	}
	++charControl->actions[charControl->currentAction].currentFrame;
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