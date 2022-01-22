#include <stdlib.h>
//#include <malloc.h>
#include "GBASound.h"
#include "GBADMA.h"
#include "GBATimer.h"
#include "UtilCommonValues.h"

#define BUFFER_SIZE 176
#define SAMPLING_FREQUENCY 10512
#define SOUND_TIMER  63940
//#define INDEX_FRACTION 12
#define INDEX_FRACTION 8
#define NUM_CHANNEL 5

const s32 sound_zero[] = {0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0};

#define MAX_DISTANCE 16
const u32 distanceAttenuation[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };

const SampleSoundChannel freeChannel = { 0, 0, 0, true, false, true, true, false, false, 0, 0, NULL, NULL };
SoundBuffer soundBuffer;
SampleSoundChannel soundChannels[NUM_CHANNEL];

//void msound_setChannel(const s8 *data, u32 datasize, 
//		u32 freq, u32 sampleSizeInBits);

void msound_init() {
    int i;
    for (i = 0; i < NUM_CHANNEL; ++i) {
	    soundChannels[i] = freeChannel;
	}
}

void msound_setChannel(const Sound *sound, bool isRepeating);

void msound_setUp() {
	*REG_SOUNDCNT_H = DIRECT_SOUNDA_VOL(1) | DIRECT_SOUNDB_VOL(1) | 
	                  //DIRECT_SOUNDA_VOL(0) | DIRECT_SOUNDB_VOL(0) | 
	                  DIRECT_SOUNDA_OUTR | DIRECT_SOUNDA_TIMER(0) |
					  DIRECT_SOUNDB_OUTL | DIRECT_SOUNDB_TIMER(0) |
					  DIRECT_SOUNDA_RESET | DIRECT_SOUNDB_RESET;
	*REG_SOUNDCNT_X = SOUND_ON;
					
	soundBuffer.currentBuffer = 0;
	//soundBuffer.buffer = malloc(BUFFER_SIZE*2*sizeof(s8));
	soundBuffer.bufferA = malloc(BUFFER_SIZE*2*sizeof(s8));
	soundBuffer.bufferB = malloc(BUFFER_SIZE*2*sizeof(s8));
	
	gbatimer_set(GBA_CLOCK_SPEED/SAMPLING_FREQUENCY);
	dma1_soundmode(soundBuffer.bufferA);
	dma2_soundmode(soundBuffer.bufferB);
} 

SampleSoundChannel* getOpenChannel() {
    int i;
    for (i = 0; i < NUM_CHANNEL; ++i) {
	    if (soundChannels[i].isOpen) {
	        return &soundChannels[i];
		}
	}
	return NULL;
}

void msound_setChannelTest(const Sound *sound, bool isRepeating, int rightPhaseDelay, int leftPhaseDelay) {
    
	SampleSoundChannel *channel = getOpenChannel();
	if (!channel) {
	    return;
	}
	if (sound->sampleSize == 8) {
		channel->size = sound->size;
	} else {
		channel->size = sound->size >> 1;
	}
	channel->aOutOfPhase = rightPhaseDelay;
	channel->bOutOfPhase = leftPhaseDelay;
	channel->isOpen = false;
	channel->repeating = isRepeating;
	channel->idxStep = (sound->frequency << INDEX_FRACTION)/SAMPLING_FREQUENCY;
	//channel->currentIdx = 0;
	channel->currentIdxA = 0;
	channel->currentIdxB = 0;
	channel->stopA = false;
	channel->stopB = false;
	channel->attenuationA = (rightPhaseDelay > 0);
	channel->attenuationB = (leftPhaseDelay > 0);
	channel->data = sound->data;
}

void msound_setChannel3d(const Sound *sound, bool isRepeating, 
    int rightPhaseDelay, int leftPhaseDelay, int distAttenuation) {
    SampleSoundChannel *channel = getOpenChannel();
	if (!channel) {
	    return;
	}
	if (sound->sampleSize == 8) {
		channel->size = sound->size;
	} else {
		channel->size = sound->size >> 1;
	}
	channel->aOutOfPhase = rightPhaseDelay;
	channel->bOutOfPhase = leftPhaseDelay;
	channel->isOpen = false;
	channel->repeating = isRepeating;
	channel->idxStep = (sound->frequency << INDEX_FRACTION)/SAMPLING_FREQUENCY;
	//channel->currentIdx = 0;
	channel->currentIdxA = 0;
	channel->currentIdxB = 0;
	channel->stopA = false;
	channel->stopB = false;
	channel->attenuationA = distAttenuation + (rightPhaseDelay > 0)*1;
	channel->attenuationB = distAttenuation + (leftPhaseDelay > 0)*1;
	//channel->attenuationA = distAttenuation;
	//channel->attenuationB = distAttenuation;
	channel->data = sound->data;
}

void msound_setChannel(const Sound *sound, bool isRepeating) {
	msound_setChannelTest(sound, isRepeating, 0, 0);
}

void msound_mix() {
	//int zero = 0;
	int startingIdx = 0, i, idxChannel;
	if (!soundBuffer.currentBuffer) {
		startingIdx = BUFFER_SIZE;
		soundBuffer.currentBuffer = 1;
	} else {
		soundBuffer.currentBuffer = 0;
	}

	//dma3_cpy32_srcFix(&soundBuffer.buffer[startingIdx], sound_zero, BUFFER_SIZE >> 2);
	dma3_cpy32(&soundBuffer.bufferA[startingIdx], sound_zero, BUFFER_SIZE >> 2);
	dma3_cpy32(&soundBuffer.bufferB[startingIdx], sound_zero, BUFFER_SIZE >> 2);
	
	for (idxChannel = 0; idxChannel < NUM_CHANNEL; ++idxChannel) {
	    SampleSoundChannel *soundChannel = &soundChannels[idxChannel];
	    if (soundChannel->isOpen) {
		    continue;
		}
		
		for(i = 0; i < BUFFER_SIZE; ++i) {
		    if (!soundChannel->stopA && i >= soundChannel->aOutOfPhase) {
			    int idxData = soundChannel->currentIdxA >> INDEX_FRACTION;
				if (soundChannel->attenuationA < MAX_DISTANCE) {
			        soundBuffer.bufferA[startingIdx + i] += (soundChannel->data[idxData] >> 
					    distanceAttenuation[soundChannel->attenuationA]);
				}
				/*if (soundChannel->attenuationA < MAX_DISTANCE) {
					soundBuffer.bufferA[startingIdx + i] += (soundChannel->data[idxData]) - 
					    ((soundChannel->data[idxData] >> 4)*soundChannel->attenuationA);
				}*/
				//soundBuffer.bufferA[startingIdx + i] += (soundChannel->data[idxData]);
				//soundBuffer.bufferA[startingIdx + i] -= (soundChannel->data[idxData] >> 4)*(soundChannel->attenuationA);
				soundChannel->currentIdxA += soundChannel->idxStep;
			}
			
			if (!soundChannel->stopB  && i >= soundChannel->bOutOfPhase) {
			    int idxData = soundChannel->currentIdxB >> INDEX_FRACTION;
				if (soundChannel->attenuationB < MAX_DISTANCE) {
				    soundBuffer.bufferB[startingIdx + i] += (soundChannel->data[idxData] >> 
					distanceAttenuation[soundChannel->attenuationB]);
				}
				/*if (soundChannel->attenuationB < MAX_DISTANCE) {
					soundBuffer.bufferB[startingIdx + i] += (soundChannel->data[idxData]) - 
					    ((soundChannel->data[idxData] >> 4)*soundChannel->attenuationB);
				}*/
				//soundBuffer.bufferB[startingIdx + i] += (soundChannel->data[idxData]);
				//soundBuffer.bufferB[startingIdx + i] -= (soundChannel->data[idxData] >> 4)*(soundChannel->attenuationB);
				soundChannel->currentIdxB += soundChannel->idxStep;
			}
			    
			if ((soundChannel->currentIdxA >> INDEX_FRACTION) >= soundChannel->size) {
				soundChannel->currentIdxA = 0;
				if (!soundChannel->repeating) {
				    soundChannel->stopA = true;
				}
			}
			
			if ((soundChannel->currentIdxB >> INDEX_FRACTION) >= soundChannel->size) {
				soundChannel->currentIdxB = 0;
				if (!soundChannel->repeating) {
				    soundChannel->stopB = true;
				}
			}
			
			if (soundChannel->stopA && soundChannel->stopB) {
				    *soundChannel = freeChannel;
					break;
			}
		}
		
		soundChannel->aOutOfPhase = 0;
		soundChannel->bOutOfPhase = 0;
	}
}

void msound_changeBuf() {
	if (!soundBuffer.currentBuffer) {
		dma2_soundmode(soundBuffer.bufferA);
		dma1_soundmode(soundBuffer.bufferB);
	}
}

void msound_process3dSound(int *distance, int *rightPhaseDelay, int *leftPhaseDelay){
	*rightPhaseDelay = 6*(*distance < 0);
	*leftPhaseDelay = 6*(*distance > 0);
	*distance = *distance >> 4;
	*distance *= (*distance < 0)*(-1) + (*distance >= 0)*1;
}
