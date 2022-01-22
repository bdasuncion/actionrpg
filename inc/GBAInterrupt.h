#include "GBATypes.h"

#ifndef GBAInterrupt
#define GBAInterrupt

#define REG_IE 			((vu16*)0x4000200)
#define REG_IF 			((vu16*)0x4000202)
#define REG_IME 		((vu16*)0x4000208)

#define REG_IFBIOS 		((vu16*)0x3007FF8)

#define IRQ_VBLANK		BIT0
#define IRQ_HBLANK		BIT1
#define IRQ_VCOUNT		BIT2

#define INTERRUPT_REG 	((u32*)0x03007FFC)

#define REG_ISR_MAIN *(fnptr*)(0x03007FFC)

static inline void gbaint_ctrl(ERegStatus isEnabled)
{
	*REG_IME = isEnabled;
}

static inline void gbaint_setRequestHandler(void (*intHndlr)(void))
{
	*INTERRUPT_REG = intHndlr;
}

typedef struct InterruptReceiver
{
	u16 irqVBlank:1;
	u16 irqHBlank:1;
	u16 irqVCount:1;
	u16 irqTimer0:1;
	u16 irqTimer1:1;
	u16 irqTimer2:1;
	u16 irqTimer3:1;
	u16 irqComm:1;
	u16 irqDMA0:1;
	u16 irqDMA1:1;
	u16 irqDMA2:1;
	u16 irqDMA3:1;
	u16 irqKeyPad:1;
	u16 irqGamePak:1;
}InterruptReceiver;

#define STRUCT_REG_IE		((InterruptReceiver*)REG_IE)
#define STRUCT_REG_IF		((InterruptReceiver*)REG_IF)
#define STRUCT_REG_IFBIOs	((InterruptReceiver*)REG_IFBIOS)

static inline void gbaint_requestVBlank(ERegStatus s)
{
	STRUCT_REG_IE->irqVBlank = s;
}

static inline void gbaint_requestVBlankAck()
{
	STRUCT_REG_IF->irqVBlank = 1;
	STRUCT_REG_IFBIOs->irqVBlank = 1;
}

#endif