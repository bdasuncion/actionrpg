#include "GBAObject.h"
#include "GBAKey.h"
#include "CharacterGhosthand.h"
#include "ManagerCharacters.h"
#include  <stdbool.h>

void ghostlyHand_controller(CharacterAttr* ghostlyHand, const MapInfo *mapInfo, CharacterCollection *charCollection);

void ghostlyHand_setCharacter(CharacterAttr* ghostlyHand) {
	ghostlyHand->controller = &ghostlyHand_controller; 
}

void ghostlyHand_controller(CharacterAttr* ghostlyHand, const MapInfo *mapInfo, CharacterCollection *charCollection) {
    ghostlyHand->nextAction = EGhosthandHidden;
	ghostlyHand->nextDirection = ELeft;
}
