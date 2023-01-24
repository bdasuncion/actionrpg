#include <stdlib.h>
#include  <stdarg.h>
#include  <stdbool.h>
#include "GBAObject.h"
#include "GBAVideo.h"
#include "GBADMA.h"
#include "GBATimer.h"
#include "GBACharacter.h"
#include "GBACharacterType.h"
#include "MapCommon.h"
#include "UtilCommonValues.h"
#include "CharacterCommon.h"

#define IMG8X8W  8
#define IMG16X16W  32
#define IMG32X32W  128
#define IMG64X64W  512

#define IMG8X16W  16
#define IMG8X32W  32
#define IMG16X32W  64
#define IMG32X64W  256

extern const FuncCharacterInit chacterInit[];
extern const FuncCharacterSet characterSet[];

//u32 time[3];
int commonDummy() {
	//mprinter_print("COMMON\n");
    return 0;
}

const CharacterAttr openSlot = {&commonDummy, &commonDummy, &commonDummy, &commonDummy, 
    &commonDummy, &commonDummy, &commonDummy, NULL, 0, NONE,0,0,0,0,0, NULL, {0, -1, 0}, NULL, NULL };

void commonRemoveCharacter(CharacterAttr *character) {
    character->type = NONE;
    commonCharacterSetPosition(character, 0, -1, 0, EDown);
	character->controller = &commonDummy;
	character->doAction = &commonDummy;
	character->setPosition = &commonDummy;
	character->getBounds = &commonDummy;
	character->checkCollision = &commonDummy;
	character->checkMapCollision = &commonDummy;
	character->checkActionCollision = &commonDummy;
	character->spriteDisplay.baseImageId = 0;
	character->spriteDisplay.imageUpdateStatus = ENoUpdate;
	character->spriteDisplay.basePalleteId = 0;
	character->spriteDisplay.palleteUpdateStatus = ENoUpdate;
}
void commonDoCharacterEvent(CharacterAttr *character, const MapInfo *mapInfo, CharacterCollection *charCollection);

void commonCharacterSetPosition(CharacterAttr* character, int x, int y, int z, EDirections direction) {
	character->position.x = CONVERT_2MOVE(x);
	character->position.y = CONVERT_2MOVE(y);
	character->position.z = CONVERT_2MOVE(z);
	character->direction = direction;
	character->nextDirection = direction;
}

const s32 uncompressedCopySize[SPRITESHAPE_COUNT][SPRITESIZE_COUNT] = {
    {IMG8X8W, IMG16X16W, IMG32X32W, IMG64X64W},
	{IMG8X16W, IMG8X32W, IMG16X32W, IMG32X64W},
	{IMG8X16W, IMG8X32W, IMG16X32W, IMG32X64W}
};

void commonCharacterInit(CharacterAttr* character, int initialize, int nextAction, EDirections direction) {
	character->spriteDisplay.currentAnimationFrame = 0;
	character->spriteDisplay.numberOfFramesPassed = 0;
	character->action = initialize;
	character->direction = direction;
	character->nextAction = nextAction;
	character->nextDirection = direction;
}

void commonCharacterMapEdgeCheck(CharacterAttr* character, const MapInfo *mapInfo) {
    int count;
	BoundingBox charBoundingBox;
	character->getBounds(character, &count, &charBoundingBox);
	
	bool leftEdge = (charBoundingBox.startX < 0);
	bool rightEdge = (charBoundingBox.endX > mapInfo->width);
	bool upperEdge = (charBoundingBox.startY < 0);
	bool lowerEdge = (charBoundingBox.endY > mapInfo->height);
	character->position.x -= CONVERT_2MOVE(leftEdge*(charBoundingBox.startX));
	character->position.y -= CONVERT_2MOVE(upperEdge*(charBoundingBox.startY));
	character->position.x -= CONVERT_2MOVE(rightEdge*(charBoundingBox.endX - mapInfo->width));
	character->position.y -= CONVERT_2MOVE(lowerEdge*(charBoundingBox.endY - mapInfo->height));

	if (character->free->type == EControlAiType) {
		((CharacterAIControl*)character->free)->downBlocked |= lowerEdge;
		((CharacterAIControl*)character->free)->upBlocked |= upperEdge;
		((CharacterAIControl*)character->free)->leftBlocked |= leftEdge;
		((CharacterAIControl*)character->free)->rightBlocked |= rightEdge;
	}	
}

const CharFuncCollisionReaction common_collisionReactions[2][8] = {
    {	&common_noMovement,
		&common_noMovement,
		&common_noMovement,
		&common_noMovement,
		&common_noMovement,
		&common_noMovement,
		&common_noMovement,
		&common_noMovement },
	{	&common_movingDown,
		&common_movingRightDownOffset,
		&common_movingRight,
		&common_movingRightUpOffset,
		&common_movingUp,
		&common_movingLeftUpOffset,
		&common_movingLeft,
		&common_movingLeftDownOffset}
};

const CharFuncCollisionReaction common_mapCollisionReactions[8] = {
	&common_mapMovingDown,
	&common_mapMovingRightDownOffset,
	&common_mapMovingRight,
	&common_mapMovingRightUpOffset,
	&common_mapMovingUp,
	&common_mapMovingLeftUpOffset,
	&common_mapMovingLeft,
	&common_mapMovingLeftDownOffset
};

const CommonMapCollision common_mapCollision[8] = {
    &commonMovingDownMapCollision,
	&commonMovingRightDownMapCollision,
	&commonMovingRightMapCollision,
	&commonMovingRightUpMapCollision,
	&commonMovingUpMapCollision,
	&commonMovingLeftUpMapCollision,
	&commonMovingLeftMapCollision,
	&commonMovingLeftDownMapCollision
};

const Position NOT_FOUND_POSITION = {-1, -1, -1};

void commonSetToOamBuffer(SpriteDisplay *spriteDisplay, OBJ_ATTR *oamBuf) {
    int i, xScreen, yScreen, id = spriteDisplay->baseImageId;
	
    for (i = 0; i < spriteDisplay->spriteSet->set[spriteDisplay->currentAnimationFrame].numberOflayers; ++i) {

        yScreen = (spriteDisplay->baseY + 
			spriteDisplay->spriteSet->set[spriteDisplay->currentAnimationFrame].layers[i].offsetY) & 0x00FF;

		oamBuf[i].attr0 = ATTR0_SET(yScreen, 
		    spriteDisplay->spriteSet->set[spriteDisplay->currentAnimationFrame].layers[i].shape);

        xScreen = (spriteDisplay->baseX + 
			spriteDisplay->spriteSet->set[spriteDisplay->currentAnimationFrame].layers[i].offsetX) & 0x01FF;
		
		oamBuf[i].attr1 = ATTR1_SET(xScreen, 
			spriteDisplay->spriteSet->set[spriteDisplay->currentAnimationFrame].layers[i].size,
			spriteDisplay->spriteSet->set[spriteDisplay->currentAnimationFrame].layers[i].hflip, 
			spriteDisplay->spriteSet->set[spriteDisplay->currentAnimationFrame].layers[i].vflip);
		
		id += spriteDisplay->spriteSet->set[spriteDisplay->currentAnimationFrame].layers[i].idOffset;
		
		oamBuf[i].attr2 =  ATTR2_SET(id,
		    spriteDisplay->basePalleteId + 
			spriteDisplay->spriteSet->set[spriteDisplay->currentAnimationFrame].layers[i].palleteidOffset, 3);
			
		oamBuf[i].fill = 0;
	}
}

void commonSetToOamBufferAsObjWindow(SpriteDisplay *spriteDisplay, OBJ_ATTR *oamBuf) {
	int i, xScreen, yScreen, id = spriteDisplay->baseImageId;

    for (i = 0; i < spriteDisplay->spriteSet->set[spriteDisplay->currentAnimationFrame].numberOflayers; ++i) {

        yScreen = (spriteDisplay->baseY + 
			spriteDisplay->spriteSet->set[spriteDisplay->currentAnimationFrame].layers[i].offsetY) & 0x00FF;

		oamBuf[i].attr0 = ATTR0_SETASWINOBJ(yScreen, 
		    spriteDisplay->spriteSet->set[spriteDisplay->currentAnimationFrame].layers[i].shape);

        xScreen = (spriteDisplay->baseX + 
			spriteDisplay->spriteSet->set[spriteDisplay->currentAnimationFrame].layers[i].offsetX) & 0x01FF;

		oamBuf[i].attr1 = ATTR1_SET(xScreen, 
			spriteDisplay->spriteSet->set[spriteDisplay->currentAnimationFrame].layers[i].size,
			spriteDisplay->spriteSet->set[spriteDisplay->currentAnimationFrame].layers[i].hflip, 
			spriteDisplay->spriteSet->set[spriteDisplay->currentAnimationFrame].layers[i].vflip);

		id += spriteDisplay->spriteSet->set[spriteDisplay->currentAnimationFrame].layers[i].idOffset;

		oamBuf[i].attr2 =  ATTR2_SET(id,
		    spriteDisplay->basePalleteId + 
			spriteDisplay->spriteSet->set[spriteDisplay->currentAnimationFrame].layers[i].palleteidOffset, 3);

		oamBuf[i].fill = 0;
	}
}
void commonDrawDisplay(SpriteDisplay *spriteDisplay) {
	int i, id = spriteDisplay->baseImageId;
	if (spriteDisplay->imageUpdateStatus == EUpdate) {
		for (i = 0; i < spriteDisplay->spriteSet->set[spriteDisplay->currentAnimationFrame].numberOflayers; ++i) {
		    
			id += spriteDisplay->spriteSet->set[spriteDisplay->currentAnimationFrame].layers[i].idOffset;
		    if (spriteDisplay->spriteSet->set[spriteDisplay->currentAnimationFrame]
			    .layers[i].compression == LZSS_COMPRESSION) {
				//gbatimer_profileStart();
			    lzss2vram(
			        spriteDisplay->spriteSet->set[spriteDisplay->currentAnimationFrame].layers[i].image, id);
				//time[i] = gbatimer_profileStop();
			} else {
			   // gbatimer_profileStart();
		    	sprite_vram_copy32_ID(
			        spriteDisplay->spriteSet->set[spriteDisplay->currentAnimationFrame].layers[i].image,
			        uncompressedCopySize[spriteDisplay->spriteSet->set[spriteDisplay->currentAnimationFrame].layers[i].shape]
					    [spriteDisplay->spriteSet->set[spriteDisplay->currentAnimationFrame].layers[i].size], id);
				//time[2] = gbatimer_profileStop();
			}
		}
	}
}

UpdateStatus commonInitializeAction(CharacterAttr* character) {
    if (character->nextAction != character->action) {
		character->spriteDisplay.currentAnimationFrame = 0;
		character->spriteDisplay.numberOfFramesPassed = 0; 
	    return EUpdate;
	} else if (character->nextDirection != character->direction) {
		return EUpdate;
	}
	
	return ENoUpdate;
}

UpdateStatus commonUpdateAnimation(CharacterAttr* character) {
	int frameCount = character->spriteDisplay.spriteSet->numberOfAnimation;
	
	if(commonInitializeAction(character) != ENoUpdate) {
	    return EUpdate;
	}
	
	++character->spriteDisplay.numberOfFramesPassed;
	if (character->spriteDisplay.numberOfFramesPassed >= 
	    character->spriteDisplay.spriteSet->set[character->spriteDisplay.currentAnimationFrame].displayForNumFrames) {
		character->spriteDisplay.numberOfFramesPassed = 0;
		++character->spriteDisplay.currentAnimationFrame;
		if (character->spriteDisplay.currentAnimationFrame >= frameCount) {
			character->spriteDisplay.currentAnimationFrame = 0;
		}
		return EUpdate;
	}
	return ENoUpdate;
}

void commonGetNextFrame(const CharacterAttr* character, int *nextScreenFrame, 
    int *nextAnimationFrame, bool *isLastFrame) {
	int frameCount = character->spriteDisplay.spriteSet->numberOfAnimation;
	
	if (character->nextDirection != character->direction || character->nextAction != character->action) {
	    *nextScreenFrame = 0;
		*nextAnimationFrame = 0;
		*isLastFrame = false;
		return;
	}
	
	*isLastFrame = false;
	*nextAnimationFrame = character->spriteDisplay.currentAnimationFrame;
	*nextScreenFrame = character->spriteDisplay.numberOfFramesPassed + 1;
	if (*nextScreenFrame >= 
	    character->spriteDisplay.spriteSet->set[character->spriteDisplay.currentAnimationFrame].displayForNumFrames) {
		*nextScreenFrame = 0;
		*nextAnimationFrame += 1;
		if (*nextAnimationFrame >= frameCount) {
		    *isLastFrame = true;
			*nextAnimationFrame = 0;
		}
	}
}

bool commonIsInScreen(int charStartX, int charEndX, int charStartY, int charEndY, 
    const Position *scr_pos, const ScreenDimension *scr_dim) {
	int screenStartX = scr_pos->x, screenEndX = scr_pos->x + scr_dim->width;
	int screenStartY = scr_pos->y, screenEndY = scr_pos->y + scr_dim->height;
	
	return (charStartX >= screenStartX && charStartX <= screenEndX ||
	    charEndX >= screenStartX && charEndX <= screenEndX) &&
		(charStartY >= screenStartY && charStartY <= screenEndY ||
		charEndY >= screenStartY && charEndY <= screenEndY);
}

bool common_checkNext(bool isOtherCharBelow, const BoundingBox *charBoundingBox, 
    const BoundingBox *otherCharBoundingBox) {
	if (isOtherCharBelow && charBoundingBox->endY  < otherCharBoundingBox->startY) {
		return false;
	} else if (charBoundingBox->startY  > otherCharBoundingBox->endY) {
		return false;
	}
	
	return true;
}

inline bool inBounds(int value, int min, int max) {
    return (value >= min & value <= max);
}

//inline bool hasCollision(const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox) {
bool hasCollision(const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox) {
    return (inBounds(charBoundingBox->startX, otherCharBoundingBox->startX, otherCharBoundingBox->endX) |
	    inBounds(charBoundingBox->endX, otherCharBoundingBox->startX, otherCharBoundingBox->endX)) & 
		(inBounds(charBoundingBox->startY, otherCharBoundingBox->startY, otherCharBoundingBox->endY) | 
		inBounds(charBoundingBox->endY, otherCharBoundingBox->startY, otherCharBoundingBox->endY));
}

bool commonCollissionPointInBounds(const Position *collisionPoint, const BoundingBox *boundingBox) {

    return inBounds(collisionPoint->x, boundingBox->startX, boundingBox->endX) &
		inBounds(collisionPoint->y, boundingBox->startY, boundingBox->endY);
}

bool commonPositionInBounds(const Position *position, const BoundingBox *boundingBox) {

    return inBounds(CONVERT_2POS(position->x), boundingBox->startX, boundingBox->endX) &
		inBounds(CONVERT_2POS(position->y), boundingBox->startY, boundingBox->endY);
}	

void common_noMovement(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox) {
}
	
void common_movingRight(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox) {
	bool didCollide = hasCollision(charBoundingBox, otherCharBoundingBox) | hasCollision(otherCharBoundingBox, charBoundingBox);
	int xoffset = (charBoundingBox->endX - otherCharBoundingBox->startX)*(charBoundingBox->endX < otherCharBoundingBox->endX);
	int deltaX = CONVERT_2POS(character->delta.x);
	bool greaterThanXOffset = xoffset > deltaX;
	character->collisionCtrl.hasCollision = didCollide;
	
	xoffset = (deltaX*greaterThanXOffset) + (xoffset*(!greaterThanXOffset));
	xoffset *= didCollide;
	
	character->position.x -= CONVERT_2MOVE(xoffset);
	
	if (character->free->type == EControlAiType) {
		((CharacterAIControl*)character->free)->rightBlocked |= (xoffset != 0);
	}
}
	
void common_movingLeft(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox) {
	bool didCollide = hasCollision(charBoundingBox, otherCharBoundingBox) | hasCollision(otherCharBoundingBox, charBoundingBox);
	int xoffset = (otherCharBoundingBox->endX - charBoundingBox->startX)*(charBoundingBox->startX > otherCharBoundingBox->startX);
	int deltaX = CONVERT_2POS(-character->delta.x);
	bool greaterThanXOffset = xoffset > deltaX;
	
	character->collisionCtrl.hasCollision = didCollide;
	xoffset = (deltaX*greaterThanXOffset) + (xoffset*(!greaterThanXOffset));
	xoffset *= didCollide;
	
	character->position.x += CONVERT_2MOVE(xoffset);
	
	if (character->free->type == EControlAiType) {
		((CharacterAIControl*)character->free)->leftBlocked |= (xoffset != 0);
	}
}

void common_movingUp(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox) {
	bool didCollide = hasCollision(charBoundingBox, otherCharBoundingBox) | hasCollision(otherCharBoundingBox, charBoundingBox);
	
	int yoffset = (otherCharBoundingBox->endY - charBoundingBox->startY)*(charBoundingBox->startY > otherCharBoundingBox->startY);
	int deltaY = CONVERT_2POS(-character->delta.y);
	bool greaterThanYOffset = yoffset > deltaY;
	character->collisionCtrl.hasCollision = didCollide;
	yoffset = (deltaY*greaterThanYOffset) + (yoffset*(!greaterThanYOffset));
	yoffset *= didCollide;

	character->position.y += CONVERT_2MOVE(yoffset);
	
	if (character->free->type == EControlAiType) {
		((CharacterAIControl*)character->free)->upBlocked |= (yoffset != 0);
	}
}

void common_movingDown(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox) {
	bool didCollide = hasCollision(charBoundingBox, otherCharBoundingBox) | hasCollision(otherCharBoundingBox, charBoundingBox);
	
	int yoffset = (charBoundingBox->endY - otherCharBoundingBox->startY)*(charBoundingBox->endY < otherCharBoundingBox->endY);
	int deltaY = CONVERT_2POS(character->delta.y);
	bool greaterThanYOffset = yoffset > deltaY;
	character->collisionCtrl.hasCollision = didCollide;
	yoffset = (deltaY*greaterThanYOffset) + (yoffset*(!greaterThanYOffset));
	yoffset *= didCollide;
	
	character->position.y -= CONVERT_2MOVE(yoffset);
	
	if (character->free->type == EControlAiType) {
		((CharacterAIControl*)character->free)->downBlocked |= (yoffset != 0);
	}
}
	
void common_movingRightUpOffset(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox) {
	bool didCollide = hasCollision(charBoundingBox, otherCharBoundingBox) | hasCollision(otherCharBoundingBox, charBoundingBox);
	character->collisionCtrl.hasCollision = didCollide;
	int xOffset = (charBoundingBox->endX - otherCharBoundingBox->startX);
	int yOffset = (otherCharBoundingBox->endY - charBoundingBox->startY);
	int deltaX = CONVERT_2POS(character->delta.x);
	int deltaY = CONVERT_2POS(-character->delta.y);
	
	bool doOffsetY = (xOffset > yOffset);
	bool greaterThanYOffset = yOffset > (CONVERT_2POS(-character->delta.y));
	bool greaterThanXOffset = xOffset > deltaX;
	character->collisionCtrl.hasCollision = didCollide;
	xOffset *= (charBoundingBox->endX < otherCharBoundingBox->endX);
	yOffset *= (charBoundingBox->startY > otherCharBoundingBox->startY);
	xOffset = (deltaX*greaterThanXOffset) + (xOffset*(!greaterThanXOffset));
	yOffset = (deltaY*greaterThanYOffset) + (yOffset*(!greaterThanYOffset));
	
	xOffset *= (!doOffsetY)*didCollide;
	yOffset *= doOffsetY*didCollide;
	
	character->position.y += CONVERT_2MOVE(yOffset);
	character->position.x -= CONVERT_2MOVE(xOffset);
	
	if (character->free->type == EControlAiType) {
		((CharacterAIControl*)character->free)->rightBlocked |= (xOffset != 0);
		((CharacterAIControl*)character->free)->upBlocked |= (yOffset != 0);
	}
}

void common_movingLeftUpOffset(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox) {
	bool didCollide = hasCollision(charBoundingBox, otherCharBoundingBox) | hasCollision(otherCharBoundingBox, charBoundingBox);
	character->collisionCtrl.hasCollision = didCollide;
	int xOffset = (otherCharBoundingBox->endX - charBoundingBox->startX);
	int yOffset = (otherCharBoundingBox->endY - charBoundingBox->startY);
	int deltaX = CONVERT_2POS(-character->delta.x);
	int deltaY = CONVERT_2POS(-character->delta.y);
	
	bool doOffsetY = (xOffset > yOffset);
	bool greaterThanYOffset = yOffset > deltaY;
	bool greaterThanXOffset = xOffset > deltaX;
	character->collisionCtrl.hasCollision = didCollide;
	
	xOffset *= (charBoundingBox->startX > otherCharBoundingBox->startX);
	yOffset *= (charBoundingBox->startY > otherCharBoundingBox->startY);
	
	xOffset = (deltaX*greaterThanXOffset) + (xOffset*(!greaterThanXOffset));
	yOffset = (deltaY*greaterThanYOffset) + (yOffset*(!greaterThanYOffset));
	
	xOffset *= (!doOffsetY)*didCollide;
	yOffset *= doOffsetY*didCollide;
	
	character->position.y += CONVERT_2MOVE(yOffset);
	character->position.x += CONVERT_2MOVE(xOffset);
	
	if (character->free->type == EControlAiType) {
		((CharacterAIControl*)character->free)->leftBlocked |= (xOffset != 0);
		((CharacterAIControl*)character->free)->upBlocked |= (yOffset != 0);
	}
}

void common_movingRightDownOffset(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox) {
	bool didCollide = hasCollision(charBoundingBox, otherCharBoundingBox) | hasCollision(otherCharBoundingBox, charBoundingBox);
	character->collisionCtrl.hasCollision = didCollide;
	int xOffset = (charBoundingBox->endX - otherCharBoundingBox->startX);
	int yOffset = (charBoundingBox->endY - otherCharBoundingBox->startY);
	int deltaX = CONVERT_2POS(character->delta.x);
	int deltaY = CONVERT_2POS(character->delta.y);

	bool doOffsetY = (xOffset > yOffset);
	bool greaterThanYOffset = yOffset > deltaY;
	bool greaterThanXOffset = xOffset > deltaX;
	character->collisionCtrl.hasCollision = didCollide;
	xOffset *= (charBoundingBox->endX < otherCharBoundingBox->endX);
	yOffset *= (charBoundingBox->endY < otherCharBoundingBox->endY);
	xOffset = (deltaX*greaterThanXOffset) + (xOffset*(!greaterThanXOffset));
	yOffset = (deltaY*greaterThanYOffset) + (yOffset*(!greaterThanYOffset));
	xOffset *= (!doOffsetY)*didCollide;
	yOffset *= doOffsetY*didCollide;
	
	character->position.y -= CONVERT_2MOVE(yOffset);
	character->position.x -= CONVERT_2MOVE(xOffset);
	
	if (character->free->type == EControlAiType) {
		((CharacterAIControl*)character->free)->rightBlocked |= (xOffset != 0);
		((CharacterAIControl*)character->free)->downBlocked |= (yOffset != 0);
	}
}

void common_movingLeftDownOffset(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox) {
	bool didCollide = hasCollision(charBoundingBox, otherCharBoundingBox) | hasCollision(otherCharBoundingBox, charBoundingBox);
	character->collisionCtrl.hasCollision = didCollide;
	int xOffset = (otherCharBoundingBox->endX - charBoundingBox->startX);
	int yOffset = (charBoundingBox->endY - otherCharBoundingBox->startY);
	int deltaX = CONVERT_2POS(-character->delta.x);
	int deltaY = CONVERT_2POS(character->delta.y);

	bool doOffsetY = (xOffset > yOffset);
	bool greaterThanYOffset = yOffset > deltaY;
	bool greaterThanXOffset = xOffset > deltaX;
	character->collisionCtrl.hasCollision = didCollide;
	xOffset *= (charBoundingBox->startX > otherCharBoundingBox->startX);
	yOffset *= (charBoundingBox->endY < otherCharBoundingBox->endY);
	xOffset = (deltaX*greaterThanXOffset) + (xOffset*(!greaterThanXOffset));	
	yOffset = (deltaY*greaterThanYOffset) + (yOffset*(!greaterThanYOffset));
	xOffset *= (!doOffsetY)*didCollide;
	yOffset *= doOffsetY*didCollide;
	
	character->position.y -= CONVERT_2MOVE(yOffset);
	character->position.x += CONVERT_2MOVE(xOffset);
	
	if (character->free->type == EControlAiType) {
		((CharacterAIControl*)character->free)->leftBlocked |= (xOffset != 0);
		((CharacterAIControl*)character->free)->downBlocked |= (yOffset != 0);
	}
}

void common_mapMovingRight(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox) {
	bool didCollide = hasCollision(charBoundingBox, otherCharBoundingBox) | hasCollision(otherCharBoundingBox, charBoundingBox);
	int xoffset = (charBoundingBox->endX - otherCharBoundingBox->startX);
	character->collisionCtrl.hasCollision = didCollide;
	xoffset += 1;
	xoffset *= didCollide;
	character->position.x -= CONVERT_2MOVE(xoffset);
	if (character->free->type == EControlAiType) {
		((CharacterAIControl*)character->free)->rightBlocked |= (xoffset != 0);
	}
}
	
void common_mapMovingLeft(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox) {
	bool didCollide = hasCollision(charBoundingBox, otherCharBoundingBox) | hasCollision(otherCharBoundingBox, charBoundingBox);
	int xoffset = (otherCharBoundingBox->endX - charBoundingBox->startX);
	character->collisionCtrl.hasCollision = didCollide;
	xoffset += 1;
	xoffset *= didCollide;
	character->position.x += CONVERT_2MOVE(xoffset);
	if (character->free->type == EControlAiType) {
		((CharacterAIControl*)character->free)->leftBlocked |= (xoffset != 0);
	}
}

void common_mapMovingUp(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox) {
	bool didCollide = hasCollision(charBoundingBox, otherCharBoundingBox) | hasCollision(otherCharBoundingBox, charBoundingBox);
	int yoffset = (otherCharBoundingBox->endY - charBoundingBox->startY);
	character->collisionCtrl.hasCollision = didCollide;
	yoffset += 1;
	yoffset *= didCollide;
	character->position.y += CONVERT_2MOVE(yoffset);
	if (character->free->type == EControlAiType) {
		((CharacterAIControl*)character->free)->upBlocked |= (yoffset != 0);
	}
}

void common_mapMovingDown(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox) {
	bool didCollide = hasCollision(charBoundingBox, otherCharBoundingBox) | hasCollision(otherCharBoundingBox, charBoundingBox);
	int yoffset = (charBoundingBox->endY - otherCharBoundingBox->startY);
	character->collisionCtrl.hasCollision = didCollide;
	yoffset += 1;
	yoffset *= didCollide;
	character->position.y -= CONVERT_2MOVE(yoffset);
	if (character->free->type == EControlAiType) {
		((CharacterAIControl*)character->free)->downBlocked |= (yoffset != 0);
	}  
}
	
void common_mapMovingRightUpOffset(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox) {
	bool didCollide = hasCollision(charBoundingBox, otherCharBoundingBox) | hasCollision(otherCharBoundingBox, charBoundingBox);
	int xOffset = (charBoundingBox->endX - otherCharBoundingBox->startX);
	int yOffset = (otherCharBoundingBox->endY - charBoundingBox->startY);
	bool doOffsetY = (xOffset > yOffset);
	character->collisionCtrl.hasCollision = didCollide;
	yOffset += 1;
	yOffset *= doOffsetY*didCollide;
	xOffset += 1;
	xOffset *= (!doOffsetY)*didCollide;
	character->position.y += CONVERT_2MOVE(yOffset);
	character->position.x -= CONVERT_2MOVE(xOffset);
	if (character->free->type == EControlAiType) {
		((CharacterAIControl*)character->free)->upBlocked |= (yOffset != 0);
		((CharacterAIControl*)character->free)->rightBlocked |= (xOffset != 0);
	}  
}

void common_mapMovingLeftUpOffset(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox) {
	bool didCollide = hasCollision(charBoundingBox, otherCharBoundingBox) | hasCollision(otherCharBoundingBox, charBoundingBox);
	int xOffset = (otherCharBoundingBox->endX - charBoundingBox->startX);
	int yOffset = (otherCharBoundingBox->endY - charBoundingBox->startY);
	bool doOffsetY = (xOffset > yOffset);
	character->collisionCtrl.hasCollision = didCollide;
	yOffset += 1;
	yOffset *= doOffsetY*didCollide;
	xOffset += 1;
	xOffset *= (!doOffsetY)*didCollide;
	character->position.y += CONVERT_2MOVE(yOffset);
	character->position.x += CONVERT_2MOVE(xOffset);
	if (character->free->type == EControlAiType) {
		((CharacterAIControl*)character->free)->upBlocked |= (yOffset != 0);
		((CharacterAIControl*)character->free)->leftBlocked |= (xOffset != 0);
	}
}

void common_mapMovingRightDownOffset(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox) {
	bool didCollide = hasCollision(charBoundingBox, otherCharBoundingBox) | hasCollision(otherCharBoundingBox, charBoundingBox);
	int xOffset = (charBoundingBox->endX - otherCharBoundingBox->startX);
	int yOffset = (charBoundingBox->endY - otherCharBoundingBox->startY);
	bool doOffsetY = (xOffset > yOffset);
	character->collisionCtrl.hasCollision = didCollide;
	yOffset += 1;
	yOffset *= doOffsetY*didCollide;
	xOffset += 1;
	xOffset *= (!doOffsetY)*didCollide;
	character->position.y -= CONVERT_2MOVE(yOffset);
	character->position.x -= CONVERT_2MOVE(xOffset);
	if (character->free->type == EControlAiType) {
		((CharacterAIControl*)character->free)->downBlocked |= (yOffset != 0);
		((CharacterAIControl*)character->free)->rightBlocked |= (xOffset != 0);
	}
}

void common_mapMovingLeftDownOffset(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox) {
	bool didCollide = hasCollision(charBoundingBox, otherCharBoundingBox) | hasCollision(otherCharBoundingBox, charBoundingBox);
	int xOffset = (otherCharBoundingBox->endX - charBoundingBox->startX);
	int yOffset = (charBoundingBox->endY - otherCharBoundingBox->startY);
	bool doOffsetY = (xOffset > yOffset);
	character->collisionCtrl.hasCollision = didCollide;
	yOffset += 1;
	yOffset *= doOffsetY*didCollide;
	xOffset += 1;
	xOffset *= (!doOffsetY)*didCollide;
	character->position.y -= CONVERT_2MOVE(yOffset);
	character->position.x += CONVERT_2MOVE(xOffset);
	if (character->free->type == EControlAiType) {
		((CharacterAIControl*)character->free)->downBlocked |= (yOffset != 0);
		((CharacterAIControl*)character->free)->leftBlocked |= (xOffset != 0);
	}
}

void commonGetBoundsFromMap(s32 x, s32 y, const MapInfo* mapInfo, BoundingBox *charBoundingBox) {
	if (mapInfo->collisionMap) {
	    int blockX = DIVIDE_BY_16(x);
	    int blockY = DIVIDE_BY_16(y)*DIVIDE_BY_16(mapInfo->width);
	    MapCollision *collision = &mapInfo->collisionMap[blockX + blockY];
		int result = (collision->width > 0)*(collision->height > 0);//*(mapInfo->collisionMap != NULL);
		charBoundingBox->startX = (x - GET_REMAINDER_16(x) + collision->x)*result;
		charBoundingBox->endX = charBoundingBox->startX + (collision->width + 1)*result;
		charBoundingBox->startY = y - GET_REMAINDER_16(y) + collision->y*result;
		charBoundingBox->endY = charBoundingBox->startY + (collision->height + 1)*result;
	} else {
		charBoundingBox->startX = 0;
		charBoundingBox->endX  = 0;
		charBoundingBox->startY = 0;
		charBoundingBox->endY = 0;
	}
}

inline void commonCheckMapCollision(CharacterAttr *character, const MapInfo* mapInfo, const Position *point, 
    const BoundingBox *characterBoundingBox, const CharFuncCollisionReaction reaction) {
	BoundingBox mapBoundingBox;
	commonGetBoundsFromMap(point->x, point->y, mapInfo, &mapBoundingBox);
	reaction(character, characterBoundingBox, &mapBoundingBox);
}

void commonMovingUpMapCollision(CharacterAttr *character, const MapInfo* mapInfo, 
	CharFuncCollisionReaction reaction) {
    int count, i;
    BoundingBox characterBoundingBox;
	for (i = 0; i < 2; ++i) {
		character->getBounds(character, &count, &characterBoundingBox);
		Position points[] = { { characterBoundingBox.startX, characterBoundingBox.startY - 1, 0},
			{ characterBoundingBox.endX, characterBoundingBox.startY - 1, 0} };
	
		commonCheckMapCollision(character, mapInfo, &points[i], &characterBoundingBox, reaction);
	}
	
}

void commonMovingDownMapCollision(CharacterAttr *character, const MapInfo* mapInfo, 
	CharFuncCollisionReaction reaction) {
    int count, i;
    BoundingBox characterBoundingBox;
	for (i = 0; i < 2; ++i) {
		character->getBounds(character, &count, &characterBoundingBox);
		Position points[] = { { characterBoundingBox.startX, characterBoundingBox.endY, 0},
        { characterBoundingBox.endX, characterBoundingBox.endY, 0} };
		
		commonCheckMapCollision(character, mapInfo, &points[i], &characterBoundingBox, reaction);
	}		
}

void commonMovingRightMapCollision(CharacterAttr *character, const MapInfo* mapInfo, 
	CharFuncCollisionReaction reaction) {
    int count, i;
    BoundingBox characterBoundingBox;
	for (i = 0; i < 2; ++i) {
		character->getBounds(character, &count, &characterBoundingBox);
		Position points[] = { { characterBoundingBox.endX, characterBoundingBox.startY, 0},
        { characterBoundingBox.endX, characterBoundingBox.endY, 0} };
	
		commonCheckMapCollision(character, mapInfo, &points[i], &characterBoundingBox, reaction);
	}
}

void commonMovingLeftMapCollision(CharacterAttr *character, const MapInfo* mapInfo, 
	CharFuncCollisionReaction reaction) {
    int count, i;
    BoundingBox characterBoundingBox;
	for (i = 0; i < 2; ++i) {
		character->getBounds(character, &count, &characterBoundingBox);
		Position points[] = { { characterBoundingBox.startX - 1, characterBoundingBox.startY, 0},
			{ characterBoundingBox.startX - 1, characterBoundingBox.endY, 0} };
	
		commonCheckMapCollision(character, mapInfo, &points[i], &characterBoundingBox, reaction);
	}
}

void commonMovingLeftUpMapCollision(CharacterAttr *character, const MapInfo* mapInfo, 
	CharFuncCollisionReaction reaction) {
    int count, i;
    BoundingBox characterBoundingBox;
	for (i = 0; i < 3; ++i) {
		character->getBounds(character, &count, &characterBoundingBox);
		Position points[] = { { characterBoundingBox.startX - 1, characterBoundingBox.endY, 0},
			{ characterBoundingBox.endX, characterBoundingBox.startY - 1, 0}, 
			{ characterBoundingBox.startX - 1, characterBoundingBox.startY - 1, 0}};
	
		commonCheckMapCollision(character, mapInfo, &points[i], &characterBoundingBox, reaction);
	}
}

void commonMovingLeftDownMapCollision(CharacterAttr *character, const MapInfo* mapInfo, 
	CharFuncCollisionReaction reaction) {
    int count, i;
    BoundingBox characterBoundingBox;
	for (i = 0; i < 3; ++i) {
		character->getBounds(character, &count, &characterBoundingBox);
		Position points[] = { { characterBoundingBox.startX - 1, characterBoundingBox.startY - 1, 0},
			{ characterBoundingBox.endX, characterBoundingBox.endY, 0},
			{ characterBoundingBox.startX - 1, characterBoundingBox.endY, 0} };
	
		commonCheckMapCollision(character, mapInfo, &points[i], &characterBoundingBox, reaction);
	}
}

void commonMovingRightUpMapCollision(CharacterAttr *character, const MapInfo* mapInfo, 
	CharFuncCollisionReaction reaction) {
    int count, i;
    BoundingBox characterBoundingBox, mapBoundingBox;
    for (i = 0; i < 3; ++i) {
		character->getBounds(character, &count, &characterBoundingBox);
		Position points[] = { { characterBoundingBox.endX, characterBoundingBox.endY, 0},
			{ characterBoundingBox.startX - 1, characterBoundingBox.startY - 1, 0},
			{ characterBoundingBox.endX, characterBoundingBox.startY - 1, 0} };
	
		commonCheckMapCollision(character, mapInfo, &points[i], &characterBoundingBox, reaction);
	}
}

void commonMovingRightDownMapCollision(CharacterAttr *character, const MapInfo* mapInfo, 
	CharFuncCollisionReaction reaction) {
    int count, i;
    BoundingBox characterBoundingBox, mapBoundingBox;
    for (i = 0; i < 3; ++i) {
		character->getBounds(character, &count, &characterBoundingBox);
		Position points[] = { { characterBoundingBox.endX, characterBoundingBox.startY - 1, 0},
			{ characterBoundingBox.startX - 1, characterBoundingBox.endY, 0},
			{ characterBoundingBox.endX, characterBoundingBox.endY, 0} };
	
		commonCheckMapCollision(character, mapInfo, &points[i], &characterBoundingBox, reaction);
	}
}

void commonSetCharacterEvent(CharacterAttr *character, const CharacterEventControl *eventControl) {
   CharacterEventControl *charControl = (CharacterEventControl*)character->free;
   charControl->type = eventControl->type;
   charControl->width = eventControl->width;
   charControl->height = eventControl->height;
   charControl->countAction = eventControl->countAction;
   charControl->currentAction = 0;
   charControl->returnControl = eventControl->returnControl;
   charControl->isRunning = true;
   charControl->actions = eventControl->actions;
}

void commonTriggerCharacterEvent(CharacterAttr *character, const MapInfo *mapInfo, CharacterCollection *charCollection) {
   CharacterAttr *targetCharacter = mchar_findCharacterType(charCollection, NAMELESS);
   CharacterEventControl *charControl = (CharacterEventControl*)character->free;
   //int width = DIVIDE_BY_2(charControl->width);
   //int height = DIVIDE_BY_2(charControl->height);
   int count;
   BoundingBox eventBox, targetBox;
   eventBox.startX = character->position.x - charControl->width;
   eventBox.endX = character->position.x + charControl->width;
   eventBox.startY = character->position.y - charControl->height;
   eventBox.endY = character->position.y + charControl->height;

    if (targetCharacter) {
       charControl->target = &targetCharacter->position;
    }
   
	targetCharacter->getBounds(targetCharacter, &count, &targetBox);
	if (hasCollision(&eventBox, &targetBox) || hasCollision(&targetBox, &eventBox)) {
	    character->controller = &commonDoCharacterEvent;
		charCollection->charactersDoEvent[charCollection->characterEventCurrentSize] = character;
		++charCollection->characterEventCurrentSize;
	}
}

void commonDoActionOneCycle(CharacterAttr *character, const MapInfo *mapInfo, 
    CharacterCollection *charCollection) {
    CharacterEventControl *eventControl = character->free;
	int nextScreenFrame, nextAnimationFrame;
    bool isLastFrame = false;
    	   
	ActionControl actionControl = eventControl->actions[eventControl->currentAction];
	
	character->nextDirection = actionControl.direction;
	character->nextAction = actionControl.action;
	
	commonGetNextFrame(character, &nextScreenFrame, &nextAnimationFrame, &isLastFrame);
	
	if (isLastFrame) {
	    ++eventControl->currentAction;
		if (eventControl->currentAction >= eventControl->countAction) {
			character->controller = eventControl->returnControl;
			eventControl->currentAction = 0;
			eventControl->countAction = 0;
			--charCollection->characterEventCurrentSize;
			charCollection->charactersDoEvent[charCollection->characterEventCurrentSize] = NULL;
		} 
	}
}

void commonDoActionByFrames(CharacterAttr *character, const MapInfo *mapInfo, CharacterCollection *charCollection) {
}

void commonDoCharacterEvent(CharacterAttr *character, const MapInfo *mapInfo, CharacterCollection *charCollection) {
    CharacterEventControl *eventControl = character->free;
	int nextScreenFrame, nextAnimationFrame;
    bool isLastFrame = false;
    	   
	ActionControl actionControl = eventControl->actions[eventControl->currentAction];
	
	character->nextDirection = actionControl.direction;
	character->nextAction = actionControl.action;
	
	commonGetNextFrame(character, &nextScreenFrame, &nextAnimationFrame, &isLastFrame);
	
	if (isLastFrame) {
	    character->controller = eventControl->returnControl;
		--charCollection->characterEventCurrentSize;
		charCollection->charactersDoEvent[charCollection->characterEventCurrentSize] = NULL;
	}
 }
 
 void transferToBoundingBox(const EventTransfer *transfer, BoundingBox *boundingBox) {
    boundingBox->startX = transfer->x;
	boundingBox->startY = transfer->y;
	boundingBox->endX = transfer->x + transfer->width;
	boundingBox->endY = transfer->y + transfer->height;
}

 void commonCheckForEvents(CharacterAttr* character, MapInfo *mapInfo) {
	int boundBoxCount = 0, i;
	BoundingBox eventBox, characterBoundingBox;
	character->getBounds(character, &boundBoxCount, &characterBoundingBox);
	for (i = 0; i < mapInfo->eventTransferCount; ++i) {
		transferToBoundingBox(&mapInfo->tranfers[i], &eventBox);
		if (hasCollision(&characterBoundingBox, &eventBox)) {
			mapInfo->transferTo = &mapInfo->tranfers[i];
			mapInfo->mapFunction = &fadeToBlack;
			break;
		}
	}
}

int commonGetCurrentAnimationFrame(const CharacterAttr* character) {
	return character->spriteDisplay.currentAnimationFrame;
}

int commonGetCurrentScreenFrame(const CharacterAttr* character) {
	return character->spriteDisplay.numberOfFramesPassed;
}

bool commonDoNextAction(CharacterAttr* character) {
    int nextScreenFrame, nextAnimationFrame;
	bool isLastFrame = false;
	CharacterAIControl *charControl = (CharacterAIControl*)character->free;
		
	commonGetNextFrame(character, &nextScreenFrame, &nextAnimationFrame, &isLastFrame);

	return (charControl->actions[charControl->currentAction].doForNumFrames == DOACTIONUNTILEND & isLastFrame) ||
		(charControl->actions[charControl->currentAction].doForNumFrames != DOACTIONUNTILEND & 
		    charControl->actions[charControl->currentAction].currentFrame >= 
			charControl->actions[charControl->currentAction].doForNumFrames);
}

bool commonDoIntializeActions(CharacterAttr* character) {
   CharacterAIControl *charControl = (CharacterAIControl*)character->free;
   return charControl->currentAction >= MAXACTIONS | ((charControl->currentAction + 1) >= charControl->countAction &
	commonDoNextAction(character));
}

const Position* commonFindCharTypeInBoundingBox(const CharacterCollection *characterCollection, 
    const BoundingBox *boundingBox, CHARACTERTYPE fromType, CHARACTERTYPE toType) {
	int i;
	for (i = 0; i < characterCollection->currentSize; ++i) {
		if (characterCollection->characters[i]->type >= fromType && 
			characterCollection->characters[i]->type <= toType) {
			if (commonPositionInBounds(&characterCollection->characters[i]->position, boundingBox)) {
				return &characterCollection->characters[i]->position;
			}
		}
	}
	return &NOT_FOUND_POSITION;
}

const Position* commonFindCharTypePositionByDistance(const CharacterCollection *characterCollection, 
    const Position *refPos, int dist, CHARACTERTYPE fromType, CHARACTERTYPE toType) {
	int i, distX, distY;
	for (i = 0; i < characterCollection->currentSize; ++i) {
		if (characterCollection->characters[i]->type >= fromType && 
			characterCollection->characters[i]->type <= toType) {
			distX = CONVERT_2POS(refPos->x) - CONVERT_2POS(characterCollection->characters[i]->position.x);
			distX *= distX;
			distY = CONVERT_2POS(refPos->y) - CONVERT_2POS(characterCollection->characters[i]->position.y);
			distY *= distY;
			dist *= dist;
			if (dist >= distX + distY) {
				return &characterCollection->characters[i]->position;
			}
		}
	}
	return &NOT_FOUND_POSITION;
}

bool commonIsFoundPosition(const Position* position) {
	return (position->x != -1) & (position->y != -1);
}