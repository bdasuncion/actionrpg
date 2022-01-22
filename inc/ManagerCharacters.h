#ifndef MANAGER_CHARACTERS
#define MANAGER_CHARACTERS

#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacterActionEvent.h"

void mchar_setDraw(CharacterCollection *reference);
void mchar_draw();
void mchar_init(CharacterCollection *charCollection, int size);
void mchar_action(CharacterCollection *charCollection);
void mchar_resolveAction(CharacterCollection *charCollection,
	const MapInfo *mapInfo, CharacterActionCollection *charActionCollection);
void mchar_setPosition(CharacterCollection *charCollection,
	 OAMCollection *oamCollection, const Position *scr_pos,
	const ScreenDimension *scr_dim);
void mchar_getPlayerCharacter(CharacterCollection *charCollection, CharacterAttr **player1);
void mchar_reinit(CharacterCollection *charCollection, CharacterAttr **player1);
CharacterAttr* mchar_findCharacterType(CharacterCollection *charCollection, int type);
void mchar_resetControlPool(ControlTypePool *freeType);
void mchar_initControlPool(ControlTypePool *freeType);
ControlTypeUnion* mchar_getControlType(ControlTypePool *freeType);
#endif