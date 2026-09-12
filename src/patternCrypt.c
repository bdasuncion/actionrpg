#include "GBASound.h"
#include <stdlib.h>

extern const Instrument instrument_bass_drum;
extern const Instrument instrument_Acoustic_Bs;

const PatternData columncrypt_0[] = {
	{&instrument_bass_drum,1319,63,0},{NULL,0,63,0},{NULL,0,63,0},{&instrument_bass_drum,1319,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{&instrument_bass_drum,2639,63,0},{NULL,0,63,0},{NULL,0,63,0},{&instrument_bass_drum,2639,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{&instrument_bass_drum,2639,63,0},{NULL,0,63,0},{NULL,0,63,0},{&instrument_bass_drum,2639,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{&instrument_bass_drum,2639,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{&instrument_bass_drum,2639,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{&instrument_bass_drum,2639,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{&instrument_bass_drum,2639,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{&instrument_bass_drum,5279,63,0},{NULL,0,63,0},{NULL,0,63,0},{&instrument_bass_drum,5279,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{&instrument_bass_drum,5279,63,0},{NULL,0,63,0},{NULL,0,63,0},{&instrument_bass_drum,5279,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{&instrument_bass_drum,5279,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{&instrument_bass_drum,5279,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{&instrument_bass_drum,5279,63,0},{NULL,0,63,0},{NULL,0,63,0},{&instrument_bass_drum,5279,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{&instrument_bass_drum,5279,63,0},{NULL,0,63,0},{NULL,0,63,0},{&instrument_bass_drum,5279,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{&instrument_bass_drum,5279,63,0},{NULL,0,63,0},{NULL,0,63,0},{&instrument_bass_drum,5279,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{&instrument_bass_drum,5279,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{&instrument_bass_drum,5279,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
};
const PatternData columncrypt_1[] = {
	{&instrument_Acoustic_Bs,7901,63,0},{&instrument_Acoustic_Bs,7901,63,0},{&instrument_Acoustic_Bs,7901,63,0},{&instrument_Acoustic_Bs,7901,63,0},{&instrument_Acoustic_Bs,7901,63,0},{&instrument_Acoustic_Bs,7901,63,0},{&instrument_Acoustic_Bs,7901,63,0},{&instrument_Acoustic_Bs,7901,63,0},{&instrument_Acoustic_Bs,7901,63,0},
	{&instrument_Acoustic_Bs,7901,63,0},{&instrument_Acoustic_Bs,7901,63,0},{&instrument_Acoustic_Bs,7901,63,0},{&instrument_Acoustic_Bs,7901,63,0},{&instrument_Acoustic_Bs,7901,63,0},{&instrument_Acoustic_Bs,7901,63,0},{&instrument_Acoustic_Bs,7901,63,0},{&instrument_Acoustic_Bs,7901,63,0},
	{&instrument_Acoustic_Bs,7901,63,0},{&instrument_Acoustic_Bs,7901,63,0},{&instrument_Acoustic_Bs,7901,63,0},{&instrument_Acoustic_Bs,9395,63,0},{&instrument_Acoustic_Bs,9395,63,0},{&instrument_Acoustic_Bs,9395,63,0},{&instrument_Acoustic_Bs,9395,63,0},{&instrument_Acoustic_Bs,9395,63,0},
	{&instrument_Acoustic_Bs,9395,63,0},{&instrument_Acoustic_Bs,9395,63,0},{&instrument_Acoustic_Bs,9395,63,0},{&instrument_Acoustic_Bs,9395,63,0},{&instrument_Acoustic_Bs,9395,63,0},{&instrument_Acoustic_Bs,9395,63,0},{&instrument_Acoustic_Bs,9395,63,0},{&instrument_Acoustic_Bs,9395,63,0},
	{&instrument_Acoustic_Bs,9395,63,0},{&instrument_Acoustic_Bs,9395,63,0},{&instrument_Acoustic_Bs,9395,63,0},{&instrument_Acoustic_Bs,9395,63,0},{&instrument_Acoustic_Bs,9395,63,0},{&instrument_Acoustic_Bs,9395,63,0},{&instrument_Acoustic_Bs,9395,63,0},{&instrument_Acoustic_Bs,9395,63,0},
	{&instrument_Acoustic_Bs,9395,63,0},{&instrument_Acoustic_Bs,9395,63,0},{&instrument_Acoustic_Bs,9395,63,0},{&instrument_Acoustic_Bs,7046,63,0},{&instrument_Acoustic_Bs,7046,63,0},{&instrument_Acoustic_Bs,7046,63,0},{&instrument_Acoustic_Bs,7046,63,0},{&instrument_Acoustic_Bs,7046,63,0},
	{&instrument_Acoustic_Bs,7046,63,0},{&instrument_Acoustic_Bs,7046,63,0},{&instrument_Acoustic_Bs,7046,63,0},{&instrument_Acoustic_Bs,7046,63,0},{&instrument_Acoustic_Bs,7046,63,0},{&instrument_Acoustic_Bs,7046,63,0},{&instrument_Acoustic_Bs,7046,63,0},{&instrument_Acoustic_Bs,7046,63,0},
	{&instrument_Acoustic_Bs,7046,63,0},{&instrument_Acoustic_Bs,7046,63,0},{&instrument_Acoustic_Bs,7046,63,0},{&instrument_Acoustic_Bs,7046,63,0},{&instrument_Acoustic_Bs,7046,63,0},{&instrument_Acoustic_Bs,7046,63,0},{&instrument_Acoustic_Bs,7046,63,0},{&instrument_Acoustic_Bs,6653,63,0},
	{&instrument_Acoustic_Bs,6653,63,0},{&instrument_Acoustic_Bs,6653,63,0},{&instrument_Acoustic_Bs,6653,63,0},{&instrument_Acoustic_Bs,6653,63,0},{&instrument_Acoustic_Bs,6653,63,0},{&instrument_Acoustic_Bs,6653,63,0},{&instrument_Acoustic_Bs,6653,63,0},{&instrument_Acoustic_Bs,6653,63,0},
	{&instrument_Acoustic_Bs,6653,63,0},{&instrument_Acoustic_Bs,6653,63,0},{&instrument_Acoustic_Bs,6653,63,0},{&instrument_Acoustic_Bs,6653,63,0},{&instrument_Acoustic_Bs,6653,63,0},{&instrument_Acoustic_Bs,6653,63,0},{&instrument_Acoustic_Bs,6653,63,0},{&instrument_Acoustic_Bs,6653,63,0},
	{&instrument_Acoustic_Bs,6653,63,0},{&instrument_Acoustic_Bs,6653,63,0},{&instrument_Acoustic_Bs,6653,63,0},{&instrument_Acoustic_Bs,6653,63,0},{&instrument_Acoustic_Bs,6653,63,0},{&instrument_Acoustic_Bs,7901,63,0},{&instrument_Acoustic_Bs,7901,63,0},{&instrument_Acoustic_Bs,7901,63,0},
	{&instrument_Acoustic_Bs,7901,63,0},{&instrument_Acoustic_Bs,7901,63,0},{&instrument_Acoustic_Bs,7901,63,0},{&instrument_Acoustic_Bs,7901,63,0},{&instrument_Acoustic_Bs,7901,63,0},{&instrument_Acoustic_Bs,7901,63,0},{&instrument_Acoustic_Bs,7901,63,0},{&instrument_Acoustic_Bs,7901,63,0},
	{&instrument_Acoustic_Bs,7901,63,0},{&instrument_Acoustic_Bs,7901,63,0},{&instrument_Acoustic_Bs,7901,63,0},{&instrument_Acoustic_Bs,7901,63,0},{&instrument_Acoustic_Bs,7901,63,0},{&instrument_Acoustic_Bs,7901,63,0},{&instrument_Acoustic_Bs,7901,63,0},{&instrument_Acoustic_Bs,7901,63,0},
	{&instrument_Acoustic_Bs,7901,63,0},{&instrument_Acoustic_Bs,7901,63,0},{&instrument_Acoustic_Bs,7901,63,0},{&instrument_Acoustic_Bs,7457,63,0},{&instrument_Acoustic_Bs,7457,63,0},{&instrument_Acoustic_Bs,7457,63,0},{&instrument_Acoustic_Bs,7457,63,0},{&instrument_Acoustic_Bs,7457,63,0},
	{&instrument_Acoustic_Bs,7457,63,0},{&instrument_Acoustic_Bs,7457,63,0},{&instrument_Acoustic_Bs,7457,63,0},{&instrument_Acoustic_Bs,7457,63,0},{&instrument_Acoustic_Bs,7457,63,0},{&instrument_Acoustic_Bs,7457,63,0},{&instrument_Acoustic_Bs,7457,63,0},{&instrument_Acoustic_Bs,7457,63,0},
	{&instrument_Acoustic_Bs,7457,63,0},{&instrument_Acoustic_Bs,7457,63,0},{&instrument_Acoustic_Bs,7457,63,0},{&instrument_Acoustic_Bs,7457,63,0},{&instrument_Acoustic_Bs,7457,63,0},{&instrument_Acoustic_Bs,7457,63,0},{&instrument_Acoustic_Bs,7457,63,0},
};
const PatternData columncrypt_2[] = {
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
};
const PatternData columncrypt_3[] = {
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
};

const PatternData *const cryptcolumn[] = {columncrypt_0,columncrypt_1,columncrypt_2,columncrypt_3,};
const MusicTrack musiccrypt = {cryptcolumn,128};
