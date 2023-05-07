#ifndef PRINT_H
#define PRINT_H

#include "main.h"

void print(Instruction inst);
void print_all(const char * filename);
void print_flags_state();
void print_flags(u8 org_flags);

#endif
