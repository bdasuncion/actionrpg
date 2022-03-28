//#include "stdio.h"

#ifndef	GBATypes
#define	GBATypes


typedef unsigned char 				u8;
typedef signed char 				s8;
typedef volatile unsigned char 		vu8;
typedef volatile signed char 		vs8;
typedef unsigned short 				u16;
typedef signed short				s16;
typedef volatile unsigned short 	vu16;
typedef volatile signed short		vs16;
typedef unsigned int				u32;
typedef signed int 					s32;
typedef volatile unsigned int		vu32;
typedef volatile signed int 		vs32;

#define ALIGN4 	__attribute__(( aligned(4) ))
#define ALIGN2 	__attribute__(( aligned(2) ))
#define EWRAM	__attribute__((section(".ewram")))
#define	IWRAM	__attribute__((section(".iwram"),long_call))
#define LONGCALL __attribute__((long_call))

#define BIT0 1
#define BIT1 (1<<1)
#define BIT2 (1<<2)
#define BIT3 (1<<3)
#define BIT4 (1<<4)
#define BIT5 (1<<5)
#define BIT6 (1<<6)
#define BIT7 (1<<7)
#define BIT8 (1<<8)
#define BIT9 (1<<9)
#define BITA (1<<10)
#define BITB (1<<11)
#define BITC (1<<12)
#define BITD (1<<13)
#define BITE (1<<14)
#define BITF (1<<15)
#define BIT16 (1<<16)
#define BIT17 (1<<17)
#define BIT18 (1<<18)
#define BIT19 (1<<19)
#define BIT20 (1<<20)
#define BIT21 (1<<21)
#define BIT22 (1<<22)
#define BIT23 (1<<23)
#define BIT24 (1<<24)
#define BIT25 (1<<25)
#define BIT26 (1<<26)
#define BIT27 (1<<27)
#define BIT28 (1<<28)
#define BIT29 (1<<29)
#define BIT30 (1<<30)
#define BIT31 (1<<31)
#define BIT(n) (1<<(n))

typedef enum ERegStatus
{
	EDisable,
	EEnable
}ERegStatus;

typedef void (*fnptr)(void);

#define DIVIDE_BY_2(x) (x >> 1)
#define DIVIDE_BY_4(x) (x >> 2)
#define DIVIDE_BY_8(x) (x >> 3)
#define DIVIDE_BY_16(x) (x >> 4)
#define DIVIDE_BY_32(x) (x >> 5)

#define GET_REMAINDER_8(x) (x&0x7)
#define GET_REMAINDER_16(x) (x&0xF)
#define GET_REMAINDER_64(x) (x&0x3F)

#define GBA_SCREEN_WIDTH 240
#define GBA_SCREEN_HEIGHT 160

#define SIZE_IN_WORDS(s) DIVIDE_BY_4(s)
#define SIZE_IN_HWORDS(s) DIVIDE_BY_2(s)
#define DIVIDE_BY_TILE_WIDTH(x) DIVIDE_BY_8(x)
#define DIVIDE_BY_TILE_HEIGHT(x) DIVIDE_BY_8(x)

#endif
