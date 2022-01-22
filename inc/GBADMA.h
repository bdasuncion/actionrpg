#include "GBATypes.h"
#include "GBASound.h"

#ifndef GBADMA
#define GBADMA

#define REG_DMA0SAD			*(vu32*)0x40000B0
#define REG_DMA0DAD			*(vu32*)0x40000B4
#define REG_DMA0CNT 		*(vu32*)0x40000B8
#define REG_DMA0CNT_N 		*(vu16*)0x40000B8
#define REG_DMA0CNT_C 		*(vu16*)0x40000BA


#define REG_DMA1SAD			*(vu32*)0x40000BC
#define REG_DMA1DAD			*(vu32*)0x40000C0
#define REG_DMA1CNT 		*(vu32*)0x40000C4
#define REG_DMA1CNT_N 		*(vu16*)0x40000C4
#define REG_DMA1CNT_C 		*(vu16*)0x40000C6


#define REG_DMA2SAD			*(vu32*)0x40000C8
#define REG_DMA2DAD			*(vu32*)0x40000CC
#define REG_DMA2CNT 		*(vu32*)0x40000D0
#define REG_DMA2CNT_N 		*(vu16*)0x40000D0
#define REG_DMA2CNT_C 		*(vu16*)0x40000D2


#define REG_DMA3SAD			*(vu32*)0x40000D4
#define REG_DMA3DAD			*(vu32*)0x40000D8
#define REG_DMA3CNT 		*(vu32*)0x40000DC
#define REG_DMA3CNT_N 		*(vu16*)0x40000DC
#define REG_DMA3CNT_C 		*(vu16*)0x40000DE



//32-BIT Register
#define DMA_DST_INC			0
#define	DMA_DST_DEC			(1<<21)
#define	DMA_DST_FIXED		(2<<21)
#define DMA_DST_RESET		(3<<21)
#define DMA_SRC_INC			0
#define	DMA_SRC_DEC			(1<<23)
#define	DMA_SRC_FIXED		(2<<23)
#define	DMA_REPEAT			BIT25
#define DMA_16				0
#define DMA_32				BIT26
#define	DMA_NOW				0
#define	DMA_AT_VBLANK		(1<<28)
#define	DMA_AT_HBLANK		(2<<28)
#define	DMA_SOUND_MODE		(3<<28)
#define DMA_IRQ				BIT30
#define	DMA_ON				BIT31


typedef struct DMA_REC
{
	const void *src;
	void *dest;
	u32	cnt;
}ALIGN4  DMA_REC;

typedef enum EDmaID
{
	EDma0,
	EDma1,
	EDma2,
	EDma3
}EDmaID;

#define dma_mem  ((volatile DMA_REC*)0x40000B0)

//general copy
static inline void dma3_cpy32(void* dst, const void* src, u32 count)
{
	dma_mem[3].cnt = 0;
	dma_mem[3].src = src;
	dma_mem[3].dest = dst;
	dma_mem[3].cnt = count|DMA_32|DMA_ON;
}

static inline void dma3_cpy32_srcFix(void* dst, const void* src, u32 count)
{
	dma_mem[3].cnt = 0;
	dma_mem[3].src = src;
	dma_mem[3].dest = dst;
	dma_mem[3].cnt = count|DMA_32|DMA_ON|DMA_SRC_FIXED;
}

static inline void dma3_cpy32_vblank(void* dst, const void* src, u32 count)
{
	dma_mem[3].cnt = 0;
	dma_mem[3].src = src;
	dma_mem[3].dest = dst;
	dma_mem[3].cnt = count|DMA_32|DMA_ON|DMA_AT_VBLANK;
}

static inline void dma3_cpy32_hblank(void* dst, const void* src, u32 count)
{
	dma_mem[3].cnt = 0;
	dma_mem[3].src = src;
	dma_mem[3].dest = dst;
	dma_mem[3].cnt = count|DMA_32|DMA_ON|DMA_AT_HBLANK;
}


static inline void dma3_cpy16(void* dst, const void* src, u32 count)
{
	dma_mem[3].cnt = 0;
	dma_mem[3].src = src;
	dma_mem[3].dest = dst;
	dma_mem[3].cnt = count|DMA_16|DMA_ON;
}

static inline void dma3_cpy16_Vblank(void* dst, const void* src, u32 count)
{
	dma_mem[3].cnt = 0;
	dma_mem[3].src = src;
	dma_mem[3].dest = dst;
	dma_mem[3].cnt = count|DMA_16|DMA_ON|DMA_AT_VBLANK;
}

static inline void dma3_cpy16_hblank(void* dst, const void* src, u32 count)
{
	dma_mem[3].cnt = 0;
	dma_mem[3].src = src;
	dma_mem[3].dest = dst;
	dma_mem[3].cnt = count|DMA_16|DMA_ON|DMA_AT_HBLANK;
}

static inline void dma_soundStop(EDmaID id)
{
	dma_mem[id].cnt = 0;
}

static inline void dma_soundmode(EDmaID id, const void* src, void *dest)
{
	dma_mem[id].cnt = 0;
	dma_mem[id].src = src;
	dma_mem[id].dest = dest;
	dma_mem[id].cnt = DMA_DST_FIXED|DMA_REPEAT|
			DMA_ON|DMA_32|DMA_SOUND_MODE;
}

static inline void dma1_soundstop() {
	dma_soundStop(EDma1);
}

static inline void dma1_soundmode(const void* src) {
	dma_soundmode(EDma1, src, REG_FIFO_A_L);
}

static inline void dma2_soundstop() {
	dma_soundStop(EDma2);
}

static inline void dma2_soundmode(const void* src) {
	dma_soundmode(EDma2, src, REG_FIFO_B_L);
}


#endif
