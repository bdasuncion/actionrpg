#ifndef CHARACTER_SPRITEMASK
#define CHARACTER_SPRITEMASK

#include "GBAObject.h"
#include "GBACharacter.h"
#include "CharacterType.h"
#include "GBAMap.h"
#include <stdbool.h>

typedef enum SpriteMaskType{
	EMaskTypeStart = 128,
	EMask16x16 = EMaskTypeStart,
	EMask16x32,
	EMask32x16,
	EMask32x32,
	EMask16x16Tall,
	EMask32x16Tall,
	EMask16x32Tall,
	EMaskTypeCount,
}SpriteMaskType;

typedef struct SpriteMaskInit {
	u16 x;
	u16 y;
	u16 z;
	u16 maskId;
	SpriteMaskType type;
}ALIGN4 SpriteMaskInit;

typedef struct SpriteMaskImage {
	SpriteMaskType type:8;
	const u32 *image;
}ALIGN4 SpriteMaskImage;

typedef struct SpriteMask {
	bool doInitMasks;
	int count;
	SpriteMaskImage *masks;
}ALIGN4 SpriteMask;

extern const u32 spriteMaskImageSize[];

typedef void (*SpriteMaskFuncInit)(struct CharacterAttr* spritemask, SpriteMaskType type, int maskId, 
	const Position *position);

void spritemask_init(struct CharacterAttr* spritemask, SpriteMaskInit *maskInit);
#endif