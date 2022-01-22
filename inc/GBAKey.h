#include "GBATypes.h"
#include  "GBAObject.h"

#ifndef GBAKey
#define GBAKey

#define REG_KEYIN 		*((vu16*)0x4000130)
#define REG_KEYCNT     	((vu16*)0x4000132)

#define KEY_A			BIT0
#define KEY_B			BIT1
#define KEY_START		BIT2
#define	KEY_SELECT		BIT3
#define KEY_RIGHT		BIT4
#define KEY_LEFT		BIT5
#define KEY_UP			BIT6
#define KEY_Pressed		BIT7
#define KEY_L			BIT8
#define KEY_R			BIT9

static inline int isKeyPressed(int keyid) {
	return (((~REG_KEYIN) & keyid) != 0);
}

static inline int isAPressed() { return isKeyPressed(KEY_A); }

static inline int isBPressed() { return isKeyPressed(KEY_B); }

static inline int isStartPressed() { return isKeyPressed(KEY_START); }

static inline int isSelectPressed() { return isKeyPressed(KEY_SELECT); }

static inline int isUpPressed() { return isKeyPressed(KEY_UP); }

static inline int isPressedPressed() { return isKeyPressed(KEY_Pressed); }

static inline int isLeftPressed() { return isKeyPressed(KEY_LEFT); }

static inline int isRightPressed() { return isKeyPressed(KEY_RIGHT); }

static inline int isLPressed() { return isKeyPressed(KEY_L); }

static inline int isRPressed() { return isKeyPressed(KEY_R); }

extern EDirections dir_from_key[16];

#define KEYPRESS_DIRECTION dir_from_key[(~REG_KEYIN>>4)&0xF]
#endif
