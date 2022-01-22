#ifndef MANAGER_PRINTER
#define MANAGER_PRINTER

void mprinter_init();
void mprinter_clear();
void mprinter_string(char *c);
void mprinter_number(int num);
void mprinter_printf(const char *str, ...);
void mprinter_print();

#endif