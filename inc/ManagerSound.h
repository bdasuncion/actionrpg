#ifndef MANAGER_SOUND
#define MANAGER_SOUnD

#include "GBATypes.h"
#include "GBASound.h"
#include "GBADMA.h"
#include "GBAObject.h"

void msound_init();
void msound_setUpMono(int quality);
void msound_setUpStereo(int quality);
void msound_mixMono(int startingIdx, int bufSize);
void msound_mixStereo(int startingIdx, int bufSize);
void msound_mixMusic(int startingIdx, int bufSize);
void msound_changeBuf();
void msound_setChannel(const Sound *sound, bool isRepeating);
void msound_setChannel3d(const Sound *sound, bool isRepeating, 
    int rightPhaseDelay, int leftPhaseDelay, int distAttenuation);
void msound_process3dSound(int *distance, int *rightPhaseDelay, int *leftPhaseDelay);
void msound_setChannelStereo(const Sound *sound, bool isRepeating, int distance);
void msound_updateTrack(Track *track);
void msound_mixSound();
#endif