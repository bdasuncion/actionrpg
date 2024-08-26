#include <stdbool.h>
#include <stdlib.h>
#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacterActionEvent.h"
#include "ManagerOAM.h"
#include "ManagerPrinter.h"
#include "CharacterCommon.h"
#include "CharacterAttackEffects.h"
#include "CharacterAlisa.h"
#include "GBATimer.h"

CharacterCollection *mchar_vreference = NULL;
AttackEffectCollection *mattackeffect_vreference = NULL;

void mchar_setDraw(CharacterCollection *reference, AttackEffectCollection *attackEffectCollection) {
	mchar_vreference = reference;
	mattackeffect_vreference = attackEffectCollection;
}

void mchar_draw() {
	if (mchar_vreference) {
		int i;
		for (i = 0; i < mchar_vreference->currentSize; ++i) {
			if (mchar_vreference->characters[i]->spriteDisplay.isInScreen) {
			    commonDrawDisplay(&mchar_vreference->characters[i]->spriteDisplay);
			}
		}
		for (i = 0; i < mattackeffect_vreference->count; ++i) {
			commonDrawDisplay(&mattackeffect_vreference->collection[i]->display);
		}
	}
}

void mchar_init(CharacterCollection *charCollection, int size) {
	if (charCollection) {
		int i;
		charCollection->poolSize = size;
		charCollection->displaySize = 0;
		charCollection->currentSize = 0;
		charCollection->characterEventCurrentSize = 0;
		charCollection->characters = 
			malloc(sizeof(CharacterAttr*)*charCollection->poolSize);
		charCollection->charactersDoEvent = 
			malloc(sizeof(CharacterAttr*)*size);
		charCollection->charactersForDisplay = 
			malloc(sizeof(CharacterAttr*)*charCollection->poolSize*2);

		for (i = 0; i < charCollection->poolSize*2; ++i) {
			charCollection->charactersForDisplay[i] = 
				malloc(sizeof(CharacterAttr));
			commonRemoveCharacter(charCollection->charactersForDisplay[i]);
		}
	}
}

void mchar_initTransferableCharacters(CharacterCollection *charCollection, int size) {
	if (charCollection) {
		int i;
		charCollection->countCharacterTransfer = 0;
		charCollection->characterTransfer = malloc(sizeof(FuncCharacterInit)*size);
	}
}

void mchar_addTransferableCharacters(CharacterCollection *charCollection, FuncCharacterInit charInitFunc) {
	if (charCollection) {
		charCollection->characterTransfer[charCollection->countCharacterTransfer] = charInitFunc;
		++charCollection->countCharacterTransfer;
	}
}	

void mchar_getPlayerCharacter(CharacterCollection *charCollection, CharacterAttr **player1, 
	ControlTypePool *controlPool) {
	
	alisa_init(charCollection->charactersForDisplay[charCollection->displaySize], controlPool);
	*player1 = charCollection->charactersForDisplay[charCollection->displaySize];
	++charCollection->displaySize;
	charCollection->characters[charCollection->currentSize] = charCollection->charactersForDisplay[charCollection->displaySize];
	++charCollection->currentSize;
}

//TODO Update this to handle multiple characters
void mchar_reinit(CharacterCollection *charCollection, CharacterAttr **player1) {
    int i;
	CharacterAttr *playable;
	for (i = 0; i < charCollection->displaySize; ++i) {
	    if (charCollection->charactersForDisplay[i]->type <= ENDPLAYABLECHARACTERTYPE) {
		    playable = charCollection->charactersForDisplay[i];
			charCollection->charactersForDisplay[i] = charCollection->charactersForDisplay[0];
			charCollection->charactersForDisplay[0] = playable;
			charCollection->characters[0] = charCollection->charactersForDisplay[0];
		} 
		
		if (i != 0) {
			commonRemoveCharacter(charCollection->charactersForDisplay[i]);
		}
	}

	charCollection->currentSize = 1;
	charCollection->displaySize = 1;
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

void mchar_arrangeCharacters(CharacterCollection *charCollection) {
	int charIdx, cmpIndex, count;
	BoundingBox charBB, otherBB;
	for (charIdx = 0; charIdx < charCollection->currentSize - 1; ++charIdx){
		cmpIndex = charIdx + 1;
		if (charCollection->characters[charIdx]->position.y <
			charCollection->characters[cmpIndex]->position.y) {
			CharacterAttr *charA = charCollection->characters[charIdx];
			charCollection->characters[charIdx] = charCollection->characters[cmpIndex];
			charCollection->characters[cmpIndex] = charA;
		}
	}
}

void mchar_checkSameYPosFurther(CharacterCollection *charCollection, int yReferencePos, int cmpIdx, int startIdx) {
	int charIdx, count;
	BoundingBox charBB, otherBB;
	charCollection->charactersForDisplay[cmpIdx]->getBounds(charCollection->charactersForDisplay[cmpIdx], &count, &otherBB);
			
	for (charIdx = startIdx; charIdx >= 0; --charIdx){
		if (charCollection->charactersForDisplay[charIdx]->position.y != yReferencePos) {
			break;
		}
		charCollection->charactersForDisplay[charIdx]->getBounds(charCollection->charactersForDisplay[charIdx], &count, &charBB);
		if (isOverlap(&otherBB, &charBB)) {
			CharacterAttr *charA = charCollection->charactersForDisplay[charIdx];
			charCollection->charactersForDisplay[charIdx] = charCollection->charactersForDisplay[cmpIdx];
			charCollection->charactersForDisplay[cmpIdx] = charA;
			
			break;
		}
	}
}

void mchar_arrangeCharactersForDisplay(CharacterCollection *charCollection) {
	int charIdx, cmpIndex, count;
	BoundingBox charBB, otherBB;
	for (charIdx = 0; charIdx < charCollection->displaySize - 1; ++charIdx){
		cmpIndex = charIdx + 1;
		charCollection->charactersForDisplay[charIdx]->getBounds(charCollection->charactersForDisplay[charIdx], &count, &charBB);
		charCollection->charactersForDisplay[cmpIndex]->getBounds(charCollection->charactersForDisplay[cmpIndex], &count, &otherBB);

		if ((charCollection->charactersForDisplay[charIdx]->position.y <
			charCollection->charactersForDisplay[cmpIndex]->position.y 
			&& !isOverlap(&otherBB, &charBB))) {
			CharacterAttr *charA = charCollection->charactersForDisplay[charIdx];
			charCollection->charactersForDisplay[charIdx] = charCollection->charactersForDisplay[cmpIndex];
			charCollection->charactersForDisplay[cmpIndex] = charA;
		} else if (otherBB.startZ > charBB.endZ){
			mchar_checkSameYPosFurther(charCollection, 
				charCollection->charactersForDisplay[charIdx]->position.y, cmpIndex, charIdx);
		}
	}
}

void mchar_resolveMapCollision(CharacterCollection *charCollection, const MapInfo *mapInfo) {
	int checkCollisionIdx;
	for (checkCollisionIdx = 0; checkCollisionIdx < charCollection->currentSize; ++checkCollisionIdx) {
		    charCollection->characters[checkCollisionIdx]->
			    checkMapCollision(charCollection->characters[checkCollisionIdx], mapInfo);
		}
}

void mchar_resolveCharacterCollision(CharacterCollection *charCollection) {
	int checkCollisionIdx;
	for (checkCollisionIdx = 0; checkCollisionIdx < charCollection->currentSize; ++checkCollisionIdx) {
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
}

inline void mchar_resolveRemovedCharacters(CharacterCollection *charCollection) {
	if (charCollection->characters[charCollection->currentSize - 1]->type == NONE) {
		--charCollection->currentSize;
	}
	
	if (charCollection->charactersForDisplay[charCollection->displaySize - 1]->type == NONE) {
		--charCollection->displaySize;
	}
}

void mchar_resolveAction(CharacterCollection *charCollection, const MapInfo *mapInfo, 
	CharacterActionCollection *charActionCollection, AttackEffectCollection *attackEffects) {

	//TODO put priority on actions
	if (charCollection) {
		int i;
		
		if (charCollection->characterEventCurrentSize < 1) {
			for (i = 0; i < charCollection->currentSize; ++i) {
				charCollection->characters[i]->doAction(charCollection->characters[i], mapInfo, 
				    charCollection, charActionCollection);
			}
		} else{
			for (i = 0; i < charCollection->characterEventCurrentSize; ++i) {
				charCollection->charactersDoEvent[i]->doAction(charCollection->charactersDoEvent[i], mapInfo, 
				    charCollection, charActionCollection);
			}
		}
		
		mchar_resolveMapCollision(charCollection, mapInfo);
		
		mchar_arrangeCharacters(charCollection);
		
		mchar_resolveCharacterCollision(charCollection);
			
		for (i = 0; i < charActionCollection->count; ++i) {
			CharacterActionEvent *actionEvent = &charActionCollection->currentActions[i];
			actionEvent->resolve(actionEvent, charCollection, attackEffects);
		}
		
		mchar_arrangeCharactersForDisplay(charCollection);
		
		mchar_resolveRemovedCharacters(charCollection);
	}
}

void mchar_removeOAMExcess(OAMCollection *oamCollection, int currentIdx) {
	OBJ_ATTR *oamBuffer = oamCollection->data;
	int idxRemoveOam;
	for (idxRemoveOam = currentIdx; idxRemoveOam < oamCollection->previousSize; ++idxRemoveOam) {
		oamBuffer[idxRemoveOam] = *((OBJ_ATTR*)&moam_removeObj);
	}
		
	oamCollection->previousSize = currentIdx;
}

void mchar_setPosition(CharacterCollection *charCollection,
	AttackEffectCollection* attackEffectCollection,
	OAMCollection *oamCollection,
	const Position *scr_pos,
	const ScreenDimension *scr_dim) {
	OBJ_ATTR *oamBuffer = oamCollection->data;
	int currentOAMIdx = 0;
	currentOAMIdx = charAttackEffect_setToOAMBuffer(attackEffectCollection, oamCollection, currentOAMIdx,
		scr_pos, scr_dim);
	currentOAMIdx = commonCharacterSetToOAMBuffer(charCollection, oamCollection, currentOAMIdx,
		scr_pos, scr_dim); 
	mchar_removeOAMExcess(oamCollection, currentOAMIdx);
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

void mchar_resetControlTypeAndSetCount(ControlTypePool *controlPool, int setCount) {
    mchar_resetControlType(controlPool);
	controlPool->currentCount = setCount;
}

void mchar_initControlType(ControlTypePool *controlPool) {
    controlPool->count = 32;
	controlPool->collection = malloc(sizeof(ControlTypeUnion)*controlPool->count);
	mchar_resetControlType(controlPool);
}

void mchar_removeControl(CharacterBaseControl *control) {
	control->type = EControlNone;
}

ControlTypeUnion* mchar_findFreeControlType(ControlTypePool *controlPool) {
    int i;
	for (i = 0; i < controlPool->currentCount; ++i) {
		if (controlPool->collection[i].baseControl.type == EControlNone) {
			return &controlPool->collection[i];
		}
	}
	return NULL;
}

ControlTypeUnion* mchar_getControlType(ControlTypePool *controlPool) {
    ControlTypeUnion *free = &controlPool->collection[controlPool->currentCount];
	++controlPool->currentCount;
	return free;
}