#include <stdlib.h>
#include <stdbool.h>
#include "GBATypes.h"
#include "GBAObject.h"
#include "GBAVideo.h"
#include "GBADMA.h"
#include "GBACharacterActionEvent.h"
#include "UtilCommonValues.h"
#include "SpriteSetAlisa.h"
#include "ManagerVram.h"
#include "ManagerSound.h"
#include "ManagerCharacterActionEvents.h"
#include "CharacterAlisa.h"
#include "CharacterCommon.h"
#include "MapCommon.h"
#include "GBAMap.h"

#define alisa_IMAGE_COUNT 1
#define alisa_PALETTE_COUNT 1

#define alisa_RUN_MVMNT_CTRL_MAX 5
//#define alisa_DASH_MVMNT_CTRL_MAX 3
#define alisa_DASH_MVMNT_CTRL_MAX 4

#define ALISA_RISING_ANIMATION_FRAME 2
#define ALISA_JUMP_MOVEMENT 3
#define ALISA_FALLING_MOVEMENT 3

#define SLASH_STARTSOUND_FRAME 3
#define DASH_STARTMOVE_FRAME 1
#define ALISA_NATTACK_ZPOS_OFFSET 16

extern const EDirections directions[EDirectionsCount];
extern const Sound soundeffect_slash;

const s32 alisa_runOffsetX[EDirectionsCount][alisa_RUN_MVMNT_CTRL_MAX] = {
	{0,0,0,0,0},
    {2*MOVE_DIAG,1*MOVE_DIAG,2*MOVE_DIAG,1*MOVE_DIAG,2*MOVE_DIAG},
	{2*MOVE_STR,1*MOVE_STR,2*MOVE_STR,1*MOVE_STR,2*MOVE_STR},
	{2*MOVE_DIAG,1*MOVE_DIAG,2*MOVE_DIAG,1*MOVE_DIAG,2*MOVE_DIAG},
	{0,0,0,0,0},
	{-2*MOVE_DIAG,-1*MOVE_DIAG,-2*MOVE_DIAG,-1*MOVE_DIAG,-2*MOVE_DIAG},
	{-2*MOVE_STR,-1*MOVE_STR,-2*MOVE_STR,-1*MOVE_STR,-2*MOVE_STR},
	{-2*MOVE_DIAG,-1*MOVE_DIAG,-2*MOVE_DIAG,-1*MOVE_DIAG,-2*MOVE_DIAG}
};

const s32 alisa_runOffsetY[EDirectionsCount][alisa_RUN_MVMNT_CTRL_MAX] = {
	{2*MOVE_STR,1*MOVE_STR,2*MOVE_STR,1*MOVE_STR,2*MOVE_STR},
	{2*MOVE_DIAG,1*MOVE_DIAG,2*MOVE_DIAG,1*MOVE_DIAG,2*MOVE_DIAG},
	{0,0,0,0,0},
	{-2*MOVE_DIAG,-1*MOVE_DIAG,-2*MOVE_DIAG,-1*MOVE_DIAG,-2*MOVE_DIAG},
	{-2*MOVE_STR,-1*MOVE_STR,-2*MOVE_STR,-1*MOVE_STR,-2*MOVE_STR},
	{-2*MOVE_DIAG,-1*MOVE_DIAG,-2*MOVE_DIAG,-1*MOVE_DIAG,-2*MOVE_DIAG},
	{0,0,0,0,0},
	{2*MOVE_DIAG,1*MOVE_DIAG,2*MOVE_DIAG,1*MOVE_DIAG,2*MOVE_DIAG}
};

const s32 alisa_dashOffsetX[EDirectionsCount][alisa_DASH_MVMNT_CTRL_MAX] = {
	{0,0,0},
	{4*MOVE_DIAG,4*MOVE_DIAG,4*MOVE_DIAG,4*MOVE_DIAG},
	{4*MOVE_STR,4*MOVE_STR,4*MOVE_STR,4*MOVE_STR},
	{4*MOVE_DIAG,4*MOVE_DIAG,4*MOVE_DIAG,4*MOVE_DIAG},
	{0,0,0},
	{-4*MOVE_DIAG,-4*MOVE_DIAG,-4*MOVE_DIAG,-4*MOVE_DIAG},
	{-4*MOVE_STR,-4*MOVE_STR,-4*MOVE_STR,-4*MOVE_STR},
	{-4*MOVE_DIAG,-4*MOVE_DIAG,-4*MOVE_DIAG,-4*MOVE_DIAG}
};

const s32 alisa_dashOffsetY[EDirectionsCount][alisa_DASH_MVMNT_CTRL_MAX] = {
	{4*MOVE_STR,4*MOVE_STR,4*MOVE_STR,4*MOVE_STR},
	{4*MOVE_DIAG,4*MOVE_DIAG,4*MOVE_DIAG,4*MOVE_DIAG},
	{0,0,0},
	{-4*MOVE_DIAG,-4*MOVE_DIAG,-4*MOVE_DIAG,-4*MOVE_DIAG},
	{-4*MOVE_STR,-4*MOVE_STR,-4*MOVE_STR,-4*MOVE_STR},
	{-4*MOVE_DIAG,-4*MOVE_DIAG,-4*MOVE_DIAG,-4*MOVE_DIAG},
	{0,0,0},
	{4*MOVE_DIAG,4*MOVE_DIAG,4*MOVE_DIAG,4*MOVE_DIAG}
};

const s32 alisa_jumpOffset[] = {1*MOVE_STR, 2*MOVE_STR, 2*MOVE_STR};
const s32 alisa_zOffsetDown[3] =  {-1*MOVE_STR, -2*MOVE_STR, -2*MOVE_STR};

const s32 alisa_jumpOffsetX[EDirectionsCount][1] = {
	{0},
	{1*MOVE_DIAG},
	{1*MOVE_STR},
	{1*MOVE_DIAG},
	{0},
	{-1*MOVE_DIAG},
	{-1*MOVE_STR},
	{-1*MOVE_DIAG}
};

const s32 alisa_jumpOffsetY[EDirectionsCount][1] = {
	{1*MOVE_STR},
	{1*MOVE_DIAG},
	{0},
	{-1*MOVE_DIAG},
	{-1*MOVE_STR},
	{-1*MOVE_DIAG},
	{0},
	{1*MOVE_DIAG}
};

#define ALISA_SCRCNVRTWIDTH 16
#define ALISA_SCRCNVRTHEIGHT 26

#define ALISA_LENGTH 12
#define ALISA_WIDTH 12
#define ALISA_HEIGHT 26

#define ALISA_PAL_CNT 2

#define ALISA_NORMALSLASH_ANIMATIONFRAME_START_COLLISION 2
#define ALISA_NORMALSLASH_ANIMATIONFRAME_END_COLLISION 3
#define ALISA_NORMALSLASH_FRAME_END_COLLISION 5

const u8 alisa_scrConversionMeasurements[EScrCnvrtMeasureCount] = {
	ALISA_SCRCNVRTWIDTH,
	ALISA_SCRCNVRTHEIGHT
};

const u8 alisa_boundingBoxMeasurements[EBBCnvrtMeasurementCount] = {
	ALISA_LENGTH,
	ALISA_WIDTH,
	ALISA_HEIGHT,
};

extern const SpriteSet maincharacter_stand;
extern const SpriteSet maincharacter_walk;
extern const unsigned short alisa_standwithsword_side_pal[16];
extern const unsigned short sword_side_set_pal[16];

void alisa_controller(CharacterAttr* alisa);
void alisa_doAction(CharacterAttr *alisa, const MapInfo *mapInfo, const void *dummy, 
    CharacterActionCollection *charActionCollection);
void checkForEvents(CharacterAttr* alisa, MapInfo *mapInfo);
void alisa_actionStand(CharacterAttr* alisa, const MapInfo *mapInfo);
void alisa_actionRun(CharacterAttr* alisa, const MapInfo *mapInfo);
void alisa_actionSlash(CharacterAttr* alisa, const MapInfo *mapInfo, 
	const void *dummy, CharacterActionCollection *charActionCollection);
void alisa_actionPrepareDash(CharacterAttr* alisa, const MapInfo *mapInfo); 
void alisa_actionDashForward(CharacterAttr* alisa, const MapInfo *mapInfo);
void alisa_actionDashBackward(CharacterAttr* alisa, const MapInfo *mapInfo);
void alisa_actionJumpUp(CharacterAttr* alisa, const MapInfo *mapInfo, 
	const void *dummy, CharacterActionCollection *charActionCollection);
void alisa_actionJumpForward(CharacterAttr* alisa, const MapInfo *mapInfo, 
	const void *dummy, CharacterActionCollection *charActionCollection);
void alisa_actionFallingDown(CharacterAttr* alisa, const MapInfo *mapInfo, 
	const void *dummy, CharacterActionCollection *charActionCollection);
void alisa_actionFallingDownForward(CharacterAttr* alisa, const MapInfo *mapInfo, 
	const void *dummy, CharacterActionCollection *charActionCollection);
void alisa_actionStunned(CharacterAttr* alisa, const MapInfo *mapInfo, 
	const void *dummy, CharacterActionCollection *charActionCollection);

//void alisa_fallingDownController(CharacterAttr* character);

int alisa_setPosition(CharacterAttr* alisa, 
	OBJ_ATTR *oamBuf, 	
	const Position *scrpos,
	const ScreenDimension *scrdim);

void alisa_draw(CharacterAttr* alisa);

void alisa_getBounds(const CharacterAttr* alisa, 
	int *count, CharBoundingBox *boundingBox);
	
//void alisa_getBoundingBoxStanding(const CharacterAttr* alisa, 
//	int *count, BoundingBox *boundingBox);

void alisa_getBoundingBoxMoving(const CharacterAttr* alisa, 
	int *count, BoundingBox *boundingBox);

void alisa_checkMapCollision(CharacterAttr* alisa, const MapInfo *mapInfo);

void alisa_checkCollision(CharacterAttr* alisa, bool isOtherCharBelow,
	bool *checkNext, const CharacterAttr* otherCharacter);

void alisa_checkActionEventCollision(CharacterAttr *alisa, CharacterActionCollection *actionEvents);

void transferToBoundingBox(const EventTransfer *transfer, BoundingBox *boundingBox);



const CharFuncAction alisa_actions[] = {
	&alisa_actionStand,
	&alisa_actionRun,
	&alisa_actionSlash,
	&alisa_actionSlash,
	&alisa_actionPrepareDash,
	&alisa_actionDashForward,
	&alisa_actionDashBackward,
	&alisa_actionJumpUp,
	&alisa_actionJumpForward,
	&alisa_actionFallingDown,
	&alisa_actionFallingDownForward,
	&alisa_actionStunned
};

const BoundingBox alisa_slashCollisionBox[8] = {
	{ -8, 8, 8, 24, 8, 18, 0,0,0,0},
	{ -8, 8, 8, 24, 8, 18, 0,0,0,0},
	{ 8, -8, 24, 8, 8, 18, 0,0,0,0},
	{ -8, -8, 8, -24, 8, 18, 0,0,0,0},
	{ -8, -8, 8, -24, 8, 18, 0,0,0,0},
	{ -8, -8, 8, -24, 8, 18, 0,0,0,0},
	{ -8, -8, -24, 8, 8, 18, 0,0,0,0},
	{ -8, 8, 8, 24, 8, 18, 0,0,0,0},
};


void alisa_init(CharacterAttr* alisa, ControlTypePool* controlPool)
{	
	//use library to get id
	alisa->id = 0;
	//use enum of character type
	alisa->type = ALISA;
	
	alisa->spriteDisplay.baseImageId = sprite_vram_findIdByType(ECharSizeSmall);
	alisa->spriteDisplay.imageUpdateStatus = EUpdate;
	alisa->spriteDisplay.basePalleteId = sprite_palette_findId(ALISA, ALISA_PAL_CNT);
	//if (1) {
	    sprite_palette_copy32_ID(alisa_standwithsword_side_pal, alisa->spriteDisplay.basePalleteId);
	    sprite_palette_copy32_ID(sword_side_set_pal, alisa->spriteDisplay.basePalleteId + 1);
	//}
	//alisa->spriteDisplay.palleteUpdateStatus = EUpdate;	
	
	
	commonCharacterInit(alisa, EAlisaInitialize, EAlisaStand, EDown);
	commonCharacterSetPosition(alisa, 0, 0, 1, EDown);
	alisa->controller = &alisa_controller;
	alisa->doAction = &alisa_doAction;
	alisa->setPosition = &alisa_setPosition;
	alisa->getBounds = &alisa_getBoundingBoxStanding;
	alisa->checkCollision = &alisa_checkCollision;
	alisa->checkMapCollision = &alisa_checkMapCollision;
	alisa->checkActionCollision = &alisa_checkActionEventCollision;
	//alisa->free = NULL;
	//CharacterPlayerControl *charControl = mchar_getControlType(controlPool);
	CharacterPlayerControl *charControl = mchar_findFreeControlType(controlPool);
	charControl->type = EControlControlType;
	charControl->currentStatus = EAlisaStatusNormal;
	charControl->buttonB_PressInterval = 0;
	charControl->buttonA_PressInterval = 0;
	charControl->buttonL_Ready = true;
	charControl->buttonR_Ready = true;
	charControl->controlMap.buttonB = &alisa_slashController;
	charControl->controlMap.buttonA = &alisa_prepareDashController;
	charControl->controlMap.buttonL = &alisa_jumpController;
	charControl->controlMap.buttonR = NULL;
	alisa->free = charControl;
	alisa->stats.maxLife = 10;
	alisa->stats.currentLife = 10;
}

void alisa_doAction(CharacterAttr* alisa,
	const MapInfo *mapInfo, const void *dummy, 
	CharacterActionCollection *charActionCollection) {
	
	if (alisa->nextAction < EAlisaActionCount) {
		alisa_actions[alisa->nextAction](alisa, mapInfo, NULL, charActionCollection);
	}
	
	commonCheckForEvents(alisa, mapInfo);
}

int alisa_setPosition(CharacterAttr* alisa,
	OBJ_ATTR *oamBuf, 
	const Position *scr_pos,
	const ScreenDimension *scr_dim) 
{
	int numberOfShadow = 0;
	alisa->spriteDisplay.baseY = CONVERT_TO_SCRYPOS(alisa->position.y, 
		scr_pos->y, alisa_scrConversionMeasurements);
	alisa->spriteDisplay.baseX = CONVERT_TO_SCRXPOS(alisa->position.x, 
		scr_pos->x, alisa_scrConversionMeasurements);
	alisa->spriteDisplay.baseY -= CONVERT_TO_SCRZPOS(alisa->position.z);
	
	//TODO add in screen check
	commonSetToOamBuffer(&alisa->spriteDisplay, oamBuf);
	alisa->spriteDisplay.isInScreen = true;
	
	numberOfShadow = commonSetShadow(alisa->spriteDisplay.baseX, 
			alisa->spriteDisplay.baseY + alisa->distanceFromGround + ALISA_SCRCNVRTHEIGHT,
			&oamBuf[alisa->spriteDisplay.spriteSet->set[alisa->spriteDisplay.currentAnimationFrame].numberOflayers]);

    return alisa->spriteDisplay.spriteSet->set[alisa->spriteDisplay.currentAnimationFrame].numberOflayers + numberOfShadow;
}

void alisa_actionStand(CharacterAttr* alisa,
	const MapInfo *mapInfo) {
    bool isLastFrame = false;

	alisa->spriteDisplay.imageUpdateStatus = ENoUpdate;
	alisa->spriteDisplay.palleteUpdateStatus = ENoUpdate;
	if (commonInitializeAction(alisa) == EUpdate) {
		alisa->spriteDisplay.currentAnimationFrame = 0;
		alisa->spriteDisplay.imageUpdateStatus = EUpdate;
		alisa->spriteDisplay.palleteUpdateStatus = EUpdate;
	}
	
	alisa->delta.x = 0;
	alisa->delta.y = 0;
	alisa->action = alisa->nextAction;
	alisa->direction = alisa->nextDirection;
	
	commonGravityEffect(alisa, alisa_zOffsetDown[alisa->movementCtrl.currentFrame&1]);
	
	alisa->movementCtrl.maxFrames = 0;
	alisa->movementCtrl.currentFrame = 0;
	
	alisa->spriteDisplay.spriteSet = alisaStandWithSwordSet[alisa->faceDirection];
	//alisa->spriteDisplay.spriteSet = &maincharacter_stand;
}

void alisa_actionRun(CharacterAttr* alisa, const MapInfo *mapInfo) {
    bool isLastFrame = false;
	alisa->spriteDisplay.imageUpdateStatus = ENoUpdate;
	alisa->spriteDisplay.palleteUpdateStatus = ENoUpdate;
	if (commonUpdateAnimation(alisa) == EUpdate) {
		alisa->spriteDisplay.imageUpdateStatus = EUpdate;
		alisa->spriteDisplay.palleteUpdateStatus = EUpdate;
	}
	
	if (alisa->action != alisa->nextAction) {
	    alisa->movementCtrl.maxFrames = alisa_RUN_MVMNT_CTRL_MAX;
		alisa->movementCtrl.currentFrame = 0;
	}
	
	alisa->action = alisa->nextAction;
	alisa->direction = alisa->nextDirection;
	
	alisa->movementCtrl.currentFrame = (!(alisa->movementCtrl.currentFrame >= alisa->movementCtrl.maxFrames))*
	    alisa->movementCtrl.currentFrame;

	//mprinter_printf("JAPANESE %d\n", 'か');
	//mprinter_printf("JAPANESE2 %d\n", 'め');
	//mprinter_printf("JAPANESE3 %d\n", '火');
	alisa->delta.x = alisa_runOffsetX[alisa->direction][alisa->movementCtrl.currentFrame];
	alisa->position.x += alisa->delta.x;
	
	alisa->delta.y = alisa_runOffsetY[alisa->direction][alisa->movementCtrl.currentFrame];
	alisa->position.y += alisa->delta.y;
	
	commonGravityEffect(alisa, alisa_zOffsetDown[alisa->movementCtrl.currentFrame&1]);
	
	++alisa->movementCtrl.currentFrame;
	//alisa->spriteDisplay.spriteSet = alisaRunSet[alisa->direction];
	alisa->spriteDisplay.spriteSet = alisaRunSet[alisa->faceDirection];
	//alisa->spriteDisplay.spriteSet = &maincharacter_walk;
}

void alisa_actionSlash(CharacterAttr* alisa, const MapInfo *mapInfo, 
	const void *dummy, CharacterActionCollection *charActionCollection) {
	BoundingBox position;
	Position collisionPoints[2];
	int attackVal = 1;
	alisa->spriteDisplay.imageUpdateStatus = ENoUpdate;
	alisa->spriteDisplay.palleteUpdateStatus = ENoUpdate;
	
	commonGravityEffect(alisa, alisa_zOffsetDown[alisa->movementCtrl.currentFrame&1]);
	if (commonUpdateAnimation(alisa) == EUpdate) {
		alisa->spriteDisplay.imageUpdateStatus = EUpdate;
		alisa->spriteDisplay.palleteUpdateStatus = EUpdate;
	}
	
	alisa->delta.x = 0;
	alisa->delta.y = 0;
	alisa->movementCtrl.maxFrames = 0;
	alisa->movementCtrl.currentFrame = 0;
	
	alisa->action = alisa->nextAction;
	alisa->direction = alisa->nextDirection;
	
	if (alisa->spriteDisplay.currentAnimationFrame >= ALISA_NORMALSLASH_ANIMATIONFRAME_START_COLLISION) {
		BoundingBox collisionBox;
		collisionBox.startX = CONVERT_2POS(alisa->position.x) + alisa_slashCollisionBox[alisa->direction].startX;
		collisionBox.startY = CONVERT_2POS(alisa->position.y) + alisa_slashCollisionBox[alisa->direction].startY;
		collisionBox.startZ = CONVERT_2POS(alisa->position.z) + alisa_slashCollisionBox[alisa->direction].startZ;
		collisionBox.endX = CONVERT_2POS(alisa->position.x) + alisa_slashCollisionBox[alisa->direction].endX;
		collisionBox.endY = CONVERT_2POS(alisa->position.y) + alisa_slashCollisionBox[alisa->direction].endY;
		collisionBox.endZ = CONVERT_2POS(alisa->position.z) + alisa_slashCollisionBox[alisa->direction].endZ;
		mchar_actione_add(charActionCollection, EActionAttack, attackVal, 1, &collisionBox);
	}
	
	if (alisa->spriteDisplay.currentAnimationFrame == SLASH_STARTSOUND_FRAME && alisa->spriteDisplay.numberOfFramesPassed == 0) {
		msound_setChannel(&soundeffect_slash, false);
	}
	
	alisa->spriteDisplay.spriteSet = alisaSlashSet[alisa->direction];
}

void alisa_actionPrepareDash(CharacterAttr* alisa, const MapInfo *mapInfo) {
    bool isLastFrame = false;
	alisa->spriteDisplay.imageUpdateStatus = ENoUpdate;
	alisa->spriteDisplay.palleteUpdateStatus = ENoUpdate;
	
	commonGravityEffect(alisa, alisa_zOffsetDown[alisa->movementCtrl.currentFrame&1]);
	if (commonUpdateAnimation(alisa) == EUpdate) {
		alisa->spriteDisplay.imageUpdateStatus = EUpdate;
		alisa->spriteDisplay.palleteUpdateStatus = EUpdate;
	}
	
	alisa->movementCtrl.maxFrames = 0;
	alisa->movementCtrl.currentFrame = 0;
	
	alisa->action = alisa->nextAction;
	alisa->direction = alisa->nextDirection;
	
	alisa->movementCtrl.currentFrame = (!(alisa->movementCtrl.currentFrame >= alisa->movementCtrl.maxFrames))*
	    alisa->movementCtrl.currentFrame;

	alisa->spriteDisplay.spriteSet = alisaPrepareDashSet[alisa->faceDirection];
}

void alisa_actionDashForward(CharacterAttr* alisa, const MapInfo *mapInfo) {
    bool isLastFrame = false;
	alisa->spriteDisplay.imageUpdateStatus = ENoUpdate;
	alisa->spriteDisplay.palleteUpdateStatus = ENoUpdate;
	if (commonUpdateAnimation(alisa) == EUpdate) {
		alisa->spriteDisplay.imageUpdateStatus = EUpdate;
		alisa->spriteDisplay.palleteUpdateStatus = EUpdate;
	}
	
	if (alisa->action != alisa->nextAction) {
	    alisa->movementCtrl.maxFrames = alisa_DASH_MVMNT_CTRL_MAX;
		alisa->movementCtrl.currentFrame = 0;
	}
	
	alisa->action = alisa->nextAction;
	alisa->direction = alisa->nextDirection;
	
	alisa->movementCtrl.currentFrame = (!(alisa->movementCtrl.currentFrame >= alisa->movementCtrl.maxFrames))*
	    alisa->movementCtrl.currentFrame;

	if (alisa->spriteDisplay.currentAnimationFrame == DASH_STARTMOVE_FRAME) {
		alisa->delta.x = alisa_dashOffsetX[alisa->direction][alisa->movementCtrl.currentFrame];
		alisa->position.x += alisa->delta.x;
		
		alisa->delta.y = alisa_dashOffsetY[alisa->direction][alisa->movementCtrl.currentFrame];
		alisa->position.y += alisa->delta.y;
	}
		
	
	++alisa->movementCtrl.currentFrame;
	alisa->spriteDisplay.spriteSet = alisaDashForwardSet[alisa->faceDirection];
}

void alisa_actionDashBackward(CharacterAttr* alisa, const MapInfo *mapInfo) {
    bool isLastFrame = false;
	alisa->spriteDisplay.imageUpdateStatus = ENoUpdate;
	alisa->spriteDisplay.palleteUpdateStatus = ENoUpdate;
	if (commonUpdateAnimation(alisa) == EUpdate) {
		alisa->spriteDisplay.imageUpdateStatus = EUpdate;
		alisa->spriteDisplay.palleteUpdateStatus = EUpdate;
	}
	
	if (alisa->action != alisa->nextAction) {
	    alisa->movementCtrl.maxFrames = alisa_DASH_MVMNT_CTRL_MAX;
		alisa->movementCtrl.currentFrame = 0;
	}
	
	alisa->action = alisa->nextAction;
	alisa->direction = alisa->nextDirection;
	
	alisa->movementCtrl.currentFrame = (!(alisa->movementCtrl.currentFrame >= alisa->movementCtrl.maxFrames))*
	    alisa->movementCtrl.currentFrame;

	if (alisa->spriteDisplay.currentAnimationFrame == 0) {
		alisa->delta.x = alisa_dashOffsetX[alisa->direction][alisa->movementCtrl.currentFrame];
		alisa->position.x += alisa->delta.x;
		
		alisa->delta.y = alisa_dashOffsetY[alisa->direction][alisa->movementCtrl.currentFrame];
		alisa->position.y += alisa->delta.y;
	}
	
	++alisa->movementCtrl.currentFrame;
	alisa->spriteDisplay.spriteSet = alisaDashBackwardWithSwordSet[alisa->faceDirection];
}

void alisa_actionJumpUp(CharacterAttr* alisa, const MapInfo *mapInfo, 
	const void *dummy, CharacterActionCollection *charActionCollection) {
	bool isLastFrame = false;

	alisa->spriteDisplay.imageUpdateStatus = ENoUpdate;
	alisa->spriteDisplay.palleteUpdateStatus = ENoUpdate;
	if (commonUpdateAnimation(alisa) == EUpdate) {
		alisa->spriteDisplay.imageUpdateStatus = EUpdate;
		alisa->spriteDisplay.palleteUpdateStatus = EUpdate;
	}
	
	if (alisa->action != alisa->nextAction) {
		alisa->movementCtrl.maxFrames = ALISA_JUMP_MOVEMENT;
	}
	
	alisa->action = alisa->nextAction;
	alisa->direction = alisa->nextDirection;
	
	alisa->movementCtrl.currentFrame = (!(alisa->movementCtrl.currentFrame >= alisa->movementCtrl.maxFrames))*
	    alisa->movementCtrl.currentFrame;

	if (alisa->spriteDisplay.currentAnimationFrame < ALISA_RISING_ANIMATION_FRAME) {
		alisa->delta.z = alisa_jumpOffset[alisa->movementCtrl.currentFrame];
		alisa->position.z += alisa->delta.z;
	}
	
	++alisa->movementCtrl.currentFrame;
	alisa->spriteDisplay.spriteSet = alisaJumpWithSwordSet[alisa->faceDirection];
}

void alisa_actionJumpForward(CharacterAttr* alisa, const MapInfo *mapInfo, 
	const void *dummy, CharacterActionCollection *charActionCollection) {
	bool isLastFrame = false;

	alisa->spriteDisplay.imageUpdateStatus = ENoUpdate;
	alisa->spriteDisplay.palleteUpdateStatus = ENoUpdate;
	if (commonUpdateAnimation(alisa) == EUpdate) {
		alisa->spriteDisplay.imageUpdateStatus = EUpdate;
		alisa->spriteDisplay.palleteUpdateStatus = EUpdate;
	}
	
	if (alisa->action != alisa->nextAction) {
		alisa->movementCtrl.maxFrames = ALISA_JUMP_MOVEMENT;
	}
	
	alisa->action = alisa->nextAction;
	alisa->direction = alisa->nextDirection;
	
	alisa->movementCtrl.currentFrame = (!(alisa->movementCtrl.currentFrame >= alisa->movementCtrl.maxFrames))*
	    alisa->movementCtrl.currentFrame;

	if (alisa->spriteDisplay.currentAnimationFrame < ALISA_RISING_ANIMATION_FRAME) {
		alisa->delta.z = alisa_jumpOffset[alisa->movementCtrl.currentFrame];
		alisa->position.z += alisa->delta.z;
		alisa->delta.x = alisa_jumpOffsetX[alisa->direction][0];
		alisa->position.x += alisa->delta.x;
		alisa->delta.y = alisa_jumpOffsetY[alisa->direction][0];
		alisa->position.y += alisa->delta.y;
	} else {
		alisa->delta.x = alisa_jumpOffsetX[alisa->direction][0];
		alisa->position.x += alisa->delta.x;
		alisa->delta.y = alisa_jumpOffsetY[alisa->direction][0];
		alisa->position.y += alisa->delta.y;
	}
	
	++alisa->movementCtrl.currentFrame;
	alisa->spriteDisplay.spriteSet = alisaJumpWithSwordSet[alisa->faceDirection];
}

void alisa_actionFallingDown(CharacterAttr* alisa, const MapInfo *mapInfo, 
	const void *dummy, CharacterActionCollection *charActionCollection) {
	bool isLastFrame = false;

	alisa->spriteDisplay.imageUpdateStatus = ENoUpdate;
	alisa->spriteDisplay.palleteUpdateStatus = ENoUpdate;
	if (commonUpdateAnimation(alisa) == EUpdate) {
		alisa->spriteDisplay.imageUpdateStatus = EUpdate;
		alisa->spriteDisplay.palleteUpdateStatus = EUpdate;
	}
	
	if (alisa->action != alisa->nextAction) {
		alisa->movementCtrl.maxFrames = ALISA_FALLING_MOVEMENT;
	}
	
	alisa->action = alisa->nextAction;
	alisa->direction = alisa->nextDirection;
	
	alisa->movementCtrl.currentFrame = (!(alisa->movementCtrl.currentFrame >= alisa->movementCtrl.maxFrames))*
	    alisa->movementCtrl.currentFrame;

	commonGravityEffect(alisa, alisa_zOffsetDown[alisa->movementCtrl.currentFrame]);
	
	
	++alisa->movementCtrl.currentFrame;
	alisa->spriteDisplay.spriteSet = alisaFallingDownSet[alisa->faceDirection];
}

void alisa_actionFallingDownForward(CharacterAttr* alisa, const MapInfo *mapInfo, 
	const void *dummy, CharacterActionCollection *charActionCollection) {
	bool isLastFrame = false;

	alisa->spriteDisplay.imageUpdateStatus = ENoUpdate;
	alisa->spriteDisplay.palleteUpdateStatus = ENoUpdate;
	if (commonUpdateAnimation(alisa) == EUpdate) {
		alisa->spriteDisplay.imageUpdateStatus = EUpdate;
		alisa->spriteDisplay.palleteUpdateStatus = EUpdate;
	}
	
	if (alisa->action != alisa->nextAction) {
		alisa->movementCtrl.maxFrames = ALISA_FALLING_MOVEMENT;
	}
	
	alisa->action = alisa->nextAction;
	alisa->direction = alisa->nextDirection;
	
	alisa->movementCtrl.currentFrame = (!(alisa->movementCtrl.currentFrame >= alisa->movementCtrl.maxFrames))*
	    alisa->movementCtrl.currentFrame;

	commonGravityEffect(alisa, alisa_zOffsetDown[alisa->movementCtrl.currentFrame]);
	
	alisa->delta.x = alisa_jumpOffsetX[alisa->direction][0];
	alisa->position.x += alisa->delta.x;
	alisa->delta.y = alisa_jumpOffsetY[alisa->direction][0];
	alisa->position.y += alisa->delta.y;
		
	++alisa->movementCtrl.currentFrame;
	alisa->spriteDisplay.spriteSet = alisaFallingDownSet[alisa->faceDirection];
}

void alisa_actionStunned(CharacterAttr* alisa, const MapInfo *mapInfo, 
	const void *dummy, CharacterActionCollection *charActionCollection) {
	BoundingBox position;
	Position collisionPoints[2];
	int attackVal = 1, countPoints = 2;
	alisa->spriteDisplay.imageUpdateStatus = ENoUpdate;
	alisa->spriteDisplay.palleteUpdateStatus = ENoUpdate;
	
	commonGravityEffect(alisa, alisa_zOffsetDown[alisa->movementCtrl.currentFrame&1]);
	
	if (commonUpdateAnimation(alisa) == EUpdate) {
		alisa->spriteDisplay.imageUpdateStatus = EUpdate;
		alisa->spriteDisplay.palleteUpdateStatus = EUpdate;
	}
	
	alisa->movementCtrl.maxFrames = 0;
	alisa->movementCtrl.currentFrame = 0;
	
	alisa->delta.x = 0;
	alisa->delta.y = 0;
	alisa->action = alisa->nextAction;
	alisa->direction = alisa->nextDirection;
	
	alisa->spriteDisplay.spriteSet = alisaStunnedSet[alisa->direction];
}

void alisa_getBoundingBoxMoving(const CharacterAttr* alisa, 
	int *count, BoundingBox *boundingBox) {
	*count = 1;
	u16 x = CONVERT_TO_BOUNDINGBOX_X(alisa->position.x, alisa_boundingBoxMeasurements);
	u16 y = CONVERT_TO_BOUNDINGBOX_Y(alisa->position.y, alisa_boundingBoxMeasurements);
	s16 z = commonConvertBoundingBoxZ(alisa->position.z);
		
	boundingBox->startX = x;
	boundingBox->startY = y;
	boundingBox->endX = x + alisa_boundingBoxMeasurements[EBBCnvrtLength];
	boundingBox->endY = y + alisa_boundingBoxMeasurements[EBBCnvrtWidth];
	boundingBox->startZ = z;
	boundingBox->endZ = z + ALISA_HEIGHT;
	/*if (alisa->position.z < 0)
		mprinter_printf("ALISA MOV -%d -%d\n", -boundingBox->startZ, -alisa->position.z);
	else
		mprinter_printf("ALISA MOV %d %d\n", boundingBox->startZ, alisa->position.z);*/
	//boundingBox->height = alisa_boundingBoxMeasurements[EBBCnvrtHeight];
	/*boundingBox->direction = alisa->direction;
	boundingBox->isMoving = true;
	boundingBox->isMovable = false;*/
}

void alisa_getBoundingBoxStanding(const CharacterAttr* alisa, 
	int *count, BoundingBox *boundingBox) {
	*count = 1;
	u16 x = CONVERT_TO_BOUNDINGBOX_X(alisa->position.x, alisa_boundingBoxMeasurements);
	u16 y = CONVERT_TO_BOUNDINGBOX_Y(alisa->position.y, alisa_boundingBoxMeasurements);
	s16 z = commonConvertBoundingBoxZ(alisa->position.z);
		
	boundingBox->startX = x;
	boundingBox->startY = y;
	boundingBox->endX = x + alisa_boundingBoxMeasurements[EBBCnvrtLength];
	boundingBox->endY = y + alisa_boundingBoxMeasurements[EBBCnvrtWidth];
	boundingBox->startZ = z;
	boundingBox->endZ = z + ALISA_HEIGHT;
	/*if (alisa->position.z < 0)
		mprinter_printf("ALISA MOV -%d -%d\n", -boundingBox->startZ, -alisa->position.z);
	else
		mprinter_printf("ALISA MOV %d %d\n", boundingBox->startZ, alisa->position.z);*/
	/*boundingBox->direction = alisa->direction;
	boundingBox->isMoving = false;
	boundingBox->isMovable = false;*/
}

const int alisa_mapCollisionXAdjust[] = {3, -3, 3, -3};
const int alisa_mapCollisionYAdjust[] = {3, 3, -3, -3};

//int xAdjust[] = {0, 0, 0, 0};
//int yAdjust[] = {0, 0, 0, 0};
void alisa_checkMapCollision(CharacterAttr* alisa, const MapInfo* mapInfo) {
    commonCharacterMapEdgeCheck(alisa, mapInfo);
	int count;
	BoundingBox mapBoundingBox, characterBoundingBox;
	CharacterPlayerControl *charControl = (CharacterAIControl*)alisa->free;
	int fallingDown = 1024;
	
	alisa->getBounds(alisa, &count, &characterBoundingBox);
	
	for (int i = 0; i < 4; ++i) {
		commonGetBoundsFromMap(CONVERT_2POS(alisa->position.x) + alisa_mapCollisionXAdjust[i], 
			CONVERT_2POS(alisa->position.y) + alisa_mapCollisionYAdjust[i], mapInfo, &mapBoundingBox);
		int dist = common_fallingDown(alisa, &characterBoundingBox, &mapBoundingBox);
		if (dist < fallingDown) {
			fallingDown = dist;
		}
	}
	
	if (fallingDown > 0 ) {
		//mprinter_printf("MAP FALLING %d\n", fallingDown);
		alisa->nextAction = EAlisaFallingDown;
		commonFallingDownCollision(alisa, mapInfo);
	} else if ((alisa->nextAction == EAlisaFallingDown ||  
		alisa->nextAction == EAlisaFallingDownForward) && fallingDown <= 0) {
		//mprinter_printf("MAP STAND\n");
		alisa->nextAction = EAlisaStand;
	}
	
	if (fallingDown >= 0 && fallingDown < alisa->distanceFromGround) {
		alisa->distanceFromGround = fallingDown;
	}
	
	common_mapCollision[alisa->direction](alisa, mapInfo, 
	    common_mapCollisionReactions[alisa->direction]);
}

void alisa_checkCollision(CharacterAttr* alisa, bool isOtherCharBelow,
	bool *checkNext, const CharacterAttr* otherCharacter) {
	
	int count, fallingDistance;
	BoundingBox alisaBoundingBox, otherCharBoundingBox;
	
	*checkNext = common_checkNext(isOtherCharBelow, &alisa->position, &otherCharacter->position);
	if (!*checkNext) {
		return;
	}
	
	alisa->getBounds(alisa, &count, &alisaBoundingBox);
	otherCharacter->getBounds(otherCharacter, &count, &otherCharBoundingBox);
	
	if (alisa->distanceFromGround != 0) {
		fallingDistance = common_fallingDownOnChar(alisa, &alisaBoundingBox, &otherCharBoundingBox);
		if (fallingDistance != 0) {
			alisa->nextAction = EAlisaFallingDown;
		} else if ((alisa->nextAction == EAlisaFallingDown || 
			alisa->nextAction == EAlisaFallingDownForward) && fallingDistance == 0) {
			alisa->nextAction = EAlisaStand;
		}
		
		if (fallingDistance >= 0 && fallingDistance < alisa->distanceFromGround ) {
			alisa->distanceFromGround = fallingDistance;
		}
	}
	alisa->getBounds(alisa, &count, &alisaBoundingBox);
	common_collisionReactions[alisa->direction]
	    (alisa, &alisaBoundingBox, &otherCharBoundingBox);
}

void alisa_checkActionEventCollision(CharacterAttr *alisa, CharacterActionCollection *actionEvents) {
    int i, j, count;
	BoundingBox charBoundingBox;
	bool isHit = false;
	CharacterPlayerControl *charControl = (CharacterAIControl*)alisa->free;
	if (alisa->stats.currentStatus == EStatusNoActionCollision) {
		return;
	}
	
	alisa->getBounds(alisa, &count, &charBoundingBox);
	for (i = 0; i < actionEvents->count; ++i) {
		CharacterActionEvent *charActionEvent = &actionEvents->currentActions[i];

		//for (j = 0; j < charActionEvent->count; ++j) {
			//isHit |= commonCollissionPointInBounds(&charActionEvent->collisionPoints[j], &charBoundingBox);
			isHit |= hasCollision(&charActionEvent->collisionBox, &charBoundingBox);
				
		//}
		if (isHit) {
			alisa->stats.currentLife -= 1;
			charControl->currentStatus = EAlisaStatusStunned;
			if (alisa->stats.currentLife <= 0) {
				//gameover
			}
			//break;
		}
	}
}
