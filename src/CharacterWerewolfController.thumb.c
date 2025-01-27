#include "GBAObject.h"
#include "ManagerPrinter.h"
#include "CharacterCommon.h"
#include "CharacterWerewolf.h"
#include  <stdbool.h>
#include  <stdlib.h>

void werewolf_scanSurroundingsController(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection);
void werewolf_huntTargetController(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection);
void werewolf_goAroundObstacleController(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection);

const EDirections werewolf_patrolDirections[] = {
    EDown, EDownright, ERight, EUpright,
	EUp, EUpleft, ELeft, EDownleft
};

void werewolf_setCharacter(CharacterAttr* character) {
    character->controller = &werewolf_scanSurroundingsController; 
}

void werewolf_scanSurroundingsController(CharacterAttr* character, 
    const MapInfo *mapInfo, const CharacterCollection *charCollection) {
	CharacterAIControl *charControl = (CharacterAIControl*)character->free;
	int i;
   
	//if (charControl->currentStatus == EWerewolfStatusHuntTarget) {
	//	character->controller;
	//	return;
	//}
	
	if (charControl->leftBlocked|charControl->rightBlocked|charControl->upBlocked|charControl->downBlocked) {
		character->controller = werewolf_goAroundObstacleController;
		charControl->currentAction = MAXACTIONS;
		return;
	}
	
	if (common_shouldDoIntializeActions(character)){
		EDirections direction = werewolf_patrolDirections[GET_REMAINDER_8(rand())];
		direction -= direction&1;
		//EDirections direction = character->nextDirection == EUpleft ? EDownright : EUpleft;
		charControl->countAction = 4;//temporary
		charControl->currentAction = 0;
		charControl->actions[0] = ((ActionControl){DOACTIONUNTILEND, 0, direction, EWerewolfFindTarget});
		character->getBounds = &werewolf_getBoundingBoxStanding;
		for (i = 1; i < charControl->countAction; ++i) {
			charControl->actions[i] = ((ActionControl){20, 0, direction, EWerewolfWalk});
		}
		
		character->nextAction = charControl->actions[charControl->currentAction].action;
		character->nextDirection = charControl->actions[charControl->currentAction].direction;
	}
	
	if (common_shouldDoNextAction(character) &&
	    charControl->currentAction < charControl->countAction - 1) {
		++charControl->currentAction;
		character->getBounds = &werewolf_getBoundingBoxMoving;
		character->nextAction = charControl->actions[charControl->currentAction].action;
		character->nextDirection = charControl->actions[charControl->currentAction].direction;
		charControl->actions[charControl->currentAction].currentFrame = 0;
	}
	++charControl->actions[charControl->currentAction].currentFrame;
}

void werewolf_goAroundObstacleController(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection) {
	CharacterAIControl *charControl = (CharacterAIControl*)character->free;
	int nextScreenFrame, nextAnimationFrame;
	bool isLastFrame = false;
   
   commonGetCharacterNextFrame(character, &nextScreenFrame, &nextAnimationFrame, &isLastFrame);
	if (charControl->currentAction >= MAXACTIONS || charControl->currentAction >= charControl->countAction) {
		charControl->currentAction = 0;
		charControl->countAction = 1;
		charControl->actions[0] = ((ActionControl){60, 0, character->direction, EWerewolfWalk});
	}
	
	if (charControl->leftBlocked && character->direction  == ELeft) {
		character->nextDirection = EUp;
	}
	
	if (charControl->rightBlocked && character->direction  == ERight) {
		character->nextDirection = EDown;
	}
	
	if (charControl->upBlocked && character->direction  == EUp) {
		character->nextDirection = ERight;
	}
	
	if (charControl->downBlocked && character->direction == EDown) {
		character->nextDirection = ELeft;
	}
	
	charControl->actions[0].direction = character->nextDirection;
	
	if (common_shouldDoNextAction(character)) {
		charControl->countAction = 0;
		charControl->currentAction = MAXACTIONS;
		charControl->leftBlocked = false;
		charControl->rightBlocked = false;
		charControl->upBlocked = false;
		charControl->downBlocked = false;
		character->controller = &werewolf_scanSurroundingsController;
	}
	
	++charControl->actions[charControl->currentAction].currentFrame;
}

void werewolf_huntTargetController(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection) {
   int nextScreenFrame, nextAnimationFrame;
   bool isLastFrame = false;
   CharacterAIControl *charControl = (CharacterAIControl*)character->free;
   Position *position = &character->position;
   int xDiff = position->x - charControl->target.x;
   int yDiff = position->y - charControl->target.y;
}

void werewolf_remove(CharacterAttr* character, 
    const MapInfo *mapInfo, CharacterCollection *charCollection) {
	//int i;
	mprinter_print("REMOVE\n");
	/*for (i = 0; i < charCollection->currentSize; ++i) {
	    if (charCollection->characters[i] == character) {
		    mprinter_print("POSITION:%d\n", i);
		}
	}*/
}