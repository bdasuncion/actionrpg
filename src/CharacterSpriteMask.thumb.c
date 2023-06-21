#include <stdlib.h>
#include <stdbool.h>
#include "GBATypes.h"
#include "GBAObject.h"
#include "GBAVideo.h"
#include "GBADMA.h"
#include "GBACharacterActionEvent.h"
#include "UtilCommonValues.h"
#include "ManagerVram.h"
#include "ManagerSound.h"
#include "ManagerCharacterActionEvents.h"
#include "CharacterCommon.h"
#include "MapCommon.h"
#include "CharacterSpriteMask.h"
#include "GBAMap.h"

const u32 spriteMaskImageSize[] = {32, 64, 64, 128};

const u8 mask_boundingBoxMeasurements[][EBBCnvrtMeasurementCount] = {
	{16,16,0},
	{16,32,0},
	{32,16,0},
	{32,32,0},
	{16,16,16},
	{16,32,16},
	{32,16,16},
};

const u8 spritemask_scrConversionMeasurements[][EScrCnvrtMeasureCount] = {
	{16,8},
	{16,16},
	{32,8},
	{32,16},
	{16,24},
	{32,8},
	{16,24},
};

const u8 spritemask_inScreenConversionMeasurements[][EScrCnvrtMeasureCount] = {
	{8,8},
	{8,16},
	{16,8},
	{16,16},
	{16,24},
	{32,8},
	{16,24},
};

const SPRITESHAPE maskShape[] = {
	SQUARE, TALL, WIDE, SQUARE
};

const SPRITESIZE maskSize[] = {
	SMALL_B, MEDIUM, MEDIUM, MEDIUM
};

void spritemask_bounds_8x8(const CharacterAttr* alisa, 
	int *count, BoundingBox *boundingBox) {
}

void spritemask_bounds_8x16(const CharacterAttr* alisa, 
	int *count, BoundingBox *boundingBox) {
}

void spritemask_bounds_16x8(const CharacterAttr* alisa, 
	int *count, BoundingBox *boundingBox) {
}

void spritemask_bounds_16x16(const CharacterAttr* alisa, 
	int *count, BoundingBox *boundingBox) {
}

void spritemask_getBoundingBox(const CharacterAttr* character, 
	int *count, BoundingBox *boundingBox) {
	*count = 1;
	u16 x = CONVERT_TO_BOUNDINGBOX_X(character->position.x, mask_boundingBoxMeasurements[character->type - EMaskTypeStart]);
	u16 y = CONVERT_TO_BOUNDINGBOX_Y(character->position.y, mask_boundingBoxMeasurements[character->type - EMaskTypeStart]);
	s16 z = commonConvertBoundingBoxZ(character->position.z);
		
	boundingBox->startX = x;
	boundingBox->startY = y;
	boundingBox->endX = x + mask_boundingBoxMeasurements[character->type - EMaskTypeStart][EBBCnvrtLength];
	boundingBox->endY = y + mask_boundingBoxMeasurements[character->type - EMaskTypeStart][EBBCnvrtWidth];
	boundingBox->startZ = z;
	boundingBox->endZ = z + mask_boundingBoxMeasurements[character->type - EMaskTypeStart][EBBCnvrtHeight];;
	/*if (alisa->position.z < 0)
		mprinter_printf("ALISA MOV -%d -%d\n", -boundingBox->startZ, -alisa->position.z);
	else
		mprinter_printf("ALISA MOV %d %d\n", boundingBox->startZ, alisa->position.z);*/
	//boundingBox->height = alisa_boundingBoxMeasurements[EBBCnvrtHeight];
	/*boundingBox->direction = character->direction;
	boundingBox->isMoving = false;
	boundingBox->isMovable = false;*/
}

void spritemask_bounds_32x16(const CharacterAttr* alisa, 
	int *count, BoundingBox *boundingBox) {
}

void spritemask_bounds_32x32(const CharacterAttr* alisa, 
	int *count, BoundingBox *boundingBox) {
}

int spritemask_setPosition(CharacterAttr* character,
	OBJ_ATTR *oamBuf, 
	const Position *scr_pos,
	const ScreenDimension *scr_dim);
	
void spritemask_init(CharacterAttr* spritemask, SpriteMaskInit *maskInit)
{	
	//use library to get id
	spritemask->id = 0;
	//use enum of character type
	spritemask->type = maskInit->type;
	
	commonCharacterSetPosition(spritemask, maskInit->x, maskInit->y, maskInit->z, EDown);
	spritemask->controller = &commonDummy;
	spritemask->doAction = &commonDummy;
	spritemask->setPosition = &spritemask_setPosition;
	spritemask->getBounds = &spritemask_getBoundingBox;
	spritemask->checkCollision = &commonDummy;
	spritemask->checkMapCollision = &commonDummy;
	spritemask->checkActionCollision = &commonDummy;
		
	spritemask->spriteDisplay.baseImageId = SPRITEMASK_IDSTART + maskInit->maskId;
	spritemask->spriteDisplay.imageUpdateStatus = EUpdate;
	spritemask->spriteDisplay.basePalleteId = 15;
}

int spritemask_setPosition(CharacterAttr* character,
	OBJ_ATTR *oamBuf, 
	const Position *scr_pos,
	const ScreenDimension *scr_dim) 
{

	int charStartX, charStartY, charEndX, charEndY;
	character->spriteDisplay.baseY = CONVERT_TO_SCRYPOS(character->position.y, 
		scr_pos->y, spritemask_scrConversionMeasurements[character->type - EMaskTypeStart]);
	character->spriteDisplay.baseX = CONVERT_TO_SCRXPOS(character->position.x, 
		scr_pos->x, spritemask_scrConversionMeasurements[character->type - EMaskTypeStart]);
	character->spriteDisplay.baseY -= CONVERT_TO_SCRZPOS(character->position.z);

	/*mprinter_printf("%d %d %d SCR %d %d %d %d\n", CONVERT_2POS(character->position.x), 
	CONVERT_2POS(character->position.y), CONVERT_2POS(character->position.z), 
	EMask16x32, EMaskTypeStart,
	spritemask_scrConversionMeasurements[EMask16x32 - EMaskTypeStart][0],
	spritemask_scrConversionMeasurements[EMask16x32 - EMaskTypeStart][1]);*/
	charStartX = CONVERT_2POS(character->position.x) - spritemask_inScreenConversionMeasurements[character->type - EMaskTypeStart][0];
	charStartY = CONVERT_2POS(character->position.y) - CONVERT_2POS(character->position.z) - spritemask_inScreenConversionMeasurements[character->type - EMaskTypeStart][1];
	charEndX = CONVERT_2POS(character->position.x) + spritemask_inScreenConversionMeasurements[character->type - EMaskTypeStart][0];
	charEndY = CONVERT_2POS(character->position.y) - CONVERT_2POS(character->position.z) + spritemask_inScreenConversionMeasurements[character->type - EMaskTypeStart][1];
	
	if (commonIsInScreen(charStartX, charEndX, charStartY, charEndY, scr_pos, scr_dim)) {
		commonSetToOamBufferAsMask(&character->spriteDisplay, oamBuf, 
			maskShape[character->type - EMaskTypeStart], maskSize[character->type - EMaskTypeStart]);
		character->spriteDisplay.isInScreen = true;
		return 1;
	}

    return 0;
}