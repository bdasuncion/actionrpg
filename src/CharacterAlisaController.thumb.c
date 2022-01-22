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
		return;
	}
	
	if (direction != EUnknown) {
		character->nextAction = EAlisaRun;
		character->nextDirection = direction;
		return;
	}
	
	character->nextAction = EAlisaStand;
}

void alisa_slashController(CharacterAttr* character) {
   int nextScreenFrame, nextAnimationFrame;
   bool isLastFrame = false;
   
   //TODO: This should check for action difference for the first frame
   commonGetNextFrame(character, &nextScreenFrame, &nextAnimationFrame, &isLastFrame);
	
   if (isLastFrame) {
	    character->controller = &alisa_controller;
	}
}
