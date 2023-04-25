#ifndef CHARACTER_COMMON
#define CHARACTER_COMMON

#include "GBAObject.h"
#include "GBACharacter.h"
#include "GBACharacterType.h"
#include "GBAMap.h"
#include <stdbool.h>

extern const CharacterAttr openSlot;
extern const s32 common_zOffsetDown;
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
bool commonCollissionPointInBounds(const Position *collisionPoint, const BoundingBox *boundingBox);
bool commonPositionInBounds(const Position *position, const BoundingBox *boundingBox);
void commonCharacterMapEdgeCheck(CharacterAttr* character, const MapInfo* mapInfo);
bool common_checkNext(bool isOtherCharBelow, const BoundingBox *charBoundingBox, 
    const BoundingBox *otherCharBoundingBox);
void common_noMovement(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox);
void common_movingRightOffset(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox);
void common_movingLeftOffset(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox);
void common_movingUpOffset(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox);
void common_movingDownOffset(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox);
void common_movingRightUpOffset(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox);
void common_movingLeftUpOffset(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox);
void common_movingRightDownOffset(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox);
void common_movingLeftDownOffset(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox);
void common_mapMovingRightOffset(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox);
void common_mapMovingLeftOffset(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox);
void common_mapMovingUpOffset(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox);
void common_mapMovingDownOffset(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox);
void common_mapMovingRightUpOffset(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox);
void common_mapMovingLeftUpOffset(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox);
void common_mapMovingRightDownOffset(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox);
void common_mapMovingLeftDownOffset(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox);
void commonGetBoundsFromMap(s32 x, s32 y, const MapInfo* mapInfo, BoundingBox *charBoundingBox);
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
extern const CharFuncCollisionReaction common_collisionReactions[2][8];
extern const CharFuncCollisionReaction common_mapCollisionReactions[8];
extern const CommonMapCollision common_mapCollision[8];
inline int commonGetCurrentAnimationFrame(const CharacterAttr* character);
inline int commonGetCurrentScreenFrame(const CharacterAttr* character);
inline bool commonDoIntializeActions(CharacterAttr* character);
inline bool commonIsFoundPosition(const Position* position);
int common_fallingDown(CharacterAttr* character, const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox);
void commonGravityEffect(CharacterAttr *character, int zOffsetDown);
int commonConvertBoundingBoxZ(int zPos);
void commonInitShadow();
void commonReverseDisplayShadow();
int commonSetShadow(int x, int y, OBJ_ATTR *oamBuf);
void commonFallingDownCollision(CharacterAttr *character, MapInfo *mapInfo);
bool isOverlap(const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox);
#endif