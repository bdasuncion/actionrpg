#include "GBATypes.h"
#include "GBAInterrupt.h"
#include "GBAVideo.h"

void mgame_setUpdater(fnptr functionUpdater)
{
	gbavid_vBlankInterrupt(EEnable);
	gbaint_setRequestHandler(functionUpdater);
	gbaint_requestVBlank(EEnable);
	gbaint_ctrl(EEnable);
}