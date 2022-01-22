#include "GBATypes.h"
#include "GBAVideo.h"
#include "GBADMA.h"
#include "GBAObject.h"

//extern void checkCollision(CHARACTER_ATTR* chara);
//extern s32 checkCollisionAI(CHARACTER_ATTR* chara);
//extern s32 checkBGCollision16X16(CHARACTER_ATTR* chara);
//extern s32 checkBGCollision16X16AI(CHARACTER_ATTR* chara);
//extern s32 checkBGCollision32X32(CHARACTER_ATTR* chara);

extern s32 checkCollision(CHARACTER_ATTR* chara, spritePlanePosition* sprite_posNew,
	spritePlanePosition* sprite_posCurr);
extern s32 checkBGCollision16X16(CHARACTER_ATTR* chara, spritePlanePosition* sprite_posNew,
	spritePlanePosition* sprite_posCurr);

