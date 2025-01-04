#include "GBATypes.h"
#include "GBAInterrupt.h"
#include "GBAVideo.h"
#include <stdbool.h>

EWRAM bool updateGameState;
void setUpdateGameState(bool shouldUpdate) {
	updateGameState = shouldUpdate;
}

bool isUpdateGameState() {
	return updateGameState;
}

void mgame_setUpdater(fnptr functionUpdater)
{
	gbavid_vBlankInterrupt(EEnable);
	gbaint_setRequestHandler(functionUpdater);
	gbaint_requestVBlank(EEnable);
	gbaint_ctrl(EEnable);
}