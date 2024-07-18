#include "GBASound.h"
#include <stdlib.h>

extern const Instrument instrument_Bass_and_Lead;
extern const Instrument instrument_Square_Wave;
extern const Instrument instrument_Flute;
extern const Instrument instrument_Shamisen;
extern const Instrument instrument_Taiko;
extern const Instrument instrument_Acoustic_Bs;
extern const Instrument instrument_Melo_Tom_1;

const PatternData columnhorror_0[] = {
	{&instrument_Square_Wave,8363,63,0},{NULL,0,63,0},{NULL,0,63,0},{&instrument_Square_Wave,9943,63,0},{NULL,0,63,0},{NULL,0,63,0},{&instrument_Square_Wave,11852,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{&instrument_Square_Wave,11186,63,0},{NULL,0,63,0},{NULL,0,63,0},{&instrument_Square_Wave,8860,63,0},{NULL,0,63,0},{NULL,0,63,0},{&instrument_Square_Wave,10559,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{&instrument_Square_Wave,11852,63,0},{NULL,0,63,0},{NULL,0,63,0},{&instrument_Square_Wave,11186,63,0},{NULL,0,63,0},{NULL,0,63,0},{&instrument_Square_Wave,9395,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{&instrument_Square_Wave,11186,63,0},{NULL,0,63,0},{NULL,0,63,0},{&instrument_Square_Wave,12559,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{&instrument_Square_Wave,11852,63,0},{NULL,0,63,0},{NULL,0,63,0},{&instrument_Square_Wave,9943,63,0},{NULL,0,63,0},{NULL,0,63,0},{&instrument_Square_Wave,11852,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{&instrument_Square_Wave,13306,63,0},{NULL,0,63,0},{NULL,0,63,0},{&instrument_Square_Wave,12559,63,0},{NULL,0,63,0},{NULL,0,63,0},{&instrument_Square_Wave,10559,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{&instrument_Square_Wave,12559,63,0},{NULL,0,63,0},{NULL,0,63,0},{&instrument_Square_Wave,14092,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{&instrument_Square_Wave,13306,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
};
/*
const PatternData columnhorror_0[] = {
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
};*/
const PatternData columnhorror_1[] = {
	{NULL,0,63,0},{&instrument_Bass_and_Lead,8363,63,0},{NULL,0,63,0},{NULL,0,63,0},{&instrument_Bass_and_Lead,9943,63,0},{NULL,0,63,0},{NULL,0,63,0},{&instrument_Bass_and_Lead,11852,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{&instrument_Bass_and_Lead,11186,63,0},{NULL,0,63,0},{NULL,0,63,0},{&instrument_Bass_and_Lead,8860,63,0},{NULL,0,63,0},{NULL,0,63,0},{&instrument_Bass_and_Lead,10559,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{&instrument_Bass_and_Lead,11852,63,0},{NULL,0,63,0},{NULL,0,63,0},{&instrument_Bass_and_Lead,11186,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{&instrument_Bass_and_Lead,9395,63,0},{NULL,0,63,0},{NULL,0,63,0},{&instrument_Bass_and_Lead,11186,63,0},{NULL,0,63,0},{NULL,0,63,0},{&instrument_Bass_and_Lead,12559,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{&instrument_Bass_and_Lead,11852,63,0},{NULL,0,63,0},{NULL,0,63,0},{&instrument_Bass_and_Lead,9943,63,0},{NULL,0,63,0},{NULL,0,63,0},{&instrument_Bass_and_Lead,11852,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{&instrument_Bass_and_Lead,13306,63,0},{NULL,0,63,0},{NULL,0,63,0},{&instrument_Bass_and_Lead,12559,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{&instrument_Bass_and_Lead,10559,63,0},{NULL,0,63,0},{NULL,0,63,0},{&instrument_Bass_and_Lead,12559,63,0},{NULL,0,63,0},{NULL,0,63,0},{&instrument_Bass_and_Lead,14092,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{&instrument_Bass_and_Lead,13306,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
};
/*
const PatternData columnhorror_1[] = {
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
};*/
const PatternData columnhorror_2[] = {
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
};
const PatternData columnhorror_3[] = {
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
};
const PatternData *columnhorror[] = {columnhorror_0,columnhorror_1,columnhorror_2,columnhorror_3};
const MusicTrack musichorror = {columnhorror,64};

const PatternData columntest2_0[] = {
	{&instrument_Flute,9943,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{&instrument_Flute,11852,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{&instrument_Flute,11186,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{&instrument_Flute,13306,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{&instrument_Flute,11852,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{&instrument_Flute,11186,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
};
const PatternData columntest2_1[] = {
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
};
const PatternData columntest2_2[] = {
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
};
const PatternData columntest2_3[] = {
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
};

const PatternData *columntest2[] = {columntest2_0,columntest2_1,columntest2_2,columntest2_3,};
const MusicTrack musictest2 = {columntest2,64};

const PatternData columnkankandara_0[] = {
	{&instrument_Taiko,8363,63,0},{NULL,0,63,0},{&instrument_Taiko,9395,63,0},{NULL,0,63,0},{&instrument_Taiko,8363,63,0},{NULL,0,63,0},{&instrument_Taiko,9395,63,0},{NULL,0,63,0},{&instrument_Taiko,8363,63,0},
	{NULL,0,63,0},{&instrument_Taiko,9395,63,0},{NULL,0,63,0},{&instrument_Taiko,8363,63,0},{NULL,0,63,0},{&instrument_Taiko,9395,63,0},{NULL,0,63,0},{&instrument_Taiko,9943,63,0},
	{NULL,0,63,0},{&instrument_Taiko,11186,63,0},{NULL,0,63,0},{&instrument_Taiko,9943,63,0},{NULL,0,63,0},{&instrument_Taiko,11186,63,0},{NULL,0,63,0},{&instrument_Taiko,9943,63,0},
	{NULL,0,63,0},{&instrument_Taiko,11186,63,0},{NULL,0,63,0},{&instrument_Taiko,9943,63,0},{NULL,0,63,0},{&instrument_Taiko,11186,63,0},{NULL,0,63,0},{&instrument_Taiko,8363,63,0},
	{NULL,0,63,0},{&instrument_Taiko,9395,63,0},{NULL,0,63,0},{&instrument_Taiko,8363,63,0},{NULL,0,63,0},{&instrument_Taiko,9395,63,0},{NULL,0,63,0},{&instrument_Taiko,8363,63,0},
	{NULL,0,63,0},{&instrument_Taiko,9395,63,0},{NULL,0,63,0},{&instrument_Taiko,8363,63,0},{NULL,0,63,0},{&instrument_Taiko,9395,63,0},{NULL,0,63,0},{&instrument_Taiko,9943,63,0},
	{NULL,0,63,0},{&instrument_Taiko,11186,63,0},{NULL,0,63,0},{&instrument_Taiko,9943,63,0},{NULL,0,63,0},{&instrument_Taiko,11186,63,0},{NULL,0,63,0},{&instrument_Taiko,9943,63,0},
	{NULL,0,63,0},{&instrument_Taiko,11186,63,0},{NULL,0,63,0},{&instrument_Taiko,9943,63,0},{NULL,0,63,0},{&instrument_Taiko,11186,63,0},{NULL,0,63,0},{&instrument_Taiko,8363,63,0},
	{NULL,0,63,0},{&instrument_Taiko,8860,63,0},{NULL,0,63,0},{&instrument_Taiko,9395,63,0},{NULL,0,63,0},{&instrument_Taiko,8363,63,0},{NULL,0,63,0},{&instrument_Taiko,8860,63,0},
	{NULL,0,63,0},{&instrument_Taiko,9395,63,0},{NULL,0,63,0},{&instrument_Taiko,8363,63,0},{NULL,0,63,0},{&instrument_Taiko,8860,63,0},{NULL,0,63,0},{&instrument_Taiko,9395,63,0},
	{NULL,0,63,0},{&instrument_Taiko,8363,63,0},{NULL,0,63,0},{&instrument_Taiko,8860,63,0},{NULL,0,63,0},{&instrument_Taiko,9395,63,0},{NULL,0,63,0},{&instrument_Taiko,9943,63,0},
	{NULL,0,63,0},{&instrument_Taiko,10559,63,0},{NULL,0,63,0},{&instrument_Taiko,11186,63,0},{NULL,0,63,0},{&instrument_Taiko,9943,63,0},{NULL,0,63,0},{&instrument_Taiko,10559,63,0},
	{NULL,0,63,0},{&instrument_Taiko,11186,63,0},{NULL,0,63,0},{&instrument_Taiko,9943,63,0},{NULL,0,63,0},{&instrument_Taiko,10559,63,0},{NULL,0,63,0},{&instrument_Taiko,11186,63,0},
	{NULL,0,63,0},{&instrument_Taiko,9943,63,0},{NULL,0,63,0},{&instrument_Taiko,10559,63,0},{NULL,0,63,0},{&instrument_Taiko,11186,63,0},{NULL,0,63,0},{&instrument_Taiko,8363,63,0},
	{NULL,0,63,0},{&instrument_Taiko,8860,63,0},{NULL,0,63,0},{&instrument_Taiko,9395,63,0},{NULL,0,63,0},{&instrument_Taiko,8363,63,0},{NULL,0,63,0},{&instrument_Taiko,8860,63,0},
	{NULL,0,63,0},{&instrument_Taiko,9395,63,0},{NULL,0,63,0},{&instrument_Taiko,8363,63,0},{NULL,0,63,0},{&instrument_Taiko,8860,63,0},{NULL,0,63,0},
};
const PatternData columnkankandara_1[] = {
	{&instrument_Shamisen,4430,63,0},{NULL,0,63,0},{&instrument_Shamisen,4971,63,0},{NULL,0,63,0},{&instrument_Shamisen,4181,63,0},{NULL,0,63,0},{&instrument_Shamisen,4430,63,0},{NULL,0,63,0},{&instrument_Shamisen,4971,63,0},
	{NULL,0,63,0},{&instrument_Shamisen,4181,63,0},{NULL,0,63,0},{&instrument_Shamisen,4430,63,0},{NULL,0,63,0},{&instrument_Shamisen,4971,63,0},{NULL,0,63,0},{&instrument_Shamisen,4181,63,0},
	{NULL,0,63,0},{&instrument_Shamisen,4430,63,0},{NULL,0,63,0},{&instrument_Shamisen,4971,63,0},{NULL,0,63,0},{&instrument_Shamisen,4181,63,0},{NULL,0,63,0},{&instrument_Shamisen,4971,63,0},
	{NULL,0,63,0},{&instrument_Shamisen,5926,63,0},{NULL,0,63,0},{&instrument_Shamisen,6279,63,0},{NULL,0,63,0},{&instrument_Shamisen,5279,63,0},{NULL,0,63,0},{&instrument_Shamisen,4971,63,0},
	{NULL,0,63,0},{&instrument_Shamisen,5279,63,0},{NULL,0,63,0},{&instrument_Shamisen,6279,63,0},{NULL,0,63,0},{&instrument_Shamisen,5926,63,0},{NULL,0,63,0},{&instrument_Shamisen,4971,63,0},
	{NULL,0,63,0},{&instrument_Shamisen,5279,63,0},{NULL,0,63,0},{&instrument_Shamisen,6279,63,0},{NULL,0,63,0},{&instrument_Shamisen,5926,63,0},{NULL,0,63,0},{&instrument_Shamisen,4971,63,0},
	{NULL,0,63,0},{&instrument_Shamisen,5279,63,0},{NULL,0,63,0},{&instrument_Shamisen,6279,63,0},{NULL,0,63,0},{&instrument_Shamisen,5926,63,0},{NULL,0,63,0},{&instrument_Shamisen,5279,63,0},
	{NULL,0,63,0},{&instrument_Shamisen,5926,63,0},{NULL,0,63,0},{&instrument_Shamisen,6279,63,0},{NULL,0,63,0},{&instrument_Shamisen,4971,63,0},{NULL,0,63,0},{&instrument_Shamisen,4181,63,0},
	{NULL,0,63,0},{&instrument_Shamisen,4697,63,0},{NULL,0,63,0},{&instrument_Shamisen,4971,63,0},{NULL,0,63,0},{&instrument_Shamisen,4181,63,0},{NULL,0,63,0},{&instrument_Shamisen,4697,63,0},
	{NULL,0,63,0},{&instrument_Shamisen,4971,63,0},{NULL,0,63,0},{&instrument_Shamisen,5593,63,0},{NULL,0,63,0},{&instrument_Shamisen,5926,63,0},{NULL,0,63,0},{&instrument_Shamisen,6279,63,0},
	{NULL,0,63,0},{&instrument_Shamisen,5279,63,0},{NULL,0,63,0},{&instrument_Shamisen,5593,63,0},{NULL,0,63,0},{&instrument_Shamisen,4697,63,0},{NULL,0,63,0},{&instrument_Shamisen,4971,63,0},
	{NULL,0,63,0},{&instrument_Shamisen,7046,63,0},{NULL,0,63,0},{&instrument_Shamisen,6653,63,0},{NULL,0,63,0},{&instrument_Shamisen,5279,63,0},{NULL,0,63,0},{&instrument_Shamisen,6279,63,0},
	{NULL,0,63,0},{&instrument_Shamisen,5926,63,0},{NULL,0,63,0},{&instrument_Shamisen,4971,63,0},{NULL,0,63,0},{&instrument_Shamisen,5593,63,0},{NULL,0,63,0},{&instrument_Shamisen,5279,63,0},
	{NULL,0,63,0},{&instrument_Shamisen,4697,63,0},{NULL,0,63,0},{&instrument_Shamisen,4430,63,0},{NULL,0,63,0},{&instrument_Shamisen,4697,63,0},{NULL,0,63,0},{&instrument_Shamisen,4971,63,0},
	{NULL,0,63,0},{&instrument_Shamisen,4181,63,0},{NULL,0,63,0},{&instrument_Shamisen,5593,63,0},{NULL,0,63,0},{&instrument_Shamisen,5279,63,0},{NULL,0,63,0},{&instrument_Shamisen,5926,63,0},
	{NULL,0,63,0},{&instrument_Shamisen,6279,63,0},{NULL,0,63,0},{&instrument_Shamisen,4697,63,0},{NULL,0,63,0},{&instrument_Shamisen,4971,63,0},{NULL,0,63,0},
};
const PatternData columnkankandara_2[] = {
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
const PatternData columnkankandara_3[] = {
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
const PatternData *columnkankandara[] = {columnkankandara_0,columnkankandara_1,columnkankandara_2,columnkankandara_3};
const MusicTrack musickankandara = {columnkankandara,128};

const PatternData columnkankandara_end_0[] = {
	{&instrument_Melo_Tom_1,17720,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{&instrument_Melo_Tom_1,19886,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{&instrument_Melo_Tom_1,18839,63,0},
	{NULL,0,63,0},{&instrument_Melo_Tom_1,19886,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{&instrument_Melo_Tom_1,17720,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{&instrument_Melo_Tom_1,19886,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{&instrument_Melo_Tom_1,18839,63,0},{NULL,0,63,0},{&instrument_Melo_Tom_1,19886,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{&instrument_Melo_Tom_1,19886,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{&instrument_Melo_Tom_1,22372,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{&instrument_Melo_Tom_1,21056,63,0},{NULL,0,63,0},{&instrument_Melo_Tom_1,22372,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{&instrument_Melo_Tom_1,19886,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{&instrument_Melo_Tom_1,22372,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{&instrument_Melo_Tom_1,21056,63,0},{NULL,0,63,0},{&instrument_Melo_Tom_1,22372,63,0},{NULL,0,63,0},{&instrument_Melo_Tom_1,21056,63,0},{NULL,0,63,0},{&instrument_Melo_Tom_1,22372,63,0},
	{NULL,0,63,0},{&instrument_Melo_Tom_1,21056,63,0},{NULL,0,63,0},{&instrument_Melo_Tom_1,22372,63,0},{NULL,0,63,0},{&instrument_Melo_Tom_1,21056,63,0},{NULL,0,63,0},
};
const PatternData columnkankandara_end_1[] = {
	{&instrument_Acoustic_Bs,5279,63,0},{NULL,0,63,0},{&instrument_Acoustic_Bs,5279,63,0},{NULL,0,63,0},{&instrument_Acoustic_Bs,5279,63,0},{NULL,0,63,0},{&instrument_Acoustic_Bs,5279,63,0},{NULL,0,63,0},{&instrument_Acoustic_Bs,5279,63,0},
	{NULL,0,63,0},{&instrument_Acoustic_Bs,5279,63,0},{NULL,0,63,0},{&instrument_Acoustic_Bs,5279,63,0},{NULL,0,63,0},{&instrument_Acoustic_Bs,5279,63,0},{NULL,0,63,0},{&instrument_Acoustic_Bs,5926,63,0},
	{NULL,0,63,0},{&instrument_Acoustic_Bs,5926,63,0},{NULL,0,63,0},{&instrument_Acoustic_Bs,5926,63,0},{NULL,0,63,0},{&instrument_Acoustic_Bs,5926,63,0},{NULL,0,63,0},{&instrument_Acoustic_Bs,5926,63,0},
	{NULL,0,63,0},{&instrument_Acoustic_Bs,5926,63,0},{NULL,0,63,0},{&instrument_Acoustic_Bs,5926,63,0},{NULL,0,63,0},{&instrument_Acoustic_Bs,6653,63,0},{NULL,0,63,0},{&instrument_Acoustic_Bs,6653,63,0},
	{NULL,0,63,0},{&instrument_Acoustic_Bs,6653,63,0},{NULL,0,63,0},{&instrument_Acoustic_Bs,6653,63,0},{NULL,0,63,0},{&instrument_Acoustic_Bs,6653,63,0},{NULL,0,63,0},{&instrument_Acoustic_Bs,6653,63,0},
	{NULL,0,63,0},{&instrument_Acoustic_Bs,6653,63,0},{NULL,0,63,0},{&instrument_Acoustic_Bs,6653,63,0},{NULL,0,63,0},{&instrument_Acoustic_Bs,6653,63,0},{NULL,0,63,0},{&instrument_Acoustic_Bs,6653,63,0},
	{NULL,0,63,0},{&instrument_Acoustic_Bs,6653,63,0},{NULL,0,63,0},{&instrument_Acoustic_Bs,6653,63,0},{NULL,0,63,0},{&instrument_Acoustic_Bs,6653,63,0},{NULL,0,63,0},{&instrument_Acoustic_Bs,6653,63,0},
	{NULL,0,63,0},{&instrument_Acoustic_Bs,6653,63,0},{NULL,0,63,0},{&instrument_Acoustic_Bs,6653,63,0},{NULL,0,63,0},{&instrument_Acoustic_Bs,6653,63,0},{NULL,0,63,0},
};
const PatternData columnkankandara_end_2[] = {
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
};
const PatternData columnkankandara_end_3[] = {
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
	{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},{NULL,0,63,0},
};

const PatternData *columnkankandara_end[] = {columnkankandara_end_0,columnkankandara_end_1,columnkankandara_end_2,columnkankandara_end_3};
const MusicTrack musickankandara_end = {columnkankandara_end,64};

