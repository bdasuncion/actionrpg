#ifndef MANAGER_SOUND
#define MANAGER_SOUnD

#include "GBATypes.h"
#include "GBASound.h"
#include "GBADMA.h"
#include "GBAObject.h"

void msound_init();
void msound_setUpMono();
void msound_setUpStereo();
void msound_mixMono();
void msound_mixStereo();
void msound_mixStereoASMR();
void msound_changeBuf();
void msound_setChannel(const Sound *sound, bool isRepeating);
void msound_setChannel3d(const Sound *sound, bool isRepeating, 
    int rightPhaseDelay, int leftPhaseDelay, int distAttenuation);
void msound_process3dSound(int *distance, int *rightPhaseDelay, int *leftPhaseDelay);
#endif