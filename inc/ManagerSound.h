#ifndef MANAGER_SOUND
#define MANAGER_SOUnD

#include "GBATypes.h"
#include "GBASound.h"
#include "GBADMA.h"
#include "GBAObject.h"

void msound_init();
void msound_setUp();
void msound_mix();
void msound_changeBuf();
void msound_setChannel(const Sound *sound, bool isRepeating);
void msound_setChannelTest(const Sound *sound, bool isRepeating, int rightPhaseDelay, int leftPhaseDelay);
void msound_process3dSound(int *distance, int *rightPhaseDelay, int *leftPhaseDelay);
#endif