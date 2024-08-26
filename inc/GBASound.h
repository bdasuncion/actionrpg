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
	u32 attenuationA:8;
	u32 attenuationB:8;
	u32 dummy:6;
	u32 currentIdxA;//20:12
	u32 currentIdxB;//20:12
	u16 idxStep;
	//const void *position;
	const s8 *data;
	const void *source;
	//const s16 *data;
}SampleSoundChannel;

typedef enum SoundQuality {
	ELowQ,
	ELowMidQ,
	EMidQ,
	EMidHighQ,
	EHighQ,
	EBestQ,
	ESoundQualityCount
} SoundQuality;

typedef struct SoundBuffer {
	u32 currentBuffer;
	SoundQuality soundQuality;
	u32 rcpMixFrequency;//For conversion from division to fixed point multiplication
	//s16	*intermediaryBufferA;
	//s16	*intermediaryBufferB;
	s8	*bufferA;
	s8	*bufferB;
}ALIGN4 SoundBuffer;

typedef struct Sound {
	u32 size;
	u32 frequency:27;
	u32 sampleSize:5;
	const void *data;
}ALIGN4 Sound;

typedef struct Instrument {
	s8 *data;
	u32 length:20;
	u32 loopStart:20;
	u32 loopLength:20;
	u32 dummy:4;
}ALIGN4 Instrument;

typedef struct PatternData {
	const Instrument *instrument;
	u32 note:16;
	u32 volume:6;
	u32 dummy:10;
}ALIGN4 PatternData;

typedef struct MusicTrack {
	//PatternData *columns[4];
	const PatternData **columns;
	int length;
}ALIGN4 MusicTrack;

typedef struct Track {
	const MusicTrack *musicTrack;
	u32 trackIndex;
	u32 framesPassed;
}ALIGN4 Track;

typedef struct MusicChannel {
	const Instrument *instrument; // pointer to the instrument
	u32 idx; // current position in the data (20.12 fixed-point)
	u32 idxStep; // increment (20.12 fixed-point)
	u32 volume; // volume (0-64, sort of 1.6 fixed-point)
	u32 length; // length of the whole sound (20.12 fixed-point)
	bool loop:1;
	bool play:1; 
} MusicChannel;

#endif
