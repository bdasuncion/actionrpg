#ifndef MANAGER_OAM
#define MANAGER_OAM

#include "GBATypes.h"
#include "GBAVideo.h"
#include "GBADMA.h"
#include "GBAObject.h"

void moam_initBuffer(OAMCollection *oamCollection);
void moam_setUpdate(OAMCollection *ref);
void moam_update();
extern const STRUCT_OBJ_ATT moam_removeObj;

#endif
