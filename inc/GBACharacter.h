#ifndef GBACharacter
#define GBACharacter

#define MAXACTIONS 8
#define DOACTIONUNTILEND 0
 
#include "GBAObject.h"
#include "GBAStructDeclarations.h"

typedef enum UpdateStatus {
	ENoUpdate,
	EUpdate
}UpdateStatus;

typedef enum ControlType {
    EControlNone,
	EControlAiType,
	EControlEventType,
	EControlControlType,
	EControlDumyType1,
	EControlDumyType2,
	EControlDumyType3,
} ControlType;

typedef enum StatusType {
    EStatusNormal,
	EStatusNoActionCollision
} StatusType;

/*typedef enum AttackType {
	EAttackNone = -1,
    EAttackHorizontalRight,
	EAttackHorizontalLeft
} AttackType;*/

typedef enum CharacterActionType {
    EActionNone = -1,
	EAttackHorizontalRight,
	EAttackHorizontalLeft,
	EAttackClawRight,
	EAttackClawLeft,
	EActionCount
} CharacterActionType;

typedef struct CharBoundingBox {
	Position upperLeftPt;
	u16 width; //y
	u16 length;//x
	u16 height;//z
} CharBoundingBox;

typedef struct SpriteLayer {
    const u32 *image;
	//u32 *palette; //TODO SHOULD REMOVE THIS
	s32 offsetX:8;
	s32 offsetY:8;
    u32 shape:2;
	u32 size:2;
	u32 hflip:1;
	u32 vflip:1;
	u32 compression:2;
	u32 idOffset:5;
	u32 palleteidOffset:3; //TODO SHOULD CHANGE THIS
}ALIGN4 SpriteLayer;

typedef struct SpriteLayerSet {
    const SpriteLayer *layers;
    u32 displayForNumFrames:16;
	u32 numberOflayers:16;
}ALIGN4 SpriteLayerSet;

typedef struct SpriteSet {
    //u32 *palette; // TODO Palette should be here
	//u32 paletteCount;
    const SpriteLayerSet *set;
    u32 numberOfAnimation;
}ALIGN4 SpriteSet;

typedef struct SpriteDisplay {
    const SpriteSet *spriteSet;
	u32 baseImageId:10;
	UpdateStatus imageUpdateStatus:1;
	u32 basePalleteId:4;
	UpdateStatus palleteUpdateStatus:1;//TODO remove?
	u32 numberOfFramesPassed:8;//Count from last update
	u32 currentAnimationFrame:7;
	bool isInScreen:1;
	u32 baseY:8;
	u32 baseX:9;
	//u32 shadow:8;
	u32 dummy:7;
}ALIGN4 SpriteDisplay;

typedef struct AttackEffect {
	SpriteDisplay display;
	Position position;
	CharacterActionType type;
}ALIGN4 AttackEffect;

typedef struct AttackEffectCollection {
	u32 count:4;
	AttackEffect **collection;
}ALIGN4 AttackEffectCollection;

typedef struct MovementControl {
    u8 maxFrames;
	u8 currentFrame;
} ALIGN2 MovementControl;

typedef struct CollisionControl {
    bool hasCollision;
	u8 countDown;
} ALIGN2 CollisionControl;

/*typedef void (*CharFuncController)(void* charAtt, const void *mapInfo, const void *characterCollection);
typedef void (*CharFuncAction)(void* charAtt, 
	const void *mapInfo, const void *characterCollection, void *charActionCollection);
typedef int (*CharFuncSetPos)(void* charAtt, void *oamBuf,
	const void *scr_pos, //TODO: Put screen dimension in its own header
	const void *scr_dim); //TODO: Put screen position it its own header

typedef void (*CharFuncGetBounds)(void* charAtt,
	int *count, void *collisionBox);
	
typedef void (*CharFuncCollisionCheck)(void* charAtt, bool isOtherCharBelow,
	bool *checkNext, void* checkWithCharAtt);
	
typedef void (*CharFuncMapCollisionCheck)(void* charAtt, void* mapInfo);

typedef void (*CharFuncActionCollision)(void *charAtt, void *actionEvents, void *attackEffects);

typedef void (*CharFuncFallingCollision)(void *charAtt, const void *boundingBox, const void *otherBoundingBox);
*/
//CharacterAttr MapInfo CharacterCollection BoundingBox CharacterActionCollection AttackEffectCollection
typedef void (*CharFuncController)(struct CharacterAttr* charAtt, const struct MapInfo *mapInfo, 
	const struct CharacterCollection *characterCollection);
typedef void (*CharFuncAction)(struct CharacterAttr* charAtt, const struct MapInfo *mapInfo, 
	const struct CharacterCollection *characterCollection, struct CharacterActionCollection *charActionCollection);
typedef int (*CharFuncSetPos)(struct CharacterAttr* charAtt, struct OBJ_ATTR *oamBuf, 
	const struct Position *scr_pos,
	const struct ScreenDimension *scr_dim); //TODO: Put screen position it its own header

typedef void (*CharFuncGetBounds)(const struct CharacterAttr* charAtt,
	int *count, struct BoundingBox *collisionBox);
	
typedef void (*CharFuncCollisionCheck)(struct CharacterAttr *charAtt, bool isOtherCharBelow,
	bool *checkNext, const struct CharacterAttr *checkWithCharAtt);
	
typedef void (*CharFuncMapCollisionCheck)(struct CharacterAttr* charAtt, const struct MapInfo* mapInfo);

typedef void (*CharFuncActionCollision)(struct CharacterAttr *charAtt, 
	struct CharacterActionCollection *actionEvents, struct AttackEffectCollection *attackEffects);

typedef void (*CharFuncFallingCollision)(struct CharacterAttr *charAtt, const struct BoundingBox *boundingBox, 
	const struct BoundingBox *otherBoundingBox);

typedef bool (*CharFuncIsHit)(struct CharacterAttr *charAtt, struct CharacterActionEvent *actionEvent); //TODO: Put screen position it its own header

typedef struct ActionControl {
	u8 doForNumFrames;
	u8 currentFrame;
	u8 direction;
	u8 action;
}ALIGN4 ActionControl;

typedef struct ControlMap {
	CharFuncController buttonB;
	CharFuncController buttonA;
	CharFuncController buttonL;
	CharFuncController buttonR;
} ALIGN4 ControlMap;

typedef struct CharacterBaseControl {
    ControlType type:3;
	u32 poolId:5;
	u32 dumy:24;
	Position target;
} ALIGN4 CharacterBaseControl;

typedef struct CharacterWaypoints {
	u32 wayPointCnt:4;
	Position wayPoints[MAXACTIONS];
}ALIGN4 CharacterWaypoints;

typedef struct CharacterPlayerControl {
    ControlType type:3;
	u32 poolId:5;
	u32 currentStatus:4;
	u32 dumy:8;
	u32 buttonB_PressInterval:5;
	u32 buttonA_PressInterval:5;
	bool buttonL_Ready:1;
	bool buttonR_Ready:1;
	Position target;
	ActionControl action;
	ControlMap controlMap;
} ALIGN4 CharacterPlayerControl;

typedef struct CharacterAIControl {
    ControlType type:3;
	u32 poolId:5;
	u32 targetId:8;
	u32 countAction:4;
	u32 currentAction:4;
	u32 currentStatus:4;
	bool leftBlocked:1;
	bool rightBlocked:1;
	bool upBlocked:1;
	bool downBlocked:1;
	u32 wayPointCnt:4;
	u32 wayPointCurrent:4;
	const Position *wayPoints;
    Position target;
    ActionControl actions[MAXACTIONS];
} ALIGN4 CharacterAIControl;

typedef struct CharacterEventControl {
    ControlType type:3;
	u32 poolId:5;
	u32 width:6;
	u32 height:6;
	u32 countAction:6;
	u32 currentAction:6;
	Position *target;
	CharFuncController returnControl;
	bool isRunning;
	const ActionControl *actions;
} ALIGN4 CharacterEventControl;

typedef union ControlTypeUnion {
    ControlType type:3;
    CharacterBaseControl baseControl;
    CharacterAIControl aiControl;
    CharacterEventControl eventControl;
	CharacterPlayerControl playerControl;
} ALIGN4 ControlTypeUnion;

typedef struct CharacterStats {
	s16 maxLife;
	s16 currentLife;
	StatusType currentStatus;
} ALIGN4 CharacterStats;

typedef struct CharacterAttr {
	CharFuncController controller;
	CharFuncAction doAction;
	CharFuncSetPos setPosition;
	//CharFunc draw;
	CharFuncGetBounds getBounds; //Do we still need this here?
	CharFuncCollisionCheck checkCollision;
	CharFuncMapCollisionCheck checkMapCollision;
	CharFuncIsHit isHit;
	SpriteDisplay spriteDisplay;
	CharacterStats stats;
	u32 id:8;
	s32 type:9;
	s32 distanceFromGround:12;
	s32 dummy:3;
	u8 action;
	EDirections direction:4;
	EDirections faceDirection:4;
	u8 nextAction;
	EDirections nextDirection:4;
	EVerticalDirections verticalDirection:4;
	MovementControl movementCtrl;
	Position position;//3HW
	Position delta;//3HW
	CollisionControl collisionCtrl;
	ControlTypeUnion *free;//Can be any object, for use in the controller
} ALIGN4 CharacterAttr;

typedef void (*CharFuncCollisionReaction)(CharacterAttr* character, 
      const struct BoundingBox *charBoundingBox, const struct BoundingBox *otherCharBoundingBox);
	  
typedef void (*CommonMapCollision)(struct CharacterAttr *character, const struct MapInfo *mapInfo, 
    CharFuncCollisionReaction reaction);
 
typedef struct ControlTypePool {
  u32 count:6;
  u32 currentCount:6;
  ControlTypeUnion *collection;
} ALIGN4 ControlTypePool;

typedef void (*FuncCharacterInit)(CharacterAttr *character, ControlTypePool* collection, CharacterWaypoints *charWaypoints);
typedef void (*FuncCharacterSet)(CharacterAttr *character);

typedef struct CharacterCollection {
    u32 poolSize:6;
	u32 currentSize:6;
	u32 displaySize:6;
	u32 characterEventCurrentSize:6;
	u32 countCharacterTransfer:8;
	CharacterAttr **characters;//Collection for all processing
	CharacterAttr **charactersForDisplay;//Collection for diplay, includes sprite masks
	CharacterAttr **charactersDoEvent;
	FuncCharacterInit *characterTransfer;
} ALIGN4 CharacterCollection;

#define MOVEFRACTION 8
#define MOVE_STR (1 << MOVEFRACTION)
#define MOVE_DIAG ((MOVE_STR*7)/10)
#define CONVERT_2MOVE(val) ((val) << MOVEFRACTION)
#define CONVERT_2POS(val) ((val) >> MOVEFRACTION)

#define CONVERT_TO_SCRXPOS(x, scr_x, stat) \
	((CONVERT_2POS(x) - (stat[EScrCnvrtWidth] >> 1)) - scr_x)&0x1FF
	
#define CONVERT_TO_SCRYPOS(y, scr_y, stat) \
	((CONVERT_2POS(y) - stat[EScrCnvrtHeight]) - scr_y)&0xFF
	
#define CONVERT_TO_SCRZPOS(z)\
	(CONVERT_2POS(z))&0xFF

#define CONVERT_TO_BOUNDINGBOX_X(x, stat) \
	(CONVERT_2POS(x) - (DIVIDE_BY_2(stat[EBBCnvrtLength])))

#define CONVERT_TO_BOUNDINGBOX_Y(y, stat) \
	(CONVERT_2POS(y) - (DIVIDE_BY_2(stat[EBBCnvrtWidth])))
	
#define CONVERT_TO_BOUNDINGBOX_Z(z) \
	(CONVERT_2POS(z))
#endif