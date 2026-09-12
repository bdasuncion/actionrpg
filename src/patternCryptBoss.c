#include "GBASound.h"
#include <stdlib.h>

extern const Instrument instrument_Steel_Drums;
extern const Instrument instrument_Taiko;

const PatternData columncrypt_boss_0[] = {
	{&instrument_Steel_Drums,2639,63,0},{&instrument_Steel_Drums,2639,63,0},{&instrument_Steel_Drums,2639,63,0},{&instrument_Steel_Drums,2639,63,0},{&instrument_Steel_Drums,2796,63,0},{&instrument_Steel_Drums,2796,63,0},{&instrument_Steel_Drums,2796,63,0},{&instrument_Steel_Drums,2796,63,0},{&instrument_Steel_Drums,2639,63,0},
	{&instrument_Steel_Drums,2639,63,0},{&instrument_Steel_Drums,2639,63,0},{&instrument_Steel_Drums,2639,63,0},{&instrument_Steel_Drums,2796,63,0},{&instrument_Steel_Drums,2796,63,0},{&instrument_Steel_Drums,2796,63,0},{&instrument_Steel_Drums,2796,63,0},{&instrument_Steel_Drums,2639,63,0},
	{&instrument_Steel_Drums,2639,63,0},{&instrument_Steel_Drums,2639,63,0},{&instrument_Steel_Drums,2639,63,0},{&instrument_Steel_Drums,2796,63,0},{&instrument_Steel_Drums,2796,63,0},{&instrument_Steel_Drums,2796,63,0},{&instrument_Steel_Drums,2796,63,0},{&instrument_Steel_Drums,2639,63,0},
	{&instrument_Steel_Drums,2639,63,0},{&instrument_Steel_Drums,2639,63,0},{&instrument_Steel_Drums,2639,63,0},{&instrument_Steel_Drums,2796,63,0},{&instrument_Steel_Drums,2796,63,0},{&instrument_Steel_Drums,2796,63,0},{&instrument_Steel_Drums,2796,63,0},{&instrument_Steel_Drums,2639,63,0},
	{&instrument_Steel_Drums,2639,63,0},{&instrument_Steel_Drums,2639,63,0},{&instrument_Steel_Drums,2639,63,0},{&instrument_Steel_Drums,2796,63,0},{&instrument_Steel_Drums,2796,63,0},{&instrument_Steel_Drums,2796,63,0},{&instrument_Steel_Drums,2796,63,0},{&instrument_Steel_Drums,2639,63,0},
	{&instrument_Steel_Drums,2639,63,0},{&instrument_Steel_Drums,2639,63,0},{&instrument_Steel_Drums,2639,63,0},{&instrument_Steel_Drums,2796,63,0},{&instrument_Steel_Drums,2796,63,0},{&instrument_Steel_Drums,2796,63,0},{&instrument_Steel_Drums,2796,63,0},{&instrument_Steel_Drums,2639,63,0},
	{&instrument_Steel_Drums,2639,63,0},{&instrument_Steel_Drums,2639,63,0},{&instrument_Steel_Drums,2639,63,0},{&instrument_Steel_Drums,2796,63,0},{&instrument_Steel_Drums,2796,63,0},{&instrument_Steel_Drums,2796,63,0},{&instrument_Steel_Drums,2796,63,0},{&instrument_Steel_Drums,2639,63,0},
	{&instrument_Steel_Drums,2639,63,0},{&instrument_Steel_Drums,2639,63,0},{&instrument_Steel_Drums,2639,63,0},{&instrument_Steel_Drums,2796,63,0},{&instrument_Steel_Drums,2796,63,0},{&instrument_Steel_Drums,2796,63,0},{&instrument_Steel_Drums,2796,63,0},
};
const PatternData columncrypt_boss_1[] = {
	{&instrument_Taiko,3523,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{&instrument_Taiko,3728,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{&instrument_Taiko,3523,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{&instrument_Taiko,3728,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{&instrument_Taiko,3523,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{&instrument_Taiko,3728,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{&instrument_Taiko,3523,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{&instrument_Taiko,3728,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{&instrument_Taiko,3523,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{&instrument_Taiko,3728,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{&instrument_Taiko,3523,63,0},{NULL,0,63,0},{NULL,0,63,0},{&instrument_Taiko,3728,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{&instrument_Taiko,3523,63,0},{NULL,0,63,0},{&instrument_Taiko,3728,63,0},{NULL,0,63,0},{&instrument_Taiko,3523,63,0},{NULL,0,63,0},{&instrument_Taiko,3728,63,0},{NULL,0,63,0},
	{&instrument_Taiko,3523,63,0},{NULL,0,63,0},{&instrument_Taiko,3728,63,0},{NULL,0,63,0},{NULL,0,63,0},{&instrument_Taiko,3523,63,0},{NULL,0,63,0},
};
const PatternData columncrypt_boss_2[] = {
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
};
const PatternData columncrypt_boss_3[] = {
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
};

const PatternData *const crypt_bosscolumn[] = {columncrypt_boss_0,columncrypt_boss_1,columncrypt_boss_2,columncrypt_boss_3,};
const MusicTrack musiccrypt_boss = {crypt_bosscolumn,64};
