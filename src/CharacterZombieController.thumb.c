#include "GBAObject.h"
#include "GBACharacter.h"
#include "GBAMap.h"
#include "CharacterZombie.h"
#include  <stdbool.h>

#define DIST_OFFSET 80

const EDirections zombie_walkDirections[] = {
    EDown, EDownright, ERight, EUpright,
	EUp, EUpleft, ELeft, EDownleft
};

void zombie_walkAroundController(CharacterAttr* character);
void zombie_huntController(CharacterAttr* character);
void zombie_isStunnedController(CharacterAttr* character);

void zombie_setCharacter(CharacterAttr* character) {
    character->controller = &zombie_walkAroundController; 
}

void zombie_getBoundingBoxMoving(const CharacterAttr* character, int *count, BoundingBox *boundingBox);
void zombie_getBoundingBoxStanding(const CharacterAttr* character, int *count, BoundingBox *boundingBox);

void changeDirection(CharacterAIControl *charControl, EDirections *goDirection) {
	if (*goDirection == EUnknown) {
		return;
	}
	if(charControl->leftBlocked) {
		*goDirection = EUp;
	}
	if(charControl->rightBlocked) {
		*goDirection = EDown;
	}
	if(charControl->upBlocked) {
		*goDirection = ERight;
	}
	if(charControl->downBlocked) {
		*goDirection = ELeft;
	}
}

void resetBlockedDirection(CharacterAIControl *charControl) {
	charControl->leftBlocked = false;
	charControl->rightBlocked = false;
	charControl->upBlocked = false;
	charControl->downBlocked = false;
}

void zombie_walkAroundController(CharacterAttr* character) {
	CharacterAIControl *charControl = (CharacterAIControl*)character->free;
	int i;
	EDirections goDirection;
   
	if (charControl->currentStatus == EZombieStatusHuntTarget) {
		charControl->currentAction = MAXACTIONS;
		character->controller = &zombie_huntController;
		zombie_huntController(character);
		return;
	}
	
	if (charControl->currentStatus == EZombieStatusStunned) {
		charControl->currentAction = MAXACTIONS;
		character->controller = &zombie_isStunnedController;
		zombie_isStunnedController(character);
		return;
	}
	
	if (commonDoIntializeActions(character)) { 
		EDirections direction = zombie_walkDirections[GET_REMAINDER_8(rand())];
		direction -= direction&1;
		charControl->countAction = 4;
		charControl->currentAction = 0;
		character->getBounds = &zombie_getBoundingBoxMoving;
		for (i = 0; i < charControl->countAction; ++i) {
			charControl->actions[i] = ((ActionControl){20, 0, direction, EZombieWalk});
		}
		character->nextAction = charControl->actions[charControl->currentAction].action;
		character->nextDirection = charControl->actions[charControl->currentAction].direction;
		resetBlockedDirection(charControl);
	}
	
	goDirection = charControl->actions[charControl->currentAction].direction;
	
	changeDirection(charControl, &goDirection);
		
	charControl->actions[charControl->currentAction].direction = goDirection;
	character->nextDirection = goDirection;
	
	if (commonDoNextAction(character) &&
	    charControl->currentAction < charControl->countAction - 1) {
		++charControl->currentAction;
		character->getBounds = &zombie_getBoundingBoxMoving;
		character->nextAction = charControl->actions[charControl->currentAction].action;
		character->nextDirection = charControl->actions[charControl->currentAction].direction;
		charControl->actions[charControl->currentAction].currentFrame = 0;
		resetBlockedDirection(charControl);
	}
	++charControl->actions[charControl->currentAction].currentFrame;
}

const EDirections FAR_TARGET[5][5] = {
 {EUpleft, EUpleft, EUp, EUpright, EUpright},
 {EUpleft, EUpleft, EUp, EUpright, EUpright},
 {ELeft, ELeft, EUnknown, ERight, ERight},
 {EDownleft, EDownleft, EDown, EDownright, EDownright},
 {EDownleft, EDownleft, EDown, EDownright, EDownright}
};

const EDirections NEAR_TARGET[5][5] = {
 {EUpleft, EUpleft, EUp, EUpright, EUpright},
 {EUpleft, EUpleft, EUp, EUpright, EUpright},
 {ELeft, ELeft, EUnknown, ERight, ERight},
 {EDownleft, EDownleft, EDown, EDownright, EDownright},
 {EDownleft, EDownleft, EDown, EDownright, EDownright}
};

void findAttackDirection(const Position *charPosition, const Position *target, EDirections *direction) {
	int xDist = CONVERT_2POS(charPosition->x) - CONVERT_2POS(target->x);
	int yDist = CONVERT_2POS(charPosition->y) - CONVERT_2POS(target->y);
	EDirections xDirection, yDirection;
	xDirection = (xDist > 0)*(ELeft) + (!(xDist > 0))*(ERight);
	yDirection = (yDist > 0)*(EUp) + (!(yDist > 0))*(EDown);
	
	xDist *= (xDist > 0) + (!(xDist > 0))*(-1);
	yDist *= (yDist > 0) + (!(yDist > 0))*(-1);
	
	*direction = (xDist > yDist)*xDirection + (!(xDist > yDist))*yDirection; 
}

void zombie_huntController(CharacterAttr* character) {
	CharacterAIControl *charControl = (CharacterAIControl*)character->free;
	int distanceX, distanceY, i;
	
	if (charControl->currentStatus == EZombieStatusWalkAround) {
		charControl->currentAction = MAXACTIONS;
		character->controller = &zombie_walkAroundController;
		zombie_walkAroundController(character);
		return;
	}
	
	if (charControl->currentStatus == EZombieStatusStunned) {
		charControl->currentAction = MAXACTIONS;
		character->controller = &zombie_isStunnedController;
		zombie_isStunnedController(character);
		return;
	}
	
	if (commonDoIntializeActions(character)) {
		charControl->countAction = 4;
		charControl->currentAction = 0;
		
		for (i = 0; i < charControl->countAction; ++i) {
			charControl->actions[i] = ((ActionControl){25, 0, EUp, EZombieChaseTarget});
		}
	}
		
	distanceX = CONVERT_2POS(charControl->target.x) - CONVERT_2POS(character->position.x) + DIST_OFFSET;
	distanceY = CONVERT_2POS(charControl->target.y) - CONVERT_2POS(character->position.y) + DIST_OFFSET;
	
	if (charControl->actions[charControl->currentAction].action != EZombieAttack && (distanceX < DIST_OFFSET*2 && distanceX >= 0) && (distanceY < DIST_OFFSET*2 && distanceY >= 0)) {
		EDirections goDirection;
		distanceX = DIVIDE_BY_32(distanceX);
		distanceY = DIVIDE_BY_32(distanceY);
		
		goDirection = FAR_TARGET[distanceY][distanceX];
		
		if (goDirection == EUnknown) {
			findAttackDirection(&character->position, &charControl->target, &goDirection);
			character->nextAction = EZombieAttack;
			charControl->actions[charControl->currentAction] = ((ActionControl){DOACTIONUNTILEND, 
				0, goDirection, EZombieAttack});
		} else {
			changeDirection(charControl, &goDirection);
			charControl->actions[charControl->currentAction].direction = goDirection;
		}
		
		character->getBounds = &zombie_getBoundingBoxMoving;
		character->nextAction = charControl->actions[charControl->currentAction].action;
		character->nextDirection = charControl->actions[charControl->currentAction].direction;
		//charControl->actions[charControl->currentAction].currentFrame = 0;*/
	}
	
	if (commonDoNextAction(character) &&
	    charControl->currentAction < charControl->countAction - 1) {
		resetBlockedDirection(charControl);
		++charControl->currentAction;
		character->getBounds = &zombie_getBoundingBoxMoving;
		character->nextAction = charControl->actions[charControl->currentAction].action;
		character->nextDirection = charControl->actions[charControl->currentAction].direction;
		charControl->actions[charControl->currentAction].currentFrame = 0;
	}
	++charControl->actions[charControl->currentAction].currentFrame;
}

void zombie_isStunnedController(CharacterAttr* character) {
	CharacterAIControl *charControl = (CharacterAIControl*)character->free;
	int distanceX, distanceY, i;
	
	if (commonDoIntializeActions(character)) {
		charControl->countAction = 1;
		charControl->currentAction = 0;
		
		character->stats.currentStatus = EStatusNoActionCollision;
		charControl->actions[charControl->currentAction] = ((ActionControl){30, 0, character->direction, EZombieStunned});
		
		character->nextAction = charControl->actions[charControl->currentAction].action;
		character->nextDirection = charControl->actions[charControl->currentAction].direction;
	}
	++charControl->actions[charControl->currentAction].currentFrame;
	
	if (commonDoNextAction(character)) {
	    charControl->currentAction = MAXACTIONS;
		character->controller = &zombie_huntController;
		character->stats.currentStatus = EStatusNormal;
		charControl->currentStatus = EZombieStatusHuntTarget;
		zombie_huntController(character);
		return;
	}
}