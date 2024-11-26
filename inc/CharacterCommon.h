#ifndef CHARACTER_COMMON
#define CHARACTER_COMMON

#include "GBAObject.h"
#include "GBACharacter.h"
#include "GBACharacterType.h"
#include "GBAMap.h"
#include "GBACharacterActionEvent.h"
#include <stdbool.h>

extern const CharacterAttr openSlot;
extern const s32 common_zOffsetDown;
void commonRemoveCharacter(CharacterAttr *character);
void commonSetToOamBuffer(SpriteDisplay *spriteDisplay, OBJ_ATTR *oamBuf);
void commonDrawDisplay(SpriteDisplay *spriteDisplay);
UpdateStatus commonUpdateCharacterAnimation(CharacterAttr* character);
UpdateStatus commonInitializeAction(CharacterAttr* character);
void commonGetCharacterNextFrame(const CharacterAttr* character, int *nextScreenFrame, 
    int *nextAnimationFrame, bool *isLastFrame);
void commonCharacterSetPosition(CharacterAttr* character, int x, int y, int z, EDirections direction);
void commonCharacterInit(CharacterAttr* character, int initialize, int action, EDirections direction);
bool commonIsInScreen(int charStartX, int charEndX, int charStartY, int charEndY, 
    const Position *scr_pos, const ScreenDimension *scr_dim);
bool hasCollision(const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox);
bool commonCollissionPointInBounds(const Position *collisionPoint, const BoundingBox *boundingBox);
bool commonPositionInBounds(const Position *position, const BoundingBox *boundingBox);
void commonCharacterMapEdgeCheck(CharacterAttr* character, const MapInfo* mapInfo);
//bool common_checkNext(bool isOtherCharBelow, const BoundingBox *charBoundingBox, 
//    const BoundingBox *otherCharBoundingBox);
bool common_checkNext(bool isOtherCharBelow, const Position *charBoundingBox, 
    const Position *otherCharBoundingBox);
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
void commonTriggerCharacterEvent(CharacterAttr *character, const MapInfo *mapInfo, const CharacterCollection *charCollection);
void commonCheckForEvents(CharacterAttr* character, MapInfo *mapInfo);
bool commonDoNextAction(CharacterAttr* character);
const Position* commonFindCharTypeInBoundingBox(const CharacterCollection *characterCollection, 
const BoundingBox *boundingBox, CHARACTERTYPE fromType, CHARACTERTYPE toType);
const Position* commonFindCharTypePositionByDistance(const CharacterCollection *characterCollection, 
	const Position *refPos, int dist, CHARACTERTYPE fromType, CHARACTERTYPE toType);
bool commonHasReachedWaypoint(const Position *waypoint, const BoundingBox *boundingBox);
extern const CharFuncCollisionReaction common_collisionReactions[8];
extern const CharFuncCollisionReaction common_mapCollisionReactions[8];
extern const CommonMapCollision common_mapCollision[8];
inline int commonGetCurrentAnimationFrame(const CharacterAttr* character);
inline int commonGetCurrentDisplayFrame(const CharacterAttr* character);
inline bool commonDoIntializeActions(CharacterAttr* character);
inline void commonRemoveActionOnInit(CharacterAttr* character, CharacterActionCollection *charActionCollection);
inline bool commonIsFoundPosition(const Position* position);
int common_fallingDown(CharacterAttr* character, const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox);
int common_fallingDownOnBoundingBox(CharacterAttr* character, 
    const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox);
void commonHandleBlockedPath(CharacterAIControl *charControl, EDirections *goDirection);
void commonGravityEffect(CharacterAttr *character, int zOffsetDown);
int commonConvertBoundingBoxZ(int zPos);
void commonInitShadow();
void commonReverseDisplayShadow();
int commonSetShadow(int x, int y, OBJ_ATTR *oamBuf);
void commonFallingDownCollision(CharacterAttr *character, MapInfo *mapInfo);
bool isOverlap(const BoundingBox *charBoundingBox, const BoundingBox *otherCharBoundingBox);
void commonSetCharType(const Position* position, const MapInfo *mapInfo, 
	CHARACTERTYPE type, CharacterCollection *characterCollection, 
	CharacterActionCollection *charActionCollection, CharacterAttr *character,
	ControlTypePool* controlPool, CharacterWaypoints *charWaypoints);
inline EDirections commonReverseDirection(EDirections direction);
inline UpdateStatus commonUpdateAnimation(SpriteDisplay *spriteDisplay);
int commonCharacterSetToOAMBuffer(CharacterCollection *charCollection,
	OAMCollection *oamCollection,
	int currentOAMIdx,
	const Position *scr_pos,
	const ScreenDimension *scr_dim);
bool commonAnimation_IsLastFrame(const SpriteDisplay* spriteDisplay);
bool commonIsCharTypeInArea(const BoundingBox *area, const CharacterCollection *characterCollection, CHARACTERTYPE findType);
void commonRegenerateCharTypeAt(const BoundingBox *boundingBoxCheckArea, const Position* position, const MapInfo *mapInfo, CHARACTERTYPE type, 
	CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection, 
	ControlTypePool* controlPool, CharacterWaypoints *charWaypoints);
//int commonDummy();
void commonSetToOamBufferAsMask(SpriteDisplay *spriteDisplay, OBJ_ATTR *oamBuf, SPRITESHAPE shape,
		SPRITESIZE size);
void commonControllerDummy(CharacterAttr* charAtt, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection);
void commonActionDummy(CharacterAttr* charAtt, const MapInfo *mapInfo, 
	const CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection);
int commonSetPositionDummy(CharacterAttr* charAtt, OBJ_ATTR *oamBuf, 
	const Position *scr_pos, const ScreenDimension *scr_dim);
void commonGetBoundsDummy(const CharacterAttr* charAtt, int *count, BoundingBox *collisionBox) ;
void commonCollisionCheckDummy(CharacterAttr *charAtt, bool isOtherCharBelow,
	bool *checkNext, const CharacterAttr *checkWithCharAtt);
void commonMapCollisionDummy(CharacterAttr* charAtt, const MapInfo* mapInfo);
void commonActionCollisionDummy(CharacterAttr *charAtt,  CharacterActionCollection *actionEvents, 
	AttackEffectCollection *attackEffects);
bool commonIsHitDummy(struct CharacterAttr *charAtt, struct CharacterActionEvent *actionEvent);
extern const EDirections FAR_TARGET[5][5];
extern const EDirections NEAR_TARGET[5][5];
void common_findDirectionOfPosition(Position *current, Position *targetPos, EDirections *goDirection);
void common_findDirectionOfTargetCharacter(Position *current, Position *target, EDirections *goDirection);
#endif