#include "GBAObject.h"
#include "GBAKey.h"
#include "CharacterCrow.h"
#include  <stdbool.h>

void crow_setCharacter(CharacterAttr* crow) {
	crow->controller = &crow_controller; 
}

void crow_controller(CharacterAttr* crow, const MapInfo *mapInfo, CharacterCollection *charCollection) {
    CharacterAttr *targetCharacter = mchar_findCharacterType(charCollection, NAMELESS);
	CharacterAIControl *charControl = (CharacterAIControl*)crow->free;
	
    crow->nextAction = ECrowStand;
	crow->nextDirection = EDown;
	
	if (targetCharacter) {
       charControl->target = targetCharacter->position;
    }
}
