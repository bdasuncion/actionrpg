#include "GBATypes.h"
#include "GBATimer.h"

inline void gbatimer_profileStart()
{
    REG_TM2D= 0;
    REG_TM3D= 0;
    REG_TM2CNT= 0;
	REG_TM3CNT= 0;
    REG_TM3CNT= TM_ON | TM_CASCADE;
    REG_TM2CNT= TM_ON;
}

inline u32 gbatimer_profileStop()
{
   REG_TM2CNT= 0;
   return (REG_TM3D<<16)|REG_TM2D;
}

//for modification
void gbatimer_set(u32 time) {
	REG_TM0D = TIME_MAX - time;
	REG_TM0CNT = TM_ON;
}