#include "GBATypes.h"
#include "GBAInterrupt.h"
#include "GBAVideo.h"
#include <stdbool.h>

void setUpdateGameState(bool shouldUpdate);
bool isUpdateGameState();
extern void mgame_setUpdater(fnptr functionUpdater);