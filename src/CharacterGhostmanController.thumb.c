#include "GBAObject.h"
#include "GBAKey.h"
#include "CharacterGhostMan.h"
#include "ManagerCharacters.h"
#include  <stdbool.h>

#define GHOSTMAN_ACTION_FOLLOW_TRIGGER_WIDTH 32
#define GHOSTMAN_ACTION_FOLLOW_TRIGGER_HEIGHT 32

void ghostMan_controller(CharacterAttr* ghostMan, const MapInfo *mapInfo, CharacterCollection *charCollection);
void ghostMan_transistionToFollowController(CharacterAttr* ghostMan, const MapInfo *mapInfo, 
    CharacterCollection *charCollection);
void ghostMan_followController(CharacterAttr* ghostMan, const MapInfo *mapInfo, 
    CharacterCollection *charCollection);
	
void ghostMan_setCharacter(CharacterAttr* ghostMan) {
	ghostMan->controller = &ghostMan_controller; 
}

void ghostMan_controller(CharacterAttr* ghostMan, const MapInfo *mapInfo, CharacterCollection *charCollection) {	
	CharacterAttr *targetCharacter = mchar_findCharacterType(charCollection, NAMELESS);
	CharacterAIControl *charControl = (CharacterAIControl*)ghostMan->free;
	int count;
	BoundingBox triggerBox, targetBox;
   //int width = DIVIDE_BY_2(charControl->width);
   //int height = DIVIDE_BY_2(charControl->height);
   
    ghostMan->nextAction = EGhostmanSit;
	ghostMan->nextDirection = ELeft;
	
	triggerBox.startX = ghostMan->position.x - GHOSTMAN_ACTION_FOLLOW_TRIGGER_WIDTH;
	triggerBox.endX = ghostMan->position.x + GHOSTMAN_ACTION_FOLLOW_TRIGGER_WIDTH;
	triggerBox.startY = ghostMan->position.y - GHOSTMAN_ACTION_FOLLOW_TRIGGER_HEIGHT;
	triggerBox.endY = ghostMan->position.y + GHOSTMAN_ACTION_FOLLOW_TRIGGER_HEIGHT;
   
    if (targetCharacter) {
       charControl->target = targetCharacter->position;
    }
   
	targetCharacter->getBounds(targetCharacter, &count, &targetBox);
	if (hasCollision(&triggerBox, &targetBox) || hasCollision(&targetBox, &triggerBox)) {
	    ghostMan->controller = &ghostMan_transistionToFollowController;
	}
}

void ghostMan_transistionToFollowController(CharacterAttr* ghostMan, const MapInfo *mapInfo, 
    CharacterCollection *charCollection) {
	int nextScreenFrame, nextAnimationFrame;
	bool isLastFrame = false;
	
	ghostMan->nextAction = EGhostmanTransitionToFollow;
	ghostMan->nextDirection = ELeft;
	
	commonGetNextFrame(ghostMan, &nextScreenFrame, &nextAnimationFrame, &isLastFrame);
	
	if (isLastFrame) {
		ghostMan->movementCtrl.maxFrames = 220;
		ghostMan->movementCtrl.currentFrame = 0;
	    ghostMan->nextAction = EGhostmanFollow;
	    ghostMan->controller = &ghostMan_followController;
	}
}

void ghostMan_followController(CharacterAttr* ghostMan, const MapInfo *mapInfo, 
    CharacterCollection *charCollection) {
	ghostMan->nextAction = EGhostmanFollow;
	ghostMan->nextDirection = ELeft;
}