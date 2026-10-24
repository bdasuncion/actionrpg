#include "GBAObject.h"
#include "GBAKey.h"
#include "CharacterCommon.h"
#include "CharacterMouthDemon.h"
#include  <stdbool.h>
#include  <stdlib.h>

#include "MapCommon.h"

#include "ManagerPrinter.h"

#define MAX_BUTTON_INTERVAL 30
#define MAX_STUN_ANIMATION 30
#define ALISA_NORMALATTACK_INTERVALMAX 8

#define ALISA_MIN_BACKWARD_DASH 4
#define ALISA_JUMPUP2_JUMPFORWARD_TRANSITIONFRAME 1

void mouthDemon_floatController(CharacterAttr* character, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection) {
	CharacterAIControl *charControl = (CharacterAIControl*)character->free;
	int i;
	//EDirections goDirection;
   
	//if (charControl->currentStatus == EMouthDemonAIStateFloat) {
	//	charControl->currentAction = MAXACTIONS;
	//	character->controller = &mouthDemon_huntController;
	//	character->controller(character, mapInfo, characterCollection);
		//return;
	//}
	
	//if (common_shouldDoIntializeActions(character)) {
	//	character->getBounds = &mouthDemon_getBoundingBoxMoving;
	//}
	
	int count;
	BoundingBox boundingBox;
	character->getBounds(character, &count, &boundingBox);
	bool hasArrived = commonHasReachedWaypoint(&charControl->wayPoints[charControl->wayPointCurrent], &boundingBox);
	
	//mprinter_printf("HAS ARRIVED %d COUNT ACTION %d\n", hasArrived, charControl->countAction);
	//mprinter_printf("POSITION %d %d %d\n", CONVERT_2POS(character->position.x), CONVERT_2POS(character->position.y), CONVERT_2POS(character->position.z));
	//mprinter_printf("TARGET %d %d %d\n", charControl->wayPoints[charControl->wayPointCurrent].x, charControl->wayPoints[charControl->wayPointCurrent].y, charControl->wayPoints[charControl->wayPointCurrent].z);
	//if (hasArrived && charControl->countAction == 0) {
	if (hasArrived) {
		++charControl->wayPointCurrent;
	
		if (charControl->wayPointCurrent >= charControl->wayPointCnt) {
			charControl->wayPointCurrent= 0;
		}
		//charControl->countAction = 1;
		//charControl->currentAction = 0;
		//charControl->actions[0] = ((ActionControl){60, 0, character->direction, EMouthDemonFloat});
		//character->nextAction = EMouthDemonFloat;
	}
	
	if (charControl->countAction > 0 && charControl->currentAction > 0) {
		mprinter_printf("END FLOAT\n");
		charControl->countAction = 0;
		charControl->currentAction =  MAXACTIONS;
	}
	
	if (charControl->countAction == 0) {
		EVerticalDirections vdirection;
		//mprinter_printf("FLOAT UP OR DOWN\n");
		common_findVerticalDirectionOfPosition(&character->position, &charControl->wayPoints[charControl->wayPointCurrent], &vdirection);
		if (vdirection == EVUp) {
			character->nextAction = EMouthDemonFloatUp;
		} else {
			character->nextAction = EMouthDemonFloatDown;
		}
		
		//character->nextAction = EMouthDemonFloat;
		return;
	} 
	
	if (charControl->countAction > 0 && charControl->currentAction <= 0) {
		mprinter_printf("DO FLOAT STEADY\n");
		common_doSetActions(charControl, character);
	} 
	
	
	if (charControl->currentAction >= charControl->countAction) {
		//charControl->countAction = 0;
		commonInitializeAISetActions(charControl);
		charControl->currentAction = MAXACTIONS;
		//character->nextDirection = direction;
		//return;
	}
	
	//character->nextAction = EMouthDemonFloat;
	//mouthDemon_doWalk(character, mapInfo, characterCollection, charControl);
}