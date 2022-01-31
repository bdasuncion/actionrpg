#include "GBAObject.h"
#include "CharacterWerewolf.h"
#include  <stdbool.h>

void werewolf_scanSurroundingsController(CharacterAttr* character, 
    const MapInfo *mapInfo, CharacterCollection *charCollection);
void werewolf_findTargetController(CharacterAttr* character);

const EDirections werewolf_patrolDirections[] = {
    EDown, EDown, ERight, ERight,
	EUp, EUp, ELeft, ELeft
};

void werewolf_setCharacter(CharacterAttr* character) {
    character->controller = &werewolf_scanSurroundingsController; 
}

void werewolf_scanSurroundingsController(CharacterAttr* character, 
    const MapInfo *mapInfo, CharacterCollection *charCollection) {
	CharacterAIControl *charControl = (CharacterAIControl*)character->free;
	int i;
   
	if (charControl->currentAction >= MAXACTIONS || charControl->currentAction >= charControl->countAction) { 
		EDirections direction = werewolf_patrolDirections[GET_REMAINDER_8(rand())];
		//EDirections direction = character->nextDirection == EUpleft ? EDownright : EUpleft;
		charControl->countAction = 4;//temporary
		charControl->currentAction = 0;
		charControl->actions[0] = ((ActionControl){DOACTIONUNTILEND, 0, direction, EWerewolfFindTarget});
		//charControl->doAction = false;
		character->controller = &werewolf_findTargetController;
		character->getBounds = &werewolf_getBoundingBoxStanding;
		//charControl->actions[0] = ((ActionControl){255, 0, direction, EWerewolfFindTarget});
		for (i = 1; i < charControl->countAction; ++i) {
			charControl->actions[i] = ((ActionControl){20, 0, direction, EWerewolfWalk});
			//charControl->actions[i] = ((ActionControl){DOACTIONUNTILEND, 0, direction, EWerewolfWalk});
		}
		
		character->nextAction = charControl->actions[charControl->currentAction].action;
		character->nextDirection = charControl->actions[charControl->currentAction].direction;
	}
	
	//character->nextAction = charControl->actions[0].action;
	//character->nextDirection = charControl->actions[0].direction;
	//charControl->actions[0].currentFrame = 0;
	//mprinter_printf("IS DO LAST FRAME? %s\n", isLastFrame ? "YES": "NO");
	if (commonDoNextAction(character) &&
	    charControl->currentAction < charControl->countAction) {
		character->getBounds = &werewolf_getBoundingBoxMoving;
		character->nextAction = charControl->actions[charControl->currentAction].action;
		character->nextDirection = charControl->actions[charControl->currentAction].direction;
		charControl->actions[charControl->currentAction].currentFrame = 0;
		++charControl->currentAction;
	}
	++charControl->actions[charControl->currentAction].currentFrame;
}

void werewolf_findTargetController(CharacterAttr* character) {
   int nextScreenFrame, nextAnimationFrame;
   bool isLastFrame = false;
   CharacterAIControl *charControl = (CharacterAIControl*)character->free;
   
   commonGetNextFrame(character, &nextScreenFrame, &nextAnimationFrame, &isLastFrame);
	
   if (isLastFrame) {
	    character->controller = &werewolf_scanSurroundingsController;
		//charControl->doAction = true;
		++charControl->currentAction;
	}
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