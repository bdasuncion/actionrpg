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

#define DOWN_DIRECTION -4
#define UP_DIRECTION 4
#define RIGHT_DIRECTION -4
#define LEFT_DIRECTION 4
#define FAR_DIST_OFFSET 80
//#define FAR_DIST_OFFSET 100
#define NEAR_DIST_OFFSET 20

void findDirection(Position *current, Position *targetPos, EDirections *goDirection) {	
	int distanceX = targetPos->x - current->x;
	int distanceY = targetPos->y - current->y;

	//mprinter_printf("CURRENT %d %d %d\n", current->x , current->y, current->z);
	//mprinter_printf("TARGET %d %d %d\n", targetPos->x , targetPos->y, targetPos->z);
	mprinter_printf("TARGET Y %d CURRENT Y %d\n", targetPos->y, current->y);
	mprinter_printf("X %d Y %d\n", distanceX , distanceY);
	if (abs(distanceX) > FAR_DIST_OFFSET || abs(distanceY) > FAR_DIST_OFFSET) {
		if (abs(distanceX) > abs(distanceY)) {
			if (distanceX < 0) {
				*goDirection = ELeft;
			} else {
				*goDirection = ERight;
			}
		} else {
			if (distanceY < 0) {
				*goDirection = EUp;
			} else {
				*goDirection = EDown;
			}
		}
	}
	
	distanceX += FAR_DIST_OFFSET;
	distanceY += FAR_DIST_OFFSET;
	
	distanceX = DIVIDE_BY_32(distanceX);
	distanceY = DIVIDE_BY_32(distanceY);
	mprinter_printf("X %d Y %d\n", distanceX , distanceY);
	
	if (distanceX < 0 || distanceX > 5) {
	}
	
	if (distanceY < 0 || distanceY > 5) {
	}
	
	*goDirection = FAR_TARGET[distanceY][distanceX];
	if (*goDirection == EUnknown) {
		distanceX = targetPos->x - current->x + NEAR_DIST_OFFSET;
		distanceY = targetPos->y - current->y + NEAR_DIST_OFFSET;
		distanceX = DIVIDE_BY_8(distanceX);
		distanceY = DIVIDE_BY_8(distanceY);

		*goDirection = NEAR_TARGET[distanceY][distanceX];
	}
}

void findDirectionOfTarget(Position *current, Position *target, EDirections *goDirection) {
	Position currentConverted = {CONVERT_2POS(current->x), CONVERT_2POS(current->y), CONVERT_2POS(current->z)};
	Position targetConverted = {CONVERT_2POS(target->x), CONVERT_2POS(target->y), CONVERT_2POS(target->z)};
	
	findDirection(&currentConverted, &targetConverted, goDirection);
}

void findDirectionOfPosition(Position *current, Position *targetPos, EDirections *goDirection) {
	Position currentConverted = {CONVERT_2POS(current->x), CONVERT_2POS(current->y), CONVERT_2POS(current->z)};
	
	findDirection(&currentConverted, targetPos, goDirection);
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
	bool hasArrived = commonHasReachedWaypoint(&charControl->patrolPoints[charControl->patrolIndex], &boundingBox);
	
	if (hasArrived) {
		mprinter_printf("ARRIVAL\n");
		++charControl->patrolIndex;
		if (charControl->patrolIndex >= charControl->patrolCnt) {
			charControl->patrolIndex= 0;
		}
	}
	//mprinter_printf("PATROL %d\n", charControl->patrolIndex);
	//mprinter_printf("DIRECTION %d\n", character->nextDirection);
	EDirections direction;
	findDirectionOfPosition(&character->position, &charControl->patrolPoints[charControl->patrolIndex], &direction);
	mprinter_printf("DIRECTION %d\n", direction);
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