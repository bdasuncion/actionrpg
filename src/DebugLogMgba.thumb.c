#include "GBAObject.h"

void mgba_log(const char* write, int size) {
	volatile u16 *debug_enable_register = (u16*)(0x4FFF780);
	*debug_enable_register = 0xC0DE;
	
	int max_characters_per_line = 256;
	int i;
	
	u8 *debug_string_register = (char*)(0x4FFF600);
	for (i = 0; i < size; ++i) {
		debug_string_register[i] = write[i];
	}
	volatile u16 *debug_flags_register = (u16*)(0x4FFF700);
    *debug_flags_register = 2 | 0x100;

}