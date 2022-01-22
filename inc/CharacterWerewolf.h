
#ifndef CHARACTER_WEREWOLF
#define CHARACTER_WEREWOLF

#include "GBAObject.h"

typedef enum WerewolfAction
{
	EWerewolfInitialize = -1,
	EWerewolfStand,
	EWerewolfWalk,
	EWerewolfFindTarget,
	EWerewolfIsHit,
	EWerewolfActionCount
} WerewolfAction;

void werewolf_init(CharacterAttr* character, ControlTypePool* controlPool);
void werewolf_setCharacter(CharacterAttr* character);
void werewolf_remove(CharacterAttr* character, 
    const MapInfo *mapInfo, CharacterCollection *charCollection);
void werewolf_getBoundingBoxStanding(const CharacterAttr* character, 
	int *count, BoundingBox *boundingBox);
void werewolf_getBoundingBoxMoving(const CharacterAttr* character, 
	int *count, BoundingBox *boundingBox);

#endif