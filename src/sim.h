#ifndef SIM_H
#define SIM_H

#include "main.h"

void *operand(Instruction *inst, u8 pos);
void exec(Instruction *inst);
void exec_all(const char *filename);

#endif
