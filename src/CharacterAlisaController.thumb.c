#include "GBAObject.h"
#include "GBAKey.h"
#include "CharacterAlisa.h"
#include  <stdbool.h>

void alisa_setCharacter(CharacterAttr* character) {
	character->controller = &alisa_controller; 
}

void alisa_controller(CharacterAttr* character) {	
	EDirections direction = KEYPRESS_DIRECTION;
	
	if (isBPressed()) {
	    character->nextAction = EAlisaNormalSwordSlash;
		character->controller = &alisa_slashController; 
		character->getBounds = &alisa_getBoundingBoxStanding;
		return;
	}
	
	if (direction != EUnknown) {
		character->nextAction = EAlisaRun;
		character->nextDirection = direction;
		character->getBounds = &alisa_getBoundingBoxMoving;
		return;
	}
	
	character->getBounds = &alisa_getBoundingBoxStanding;
	character->nextAction = EAlisaStand;
}

void alisa_slashController(CharacterAttr* character) {
   int nextScreenFrame, nextAnimationFrame;
   bool isLastFrame = false;
   
   commonGetNextFrame(character, &nextScreenFrame, &nextAnimationFrame, &isLastFrame);
	
   if (isLastFrame) {
	    character->controller = &alisa_controller;
	}
}
