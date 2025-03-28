﻿#include <stdlib.h>
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
#include "ManagerPrinter.h"
#include "CharacterAlisa.h"
#include "CharacterCommon.h"
#include "MapCommon.h"
#include "GBAMap.h"
#include "ManagerCharacters.h"
#include "ManagerPrinter.h"
#define ALISA_RUN_MVMNT_CTRL_MAX 5
#define ALISA_DASH_MVMNT_CTRL_MAX 4

#define ALISA_RISING_ANIMATION_FRAME 2
#define ALISA_JUMP_MOVEMENT 3
#define ALISA_FALLING_MOVEMENT 3

#define ALISA_SLASH_STARTSOUND_FRAME 3
#define ALISA_NATTACK_ZPOS_OFFSET 16

extern const EDirections directions[EDirectionsCount];
extern const Sound soundeffect_slash;

const s32 alisa_runOffsetX[EDirectionsCount][ALISA_RUN_MVMNT_CTRL_MAX] = {
	{0,0,0,0,0},
    {2*MOVE_DIAG,1*MOVE_DIAG,2*MOVE_DIAG,1*MOVE_DIAG,2*MOVE_DIAG},
	{2*MOVE_STR,1*MOVE_STR,2*MOVE_STR,1*MOVE_STR,2*MOVE_STR},
	{2*MOVE_DIAG,1*MOVE_DIAG,2*MOVE_DIAG,1*MOVE_DIAG,2*MOVE_DIAG},
	{0,0,0,0,0},
	{-2*MOVE_DIAG,-1*MOVE_DIAG,-2*MOVE_DIAG,-1*MOVE_DIAG,-2*MOVE_DIAG},
	{-2*MOVE_STR,-1*MOVE_STR,-2*MOVE_STR,-1*MOVE_STR,-2*MOVE_STR},
	{-2*MOVE_DIAG,-1*MOVE_DIAG,-2*MOVE_DIAG,-1*MOVE_DIAG,-2*MOVE_DIAG}
};

const s32 alisa_runOffsetY[EDirectionsCount][ALISA_RUN_MVMNT_CTRL_MAX] = {
	{2*MOVE_STR,1*MOVE_STR,2*MOVE_STR,1*MOVE_STR,2*MOVE_STR},
	{2*MOVE_DIAG,1*MOVE_DIAG,2*MOVE_DIAG,1*MOVE_DIAG,2*MOVE_DIAG},
	{0,0,0,0,0},
	{-2*MOVE_DIAG,-1*MOVE_DIAG,-2*MOVE_DIAG,-1*MOVE_DIAG,-2*MOVE_DIAG},
	{-2*MOVE_STR,-1*MOVE_STR,-2*MOVE_STR,-1*MOVE_STR,-2*MOVE_STR},
	{-2*MOVE_DIAG,-1*MOVE_DIAG,-2*MOVE_DIAG,-1*MOVE_DIAG,-2*MOVE_DIAG},
	{0,0,0,0,0},
	{2*MOVE_DIAG,1*MOVE_DIAG,2*MOVE_DIAG,1*MOVE_DIAG,2*MOVE_DIAG}
};

const s32 alisa_dashOffsetX[EDirectionsCount][ALISA_DASH_MVMNT_CTRL_MAX] = {
	{0,0,0},
	{4*MOVE_DIAG,4*MOVE_DIAG,4*MOVE_DIAG,4*MOVE_DIAG},
	{4*MOVE_STR,4*MOVE_STR,4*MOVE_STR,4*MOVE_STR},
	{4*MOVE_DIAG,4*MOVE_DIAG,4*MOVE_DIAG,4*MOVE_DIAG},
	{0,0,0},
	{-4*MOVE_DIAG,-4*MOVE_DIAG,-4*MOVE_DIAG,-4*MOVE_DIAG},
	{-4*MOVE_STR,-4*MOVE_STR,-4*MOVE_STR,-4*MOVE_STR},
	{-4*MOVE_DIAG,-4*MOVE_DIAG,-4*MOVE_DIAG,-4*MOVE_DIAG}
};

const s32 alisa_dashOffsetY[EDirectionsCount][ALISA_DASH_MVMNT_CTRL_MAX] = {
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

const s32 alisa_jumpOffsetX[EDirectionsCount] = {
	{0},
	{1*MOVE_DIAG},
	{1*MOVE_STR},
	{1*MOVE_DIAG},
	{0},
	{-1*MOVE_DIAG},
	{-1*MOVE_STR},
	{-1*MOVE_DIAG}
};

const s32 alisa_jumpOffsetY[EDirectionsCount] = {
	{1*MOVE_STR},
	{1*MOVE_DIAG},
	{0},
	{-1*MOVE_DIAG},
	{-1*MOVE_STR},
	{-1*MOVE_DIAG},
	{0},
	{1*MOVE_DIAG}
};
const CharacterActionType alisa_NormalAttack[EDirectionsCount] = {
	EAttackHorizontalRight,
	EAttackHorizontalRight,
	EAttackHorizontalRight,
	EAttackHorizontalLeft,
	EAttackHorizontalLeft,
	EAttackHorizontalLeft,
	EAttackHorizontalLeft,
	EAttackHorizontalRight
};

#define ALISA_SCRCNVRTWIDTH 16
#define ALISA_SCRCNVRTHEIGHT 28

//#define ALISA_LENGTH 12
//#define ALISA_WIDTH 12
#define ALISA_LENGTH 10
#define ALISA_WIDTH 6
#define ALISA_HEIGHT 26

#define ALISA_PAL_CNT 2

#define ALISA_NORMALSLASH_ANIMATIONFRAME_START_COLLISION 2
#define ALISA_NORMALSLASH_ANIMATIONFRAME_END_COLLISION 3
#define ALISA_NORMALSLASH_FRAME_END_COLLISION 5

const s32 alisa_normalSlashOffsetX[EDirectionsCount][2] = {
	{-6, 4},
	{-6, 4},
	{0, 0},
	{0, 0},
	{6, -4},
	{6, -4},
	{0, 0},
	{0, 0}
};

const s32 alisa_normalSlashOffsetY[EDirectionsCount][2] = {
	{0, 0},
	{0, 0},
	{6, -4},
	{6, -4},
	{0, 0},
	{0, 0},
	{6, -4},
	{6, -4}
};

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

void alisa_controller(CharacterAttr* charAtt, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection);
void alisa_doAction(CharacterAttr *alisa, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection);
void checkForEvents(CharacterAttr* alisa, MapInfo *mapInfo);
void alisa_actionStand(CharacterAttr* alisa, const MapInfo *mapInfo,
	const CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection);
void alisa_actionRun(CharacterAttr* alisa, const MapInfo *mapInfo,
	const CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection);
void alisa_actionSlash(CharacterAttr* alisa, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection);
void alisa_actionStrongSlash(CharacterAttr* alisa, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection);
void alisa_actionPrepareDash(CharacterAttr* alisa, const MapInfo *mapInfo,
	const CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection); 
void alisa_actionDashForward(CharacterAttr* alisa, const MapInfo *mapInfo,
	const CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection);
void alisa_actionDashBackward(CharacterAttr* alisa, const MapInfo *mapInfo,
	const CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection);
void alisa_actionJumpUp(CharacterAttr* alisa, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection);
void alisa_actionJumpForward(CharacterAttr* alisa, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection);
void alisa_actionFallingDown(CharacterAttr* alisa, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection);
void alisa_actionFallingDownForward(CharacterAttr* alisa, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection);
void alisa_actionStunned(CharacterAttr* alisa, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection);

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

bool alisa_isHit(CharacterAttr *alisa, CharacterActionEvent *actionEvent);

void transferToBoundingBox(const EventTransfer *transfer, BoundingBox *boundingBox);



const CharFuncAction alisa_actions[] = {
	&alisa_actionStand,
	&alisa_actionRun,
	&alisa_actionSlash,
	&alisa_actionStrongSlash,
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
	{ -8, 8, 8, 24, 8, 18},
	{ -8, 8, 8, 24, 8, 18},
	{ 8, 24, -8, 8, 8, 18},
	{ -8, 8, -24, -8, 8, 18},
	{ -8, 8, -24, -8, 8, 18},
	{ -8, 8, -24, -8, 8, 18},
	{ -24, -8, -8, 8, 8, 18},
	{ -8, 8, 8, 24, 8, 18},
};


void alisa_init(CharacterAttr* alisa, ControlTypePool* controlPool, CharacterWaypoints *charWaypoints)
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
	alisa->isHit = &alisa_isHit;
	//alisa->free = NULL;
	//CharacterPlayerControl *charControl = mchar_getControlType(controlPool);
	CharacterPlayerControl *charControl = (CharacterPlayerControl*)mchar_findFreeControlType(controlPool);
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
	alisa->free = (ControlTypeUnion*)charControl;
	alisa->stats.maxLife = 10;
	alisa->stats.currentLife = 10;
}

void alisa_doAction(CharacterAttr* alisa,
	const MapInfo *mapInfo, const CharacterCollection *characterCollection, 
	CharacterActionCollection *charActionCollection) {
	if(alisa->nextAction >= EAlisaActionCount && alisa->nextAction <= EAlisaInitialize) {
		alisa->nextAction = EAlisaStand;
	}
	
	alisa_actions[alisa->nextAction](alisa, mapInfo, NULL, charActionCollection);
	commonCheckForEvents(alisa, mapInfo);
}

int alisa_setPosition(CharacterAttr* alisa,
	OBJ_ATTR *oamBuf, 
	const Position *scr_pos,
	const ScreenDimension *scr_dim) 
{
	int numberOfShadow = 0, currentAnimation;

	alisa->spriteDisplay.baseY = CONVERT_TO_SCRYPOS(alisa->position.y, 
		scr_pos->y, alisa_scrConversionMeasurements);
	alisa->spriteDisplay.baseX = CONVERT_TO_SCRXPOS(alisa->position.x, 
		scr_pos->x, alisa_scrConversionMeasurements);
	alisa->spriteDisplay.baseY -= CONVERT_TO_SCRZPOS(alisa->position.z);
	
	//TODO add in screen check
	commonSetToOamBuffer(&alisa->spriteDisplay, oamBuf);
	alisa->spriteDisplay.isInScreen = true;
	
	currentAnimation = commonGetCurrentAnimationFrame(alisa);
	numberOfShadow = commonSetShadow(alisa->spriteDisplay.baseX, 
			alisa->spriteDisplay.baseY + alisa->distanceFromGround + ALISA_SCRCNVRTHEIGHT,
			&oamBuf[alisa->spriteDisplay.spriteSet->set[currentAnimation].numberOflayers]);
			
    return alisa->spriteDisplay.spriteSet->set[currentAnimation].numberOflayers + numberOfShadow;
}

void alisa_actionStand(CharacterAttr* alisa,
	const MapInfo *mapInfo, const CharacterCollection *characterCollection, 
	CharacterActionCollection *charActionCollection) {
    bool isLastFrame = false;

	//mprinter_printf("STAND\n");
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
	alisa->direction = alisa->nextDirection&EDirectionsMax;
	
	commonGravityEffect(alisa, alisa_zOffsetDown[alisa->movementCtrl.currentFrame&1]);
	
	alisa->movementCtrl.maxFrames = 0;
	alisa->movementCtrl.currentFrame = 0;
	
	alisa->spriteDisplay.spriteSet = alisaStandWithSwordSet[alisa->faceDirection&EDirectionsMax];
	//alisa->spriteDisplay.spriteSet = &maincharacter_stand;
}

void alisa_actionRun(CharacterAttr* alisa, const MapInfo *mapInfo,
	const CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection) {
    bool isLastFrame = false;
	//mprinter_printf("RUN %d %d\n", alisa->spriteDisplay.currentAnimationFrame, alisa->movementCtrl.currentFrame);
	alisa->spriteDisplay.imageUpdateStatus = ENoUpdate;
	alisa->spriteDisplay.palleteUpdateStatus = ENoUpdate;
	if (commonUpdateCharacterAnimation(alisa) == EUpdate) {
		alisa->spriteDisplay.imageUpdateStatus = EUpdate;
		alisa->spriteDisplay.palleteUpdateStatus = EUpdate;
	}
	
	if (alisa->action != alisa->nextAction) {
	    alisa->movementCtrl.maxFrames = ALISA_RUN_MVMNT_CTRL_MAX;
		alisa->movementCtrl.currentFrame = 0;
	}
	
	alisa->action = alisa->nextAction;
	alisa->direction = alisa->nextDirection&EDirectionsMax;
	
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
	alisa->spriteDisplay.spriteSet = alisaRunSet[alisa->faceDirection&EDirectionsMax];
	//alisa->spriteDisplay.spriteSet = &maincharacter_walk;
}

void alisa_actionSlash(CharacterAttr* alisa, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection) {
	BoundingBox position;
	Position collisionPoints[2];
	int attackVal = 1;
	mprinter_printf("SLASH\n");
	alisa->spriteDisplay.imageUpdateStatus = ENoUpdate;
	alisa->spriteDisplay.palleteUpdateStatus = ENoUpdate;
	
	commonGravityEffect(alisa, alisa_zOffsetDown[alisa->movementCtrl.currentFrame&1]);
	if (commonUpdateCharacterAnimation(alisa) == EUpdate) {
		alisa->spriteDisplay.imageUpdateStatus = EUpdate;
		alisa->spriteDisplay.palleteUpdateStatus = EUpdate;
	}
	
	alisa->delta.x = 0;
	alisa->delta.y = 0;
	alisa->movementCtrl.maxFrames = 0;
	alisa->movementCtrl.currentFrame = 0;
	
	alisa->action = alisa->nextAction;
	alisa->direction = alisa->nextDirection&EDirectionsMax;
	
	int currentAnimationFrame = commonGetCurrentAnimationFrame(alisa);
	int displayCountFrame = commonGetCurrentDisplayFrame(alisa);
	if (currentAnimationFrame >= ALISA_NORMALSLASH_ANIMATIONFRAME_START_COLLISION && 
		currentAnimationFrame <= ALISA_NORMALSLASH_ANIMATIONFRAME_END_COLLISION) {
		BoundingBox collisionBox;
		collisionBox.startX = CONVERT_2POS(alisa->position.x) + alisa_slashCollisionBox[alisa->faceDirection&EDirectionsMax].startX + 
			alisa_normalSlashOffsetX[alisa->faceDirection&EDirectionsMax][currentAnimationFrame];
		collisionBox.startY = CONVERT_2POS(alisa->position.y) + alisa_slashCollisionBox[alisa->faceDirection&EDirectionsMax].startY + 
			alisa_normalSlashOffsetY[alisa->faceDirection&EDirectionsMax][currentAnimationFrame];
		collisionBox.startZ = CONVERT_2POS(alisa->position.z) + alisa_slashCollisionBox[alisa->faceDirection&EDirectionsMax].startZ;
		collisionBox.endX = CONVERT_2POS(alisa->position.x) + alisa_slashCollisionBox[alisa->faceDirection&EDirectionsMax].endX +
			alisa_normalSlashOffsetX[alisa->faceDirection&EDirectionsMax][currentAnimationFrame];
		collisionBox.endY = CONVERT_2POS(alisa->position.y) + alisa_slashCollisionBox[alisa->faceDirection&EDirectionsMax].endY +
			alisa_normalSlashOffsetY[alisa->faceDirection&EDirectionsMax][currentAnimationFrame];
		collisionBox.endZ = CONVERT_2POS(alisa->position.z) + alisa_slashCollisionBox[alisa->faceDirection&EDirectionsMax].endZ;
		if (displayCountFrame < ALISA_NORMALSLASH_FRAME_END_COLLISION){
			mchar_actione_add(alisa, charActionCollection, alisa_NormalAttack[alisa->faceDirection&EDirectionsMax], attackVal, 1, &collisionBox);
		} else {
			mchar_actione_remove(alisa, charActionCollection);
		}
	}
	
	if (commonGetCurrentAnimationFrame(alisa) == ALISA_SLASH_STARTSOUND_FRAME && commonGetCurrentDisplayFrame(alisa) == 0) {
		msound_setChannel(&soundeffect_slash, false);
	}
	
	alisa->spriteDisplay.spriteSet = alisaSlashSet[alisa->faceDirection&EDirectionsMax];
}

void alisa_actionStrongSlash(CharacterAttr* alisa, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection) {
	BoundingBox position;
	Position collisionPoints[2];
	int attackVal = 1;
	mprinter_printf("Strong SLASH\n");
	alisa->spriteDisplay.imageUpdateStatus = ENoUpdate;
	alisa->spriteDisplay.palleteUpdateStatus = ENoUpdate;
	
	commonGravityEffect(alisa, alisa_zOffsetDown[alisa->movementCtrl.currentFrame&1]);
	if (commonUpdateCharacterAnimation(alisa) == EUpdate) {
		alisa->spriteDisplay.imageUpdateStatus = EUpdate;
		alisa->spriteDisplay.palleteUpdateStatus = EUpdate;
	}
	
	alisa->delta.x = 0;
	alisa->delta.y = 0;
	alisa->movementCtrl.maxFrames = 0;
	alisa->movementCtrl.currentFrame = 0;
	
	alisa->action = alisa->nextAction;
	alisa->direction = alisa->nextDirection&EDirectionsMax;
	
	int currentAnimationFrame = commonGetCurrentAnimationFrame(alisa);
	int displayCountFrame = commonGetCurrentDisplayFrame(alisa);
	if (currentAnimationFrame >= ALISA_NORMALSLASH_ANIMATIONFRAME_START_COLLISION && 
		currentAnimationFrame <= ALISA_NORMALSLASH_ANIMATIONFRAME_END_COLLISION) {
		BoundingBox collisionBox;
		collisionBox.startX = CONVERT_2POS(alisa->position.x) + alisa_slashCollisionBox[alisa->faceDirection&EDirectionsMax].startX + 
			alisa_normalSlashOffsetX[alisa->faceDirection&EDirectionsMax][currentAnimationFrame];
		collisionBox.startY = CONVERT_2POS(alisa->position.y) + alisa_slashCollisionBox[alisa->faceDirection&EDirectionsMax].startY + 
			alisa_normalSlashOffsetY[alisa->faceDirection&EDirectionsMax][currentAnimationFrame];
		collisionBox.startZ = CONVERT_2POS(alisa->position.z) + alisa_slashCollisionBox[alisa->faceDirection&EDirectionsMax].startZ;
		collisionBox.endX = CONVERT_2POS(alisa->position.x) + alisa_slashCollisionBox[alisa->faceDirection&EDirectionsMax].endX +
			alisa_normalSlashOffsetX[alisa->faceDirection&EDirectionsMax][currentAnimationFrame];
		collisionBox.endY = CONVERT_2POS(alisa->position.y) + alisa_slashCollisionBox[alisa->faceDirection&EDirectionsMax].endY +
			alisa_normalSlashOffsetY[alisa->faceDirection&EDirectionsMax][currentAnimationFrame];
		collisionBox.endZ = CONVERT_2POS(alisa->position.z) + alisa_slashCollisionBox[alisa->faceDirection&EDirectionsMax].endZ;
		if (displayCountFrame < ALISA_NORMALSLASH_FRAME_END_COLLISION){
			mchar_actione_add(alisa, charActionCollection, alisa_NormalAttack[alisa->faceDirection&EDirectionsMax], attackVal, 1, &collisionBox);
		} else {
			mchar_actione_remove(alisa, charActionCollection);
		}
	}
	
	if (commonGetCurrentAnimationFrame(alisa) == ALISA_SLASH_STARTSOUND_FRAME && commonGetCurrentDisplayFrame(alisa) == 0) {
		msound_setChannel(&soundeffect_slash, false);
	}
	
	alisa->spriteDisplay.spriteSet = alisaReverseSwordSlashSet[alisa->faceDirection&EDirectionsMax];
}

void alisa_actionPrepareDash(CharacterAttr* alisa, const MapInfo *mapInfo,
	const CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection) {
    bool isLastFrame = false;
	mprinter_printf("PREPARE DASH\n");
	alisa->spriteDisplay.imageUpdateStatus = ENoUpdate;
	alisa->spriteDisplay.palleteUpdateStatus = ENoUpdate;
	
	commonGravityEffect(alisa, alisa_zOffsetDown[alisa->movementCtrl.currentFrame&1]);
	if (commonUpdateCharacterAnimation(alisa) == EUpdate) {
		alisa->spriteDisplay.imageUpdateStatus = EUpdate;
		alisa->spriteDisplay.palleteUpdateStatus = EUpdate;
	}
	
	alisa->movementCtrl.maxFrames = 0;
	alisa->movementCtrl.currentFrame = 0;
	
	alisa->action = alisa->nextAction;
	alisa->direction = alisa->nextDirection&EDirectionsMax;
	
	alisa->movementCtrl.currentFrame = (!(alisa->movementCtrl.currentFrame >= alisa->movementCtrl.maxFrames))*
	    alisa->movementCtrl.currentFrame;

	alisa->spriteDisplay.spriteSet = alisaPrepareDashSet[alisa->faceDirection&EDirectionsMax];
}

void alisa_actionDashForward(CharacterAttr* alisa, const MapInfo *mapInfo,
	const CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection) {
    bool isLastFrame = false;
	mprinter_printf("DASH FORWARD\n");
	alisa->spriteDisplay.imageUpdateStatus = ENoUpdate;
	alisa->spriteDisplay.palleteUpdateStatus = ENoUpdate;
	if (commonUpdateCharacterAnimation(alisa) == EUpdate) {
		alisa->spriteDisplay.imageUpdateStatus = EUpdate;
		alisa->spriteDisplay.palleteUpdateStatus = EUpdate;
	}
	
	if (alisa->action != alisa->nextAction) {
	    alisa->movementCtrl.maxFrames = ALISA_DASH_MVMNT_CTRL_MAX;
		alisa->movementCtrl.currentFrame = 0;
	}
	
	alisa->action = alisa->nextAction;
	alisa->direction = alisa->nextDirection&EDirectionsMax;
	
	alisa->movementCtrl.currentFrame = (!(alisa->movementCtrl.currentFrame >= alisa->movementCtrl.maxFrames))*
	    alisa->movementCtrl.currentFrame;

	if (commonGetCurrentAnimationFrame(alisa) == ALISA_DASH_STARTMOVE_FRAME) {
		alisa->delta.x = alisa_dashOffsetX[alisa->direction][alisa->movementCtrl.currentFrame];
		alisa->position.x += alisa->delta.x;
		
		alisa->delta.y = alisa_dashOffsetY[alisa->direction][alisa->movementCtrl.currentFrame];
		alisa->position.y += alisa->delta.y;
	} else if (commonGetCurrentAnimationFrame(alisa) > ALISA_DASH_STARTMOVE_FRAME) {
		commonGravityEffect(alisa, alisa_zOffsetDown[alisa->movementCtrl.currentFrame&1]);
	}
		
	
	++alisa->movementCtrl.currentFrame;
	alisa->spriteDisplay.spriteSet = alisaDashForwardSet[alisa->faceDirection&EDirectionsMax];
}

void alisa_actionDashBackward(CharacterAttr* alisa, const MapInfo *mapInfo,
	const CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection) {
    bool isLastFrame = false;
	mprinter_printf("DASH BACKWARD\n");
	alisa->spriteDisplay.imageUpdateStatus = ENoUpdate;
	alisa->spriteDisplay.palleteUpdateStatus = ENoUpdate;
	if (commonUpdateCharacterAnimation(alisa) == EUpdate) {
		alisa->spriteDisplay.imageUpdateStatus = EUpdate;
		alisa->spriteDisplay.palleteUpdateStatus = EUpdate;
	}
	
	if (alisa->action != alisa->nextAction) {
	    alisa->movementCtrl.maxFrames = ALISA_DASH_MVMNT_CTRL_MAX;
		alisa->movementCtrl.currentFrame = 0;
	}
	
	alisa->action = alisa->nextAction;
	alisa->direction = alisa->nextDirection&EDirectionsMax;
	
	alisa->movementCtrl.currentFrame = (!(alisa->movementCtrl.currentFrame >= alisa->movementCtrl.maxFrames))*
	    alisa->movementCtrl.currentFrame;

	if (commonGetCurrentAnimationFrame(alisa) == 0) {
		alisa->delta.x = alisa_dashOffsetX[alisa->direction][alisa->movementCtrl.currentFrame];
		alisa->position.x += alisa->delta.x;
		
		alisa->delta.y = alisa_dashOffsetY[alisa->direction][alisa->movementCtrl.currentFrame];
		alisa->position.y += alisa->delta.y;
	} else {
		commonGravityEffect(alisa, alisa_zOffsetDown[alisa->movementCtrl.currentFrame&1]);
	}
	
	++alisa->movementCtrl.currentFrame;
	alisa->spriteDisplay.spriteSet = alisaDashBackwardWithSwordSet[alisa->faceDirection&EDirectionsMax];
}

void alisa_actionJumpUp(CharacterAttr* alisa, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection) {
	bool isLastFrame = false;
	mprinter_printf("JUMP UP\n");

	alisa->spriteDisplay.imageUpdateStatus = ENoUpdate;
	alisa->spriteDisplay.palleteUpdateStatus = ENoUpdate;
	if (commonUpdateCharacterAnimation(alisa) == EUpdate) {
		alisa->spriteDisplay.imageUpdateStatus = EUpdate;
		alisa->spriteDisplay.palleteUpdateStatus = EUpdate;
	}
	
	if (alisa->action != alisa->nextAction) {
		alisa->movementCtrl.maxFrames = ALISA_JUMP_MOVEMENT;
	}
	
	alisa->action = alisa->nextAction;
	alisa->direction = alisa->nextDirection&EDirectionsMax;
	
	alisa->movementCtrl.currentFrame = (!(alisa->movementCtrl.currentFrame >= alisa->movementCtrl.maxFrames))*
	    alisa->movementCtrl.currentFrame;

	if (alisa->spriteDisplay.currentAnimationFrame < ALISA_RISING_ANIMATION_FRAME) {
		alisa->delta.z = alisa_jumpOffset[alisa->movementCtrl.currentFrame];
		alisa->position.z += alisa->delta.z;
	}
	
	++alisa->movementCtrl.currentFrame;
	alisa->spriteDisplay.spriteSet = alisaJumpWithSwordSet[alisa->faceDirection&EDirectionsMax];
}

void alisa_actionJumpForward(CharacterAttr* alisa, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection) {
	bool isLastFrame = false;
	
	mprinter_printf("JUMP FORWARD\n");
	
	alisa->spriteDisplay.imageUpdateStatus = ENoUpdate;
	alisa->spriteDisplay.palleteUpdateStatus = ENoUpdate;
	if (commonUpdateCharacterAnimation(alisa) == EUpdate) {
		alisa->spriteDisplay.imageUpdateStatus = EUpdate;
		alisa->spriteDisplay.palleteUpdateStatus = EUpdate;
	}
	
	if (alisa->action != alisa->nextAction) {
		alisa->movementCtrl.maxFrames = ALISA_JUMP_MOVEMENT;
	}
	
	alisa->action = alisa->nextAction;
	alisa->direction = alisa->nextDirection&EDirectionsMax;
	
	alisa->movementCtrl.currentFrame = (!(alisa->movementCtrl.currentFrame >= alisa->movementCtrl.maxFrames))*
	    alisa->movementCtrl.currentFrame;

	if (commonGetCurrentAnimationFrame(alisa) < ALISA_RISING_ANIMATION_FRAME) {
		alisa->delta.z = alisa_jumpOffset[alisa->movementCtrl.currentFrame];
		alisa->position.z += alisa->delta.z;
		alisa->delta.x = alisa_jumpOffsetX[alisa->direction];
		alisa->position.x += alisa->delta.x;
		alisa->delta.y = alisa_jumpOffsetY[alisa->direction];
		alisa->position.y += alisa->delta.y;
	} else {
		alisa->delta.x = alisa_jumpOffsetX[alisa->direction];
		alisa->position.x += alisa->delta.x;
		alisa->delta.y = alisa_jumpOffsetY[alisa->direction];
		alisa->position.y += alisa->delta.y;
	}
	
	++alisa->movementCtrl.currentFrame;
	alisa->spriteDisplay.spriteSet = alisaJumpWithSwordSet[alisa->faceDirection&EDirectionsMax];
}

void alisa_actionFallingDown(CharacterAttr* alisa, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection) {
	bool isLastFrame = false;

	mprinter_printf("FALLING DOWN\n");
	alisa->spriteDisplay.imageUpdateStatus = ENoUpdate;
	alisa->spriteDisplay.palleteUpdateStatus = ENoUpdate;
	if (commonUpdateCharacterAnimation(alisa) == EUpdate) {
		alisa->spriteDisplay.imageUpdateStatus = EUpdate;
		alisa->spriteDisplay.palleteUpdateStatus = EUpdate;
	}
	
	if (alisa->action != alisa->nextAction) {
		alisa->movementCtrl.maxFrames = ALISA_FALLING_MOVEMENT;
	}
	
	alisa->action = alisa->nextAction;
	alisa->direction = alisa->nextDirection&EDirectionsMax;
	
	alisa->movementCtrl.currentFrame = (!(alisa->movementCtrl.currentFrame >= alisa->movementCtrl.maxFrames))*
	    alisa->movementCtrl.currentFrame;

	commonGravityEffect(alisa, alisa_zOffsetDown[alisa->movementCtrl.currentFrame]);
	
	
	++alisa->movementCtrl.currentFrame;
	alisa->spriteDisplay.spriteSet = alisaFallingDownSet[alisa->faceDirection&EDirectionsMax];
}

void alisa_actionFallingDownForward(CharacterAttr* alisa, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection) {
	bool isLastFrame = false;

	mprinter_printf("FALLING FORWARD\n");
	alisa->spriteDisplay.imageUpdateStatus = ENoUpdate;
	alisa->spriteDisplay.palleteUpdateStatus = ENoUpdate;
	if (commonUpdateCharacterAnimation(alisa) == EUpdate) {
		alisa->spriteDisplay.imageUpdateStatus = EUpdate;
		alisa->spriteDisplay.palleteUpdateStatus = EUpdate;
	}
	
	if (alisa->action != alisa->nextAction) {
		alisa->movementCtrl.maxFrames = ALISA_FALLING_MOVEMENT;
	}
	
	alisa->action = alisa->nextAction;
	alisa->direction = alisa->nextDirection&EDirectionsMax;
	
	alisa->movementCtrl.currentFrame = (!(alisa->movementCtrl.currentFrame >= alisa->movementCtrl.maxFrames))*
	    alisa->movementCtrl.currentFrame;

	commonGravityEffect(alisa, alisa_zOffsetDown[alisa->movementCtrl.currentFrame]);
	
	alisa->delta.x = alisa_jumpOffsetX[alisa->direction];
	alisa->position.x += alisa->delta.x;
	alisa->delta.y = alisa_jumpOffsetY[alisa->direction];
	alisa->position.y += alisa->delta.y;
		
	++alisa->movementCtrl.currentFrame;
	alisa->spriteDisplay.spriteSet = alisaFallingDownSet[alisa->faceDirection&EDirectionsMax];
}

void alisa_actionStunned(CharacterAttr* alisa, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection) {
	BoundingBox position;
	Position collisionPoints[2];
	int attackVal = 1, countPoints = 2;
	mprinter_printf("STUNNED\n");
	alisa->spriteDisplay.imageUpdateStatus = ENoUpdate;
	alisa->spriteDisplay.palleteUpdateStatus = ENoUpdate;
	
	commonGravityEffect(alisa, alisa_zOffsetDown[alisa->movementCtrl.currentFrame&1]);
	
	if (commonUpdateCharacterAnimation(alisa) == EUpdate) {
		alisa->spriteDisplay.imageUpdateStatus = EUpdate;
		alisa->spriteDisplay.palleteUpdateStatus = EUpdate;
	}
	
	commonRemoveActionOnInit(alisa, charActionCollection);
	
	alisa->movementCtrl.maxFrames = 0;
	alisa->movementCtrl.currentFrame = 0;
	
	alisa->delta.x = 0;
	alisa->delta.y = 0;
	alisa->action = alisa->nextAction;
	alisa->direction = alisa->nextDirection&EDirectionsMax;
	
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

const int alisa_mapCollisionXAdjust[] = { (ALISA_LENGTH >> 1), -(ALISA_LENGTH >> 1), (ALISA_LENGTH >> 1), -(ALISA_LENGTH >> 1)};
const int alisa_mapCollisionYAdjust[] = {(ALISA_WIDTH >> 1), (ALISA_WIDTH >> 1), -(ALISA_WIDTH >> 1), -(ALISA_WIDTH >> 1)};

//int xAdjust[] = {0, 0, 0, 0};
//int yAdjust[] = {0, 0, 0, 0};
void alisa_checkMapCollision(CharacterAttr* alisa, const MapInfo* mapInfo) {
	commonCharacterMapEdgeCheck(alisa, mapInfo);
	int count;
	BoundingBox mapBoundingBox, characterBoundingBox;
	CharacterPlayerControl *charControl = (CharacterPlayerControl*)alisa->free;
	int fallingDown = 1024;
	alisa->direction &= EDirectionsMax;
	
	if (alisa->action == EAlisaFallingDown ||  
		alisa->action == EAlisaFallingDownForward) {
		common_mapCollision[alisa->direction](alisa, mapInfo, 
			common_mapCollisionReactionsWhileFallingDown[alisa->direction]);
	}

	alisa->getBounds(alisa, &count, &characterBoundingBox);
	
	for (int i = 0; i < 4; ++i) {
		commonGetBoundsFromMap(CONVERT_2POS(alisa->position.x) + alisa_mapCollisionXAdjust[i], 
			CONVERT_2POS(alisa->position.y) + alisa_mapCollisionYAdjust[i], mapInfo, &mapBoundingBox);
		int dist = common_fallingDown(alisa, &characterBoundingBox, &mapBoundingBox);
		if (dist < fallingDown && dist >= 0) {
			fallingDown = dist;
		}
	}
	
	if (fallingDown > 0 ) {
		alisa->nextAction = EAlisaFallingDown;
	} else if ((alisa->action == EAlisaFallingDown ||  
		alisa->action == EAlisaFallingDownForward) && fallingDown <= 0) {
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
		fallingDistance = common_fallingDownOnBoundingBox(alisa, &alisaBoundingBox, &otherCharBoundingBox);
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

bool alisa_isHit(CharacterAttr *alisa, CharacterActionEvent *actionEvent) {

	CharacterPlayerControl *charControl = (CharacterPlayerControl*)(CharacterAIControl*)alisa->free;
	if (alisa->stats.currentStatus == EStatusNoActionCollision) {
		return false;
	}
	alisa->stats.currentLife -= 1;
	charControl->currentStatus = EAlisaStatusStunned;
	if (alisa->stats.currentLife <= 0) {
		//gameover
	}
	return true;
}
