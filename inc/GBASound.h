#ifndef GBASound
#define GBASound

#include "GBATypes.h"
#include <stdbool.h>

#define REG_SOUND1CNT_L ((vu16*)0x04000060)
#define REG_SOUND1CNT_H ((vu16*)0x04000062)
#define REG_SOUND1CNT_X ((vu16*)0x04000064)
#define REG_SOUND2CNT_L ((vu16*)0x04000068)
#define REG_SOUND2CNT_H ((vu16*)0x0400006C)
#define REG_SOUND3CNT_L ((vu16*)0x04000070)
#define REG_SOUND3CNT_H ((vu16*)0x04000072)
#define REG_SOUND3CNT_X ((vu16*)0x04000074)
#define REG_SOUND4CNT_L ((vu16*)0x04000078)
#define REG_SOUND4CNT_H ((vu16*)0x0400007C)
#define REG_SOUNDCNT_L  ((vu16*)0x04000080)
#define REG_SOUNDCNT_H  ((vu16*)0x04000082)
#define REG_SOUNDCNT_X  ((vu16*)0x04000084)
#define REG_SOUNDBIAS   ((vu16*)0x04000088)
#define REG_WAVE_RAM0_L ((vu16*)0x04000090)
#define REG_WAVE_RAM0_H ((vu16*)0x04000092)
#define REG_WAVE_RAM1_L ((vu16*)0x04000094)
#define REG_WAVE_RAM1_H ((vu16*)0x04000096)
#define REG_WAVE_RAM2_L ((vu16*)0x04000098)
#define REG_WAVE_RAM2_H ((vu16*)0x0400009A)
#define REG_WAVE_RAM3_L ((vu16*)0x0400009C)
#define REG_WAVE_RAM3_H ((vu16*)0x0400009E)
#define REG_FIFO_A_L    ((vu16*)0x040000A0)
#define REG_FIFO_A_H    ((vu16*)0x040000A2)
#define REG_FIFO_B_L    ((vu16*)0x040000A4)
#define REG_FIFO_B_H    ((vu16*)0x040000A6)

#define DIRECT_SOUNDA_VOL(vol) vol << 2
#define DIRECT_SOUNDB_VOL(vol) vol << 3
#define DIRECT_SOUNDA_OUTR 1 << 8
#define DIRECT_SOUNDA_OUTL 1 << 9
#define DIRECT_SOUNDA_TIMER(timer) timer << 10
#define DIRECT_SOUNDA_RESET 1 << 11

#define DIRECT_SOUNDB_OUTR 1 << 12
#define DIRECT_SOUNDB_OUTL 1 << 13
#define DIRECT_SOUNDB_TIMER(timer) timer << 14
#define DIRECT_SOUNDB_RESET 1 << 15

#define SOUND_ON			1 << 7

typedef struct SampleSoundChannel
{
	u32 size;
	u32 aOutOfPhase:3;
	u32 bOutOfPhase:3;
	bool isOpen:1;
	bool repeating:1;
	bool stopA:1;
	bool stopB:1;
	u32 attenuationA:4;
	u32 attenuationB:4;
	u32 currentIdxA;//20:12
	u32 currentIdxB;//20:12
	u16 idxStep;
	//const void *position;
	const s8 *data;
}SampleSoundChannel;

typedef struct SoundBuffer {
	u32 currentBuffer;
	//s8	*buffer;
	s8	*bufferA;
	s8	*bufferB;
}ALIGN4 SoundBuffer;

typedef struct Sound {
	u32 size;
	u32 frequency:27;
	u32 sampleSize:5;
	const void *data;
}ALIGN4 Sound;

#endif
