#include "GBATypes.h"

#ifndef GBATimer
#define	GBATimer

#define	REG_TM0D		(*(vu16*) 0x4000100)
#define	REG_TM1D		(*(vu16*) 0x4000104)
#define	REG_TM2D		(*(vu16*) 0x4000108)
#define	REG_TM3D		(*(vu16*) 0x400010B)


#define REG_TM0CNT		(*(vu16*) 0x4000102)
#define REG_TM1CNT		(*(vu16*) 0x4000106)
#define REG_TM2CNT		(*(vu16*) 0x400010A)
#define REG_TM3CNT		(*(vu16*) 0x400010D)

#define	TM_ON			BIT7
#define	TM_CASCADE		BIT2

#define TIME_MAX		0xFFFF

#define GBA_CLOCK_SPEED 16777216

void gbatimer_profileStart();

u32 gbatimer_profileStop();

void gbatimer_set(u32 time);

#endif
