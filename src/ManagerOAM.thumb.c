#include <stdlib.h>
#include "GBATypes.h"
#include "GBAVideo.h"
#include "GBADMA.h"
#include "GBAObject.h"

#define MAX_SPRITES 128
#define MAXCHARONSCR 16
#define MAXCHAROFFSCR 32

EWRAM OAMCollection *moam_vreference = NULL;
#define SPRITE_OFFSCREEN_Y 161
#define SPRITE_OFFSCREEN_X 241
#define OBJ_MODE_DISABLE 2
const STRUCT_OBJ_ATT moam_removeObj = {
	{ SPRITE_OFFSCREEN_Y, OBJ_MODE_DISABLE,0,0,0,0 },
	{ SPRITE_OFFSCREEN_X, 0,0,0,0 },
	{0,0,0},
	{0}
};

void moam_initBuffer(OAMCollection *oamCollection) {
	int i;
	for (i = 0; i < oamCollection->size; ++i) {
		oamCollection->data[i] = *((OBJ_ATTR*)&moam_removeObj);
	}
}

void moam_setUpdate(OAMCollection *ref) {
	moam_vreference = ref;
}

void moam_update() {
	if (moam_vreference) {
		dma3_cpy32(OAM_MEMORY, moam_vreference->data,
			DIVIDE_BY_4(moam_vreference->size*sizeof(OBJ_ATTR)));
	}
}


