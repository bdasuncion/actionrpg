#include "GBAObject.h"
#include "GBAKey.h"
#include "CharacterAlisa.h"
#include  <stdbool.h>
#include  <stdlib.h>

#define MAX_BUTTON_INTERVAL 30
#define MAX_STUN_ANIMATION 30
#define ALISA_NORMALATTACK_INTERVALMAX 8

#define ALISA_MIN_BACKWARD_DASH 4

void alisa_stunnedController(CharacterAttr* character);
void alisa_slashController(CharacterAttr* character);
void alisa_prepareDashController(CharacterAttr* character);
void alisa_dashForwardController(CharacterAttr* character);
void alisa_dashBackwardController(CharacterAttr* character);
void alisa_fallingDownController(CharacterAttr* character);

const EDirections DEFAULT_DIRECTIONMAP[EDirectionsCount] = {
	EDown,EDown,ERight,EUp,EUp,EUp,ELeft,EDown
};

ControlMap alisaControlMap = {
	&alisa_slashController, NULL, NULL, NULL
};

bool controlButtonCheck(CharacterAttr* character) {
	CharacterPlayerControl *charControl = (CharacterPlayerControl*)character->free;
	if (!isBPressed()) {
		charControl->buttonB_PressInterval = 0;
	}
	
	if (!isAPressed()) {
		charControl->buttonA_PressInterval = 0;
	}
	
	if (!isLPressed()) {
		charControl->buttonL_Ready = true;
	}
	
	if (!isRPressed()) {
		charControl->buttonR_Ready = true;
	}

	if (isBPressed()) {
		bool isInit = charControl->buttonB_PressInterval == 0;
		if (isInit) {
			character->controller = charControl->controlMap.buttonB;
		}
		charControl->buttonB_PressInterval += 1*(charControl->buttonB_PressInterval < MAX_BUTTON_INTERVAL);
		return isInit;
	}
	
	if (isAPressed()) {
		bool isInit = charControl->buttonA_PressInterval == 0;
		if (isInit) {
			character->controller = charControl->controlMap.buttonA;
		}
		charControl->buttonA_PressInterval += 1*(charControl->buttonA_PressInterval < MAX_BUTTON_INTERVAL);
		return isInit;
	}
	
	if (isLPressed() && charControl->buttonL_Ready) {
		//charControl->buttonL_Ready = false;
		character->controller = charControl->controlMap.buttonL;
	}
	
	/*if (isRPressed() && charControl->buttonR_Ready) {
		charControl->buttonR_Ready = false;
	}*/
	
	return false;
};

bool controlButtonHold(CharacterPlayerControl *control, const CharFuncController functionToFind, 
	int *holdInterval, int intervalMax) {
	//if (functionToFind == alisaControlMap.buttonB) {
	if (functionToFind == control->controlMap.buttonB) {
		if (!isBPressed()) {
			*holdInterval = control->buttonB_PressInterval;
			control->buttonB_PressInterval = 0;
			return true;
		} else if (isBPressed()){
			control->buttonB_PressInterval += 1*(control->buttonB_PressInterval < MAX_BUTTON_INTERVAL);
		}
		
		*holdInterval = control->buttonB_PressInterval;
		if (control->buttonB_PressInterval >= intervalMax) {
			return true;
		}
	}
	
	return false;
}

void alisa_setCharacter(CharacterAttr* character) {
	character->controller = &alisa_controller; 
}

bool alisa_isStunned(CharacterAttr* character, CharacterPlayerControl *charControl) {
	if (charControl->currentStatus == EAlisaStatusStunned) {
		character->controller = &alisa_stunnedController; 
		alisa_stunnedController(character);
		return true;
	}
	return false;
}

bool alisa_isFalling(CharacterAttr* character, CharacterPlayerControl *charControl) {
	if (character->nextAction == EAlisaFallingDown) {
		character->controller = &alisa_fallingDownController; 
		alisa_fallingDownController(character);
		return true;
	}
	
	return false;
}

bool alisa_hasLanded(CharacterAttr* character, CharacterPlayerControl *charControl) {
	if (character->nextAction != EAlisaFallingDown) {
		character->controller = &alisa_controller;
		character->controller(character, NULL, NULL);
	}
	return false;
}

void alisa_controller(CharacterAttr* character) {	
	EDirections direction = KEYPRESS_DIRECTION;
	CharacterPlayerControl *charControl = (CharacterPlayerControl*)character->free;
	character->distanceFromGround = 1024;

	if (alisa_isInterruptAction(character, charControl)) {
		return;
	}
	
	if (controlButtonCheck(character)) {
		character->controller(character, NULL, NULL);
		return;
	}

	character->stats.currentStatus = EStatusNormal;
	
	if (direction != EUnknown) {
		character->nextAction = EAlisaRun;
		character->nextDirection = direction;
		if (!((direction == EUpleft | direction == EDownleft) & character->faceDirection == ELeft) && 
			!((direction == EUpright | direction == EDownright) & character->faceDirection == ERight)) {
			character->faceDirection = DEFAULT_DIRECTIONMAP[direction];
		}
		//character->faceDirection = DEFAULT_DIRECTIONMAP[direction];
		character->getBounds = &alisa_getBoundingBoxMoving;
		return;
	}
	
	character->getBounds = &alisa_getBoundingBoxStanding;
	character->nextAction = EAlisaStand;
}

void alisa_slashController(CharacterAttr* character) {
   int nextScreenFrame, nextAnimationFrame, hold;
   bool isLastFrame = false;
   CharacterPlayerControl *charControl = (CharacterPlayerControl*)character->free;
   character->distanceFromGround = 1024;
   
   	if (alisa_isInterruptAction(character, charControl)) {
		return;
	}
	
	character->stats.currentStatus = EStatusNormal;
	character->getBounds = &alisa_getBoundingBoxStanding;
	
	if (controlButtonHold(charControl, &alisa_slashController, &hold, ALISA_NORMALATTACK_INTERVALMAX) &&
		(character->nextAction != EAlisaNormalSwordSlash && character->nextAction != EAlisaStrongSwordSlash)) {
		//TODO Add strong attack for when normal attack threshhold is reached
		if (hold >= ALISA_NORMALATTACK_INTERVALMAX) {
			character->nextAction = EAlisaStrongSwordSlash;
		} else {
			character->nextAction = EAlisaNormalSwordSlash;
		}
	}
	
	if (character->nextAction == EAlisaNormalSwordSlash || character->nextAction == EAlisaStrongSwordSlash) {
		commonGetNextFrame(character, &nextScreenFrame, &nextAnimationFrame, &isLastFrame);
//		mprinter_printf("%s\n", character->nextAction == EAlisaNormalSwordSlash ? "NORMAL": "STRONG");
		if (isLastFrame) {
			character->controller = &alisa_controller;
			character->controller(character, NULL, NULL);
		}
		return;
	}
	
	character->nextAction = EAlisaStand;
}

void alisa_prepareDashController(CharacterAttr* character) {
    EDirections direction = KEYPRESS_DIRECTION;
    int nextScreenFrame, nextAnimationFrame, hold;
    bool isLastFrame = false;
    CharacterPlayerControl *charControl = (CharacterPlayerControl*)character->free;
      
   	if (alisa_isStunned(character, charControl)) {
		return;
	}
	
	character->stats.currentStatus = EStatusNormal;
	character->getBounds = &alisa_getBoundingBoxMoving;
	
	character->nextAction = EAlisaPrepareDash;
	
	if (direction != EUnknown) {
		character->nextDirection = direction;
		EDirections clockwise = (character->faceDirection - 1)&EDirectionsMax;
		EDirections counterClockwise = (character->faceDirection + 1)&EDirectionsMax;
		if (direction != character->faceDirection & 
			direction != clockwise & direction != counterClockwise &
			character->spriteDisplay.numberOfFramesPassed >= ALISA_MIN_BACKWARD_DASH &
			character->nextAction == character->action) {
			character->controller = &alisa_dashBackwardController;
			character->controller(character, NULL, NULL);
			return;
		}
	}
	
	commonGetNextFrame(character, &nextScreenFrame, &nextAnimationFrame, &isLastFrame);

//	mprinter_printf("FRAMES %d %d %d\n", nextScreenFrame, nextAnimationFrame,  isLastFrame);
	if (isLastFrame) {
		character->controller = &alisa_dashForwardController;
		character->controller(character, NULL, NULL);
	}
}

void alisa_dashForwardController(CharacterAttr* character) {
   int nextScreenFrame, nextAnimationFrame, hold;
   bool isLastFrame = false;
   CharacterPlayerControl *charControl = (CharacterPlayerControl*)character->free;
      
   	if (alisa_isStunned(character, charControl)) {
		return;
	}
	
	character->stats.currentStatus = EStatusNormal;
	character->getBounds = &alisa_getBoundingBoxMoving;
	
	character->nextAction = EAlisaDashForward;
	
	commonGetNextFrame(character, &nextScreenFrame, &nextAnimationFrame, &isLastFrame);

	if (isLastFrame) {
		character->controller = &alisa_controller;
	}
}

void alisa_dashBackwardController(CharacterAttr* character) {
   int nextScreenFrame, nextAnimationFrame, hold;
   bool isLastFrame = false;
   CharacterPlayerControl *charControl = (CharacterPlayerControl*)character->free;
      
    if (alisa_isStunned(character, charControl)) {
		return;
	}
	
	character->stats.currentStatus = EStatusNormal;
	character->getBounds = &alisa_getBoundingBoxMoving;
	
	character->nextAction = EAlisaDashBackward;
	
	commonGetNextFrame(character, &nextScreenFrame, &nextAnimationFrame, &isLastFrame);

	//mprinter_printf("FRAMES %d %d %d\n", nextScreenFrame, nextAnimationFrame,  isLastFrame);
	if (isLastFrame) {
		character->nextDirection = character->faceDirection;
		character->controller = &alisa_controller;
		character->controller(character, NULL, NULL);
	}
}

void alisa_jumpController(CharacterAttr* character) {
   //EDirections direction = KEYPRESS_DIRECTION;
   int nextScreenFrame, nextAnimationFrame, hold;
   bool isLastFrame = false;
   CharacterPlayerControl *charControl = (CharacterPlayerControl*)character->free;
    character->distanceFromGround = 1024;
 
	if (alisa_isStunned(character, charControl)) {
		return;
	}
	
    if (alisa_hasLanded(character, charControl)) {
		return;
	}
	
	character->getBounds = &alisa_getBoundingBoxMoving;
	
	character->nextAction = EAlisaJump;
	
	commonGetNextFrame(character, &nextScreenFrame, &nextAnimationFrame, &isLastFrame);
	if (isLastFrame) {
		//mprinter_printf("")
		character->nextDirection = character->direction;
		character->nextAction = EAlisaFallingDown;
		character->controller = &alisa_fallingDownController;
		character->controller(character, NULL, NULL);
	}
}

void alisa_fallingDownController(CharacterAttr* character) {
   int nextScreenFrame, nextAnimationFrame, hold;
   bool isLastFrame = false;
   CharacterPlayerControl *charControl = (CharacterPlayerControl*)character->free;
   character->distanceFromGround = 1024;

   	if (alisa_isStunned(character, charControl)) {
		return;
	}
   
	if (alisa_hasLanded(character, charControl)) {
		return;
	}
   
	character->nextAction = EAlisaFallingDown;
}

void alisa_stunnedController(CharacterAttr* character) {
	int nextScreenFrame, nextAnimationFrame;
	bool isLastFrame = false;
	CharacterPlayerControl *charControl = (CharacterPlayerControl*)character->free;
	
	//mprinter_printf("ACTIONS %d %d\n", character->nextAction, character->action);
	commonGetNextFrame(character, &nextScreenFrame, &nextAnimationFrame, &isLastFrame);
	
	//mprinter_printf("SCREEN %d %d\n", nextScreenFrame, MAX_STUN_ANIMATION);
	if (nextScreenFrame > MAX_STUN_ANIMATION) {
		charControl->currentStatus = EAlisaStatusNormal;
		character->controller = &alisa_controller;
		//alisa_controller(character);
		return;
	}
	
	character->getBounds = &alisa_getBoundingBoxStanding;
	character->nextAction = EAlisaStunned;
	character->stats.currentStatus = EStatusNoActionCollision;
}
