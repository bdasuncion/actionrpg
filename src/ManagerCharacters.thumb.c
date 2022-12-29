#include <stdbool.h>
#include <stdlib.h>
#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacterActionEvent.h"
#include "ManagerOAM.h"
#include "ManagerPrinter.h"
#include "CharacterCommon.h"
#include "GBATimer.h"

CharacterCollection *mchar_vreference = NULL;

void mchar_setDraw(CharacterCollection *reference) {
	mchar_vreference = reference;
}

void mchar_draw() {
	if (mchar_vreference) {
		int i;
		//gbatimer_profileStart();
		for (i = 0; i < mchar_vreference->currentSize; ++i) {
			if (mchar_vreference->characters[i]->spriteDisplay.isInScreen) {
			    commonDrawDisplay(&mchar_vreference->characters[i]->spriteDisplay);
			}
			//mchar_vreference->characters[i]->draw(
			//	mchar_vreference->characters[i]);
		}
		//mprinter_printf("STOP:%d", gbatimer_profileStop());
		//mprinter_number(0);
	}
}

void mchar_init(CharacterCollection *charCollection, int size) {
	if (charCollection) {
		int i;
		charCollection->poolSize = size;
		charCollection->currentSize = 0;
		charCollection->characterEventCurrentSize = 0;
		charCollection->characters = 
			malloc(sizeof(CharacterAttr*)*size);
		charCollection->charactersDoEvent = 
			malloc(sizeof(CharacterAttr*)*size);
		for (i = 0; i < size; ++i) {
			charCollection->characters[i] = 
				malloc(sizeof(CharacterAttr));
			//*charCollection->characters[i] = openSlot;
			commonRemoveCharacter(charCollection->characters[i]);
		}
	}
}

void mchar_getPlayerCharacter(CharacterCollection *charCollection, CharacterAttr **player1, 
	ControlTypePool *controlPool) {
	alisa_init(charCollection->characters[charCollection->currentSize], controlPool);
	//nameless_init(charCollection->characters[charCollection->currentSize]);
	*player1 = charCollection->characters[charCollection->currentSize];
	++charCollection->currentSize;
}

void mchar_reinit(CharacterCollection *charCollection, CharacterAttr **player1) {
    int i;
	CharacterAttr *playable;
    for (i = 0; i < charCollection->currentSize; ++i) {
	    if (charCollection->characters[i]->type <= ENDPLAYABLECHARACTERTYPE) {
		    playable = charCollection->characters[i];
			charCollection->characters[i] = charCollection->characters[0];
			charCollection->characters[0] = playable;
		} 
		
		if (i != 0) {
		    //*charCollection->characters[i] = openSlot;
			commonRemoveCharacter(charCollection->characters[i]);
		}
	}
	
	charCollection->currentSize = 1;
	*player1 = playable;
}

void mchar_action(CharacterCollection *charCollection, const MapInfo *mapInfo)
{
	if (charCollection) {
		int i; 
		if (charCollection->characterEventCurrentSize < 1) {
			for (i = 0; i < charCollection->currentSize; ++i) {
				charCollection->characters[i]->controller(charCollection->characters[i], mapInfo, charCollection);
			}
		} else {
			for (i = 0; i < charCollection->characterEventCurrentSize; ++i) {
				charCollection->charactersDoEvent[i]->controller(charCollection->charactersDoEvent[i], mapInfo, charCollection);
			}
		}
	}
}

void mchar_resolveAction(CharacterCollection *charCollection,
	const MapInfo *mapInfo, CharacterActionCollection *charActionCollection) {

	//TODO put priority on actions
	if (charCollection) {
		int i, charIdx, checkCollisionIdx;
		
		for (charIdx = 0; charIdx < charCollection->currentSize - 1; ++charIdx){
			int cmpIndex = charIdx + 1;
			if (charCollection->characters[charIdx]->position.y <
			    charCollection->characters[cmpIndex]->position.y) {
				CharacterAttr *charA = charCollection->characters[charIdx];
				charCollection->characters[charIdx] = charCollection->characters[cmpIndex];
				charCollection->characters[cmpIndex] = charA;
			}
		}
		
		if (charCollection->characters[charCollection->currentSize - 1]->type == NONE) {
		    --charCollection->currentSize;
		}
		
		if (charCollection->characterEventCurrentSize < 1) {
			for (i = 0; i < charCollection->currentSize; ++i) {
				charCollection->characters[i]->doAction(charCollection->characters[i], mapInfo, 
				    charCollection, charActionCollection);
				//mapInfo->collisionCheck(mapInfo, charCollection->characters[i]);
			}
		} else{
			for (i = 0; i < charCollection->characterEventCurrentSize; ++i) {
				charCollection->charactersDoEvent[i]->doAction(charCollection->charactersDoEvent[i], mapInfo, 
				    charCollection, charActionCollection);
			}
		}
		
		for (checkCollisionIdx = 0; checkCollisionIdx < charCollection->currentSize; ++checkCollisionIdx) {
		    //int count = 0, compareCount = 0;
            int ascendingIdx, descendingIdx;
			bool checkNext = false;
			CharacterAttr *character = charCollection->characters[checkCollisionIdx];
		    for (descendingIdx = checkCollisionIdx - 1; descendingIdx >= 0; --descendingIdx) {
				character->checkCollision(character, true, &checkNext, charCollection->characters[descendingIdx]);
				
				if (!checkNext) {
				    break;
				}
			}
			
		    for (ascendingIdx = checkCollisionIdx + 1; ascendingIdx < charCollection->currentSize; ++ascendingIdx) {
				character->checkCollision(character, false, &checkNext, charCollection->characters[ascendingIdx]);
				
				if (!checkNext) {
				    break;
				}
			}
		}
		
		for (checkCollisionIdx = 0; checkCollisionIdx < charCollection->currentSize; ++checkCollisionIdx) {
		    charCollection->characters[checkCollisionIdx]->
			    checkMapCollision(charCollection->characters[checkCollisionIdx], mapInfo);
		}
		
		
		for (i = 0; i < charCollection->currentSize; ++i) {
			charCollection->characters[i]->checkActionCollision(charCollection->characters[i], charActionCollection);
		}
	}
}

void mchar_checkCollisionAbove(BoundingBox *boundingBox, BoundingBox *checkWithBoundingBox, int idx) {
    if (boundingBox->direction == EUnknown) {
	    return;
	}
    if (((boundingBox->startX >= checkWithBoundingBox->startX && 
	    boundingBox->startX <= checkWithBoundingBox->endX) ||
		(boundingBox->endX >= checkWithBoundingBox->startX &&
		boundingBox->endX <= checkWithBoundingBox->endX)) && 
		((boundingBox->startY >= checkWithBoundingBox->startY && 
	    boundingBox->startY <= checkWithBoundingBox->endY) ||
		(boundingBox->endY >= checkWithBoundingBox->startY &&
		boundingBox->endY <= checkWithBoundingBox->endY))) {
	}
}

void mchar_checkCollisionBelow(BoundingBox *boundingBox, BoundingBox *checkWithBoundingBox, int idx) {
    if (boundingBox->direction == EUnknown) {
	    return;
	}
    if (((boundingBox->startX >= checkWithBoundingBox->startX && 
	    boundingBox->startX <= checkWithBoundingBox->endX) ||
		(boundingBox->endX >= checkWithBoundingBox->startX &&
		boundingBox->endX <= checkWithBoundingBox->endX)) && 
		((boundingBox->startY >= checkWithBoundingBox->startY && 
	    boundingBox->startY <= checkWithBoundingBox->endY) ||
		(boundingBox->endY >= checkWithBoundingBox->startY &&
		boundingBox->endY <= checkWithBoundingBox->endY))) {
	}
}


void mchar_setPosition(CharacterCollection *charCollection,
	OAMCollection *oamCollection,
	const Position *scr_pos,
	const ScreenDimension *scr_dim) {
	OBJ_ATTR *oamBuffer = oamCollection->data;
	if (charCollection) {
		int charIdx, oamIdx, idxRemoveOam;
		
		for (charIdx = 0, oamIdx = 0; charIdx < charCollection->currentSize; ++charIdx) {
			oamIdx += charCollection->
				characters[charIdx]->setPosition(
					charCollection->characters[charIdx], 
					&oamBuffer[oamIdx], scr_pos, scr_dim);
		}
		
		for (idxRemoveOam = oamIdx; idxRemoveOam < oamCollection->previousSize; ++idxRemoveOam) {
			oamBuffer[idxRemoveOam] = *((OBJ_ATTR*)&moam_removeObj);
		}
		
		oamCollection->previousSize = oamIdx;
	}
}

CharacterAttr* mchar_findCharacterType(CharacterCollection *charCollection, int type) {
	if (charCollection) {
		int charIdx, oamIdx, idxRemoveOam;
		
		for (charIdx = 0, oamIdx = 0; charIdx < charCollection->currentSize;  ++charIdx) {
			if (charCollection->characters[charIdx]->type == type) {
			    return charCollection->characters[charIdx];
			}
		}
	}
	return NULL;
}

void mchar_resetControlType(ControlTypePool *controlPool) {
    int i;
	for (i = 0; i < controlPool->count; ++i) {
	    controlPool->collection[i].baseControl.type = EControlNone;
		controlPool->collection[i].baseControl.poolId = i;
	}
	controlPool->currentCount = 0;
}

void mchar_initControlType(ControlTypePool *controlPool) {
    controlPool->count = 32;
	controlPool->collection = malloc(sizeof(ControlTypeUnion)*controlPool->count);
	mchar_resetControlType(controlPool);
}

ControlTypeUnion* mchar_getControlType(ControlTypePool *controlPool) {
    ControlTypeUnion *free = &controlPool->collection[controlPool->currentCount];
	++controlPool->currentCount;
	return free;
}