#include <stdlib.h>
#include <stdbool.h>
#include "GBATypes.h"
#include "GBAObject.h"
#include "GBAVideo.h"
#include "GBADMA.h"
#include "UtilCommonValues.h"
#include "SpriteSetWerewolf.h"
#include "ManagerVram.h"
#include "CharacterWerewolf.h"

#include "CharacterCommon.h"

#include "ManagerPrinter.h"

extern const EDirections directions[EDirectionsCount];

extern const unsigned short werewolfupperbody_run_down_pal[16];

#define WEREWOLF_LENGTH 16
#define WEREWOLF_WIDTH 12
#define WEREWOLF_HEIGHT 24

#define WEREWOLF_SCRCNVRTWIDTH 16
#define WEREWOLF_SCRCNVRTHEIGHT 26

#define WEREWOLF_SCREENDISPLAYOFFSET_X 10
#define WEREWOLF_SCREENDISPLAYOFFSET_Y 28

#define WEREWOLF_PAL_CNT 1

const u8 werewolf_scrConversionMeasurements[EScrCnvrtMeasureCount] = {
	WEREWOLF_SCRCNVRTWIDTH,
	WEREWOLF_SCRCNVRTHEIGHT
};

const u8 werewolf_boundingBoxMeasurements[EBBCnvrtMeasurementCount] = {
	WEREWOLF_LENGTH,
	WEREWOLF_WIDTH,
	WEREWOLF_HEIGHT,
};


void werewolf_scanSurroundings(CharacterAttr* character);
void werewolf_actionWalk(CharacterAttr* character, const MapInfo *mapInfo, const CharacterCollection *characterCollection);
void werewolf_getBounds(const CharacterAttr* character, int *count, CharBoundingBox *boundingBox);
int werewolf_setPosition(CharacterAttr* character, OBJ_ATTR *oamBuf, 
    const Position *scr_pos, const ScreenDimension *scr_dim);

void werewolf_getBoundingBox(const CharacterAttr* character, 
	int *count, BoundingBox *boundingBox);

void werewolf_checkMapCollision(CharacterAttr* character, const MapInfo* mapInfo);
	
void werewolf_checkCollision(const CharacterAttr* character, bool isOtherCharBelow,
	bool *checkNext, const CharacterAttr* otherCharacter);
	
CharFuncAction werewolf_actions[] = {
	NULL,
	&werewolf_actionWalk
};

void werewolf_doAction(CharacterAttr* character, const MapInfo *mapInfo, 
    const CharacterCollection *characterCollection);

void werewolf_init(CharacterAttr* character, ControlTypePool* controlPool) {

//use library to get id
	character->id = 0;
	//use enum of character type
	character->type = WEREWOLF;
	
	//set to 0
	commonCharacterInit(character, EWerewolfInitialize, EWerewolfWalk, EDown);
	commonCharacterSetPosition(character, 0, 0, 0, EDown);
	character->controller = &werewolf_scanSurroundings;
	character->doAction = &werewolf_doAction;
	character->setPosition = &werewolf_setPosition;
	//character->getBounds = &werewolf_getBounds;
	character->getBounds = &werewolf_getBoundingBox;
	character->checkCollision = &werewolf_checkCollision;
	character->checkMapCollision = werewolf_checkMapCollision;
		
	character->spriteDisplay.baseImageId = sprite_vram_findId();
	character->spriteDisplay.imageUpdateStatus = EUpdate;
	character->spriteDisplay.basePalleteId = sprite_palette_findId(WEREWOLF, WEREWOLF_PAL_CNT);
	sprite_palette_copy32_ID(werewolfupperbody_run_down_pal, character->spriteDisplay.basePalleteId);
	character->spriteDisplay.palleteUpdateStatus = EUpdate;
}

void werewolf_doAction(CharacterAttr* character,
	const MapInfo *mapInfo, const CharacterCollection *characterCollection) {
	
	int boundBoxCount = 0;
	CharBoundingBox boundingBox;
	
	if (character->nextAction < EWerewolfActionCount) {
		werewolf_actions[character->nextAction](character, mapInfo, characterCollection);
	}
	
	//TODO Check BG collision here
	character->getBounds(character, &boundBoxCount, &boundingBox);
	//mapInfo->collisionCheck(mapInfo, &boundingBox, character->direction);
}

void werewolf_actionWalk(CharacterAttr* character,
	const MapInfo *mapInfo, const CharacterCollection *characterCollection) {
	
	bool isLastFrame = false;
	character->spriteDisplay.imageUpdateStatus = ENoUpdate;
	character->spriteDisplay.palleteUpdateStatus = ENoUpdate;
	if (updateAnimation(character) == EUpdate) {
		character->spriteDisplay.imageUpdateStatus = EUpdate;
		character->spriteDisplay.palleteUpdateStatus = EUpdate;
	}
	
	character->action = character->nextAction;
	character->direction = character->nextDirection;
		
	//character->position.x +=
	//	alisa_runOffsetX[0][character->direction];
		
	//character->position.y +=
	//	alisa_runOffsetY[0][character->direction];
		
	character->spriteDisplay.spriteSet = werewolfRun[EDown];
}

int werewolf_setPosition(CharacterAttr* character,
	OBJ_ATTR *oamBuf, 
	const Position *scr_pos,
	const ScreenDimension *scr_dim) 
{

	int charStartX, charStartY, charEndX, charEndY;
	
	character->spriteDisplay.baseY = CONVERT_TO_SCRYPOS(character->position.y, 
		scr_pos->y, werewolf_scrConversionMeasurements);
	character->spriteDisplay.baseX = CONVERT_TO_SCRXPOS(character->position.x, 
		scr_pos->x, werewolf_scrConversionMeasurements);
	
	//TODO name these numbers
	charStartX = character->position.x - WEREWOLF_SCREENDISPLAYOFFSET_X;
	charStartY = character->position.y;
	charEndX = character->position.x + WEREWOLF_SCREENDISPLAYOFFSET_X;
	charEndY = character->position.y - WEREWOLF_SCREENDISPLAYOFFSET_Y;
	
	//character->spriteDisplay.isInScreen = true;
	if (commonIsInScreen(charStartX, charEndX, charStartY, charEndY, scr_pos, scr_dim)) {
		character->spriteDisplay.isInScreen = true;
		commonSetToOamBuffer(&character->spriteDisplay, oamBuf);
	
		return character->spriteDisplay.spriteSet->set[character->spriteDisplay.currentAnimationFrame].numberOflayers;
	}
	
	character->spriteDisplay.isInScreen = false;
	return 0;
}

void werewolf_getBounds(const CharacterAttr* character, 
	int *count, CharBoundingBox *boundingBox) {
	*count = 1;
	u16 x = CONVERT_TO_BOUNDINGBOX_X(character->position.x, werewolf_boundingBoxMeasurements);
	u16 y = CONVERT_TO_BOUNDINGBOX_Y(character->position.y, werewolf_boundingBoxMeasurements);
	boundingBox->upperLeftPt.x = x;
	boundingBox->upperLeftPt.y = y;
	boundingBox->upperLeftPt.z = 0;
	boundingBox->length = werewolf_boundingBoxMeasurements[EBBCnvrtLength];
	boundingBox->width = werewolf_boundingBoxMeasurements[EBBCnvrtWidth];
	boundingBox->height = werewolf_boundingBoxMeasurements[EBBCnvrtHeight];
}

void werewolf_getBoundingBox(const CharacterAttr* character, 
	int *count, BoundingBox *boundingBox) {
	*count = 1;
	u16 x = CONVERT_TO_BOUNDINGBOX_X(character->position.x, werewolf_boundingBoxMeasurements);
	u16 y = CONVERT_TO_BOUNDINGBOX_Y(character->position.y, werewolf_boundingBoxMeasurements);
	boundingBox->startX = x;
	boundingBox->startY = y;
	boundingBox->endX = x + werewolf_boundingBoxMeasurements[EBBCnvrtLength];
	boundingBox->endY = y + werewolf_boundingBoxMeasurements[EBBCnvrtWidth];
	//boundingBox->height = werewolf_boundingBoxMeasurements[EBBCnvrtHeight];
}

void werewolf_checkMapCollision(CharacterAttr* character, const MapInfo* mapInfo) {
}

void werewolf_checkCollision(const CharacterAttr* character, bool isOtherCharBelow,
	bool *checkNext, const CharacterAttr* otherCharacter) {
	
	int count;
	BoundingBox charBoundingBox, otherCharBoundingBox;
	character->getBounds(character, &count, &charBoundingBox);
	otherCharacter->getBounds(otherCharacter, &count, &otherCharBoundingBox);
	 
	*checkNext = common_checkNext(isOtherCharBelow, &charBoundingBox, &otherCharBoundingBox);
	if (!*checkNext) {
		return;
	}
}
