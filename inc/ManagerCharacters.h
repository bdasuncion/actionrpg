#ifndef MANAGER_CHARACTERS
#define MANAGER_CHARACTERS

#include "GBATypes.h"
#include "GBAObject.h"
#include "GBAMap.h"
#include "GBACharacterActionEvent.h"

void mchar_setDraw(CharacterCollection *reference, AttackEffectCollection *attackEffectCollection);
void mchar_draw();
void mchar_init(CharacterCollection *charCollection, int size);
void mchar_action(CharacterCollection *charCollection);
void mchar_resolveAction(CharacterCollection *charCollection, const MapInfo *mapInfo, 
	CharacterActionCollection *charActionCollection, AttackEffectCollection *attackEffectCollection);
void mchar_setPosition(CharacterCollection *charCollection,
	AttackEffectCollection* attackEffectCollection,
	OAMCollection *oamCollection,
	const Position *scr_pos,
	const ScreenDimension *scr_dim);
void mchar_getPlayerCharacter(CharacterCollection *charCollection, CharacterAttr **player1,
	ControlTypePool *controlPool);
void mchar_reinit(CharacterCollection *charCollection, CharacterAttr **player1);
CharacterAttr* mchar_findCharacterType(CharacterCollection *charCollection, int type);
void mchar_resetControlPool(ControlTypePool *freeType);
void mchar_initControlPool(ControlTypePool *freeType);
ControlTypeUnion* mchar_getControlType(ControlTypePool *freeType);
#endif