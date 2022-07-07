#ifndef CHARACTER_COMMON
#define CHARACTER_COMMON

#include "GBAObject.h"
#include "GBACharacter.h"
#include "GBACharacterType.h"
#include "GBAMap.h"
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
void common_mapMovingRight(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox);
void common_mapMovingLeft(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox);
void common_mapMovingUp(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox);
void common_mapMovingDown(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox);
void common_mapMovingRightUpOffset(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox);
void common_mapMovingLeftUpOffset(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox);
void common_mapMovingRightDownOffset(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox);
void common_mapMovingLeftDownOffset(CharacterAttr* character, 
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
void commonTriggerCharacterEvent(CharacterAttr *character, const MapInfo *mapInfo, CharacterCollection *charCollection);
void commonCheckForEvents(CharacterAttr* character, MapInfo *mapInfo);
bool commonDoNextAction(CharacterAttr* character);
const Position* commonFindCharTypeInBoundingBox(const CharacterCollection *characterCollection, 
const BoundingBox *boundingBox, CHARACTERTYPE fromType, CHARACTERTYPE toType);
const Position* commonFindCharTypePositionByDistance(const CharacterCollection *characterCollection, 
    const Position *refPos, int dist, CHARACTERTYPE fromType, CHARACTERTYPE toType);
const CharFuncCollisionReaction common_collisionReactions[2][8];
const CharFuncCollisionReaction common_mapCollisionReactions[8];
const CommonMapCollision common_mapCollision[8];
inline int commonGetCurrentAnimationFrame(const CharacterAttr* character);
inline int commonGetCurrentScreenFrame(const CharacterAttr* character);
inline bool commonDoIntializeActions(CharacterAttr* character);
inline bool commonIsFoundPosition(const Position* position);
#endif