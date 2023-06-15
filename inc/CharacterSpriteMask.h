#ifndef CHARACTER_SPRITEMASK
#define CHARACTER_SPRITEMASK

#include "GBAObject.h"
#include "GBACharacter.h"
#include "GBACharacterType.h"
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

extern const u32 spriteMaskImageSize[];

typedef void (*SpriteMaskFuncInit)(CharacterAttr* spritemask, SpriteMaskType type, int maskId, 
	const Position *position); 

#endif