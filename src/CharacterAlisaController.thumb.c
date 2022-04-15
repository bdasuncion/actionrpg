#include "GBAObject.h"
#include "GBAKey.h"
#include "CharacterAlisa.h"
#include  <stdbool.h>
#include  <stdlib.h>

#define MAX_BUTTON_INTERVAL 30
#define MAX_STUN_ANIMATION 30
#define ALISA_NORMALATTACK_THRESHHOLD 15
void alisa_stunnedController(CharacterAttr* character);
void alisa_slashController(CharacterAttr* character);


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
	
	/*if (isAPressed() && charControl->buttonA_Ready) {
		charControl->buttonA_Ready = false;
	}
	
	if (isLPressed() && charControl->buttonL_Ready) {
		charControl->buttonL_Ready = false;
	}
	
	if (isRPressed() && charControl->buttonR_Ready) {
		charControl->buttonR_Ready = false;
	}*/
	
	return false;
};

bool controlButtonHold(CharacterPlayerControl *control, const CharFuncController functionToFind, 
	int *holdInterval, int threshhold) {
	if (functionToFind == alisaControlMap.buttonB) {
		if (!isBPressed()) {
			*holdInterval = control->buttonB_PressInterval;
			control->buttonB_PressInterval = 0;
			return true;
		} else if (isBPressed()){
			control->buttonB_PressInterval += 1*(control->buttonB_PressInterval < MAX_BUTTON_INTERVAL);
		}
		
		if (control->buttonB_PressInterval >= threshhold) {
			return true;
		}
	}
	
	return false;
}

void alisa_setCharacter(CharacterAttr* character) {
	character->controller = &alisa_controller; 
}

void alisa_controller(CharacterAttr* character) {	
	EDirections direction = KEYPRESS_DIRECTION;
	CharacterPlayerControl *charControl = (CharacterPlayerControl*)character->free;

	if (charControl->currentStatus == EAlisaStatusStunned) {
		character->controller = &alisa_stunnedController; 
		alisa_stunnedController(character);
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
      
   	if (charControl->currentStatus == EAlisaStatusStunned) {
		alisa_stunnedController(character);
		character->controller = &alisa_stunnedController; 
		character->getBounds = &alisa_getBoundingBoxStanding;
		return;
	}
	
	character->stats.currentStatus = EStatusNormal;
	character->getBounds = &alisa_getBoundingBoxStanding;
	
	if (controlButtonHold(charControl, &alisa_slashController, &hold, ALISA_NORMALATTACK_THRESHHOLD) &&
		character->nextAction != EAlisaNormalSwordSlash) {
		//TODO Add strong attack for when normal attack threshhold is reached
		character->nextAction = EAlisaNormalSwordSlash;
	}
	
	if (character->nextAction == EAlisaNormalSwordSlash) {
		commonGetNextFrame(character, &nextScreenFrame, &nextAnimationFrame, &isLastFrame);

		if (isLastFrame) {
			character->controller = &alisa_controller;
		}
		return;
	}
	
	character->nextAction = EAlisaStand;
}

void alisa_stunnedController(CharacterAttr* character) {
	int nextScreenFrame, nextAnimationFrame;
	bool isLastFrame = false;
	CharacterPlayerControl *charControl = (CharacterPlayerControl*)character->free;
	
	commonGetNextFrame(character, &nextScreenFrame, &nextAnimationFrame, &isLastFrame);
	
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
