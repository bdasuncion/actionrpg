#ifndef CHARACTER_COMMON
#define CHARACTER_COMMON

#include "GBAObject.h"
#include "GBACharacter.h"
#include <stdbool.h>

extern const CharacterAttr openSlot;
void commonRemoveCharacter(CharacterAttr *character);
void commonSetToOamBuffer(SpriteDisplay *spriteDisplay, OBJ_ATTR *oamBuf);
void commonDrawDisplay(SpriteDisplay *spriteDisplay);
UpdateStatus commonUpdateAnimation(CharacterAttr* character);
UpdateStatus commonInitializeAction(CharacterAttr* character);
void commonGetNextFrame(const CharacterAttr* character, int *nextScreenFrame, 
    int *nextAnimationFrame, bool *isLastFrame);
void commonCharacterSetPosition(CharacterAttr* character, int x, int y, int z, EDirections direction);
void commonCharacterInit(CharacterAttr* character, int initialize, int action, EDirections direction);
bool commonIsInScreen(int charStartX, int charEndX, int charStartY, int charEndY, 
    const Position *scr_pos, const ScreenDimension *scr_dim);
bool hasCollision(const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox);
bool commonPositionInBounds(const Position *position, const BoundingBox *boundingBox);
void commonCharacterMapEdgeCheck(CharacterAttr* character, const MapInfo* mapInfo);
bool common_checkNext(bool isOtherCharBelow, const BoundingBox *charBoundingBox, 
    const BoundingBox *otherCharBoundingBox);
void common_noMovement(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox);
void common_movingRight(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox);
void common_movingLeft(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox);
void common_movingUp(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox);
void common_movingDown(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox);
void common_movingRightUpOffset(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox);
void common_movingLeftUpOffset(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox);
void common_movingRightDownOffset(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox);
void common_movingLeftDownOffset(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox);
void commonGetBoundsFromMap(s16 x, s16 y, const MapInfo* mapInfo, BoundingBox *charBoundingBox);
void commonMovingUpMapCollision(CharacterAttr *character, const MapInfo* mapInfo, CharFuncCollisionReaction reaction);
void commonMovingDownMapCollision(CharacterAttr *character, const MapInfo* mapInfo, CharFuncCollisionReaction reaction);
void commonMovingRightMapCollision(CharacterAttr *character, const MapInfo* mapInfo, CharFuncCollisionReaction reaction);
void commonMovingLeftMapCollision(CharacterAttr *character, const MapInfo* mapInfo, CharFuncCollisionReaction reaction);
void commonMovingLeftUpMapCollision(CharacterAttr *character, const MapInfo* mapInfo, CharFuncCollisionReaction reaction);
void commonMovingLeftDownMapCollision(CharacterAttr *character, const MapInfo* mapInfo, CharFuncCollisionReaction reaction);
void commonMovingRightUpMapCollision(CharacterAttr *character, const MapInfo* mapInfo, CharFuncCollisionReaction reaction);
void commonMovingRightDownMapCollision(CharacterAttr *character, const MapInfo* mapInfo, CharFuncCollisionReaction reaction);
void commonSetCharacterEvent(CharacterAttr *character, const CharacterEventControl *eventControl);
void commonTriggerCharacterEvent(CharacterAttr *character, const void *mapInfo, const void *charCollection);
void commonCheckForEvents(CharacterAttr* character, MapInfo *mapInfo);
bool commonDoNextAction(CharacterAttr* character);
#endif