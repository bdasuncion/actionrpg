#include "GBAObject.h"
#include "GBAKey.h"
#include "CharacterCommon.h"
#include "CharacterAlisa.h"
#include  <stdbool.h>
#include  <stdlib.h>

#include "ManagerPrinter.h"

#define MAX_BUTTON_INTERVAL 30
#define MAX_STUN_ANIMATION 30
#define ALISA_NORMALATTACK_INTERVALMAX 8

#define ALISA_MIN_BACKWARD_DASH 4
#define ALISA_JUMPUP2_JUMPFORWARD_TRANSITIONFRAME 1

void alisa_stunnedController(CharacterAttr* charAtt, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection);
void alisa_slashController(CharacterAttr* charAtt, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection);
void alisa_prepareDashController(CharacterAttr* charAtt, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection);
void alisa_dashForwardController(CharacterAttr* charAtt, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection);
void alisa_dashBackwardController(CharacterAttr* charAtt, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection);
void alisa_fallingDownController(CharacterAttr* charAtt, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection);
void alisa_fallingDownForwardController(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection);
void alisa_jumpForwardController(CharacterAttr* charAtt, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection);

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
		charControl->buttonL_Ready = false;
		character->controller = charControl->controlMap.buttonL;
		return true;
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
			//control->buttonB_PressInterval = 0;
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

bool alisa_isStunned(CharacterAttr* character, CharacterPlayerControl *charControl,
	const MapInfo *mapInfo, const CharacterCollection *characterCollection) {
	if (charControl->currentStatus == EAlisaStatusStunned) {
		character->controller = &alisa_stunnedController; 
		alisa_stunnedController(character, mapInfo, characterCollection);
		return true;
	}
	return false;
}

bool alisa_isFalling(CharacterAttr* character, CharacterPlayerControl *charControl,
	const MapInfo *mapInfo, const CharacterCollection *characterCollection) {
	if (character->nextAction == EAlisaFallingDown) {
		character->controller = &alisa_fallingDownController; 
		alisa_fallingDownController(character, mapInfo, characterCollection);
		return true;
	}
	
	return false;
}

bool alisa_hasLanded(CharacterAttr* character, CharacterPlayerControl *charControl,
	const MapInfo *mapInfo, const CharacterCollection *characterCollection) {
	if (character->nextAction != EAlisaFallingDown &&  character->nextAction != EAlisaFallingDownForward) {
		//character->faceDirection = character->direction;
		character->controller = &alisa_controller;
		character->controller(character, mapInfo, characterCollection);
		return true;
	}
	return false;
}

void alisa_controller(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection) {	
	EDirections direction = KEYPRESS_DIRECTION;
	mprinter_printf("PRESS %d\n", KEYPRESS);
	//mprinter_printf("PRESS %d\n", 0xF);
	CharacterPlayerControl *charControl = (CharacterPlayerControl*)character->free;
	character->distanceFromGround = 1024;

	if (alisa_isStunned(character, charControl, mapInfo, characterCollection)) {
		return;
	}
	
	if (alisa_isFalling(character, charControl, mapInfo, characterCollection)) {
		return;
	}
	
	if (controlButtonCheck(character)) {
		character->controller(character, mapInfo, characterCollection);
		return;
	}

	character->stats.currentStatus = EStatusNormal;
	
	if (direction != EUnknown) {
		character->nextAction = EAlisaRun;
		character->nextDirection = direction&EDirectionsMax;
		if (!((direction == EUpleft | direction == EDownleft) & character->faceDirection == ELeft) && 
			!((direction == EUpright | direction == EDownright) & character->faceDirection == ERight)) {
			character->faceDirection = DEFAULT_DIRECTIONMAP[direction]&EDirectionsMax;
		}
		//character->faceDirection = DEFAULT_DIRECTIONMAP[direction];
		character->getBounds = &alisa_getBoundingBoxMoving;
		return;
	}
	
	character->getBounds = &alisa_getBoundingBoxStanding;
	character->nextAction = EAlisaStand;
}

void alisa_normalSlashController(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection) {
	int nextScreenFrame, nextAnimationFrame, hold;
	bool isLastFrame = false;
	CharacterPlayerControl *charControl = (CharacterPlayerControl*)character->free;
	character->distanceFromGround = 1024;

	if (alisa_isStunned(character, charControl, mapInfo, characterCollection)) {
		return;
	}

	if (alisa_isFalling(character, charControl, mapInfo, characterCollection)) {
		return;
	}
	character->nextAction = EAlisaNormalSwordSlash;
	commonGetCharacterNextFrame(character, &nextScreenFrame, &nextAnimationFrame, &isLastFrame);
	if (isLastFrame) {
		character->controller = &alisa_controller;
		character->controller(character, mapInfo, characterCollection);
		return;
	}
}

void alisa_strongSlashController(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection) {
	int nextScreenFrame, nextAnimationFrame, hold;
	bool isLastFrame = false;
	CharacterPlayerControl *charControl = (CharacterPlayerControl*)character->free;
	character->distanceFromGround = 1024;

	if (alisa_isStunned(character, charControl, mapInfo, characterCollection)) {
		return;
	}

	if (alisa_isFalling(character, charControl, mapInfo, characterCollection)) {
		return;
	}
	character->nextAction = EAlisaStrongSwordSlash;
	commonGetCharacterNextFrame(character, &nextScreenFrame, &nextAnimationFrame, &isLastFrame);
	if (isLastFrame) {
		character->controller = &alisa_controller;
		character->controller(character, mapInfo, characterCollection);
		return;
	}
}

void alisa_slashController(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection) {
   int nextScreenFrame, nextAnimationFrame, hold;
   bool isLastFrame = false;
   CharacterPlayerControl *charControl = (CharacterPlayerControl*)character->free;
   character->distanceFromGround = 1024;
   
   	if (alisa_isStunned(character, charControl, mapInfo, characterCollection)) {
		return;
	}
	
	if (alisa_isFalling(character, charControl, mapInfo, characterCollection)) {
		return;
	}

	character->stats.currentStatus = EStatusNormal;
	character->getBounds = &alisa_getBoundingBoxStanding;
	
	if (controlButtonHold(charControl, &alisa_slashController, &hold, ALISA_NORMALATTACK_INTERVALMAX) &&
		(character->nextAction != EAlisaNormalSwordSlash && character->nextAction != EAlisaStrongSwordSlash)) {
		//TODO Add strong attack for when normal attack threshhold is reached
		if (hold >= ALISA_NORMALATTACK_INTERVALMAX) {
			character->nextAction = EAlisaStrongSwordSlash;
			character->controller = &alisa_strongSlashController;
			character->controller(character, mapInfo, characterCollection);
			return;
		} else {
			character->nextAction = EAlisaNormalSwordSlash;
			character->controller = &alisa_normalSlashController;
			character->controller(character, mapInfo, characterCollection);
		}
	}
	
	character->nextAction = EAlisaStand;
}

void alisa_prepareDashController(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection) {
    EDirections direction = KEYPRESS_DIRECTION;
    int nextScreenFrame, nextAnimationFrame, hold;
    bool isLastFrame = false;
    CharacterPlayerControl *charControl = (CharacterPlayerControl*)character->free;
    character->distanceFromGround = 1024;
   	if (alisa_isStunned(character, charControl, mapInfo, characterCollection)) {
		return;
	}
	
	if (alisa_isFalling(character, charControl, mapInfo, characterCollection)) {
		return;
	}
	
	character->stats.currentStatus = EStatusNormal;
	character->getBounds = &alisa_getBoundingBoxMoving;
	
	character->nextAction = EAlisaPrepareDash;
	
	commonGetCharacterNextFrame(character, &nextScreenFrame, &nextAnimationFrame, &isLastFrame);
	
	if (direction != EUnknown) {
		character->nextDirection = direction&EDirectionsMax;
		EDirections clockwise = (character->faceDirection - 1)&EDirectionsMax;
		EDirections counterClockwise = (character->faceDirection + 1)&EDirectionsMax;
		if (direction != character->faceDirection & 
			direction != clockwise & direction != counterClockwise &
			character->spriteDisplay.numberOfFramesPassed >= ALISA_MIN_BACKWARD_DASH &
			character->nextAction == character->action) {
			character->controller = &alisa_dashBackwardController;
			character->controller(character, mapInfo, characterCollection);
			return;
		} else if (isLastFrame) {
			character->controller = &alisa_dashForwardController;
			character->controller(character, mapInfo, characterCollection);
			return;
		}
	}

	if (isLastFrame) {
		if (alisa_isFalling(character, charControl, mapInfo, characterCollection)) {
			return;
		}
		character->nextDirection = commonReverseDirection(character->faceDirection&EDirectionsMax)&EDirectionsMax;
		character->controller = &alisa_dashBackwardController;
		character->controller(character, mapInfo, characterCollection);
	}
}

void alisa_dashForwardController(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection) {
	int nextScreenFrame, nextAnimationFrame, hold;
	bool isLastFrame = false;
	CharacterPlayerControl *charControl = (CharacterPlayerControl*)character->free;
    character->distanceFromGround = 1024;
	
   	if (alisa_isStunned(character, charControl, mapInfo, characterCollection)) {
		return;
	}
	
	if (commonGetCurrentAnimationFrame(character) > ALISA_DASH_STARTMOVE_FRAME &&
		alisa_isFalling(character, charControl, mapInfo, characterCollection)) {
		return;
	}
	
	if (commonGetCurrentAnimationFrame(character) > ALISA_DASH_STARTMOVE_FRAME &&
		alisa_isFalling(character, charControl, mapInfo, characterCollection)) {
		return;
	}
	
	character->stats.currentStatus = EStatusNormal;
	character->getBounds = &alisa_getBoundingBoxMoving;
	
	character->nextAction = EAlisaDashForward;
	
	commonGetCharacterNextFrame(character, &nextScreenFrame, &nextAnimationFrame, &isLastFrame);

	if (isLastFrame) {
		character->controller = &alisa_controller;
		character->controller(character, mapInfo, characterCollection);
	}
}

void alisa_dashBackwardController(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection) {
	int nextScreenFrame, nextAnimationFrame, hold;
	bool isLastFrame = false;
	CharacterPlayerControl *charControl = (CharacterPlayerControl*)character->free;
	character->distanceFromGround = 1024;
      
    if (alisa_isStunned(character, charControl, mapInfo, characterCollection)) {
		return;
	}
	
	if (commonGetCurrentAnimationFrame(character) > 0 && 
		alisa_isFalling(character, charControl, mapInfo, characterCollection)) {
			return;
	}
	
	character->stats.currentStatus = EStatusNormal;
	character->getBounds = &alisa_getBoundingBoxMoving;
	
	character->nextAction = EAlisaDashBackward;
	
	commonGetCharacterNextFrame(character, &nextScreenFrame, &nextAnimationFrame, &isLastFrame);

	//mprinter_printf("FRAMES %d %d %d\n", nextScreenFrame, nextAnimationFrame,  isLastFrame);
	if (isLastFrame) {
		character->nextDirection = character->faceDirection&EDirectionsMax;
		character->controller = &alisa_controller;
		character->controller(character, mapInfo, characterCollection);
	}
}

void alisa_jumpUpController(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection) {
   EDirections direction = KEYPRESS_DIRECTION;
   mprinter_printf("PRESS %d", KEYPRESS);
   int nextScreenFrame, nextAnimationFrame, hold;
   bool isLastFrame = false;
   CharacterPlayerControl *charControl = (CharacterPlayerControl*)character->free;
   character->distanceFromGround = 1024;
 
	if (alisa_isStunned(character, charControl, mapInfo, characterCollection)) {
		return;
	}
	
	character->getBounds = &alisa_getBoundingBoxMoving;	
	character->nextAction = EAlisaJumpUp;
		
	if (commonGetCurrentAnimationFrame(character) >= ALISA_JUMPUP2_JUMPFORWARD_TRANSITIONFRAME && 
		direction != EUnknown && (character->nextAction == character->action)) {
		EDirections clockwise = (character->faceDirection - 1)&EDirectionsMax;
		EDirections counterClockwise = (character->faceDirection + 1)&EDirectionsMax;
		if (direction == character->faceDirection | 
			direction == clockwise | direction == counterClockwise) {
			character->nextAction = EAlisaJumpForward;
			character->action = EAlisaJumpForward;
			character->nextDirection = direction&EDirectionsMax;
			character->controller = &alisa_jumpForwardController;
			character->controller(character, mapInfo, characterCollection);
			return;
		}
	}
	
	commonGetCharacterNextFrame(character, &nextScreenFrame, &nextAnimationFrame, &isLastFrame);
	if (isLastFrame) {
		character->nextDirection = character->direction&EDirectionsMax;
		character->nextAction = EAlisaFallingDown;
		character->controller = &alisa_fallingDownController;
		character->controller(character, mapInfo, characterCollection);
	}
}

void alisa_jumpForwardController(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection) {
   //EDirections direction = KEYPRESS_DIRECTION;
   int nextScreenFrame, nextAnimationFrame, hold;
   bool isLastFrame = false;
   CharacterPlayerControl *charControl = (CharacterPlayerControl*)character->free;
    character->distanceFromGround = 1024;
 
	if (alisa_isStunned(character, charControl, mapInfo, characterCollection)) {
		return;
	}
	
	character->getBounds = &alisa_getBoundingBoxMoving;
	
	character->nextAction = EAlisaJumpForward;
	
	commonGetCharacterNextFrame(character, &nextScreenFrame, &nextAnimationFrame, &isLastFrame);
	if (isLastFrame) {
		character->nextDirection = character->direction&EDirectionsMax;
		character->nextAction = EAlisaFallingDownForward;
		character->controller = &alisa_fallingDownForwardController;
		character->controller(character, mapInfo, characterCollection);
	}
}

void alisa_jumpController(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection) {
   EDirections direction = KEYPRESS_DIRECTION;
   //if (direction != EUnknown) {
   if (direction == character->direction) {
		character->controller = &alisa_jumpForwardController;
		character->controller(character, mapInfo, characterCollection);
   } else {
		character->controller = &alisa_jumpUpController;
		character->controller(character, mapInfo, characterCollection);
   }
}

void alisa_fallingDownForwardController(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection) {
   int nextScreenFrame, nextAnimationFrame, hold;
   EDirections direction = KEYPRESS_DIRECTION;
   bool isLastFrame = false;
   CharacterPlayerControl *charControl = (CharacterPlayerControl*)character->free;
   character->distanceFromGround = 1024;

   	if (alisa_isStunned(character, charControl, mapInfo, characterCollection)) {
		return;
	}
   
	if (alisa_hasLanded(character, charControl, mapInfo, characterCollection)) {
		return;
	}

	if (direction == character->nextDirection) {
		character->nextAction = EAlisaFallingDownForward;
	} else {
		character->nextAction = EAlisaFallingDown;
	}
}

void alisa_fallingDownController(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection) {
   int nextScreenFrame, nextAnimationFrame, hold;
   bool isLastFrame = false;
   CharacterPlayerControl *charControl = (CharacterPlayerControl*)character->free;
   character->distanceFromGround = 1024;

   	if (alisa_isStunned(character, charControl, mapInfo, characterCollection)) {
		return;
	}
   
	if (alisa_hasLanded(character, charControl, mapInfo, characterCollection)) {
		return;
	}

	character->nextAction = EAlisaFallingDown;
}

void alisa_stunnedController(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection) {
	int nextScreenFrame, nextAnimationFrame;
	bool isLastFrame = false;
	CharacterPlayerControl *charControl = (CharacterPlayerControl*)character->free;
	
	//mprinter_printf("ACTIONS %d %d\n", character->nextAction, character->action);
	commonGetCharacterNextFrame(character, &nextScreenFrame, &nextAnimationFrame, &isLastFrame);
	
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