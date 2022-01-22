#ifndef CHARACTER_CROW
#define CHARACTER_CROW

#include "GBAObject.h"
#include "GBASound.h"
#include "ImageCrow.h"

typedef enum CrowAction
{
	ECrowInitialize = -1,
	ECrowStand,
	ECrowFly,
	ECrowActionCount
} CrowAction;

void crow_controller(CharacterAttr* character, const MapInfo *mapInfo, CharacterCollection *charCollection);
void crow_actionStand(CharacterAttr* alisa,
	const MapInfo *mapInfo, const void *dummy);
void crow_doAction(CharacterAttr* crow,
	const MapInfo *mapInfo, const void *dummy);
int crow_setPosition(CharacterAttr* crow,
	OBJ_ATTR *oamBuf, 
	const Position *scr_pos,
	const ScreenDimension *scr_dim);
void crow_getBoundingBox(const CharacterAttr* character, 
	int *count, BoundingBox *boundingBox);
void crow_checkMapCollision(CharacterAttr* character, const MapInfo* mapInfo);
void crow_checkCollision(const CharacterAttr* character, bool isOtherCharBelow,
	bool *checkNext, const CharacterAttr* otherCharacter);
extern const Sound soundeffect_crow;
#endif