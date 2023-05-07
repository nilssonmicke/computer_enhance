#include "main.h"
#include "cycles.h"
#include "operand.h"

i32 effective_address_cycles(Instruction inst, i32 operator)
{
  i32 cycles = 0;
  switch(inst.op[operator].type)
  {
    case OPERAND_MEM16_D8:
    case OPERAND_MEM16_D16:
    case OPERAND_MEM8_D8:
    case OPERAND_MEM8_D16:
      cycles = 6;
    break;
    case OPERAND_MEM16_SI:
    case OPERAND_MEM16_DI:
    case OPERAND_MEM16_BX:
    //case OPERAND_MEM16_BP:
    case OPERAND_MEM8_SI:
    case OPERAND_MEM8_DI:
    case OPERAND_MEM8_BX:
    //case OPERAND_MEM8_BP:
      cycles = 5;
    break;
    case OPERAND_MEM16_BP_D8:
    case OPERAND_MEM8_BP_D8:
    case OPERAND_MEM8_BP_D16:
    case OPERAND_MEM16_BP_D16:
      if(inst.op[operator].data_lo == 0 && inst.op[operator].data_hi == 0)
        cycles = 5;
      else
        cycles = 9;
    break;
    case OPERAND_MEM16_BX_D8:
    case OPERAND_MEM16_BX_D16:
    case OPERAND_MEM8_BX_D8:
    case OPERAND_MEM8_BX_D16:
    case OPERAND_MEM16_SI_D8:
    case OPERAND_MEM16_SI_D16:
    case OPERAND_MEM8_SI_D8:
    case OPERAND_MEM8_SI_D16:
    case OPERAND_MEM16_DI_D8:
    case OPERAND_MEM16_DI_D16:
    case OPERAND_MEM8_DI_D8:
    case OPERAND_MEM8_DI_D16:
      cycles = 9;
    break;
    case OPERAND_MEM8_BP_DI:
    case OPERAND_MEM8_BX_SI:
    case OPERAND_MEM16_BP_DI:
    case OPERAND_MEM16_BX_SI:
      cycles = 7;
    break;
    case OPERAND_MEM8_BP_SI:
    case OPERAND_MEM8_BX_DI:
    case OPERAND_MEM16_BP_SI:
    case OPERAND_MEM16_BX_DI:
      cycles = 8;
    break;
    case OPERAND_MEM8_BP_DI_D8:
    case OPERAND_MEM8_BX_SI_D8:
    case OPERAND_MEM16_BP_DI_D8:
    case OPERAND_MEM16_BX_SI_D8:
    case OPERAND_MEM8_BP_DI_D16:
    case OPERAND_MEM8_BX_SI_D16:
    case OPERAND_MEM16_BP_DI_D16:
    case OPERAND_MEM16_BX_SI_D16:
      cycles = 11;
    break;    
    case OPERAND_MEM8_BP_SI_D8:
    case OPERAND_MEM8_BX_DI_D8:
    case OPERAND_MEM16_BP_SI_D8:
    case OPERAND_MEM16_BX_DI_D8:
    case OPERAND_MEM8_BP_SI_D16:
    case OPERAND_MEM8_BX_DI_D16:
    case OPERAND_MEM16_BP_SI_D16:
    case OPERAND_MEM16_BX_DI_D16:
      cycles = 12;
    break;      
  }
  return cycles;
}

i32 transfer_cycles(Instruction *inst, u8 pos, i32 multiplier)
{
  #ifdef MODE_8080
    if(isMem16(inst->op[pos].type))
      return 4 * multiplier;
    return 0;
  #else 
    i32 address = (i32)((i64)operand(inst, pos) - (i64)memory);
    if((address & 0x1) && isMem16(inst->op[pos].type))
      return 4 * multiplier;
    return 0;
  #endif
}


i32 count_cycles(Instruction inst)
{
  i32 cycles = 0;
  switch(inst.mnemonic)
  {
    case OPERATOR_MOV:
      if(isReg(inst.op[LEFT].type))
      {
        if(isImmed(inst.op[RIGHT].type))
          cycles = 4;
        else if(isReg(inst.op[RIGHT].type))
          cycles = 2;
        else if(isMem(inst.op[RIGHT].type))
          cycles = 8 + effective_address_cycles(inst, 1) + transfer_cycles(&inst, RIGHT, 1);
      }
      else if(isMem(inst.op[LEFT].type))
      {
        if(isReg(inst.op[RIGHT].type))
          cycles = 9 + effective_address_cycles(inst, 0) + transfer_cycles(&inst, LEFT, 1);
        else if(isImmed(inst.op[RIGHT].type))
          cycles = 10 + effective_address_cycles(inst, 0);
      }
    break;
    case OPERATOR_ADD:
      if(isReg(inst.op[LEFT].type))
      {
        if(isReg(inst.op[RIGHT].type))
          cycles = 3;
        else if(isImmed(inst.op[RIGHT].type))
          cycles = 4;
        else if(isMem(inst.op[RIGHT].type))
          cycles = 9 + effective_address_cycles(inst, 1) + transfer_cycles(&inst, RIGHT, 1);
      }
      else if(isMem(inst.op[LEFT].type))
      {
        if(isReg(inst.op[RIGHT].type))
          cycles = 16 + effective_address_cycles(inst, 0)+ transfer_cycles(&inst, LEFT, 2);
        else if(isImmed(inst.op[RIGHT].type))
          cycles = 17 + effective_address_cycles(inst, 0) + transfer_cycles(&inst, LEFT, 2);
      }

    break;
      
  }
  return cycles;
}
