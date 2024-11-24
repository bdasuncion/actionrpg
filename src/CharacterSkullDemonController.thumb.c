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

const EDirections skulldemon_walkDirections[] = {
    EDown, EDownright, ERight, EUpright,
	EUp, EUpleft, ELeft, EDownleft
};

void skulldemon_walkAroundController(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection);

void skulldemon_getBoundingBoxMoving(const CharacterAttr* character, 
	int *count, BoundingBox *boundingBox);

void skulldemon_setCharacter(CharacterAttr* character) {
    character->controller = &skulldemon_walkAroundController; 
}

void skulldemon_walkAroundController(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection) {
	CharacterAIControl *charControl = (CharacterAIControl*)character->free;
	int i;
	EDirections goDirection;
   
	/*if (charControl->currentStatus == EZombieStatusHuntTarget) {
		charControl->currentAction = MAXACTIONS;
		character->controller = &zombie_huntController;
		zombie_huntController(character, mapInfo, characterCollection);
		return;
	}*/
	
	/*if (charControl->currentStatus == ESkullDemonStatusStunned) {
		charControl->currentAction = MAXACTIONS;
		character->controller = &zombie_isStunnedController;
		zombie_isStunnedController(character, mapInfo, characterCollection);
		return;
	}*/
	
	if (commonDoIntializeActions(character)) {
		//mprinter_printf("INIT\n");
		//EDirections direction;
		//findDirectionOfPosition(&character->position, &charControl->patrolPoints[0], &direction);
		//charControl->patrolIndex = 0;
		//charControl->countAction = 4;
		//charControl->currentAction = 0;
		character->getBounds = &skulldemon_getBoundingBoxMoving;
		//for (i = 0; i < charControl->countAction; ++i) {
		//	charControl->actions[i] = ((ActionControl){20, 0, direction, ESkullDemonWalk});
		//}
		//character->nextAction = ESkullDemonWalk;
		//character->nextDirection = direction;
		//resetBlockedDirection(charControl);
	}
	
	//goDirection = charControl->actions[charControl->currentAction].direction;
	
	//changeDirection(charControl, &goDirection);
		
	//charControl->actions[charControl->currentAction].direction = goDirection;
	//character->nextDirection = goDirection;
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
	//mprinter_printf("PATROL %d\n", charControl->patrolIndex);
	//mprinter_printf("DIRECTION %d\n", character->nextDirection);
	EDirections direction;
	common_findDirectionOfPosition(&character->position, &charControl->wayPoints[charControl->wayPointCurrent], &direction);
	character->nextAction = ESkullDemonWalk;
	character->nextDirection = direction;
		
	//if (commonDoNextAction(character) &&
	//    charControl->currentAction < charControl->countAction - 1) {
	/*if (commonDoNextAction(character)) {
		++charControl->currentAction;
		character->getBounds = &skulldemon_getBoundingBoxMoving;
		character->nextAction = charControl->actions[charControl->currentAction].action;
		character->nextDirection = charControl->actions[charControl->currentAction].direction;
		charControl->actions[charControl->currentAction].currentFrame = 0;
		//resetBlockedDirection(charControl);
	}
	++charControl->actions[charControl->currentAction].currentFrame;*/
}