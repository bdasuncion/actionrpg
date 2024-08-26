#include <stdlib.h>
//#include <malloc.h>
#include "GBASound.h"
#include "GBADMA.h"
#include "GBATimer.h"
#include "UtilCommonValues.h"
#include "ManagerSound.h"

#define BUFFER_SIZE 176
#define SAMPLING_FREQUENCY 10512
#define SOUND_TIMER  63940
#define INDEX_FRACTION 12
//#define INDEX_FRACTION 8
#define RCPMIXFREQFRACTION 16
#define SOUNDEFFECT_NUM_CHANNEL 5
#define MUSIC_NUM_CHANNEL 4

#define UPDATE_ONFRAME_1  0
#define UPDATE_ONFRAME_2  7
#define UPDATE_MAXCOUNT  14
#define NATIVE_GBA_SAMPLERATE 32768 

const int PLAYBACKFREQ[ESoundQualityCount] = {
	10512, 13379, 18157, 21024, 26758, 31536
};

const int SOUNDBUFFERSIZE[ESoundQualityCount] = {
	176, 224, 304, 352, 448, 528
};

const s32 sound_zero[] = {0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0};

#define MAX_DISTANCE 16
const u32 distanceAttenuation[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };

const SampleSoundChannel freeSoundEffectChannel = { 0, 0, 0, true, false, true, true, false, false, 0, 0, 0, 0, 0, 0};
const MusicChannel freeMusicChannel = { NULL, 0, 0, 0, 0};
SoundBuffer soundBuffer;
SampleSoundChannel soundChannels[SOUNDEFFECT_NUM_CHANNEL];
MusicChannel musicChannels[MUSIC_NUM_CHANNEL] = {{0,0,0,0,0,0,0}, {0,0,0,0,0,0,0}, {0,0,0,0,0,0,0}, {0,0,0,0,0,0,0}};

void msound_init() {
    int i;
    for (i = 0; i < SOUNDEFFECT_NUM_CHANNEL; ++i) {
	    soundChannels[i] = freeSoundEffectChannel;
	}
	
	for (i = 0; i < MUSIC_NUM_CHANNEL; ++i) {
		musicChannels[i] = freeMusicChannel;
	}
}

void msound_setUpMono(int quality) {
	*REG_SOUNDCNT_H = DIRECT_SOUNDB_VOL(1) | DIRECT_SOUNDB_OUTR |
					DIRECT_SOUNDB_OUTL | DIRECT_SOUNDB_TIMER(0)|
					DIRECT_SOUNDB_RESET;
	*REG_SOUNDCNT_X = SOUND_ON;
					
	soundBuffer.currentBuffer = 0;
	soundBuffer.bufferA = malloc(SOUNDBUFFERSIZE[quality]*2*sizeof(s8));
	soundBuffer.soundQuality = quality;
	soundBuffer.rcpMixFrequency = (1<<(INDEX_FRACTION + RCPMIXFREQFRACTION))/PLAYBACKFREQ[quality];
	gbatimer_set(GBA_CLOCK_SPEED/PLAYBACKFREQ[quality]);
	dma2_soundmode(soundBuffer.bufferA);
}

void msound_setUpStereo(int quality) {
	*REG_SOUNDCNT_H = DIRECT_SOUNDA_VOL(1) | DIRECT_SOUNDB_VOL(1) | 
	                  //DIRECT_SOUNDA_VOL(0) | DIRECT_SOUNDB_VOL(0) | 
	                  DIRECT_SOUNDA_OUTR | DIRECT_SOUNDA_TIMER(0) |
					  DIRECT_SOUNDB_OUTL | DIRECT_SOUNDB_TIMER(0) |
					  DIRECT_SOUNDA_RESET | DIRECT_SOUNDB_RESET;
	*REG_SOUNDCNT_X = SOUND_ON;
					
	soundBuffer.currentBuffer = 0;
	soundBuffer.bufferA = malloc(SOUNDBUFFERSIZE[quality]*2*sizeof(s8));
	soundBuffer.bufferB = malloc(SOUNDBUFFERSIZE[quality]*2*sizeof(s8));
	soundBuffer.soundQuality = quality;
	soundBuffer.rcpMixFrequency = (1<<(INDEX_FRACTION + RCPMIXFREQFRACTION))/PLAYBACKFREQ[quality];
	gbatimer_set(GBA_CLOCK_SPEED/PLAYBACKFREQ[quality]);
	dma1_soundmode(soundBuffer.bufferA);
	dma2_soundmode(soundBuffer.bufferB);
} 

SampleSoundChannel* getOpenChannel() {
    int i;
    for (i = 0; i < SOUNDEFFECT_NUM_CHANNEL; ++i) {
	    if (soundChannels[i].isOpen) {
	        return &soundChannels[i];
		}
	}
	return NULL;
}

SampleSoundChannel* hasCurrentlySameSound(const void *data, const void *characterSource) {
	int i;
    for (i = 0; i < SOUNDEFFECT_NUM_CHANNEL; ++i) {
	    if (data == soundChannels[i].data) {
	        return &soundChannels[i];
		}
	}
	return NULL;
}

void msound_setChannel3d(const Sound *sound, bool isRepeating, 
    int rightPhaseDelay, int leftPhaseDelay, int distance) {
	int distAttenuation;
	SampleSoundChannel *channel = getOpenChannel();
	if (!channel) {
	    return;
	}
	if (hasCurrentlySameSound(sound->data, NULL)) {
		return;
	}
	if (sound->sampleSize == 8) {
		channel->size = sound->size;
	} else {
		channel->size = sound->size >> 1;
	}
	distAttenuation = distance*((distance < 0)*(-1) + (distance >= 0)*1);
	channel->aOutOfPhase = rightPhaseDelay;
	channel->bOutOfPhase = leftPhaseDelay;
	channel->isOpen = false;
	channel->repeating = isRepeating;
	channel->idxStep = (sound->frequency * soundBuffer.rcpMixFrequency) >> RCPMIXFREQFRACTION;
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

void msound_setChannelStereo(const Sound *sound, bool isRepeating, int distance) {
	int rightPhaseDelay, leftPhaseDelay, direction, convertedDist;
	
	direction = (distance < 0)*(-1) + (distance > 0)*(1);
	convertedDist = distance*direction;
	convertedDist = convertedDist >> 4;
	convertedDist *= direction;
	
	rightPhaseDelay = 6*(convertedDist < 0);
	leftPhaseDelay = 6*(convertedDist > 0);
	msound_setChannel3d(sound, isRepeating, rightPhaseDelay, leftPhaseDelay, convertedDist);
}

void msound_setChannel(const Sound *sound, bool isRepeating) {
	msound_setChannel3d(sound, isRepeating, 0, 0, 0);
}

void msound_setMusicChannel(int idx, const PatternData *pattern) {
	if (pattern->instrument != NULL) {
		musicChannels[idx].instrument = pattern->instrument;
		musicChannels[idx].idx = 0;
		musicChannels[idx].idxStep = (pattern->note * soundBuffer.rcpMixFrequency) >> RCPMIXFREQFRACTION;
		musicChannels[idx].length = pattern->instrument->length;
		musicChannels[idx].loop = false;
		musicChannels[idx].play = true;
	} /*else {
		musicChannels[idx].idxStep = 0;
		musicChannels[idx].length = 0;
		musicChannels[idx].loop = 0;
	}*/
}

void msound_setRow(Track *track) {
	int i;
	for (i = 0; i < 4; ++i) {
		msound_setMusicChannel(i, &track->musicTrack->columns[i][track->trackIndex]);
	}
}

void msound_updateTrack(Track *track) {
	if (track->musicTrack == NULL) {
		musicChannels[0].play = false;
		musicChannels[1].play = false;
		musicChannels[2].play = false;
		musicChannels[3].play = false;
		return;
	}
	if (track->framesPassed == UPDATE_ONFRAME_1) {
		msound_setRow(track);
		++track->trackIndex;
	} else if (track->framesPassed == UPDATE_ONFRAME_2) {
		msound_setRow(track);
		++track->trackIndex;
	}
	++track->framesPassed;
	if (track->framesPassed >= UPDATE_MAXCOUNT) {
		track->framesPassed = 0;
	}
	
	if (track->trackIndex >= track->musicTrack->length) {
		track->trackIndex = 0;
	}
}

ARM_IWRAM void msound_mixMono(int startingIdx, int bufSize) {
	int i, idxChannel;

	dma3_cpy32(&soundBuffer.bufferA[startingIdx], sound_zero, bufSize >> 2);
	//dma3_cpy32(&soundBuffer.bufferB[startingIdx], sound_zero, BUFFER_SIZE >> 2);
	
	for (idxChannel = 0; idxChannel < SOUNDEFFECT_NUM_CHANNEL; ++idxChannel) {
	    SampleSoundChannel *soundChannel = &soundChannels[idxChannel];
	    if (soundChannel->isOpen) {
		    continue;
		}
		
		for(i = 0; i < bufSize; ++i) {
		    if (!soundChannel->stopA) {
			    int idxData = soundChannel->currentIdxA >> INDEX_FRACTION;
			    soundBuffer.bufferA[startingIdx + i] += soundChannel->data[idxData];
				soundChannel->currentIdxA += soundChannel->idxStep;
			}
			    
			if ((soundChannel->currentIdxA >> INDEX_FRACTION) >= soundChannel->size) {
				soundChannel->currentIdxA = 0;
				if (!soundChannel->repeating) {
				    soundChannel->stopA = true;
				}
			}
			
			if (soundChannel->stopA) {
				    *soundChannel = freeSoundEffectChannel;
					break;
			}
		}
	}
}

void msound_mixSound() {
	int startingIdx = 0, bufSize = SOUNDBUFFERSIZE[soundBuffer.soundQuality], i;
	if (!soundBuffer.currentBuffer) {
		startingIdx = bufSize;
		soundBuffer.currentBuffer = 1;
	} else {
		soundBuffer.currentBuffer = 0;
	}
	
	dma3_cpy32(&soundBuffer.bufferA[startingIdx], sound_zero, bufSize >> 2);
	dma3_cpy32(&soundBuffer.bufferB[startingIdx], sound_zero, bufSize >> 2);
	
	msound_mixMono(startingIdx, bufSize);
	msound_mixMusic(startingIdx, bufSize);
}

#define ATTENUATION 2
void msound_mixStereo(int startingIdx, int bufSize) {
	int i, idxChannel;
	
	for (idxChannel = 0; idxChannel < SOUNDEFFECT_NUM_CHANNEL; ++idxChannel) {
	    SampleSoundChannel *soundChannel = &soundChannels[idxChannel];
	    if (soundChannel->isOpen) {
		    continue;
		}
		
		for(i = 0; i < bufSize; ++i) {
		    if (!soundChannel->stopA && i >= soundChannel->aOutOfPhase) {
			    int idxData = soundChannel->currentIdxA >> INDEX_FRACTION;
				if (soundChannel->attenuationA < MAX_DISTANCE) {
					int sound = 0;
					if (soundChannel->data[idxData] > 0) {
						sound = soundChannel->data[idxData] - (soundChannel->attenuationA*ATTENUATION);
						if (sound < 0){
							sound = 0;
						}
					} else if (soundChannel->data[idxData] < 0){
						sound = soundChannel->data[idxData] + (soundChannel->attenuationA*ATTENUATION);
						if (sound > 0){
							sound = 0;
						}
					}
					soundBuffer.bufferA[startingIdx + i] += sound;
					//soundBuffer.intermediaryBufferA[i] += sound;
				}
				soundChannel->currentIdxA += soundChannel->idxStep;
			}
			
			if (!soundChannel->stopB  && i >= soundChannel->bOutOfPhase) {
			    int idxData = soundChannel->currentIdxB >> INDEX_FRACTION;
				if (soundChannel->attenuationB < MAX_DISTANCE) {
					int sound = 0;
					if (soundChannel->data[idxData] > 0) {
						sound = soundChannel->data[idxData] - (soundChannel->attenuationB*ATTENUATION);
						if (sound < 0){
							sound = 0;
						}
					} else if (soundChannel->data[idxData] < 0){
						sound = soundChannel->data[idxData] + (soundChannel->attenuationB*ATTENUATION);
						if (sound > 0){
							sound = 0;
						}
					}
					soundBuffer.bufferB[startingIdx + i] += sound;
					//soundBuffer.intermediaryBufferB[startingIdx + i] += sound;
				}
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
				    *soundChannel = freeSoundEffectChannel;
					break;
			}
		}
		
		soundChannel->aOutOfPhase = 0;
		soundChannel->bOutOfPhase = 0;
	}
}

ARM_IWRAM void msound_mixMusic(int startingIdx, int bufSize) {
	int i, idxChannel;
	
	for (idxChannel = 0; idxChannel < MUSIC_NUM_CHANNEL; ++idxChannel) {
		MusicChannel *currentChannel = &musicChannels[idxChannel];
		if (!currentChannel->length || !currentChannel->play) {
			continue;
		}

		for(i = 0; i < bufSize; ++i) {
			int idxData = currentChannel->idx >> INDEX_FRACTION;
			/*if (idxData >= currentChannel->length) {
				//mprinter_printf("STOP %d\n", idxData);
				currentChannel->play = false;
				break;
			}*/
			if (!currentChannel->loop && (idxData >= currentChannel->length)) {
				idxData = currentChannel->instrument->loopStart;
				currentChannel->idx = currentChannel->instrument->loopStart << INDEX_FRACTION;
				currentChannel->loop = true;
			} else if (currentChannel->loop && (idxData >= 
				(currentChannel->instrument->loopStart + currentChannel->instrument->loopLength))) {
				idxData = currentChannel->instrument->loopStart;
				currentChannel->idx = currentChannel->instrument->loopStart << INDEX_FRACTION;
			}
			soundBuffer.bufferA[startingIdx + i] += currentChannel->instrument->data[idxData];
			//soundBuffer.bufferB[startingIdx + i] += currentChannel->instrument->data[idxData];
			//soundBuffer.intermediaryBufferA[i] += currentChannel->instrument->data[idxData];
			//soundBuffer.intermediaryBufferB[i] += currentChannel->instrument->data[idxData];
			currentChannel->idx += currentChannel->idxStep;
		}
	}
}

void msound_changeBuf() {
	if (!soundBuffer.currentBuffer) {
		dma2_soundmode(soundBuffer.bufferA);
		//dma1_soundmode(soundBuffer.bufferA);
	}
}

void msound_process3dSound(int *distance, int *rightPhaseDelay, int *leftPhaseDelay){
	*rightPhaseDelay = 6*(*distance < 0);
	*leftPhaseDelay = 6*(*distance > 0);
	*distance = *distance >> 4;
	*distance *= (*distance < 0)*(-1) + (*distance >= 0)*1;
}
