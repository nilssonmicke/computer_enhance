#include "sim.h"
#include "decoder.h"
#include "operand.h"
#include "operator.h"
#include "print.h"
#include "cycles.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

u8 * prev_ip = NULL;

void print_ip()
{
  printf("IP:0x%hX->0x%hX ", (u16)(prev_ip - memory), (u16)(ip - memory));
}

void *operand(Instruction *inst, u8 pos)
{
  switch (inst->op[pos].type)
  {
  case OPERAND_NONE:
    return NULL;
  case OPERAND_REG_AL:
    return &registers.al;
  case OPERAND_REG_CL:
    return &registers.cl;
  case OPERAND_REG_DL:
    return &registers.dl;
  case OPERAND_REG_BL:
    return &registers.bl;
  case OPERAND_REG_AH:
    return &registers.ah;
  case OPERAND_REG_CH:
    return &registers.ch;
  case OPERAND_REG_DH:
    return &registers.dh;
  case OPERAND_REG_BH:
    return &registers.bh;
  case OPERAND_REG_AX:
    return &registers.ax;
  case OPERAND_REG_CX:
    return &registers.cx;
  case OPERAND_REG_DX:
    return &registers.dx;
  case OPERAND_REG_BX:
    return &registers.bx;
  case OPERAND_REG_SP:
    return &registers.sp;
  case OPERAND_REG_BP:
    return &registers.bp;
  case OPERAND_REG_SI:
    return &registers.si;
  case OPERAND_REG_DI:
    return &registers.di;
  case OPERAND_IMMED_8:
  case OPERAND_IMMED_16:
    return &inst->op[pos].data_lo;
  case OPERAND_SEG_SS:
    return &registers.ss;
  case OPERAND_SEG_ES:
    return &registers.es;
  case OPERAND_SEG_CS:
    return &registers.cs;
  case OPERAND_SEG_DS:
    return &registers.ds;
  case OPERAND_JMP_8:
    return &inst->op[pos].data_lo;
  case OPERAND_MEM16_SI:
    return memory + registers.si;
  case OPERAND_MEM16_DI:
    return memory + registers.di;  
  case OPERAND_MEM16_BX:
    return memory + registers.bx;
  case OPERAND_MEM16_D16:
    return memory + (((u16)inst->op[pos].data_hi) << 8 | ((u16)inst->op[pos].data_lo));
  case OPERAND_MEM8_BX_D8:
  case OPERAND_MEM16_BX_D8:
    return memory + (registers.bx + (u16)inst->op[pos].data_lo);
  case OPERAND_MEM8_BX_D16:
  case OPERAND_MEM16_BX_D16:
    return memory + registers.bx + (((u16)inst->op[pos].data_hi) << 8 | ((u16)inst->op[pos].data_lo));
  case OPERAND_MEM16_BP_SI:
    return  memory + (registers.bp + registers.si);
  case OPERAND_MEM8_BP_D8:
  case OPERAND_MEM16_BP_D8:
    return  memory + (registers.bp + (u16)inst->op[pos].data_lo);
  case OPERAND_MEM8_DI_D16:
  case OPERAND_MEM16_DI_D16:
    return memory + registers.di + (((u16)inst->op[pos].data_hi) << 8 | ((u16)inst->op[pos].data_lo)); 
  case OPERAND_MEM8_BP_D16:
  case OPERAND_MEM16_BP_D16:
    return memory + registers.bp + (((u16)inst->op[pos].data_hi) << 8 | ((u16)inst->op[pos].data_lo));
  case OPERAND_MEM8_SI_D16:   
  case OPERAND_MEM16_SI_D16:
    return memory + registers.si + (((u16)inst->op[pos].data_hi) << 8 | ((u16)inst->op[pos].data_lo));
  case OPERAND_MEM8_BP_DI: 
  case OPERAND_MEM16_BP_DI:
    return memory + registers.bp + registers.di; 
  case OPERAND_MEM8_BX_SI:
  case OPERAND_MEM16_BX_SI:
    return memory + registers.bx + registers.si;
  case OPERAND_MEM8_BX_DI:
  case OPERAND_MEM16_BX_DI:
    return memory + registers.bx + registers.di;
  case OPERAND_MEM8_BP_DI_D16:
  case OPERAND_MEM16_BP_DI_D16:
    return memory + registers.bp + registers.di + (((u16)inst->op[pos].data_hi) << 8 | ((u16)inst->op[pos].data_lo));
  case OPERAND_MEM8_BX_SI_D16:
  case OPERAND_MEM16_BX_SI_D16:
    return memory + registers.bx + registers.si + (((u16)inst->op[pos].data_hi) << 8 | ((u16)inst->op[pos].data_lo));
  case OPERAND_MEM8_BP_SI_D16:
  case OPERAND_MEM16_BP_SI_D16:
    return memory + registers.bp + registers.si + (((u16)inst->op[pos].data_hi) << 8 | ((u16)inst->op[pos].data_lo));
  case OPERAND_MEM8_BX_DI_D16:
  case OPERAND_MEM16_BX_DI_D16:
    return memory + registers.bx + registers.di + (((u16)inst->op[pos].data_hi) << 8 | ((u16)inst->op[pos].data_lo));
  
    
  }
  printf("Operand unk = '0x%X'\n", inst->op[pos].type);
  exit(-1);
  return NULL;
}

void exec8(Instruction *inst)
{
  u8 org_flags = flags;
  i8 * dest = (i8*)operand(inst, LEFT);
  i8 * src = (i8*)operand(inst, RIGHT);

  i8 org_dest = *dest;
  i8 org_src = 0;

  if(src != NULL)
    org_src = *src;

  switch (inst->mnemonic)
  {
    case OPERATOR_MOV:
    {
      if(isMem(inst->op[LEFT].type))
        printf("MEM(0x%hX)->", org_dest);
      else
        printf("%s(0x%hX)->", OPERAND_REG[inst->op[LEFT].type], org_dest);
      memcpy(dest, src, 1);
      printf("(0x%hX) ", *dest);
      print_ip();
      printf("\n");
      break;
    }
    case OPERATOR_ADD:
    {
      printf("%s(0x%hX)->", OPERAND_REG[inst->op[LEFT].type], org_dest);
      *dest += *src; 
      printf("(0x%hX) ", *dest);

      setFlag(*dest == 0, FLAG_ZERO);
      setFlag(*dest & 0x80, FLAG_SIGN);
      setFlag(
        (org_dest > 0 && org_src > 0 && *dest < 0) ||
        (org_dest < 0 && org_src < 0 && *dest > 0), 
        FLAG_OVERFLOW
      );
      setFlag((u32)org_dest + (u32)org_src > 0xFF, FLAG_CARRY);
      setFlag(getParity(*dest), FLAG_PARITY);
      setFlag((u32)(org_dest & 0xF) + (u32)(org_src & 0xF) > 0xF, FLAG_AUXILIARY_CARRY);
      print_ip();     
      print_flags(org_flags);
      printf("\n");

      break; 
    }
    case OPERATOR_SUB:
    {
      printf("%s(0x%hX)->", OPERAND_REG[inst->op[LEFT].type], org_dest);
      *dest -= *src; 
      printf("(0x%hX) ", *dest);
    
      setFlag(*dest == 0, FLAG_ZERO);
      setFlag(*dest & 0x80, FLAG_SIGN);
      setFlag(
        (org_dest < 0 && org_src > 0 && *dest > 0) ||
        (org_dest > 0 && org_src < 0 && *dest < 0), 
        FLAG_OVERFLOW
      );
      setFlag((u32)org_dest - (u32)org_src > 0xFF, FLAG_CARRY);
      setFlag(getParity(*dest), FLAG_PARITY);
      setFlag((u32)(org_dest & 0xF) - (u32)(org_src & 0xF) > 0xF, FLAG_AUXILIARY_CARRY);
      print_ip();
      print_flags(org_flags);
      printf("\n");

      break; 
    }
    case OPERATOR_CMP:
    {
      i8 tmp = *dest - *src;
      
      setFlag(tmp == 0, FLAG_ZERO);
      setFlag(tmp & 0x80, FLAG_SIGN);
      setFlag(
        (org_dest < 0 && org_src > 0 && tmp > 0) ||
        (org_dest > 0 && org_src < 0 && tmp < 0), 
        FLAG_OVERFLOW
      );
      setFlag((u32)org_dest - (u32)org_src > 0xFF, FLAG_CARRY);
      setFlag(getParity(tmp), FLAG_PARITY);
      setFlag((u32)(org_dest & 0xF) - (u32)(org_src & 0xF) > 0xF, FLAG_AUXILIARY_CARRY);
      print_ip();
      print_flags(org_flags);
      printf("\n");
      break; 
    }
    case OPERATOR_JNE:
    {
      if(!(flags & FLAG_ZERO))
        ip += org_dest;
      print_ip();
      printf("\n");
      break;
    }
    case OPERATOR_JE:
    {
      if(flags & FLAG_ZERO)
        ip += org_dest;
      print_ip();
      printf("\n");
      break;
    }
    case OPERATOR_JP:
    {
      if(flags & FLAG_PARITY)
        ip += org_dest;
      print_ip();
      printf("\n");
      break;
    }
    case OPERATOR_JB:
    {
      if(flags & FLAG_CARRY)
        ip += org_dest;
      print_ip();
      printf("\n");
      break;
    }
    case OPERATOR_LOOPNZ:
    {
      printf("CX(0x%hX)->", registers.cx);
      if(--registers.cx)
        ip += org_dest;
      printf("(0x%hX) ", registers.cx);
      print_ip();
      printf("\n");
      break;
    }
    case OPERATOR_LOOP:
    {
      printf("CX(0x%hX)->", registers.cx);
      if(--registers.cx)
        ip += org_dest;
      printf("(0x%hX) ", registers.cx);
      print_ip();
      printf("\n");
      break;
    }
  }
}

void exec16(Instruction *inst)
{
  i16 org_src = 0;

  if(operandSize(inst->op[RIGHT].type) == 1)
    org_src = *(i8*)operand(inst, RIGHT);
  else if(operandSize(inst->op[RIGHT].type) == 2) 
    org_src = *(i16*)operand(inst, RIGHT);
  
  u8 org_flags = flags;
  i16 * dest = (i16*)operand(inst, LEFT);
  i16 * src = &org_src;
  i16 org_dest = *(i16*)dest;

  switch (inst->mnemonic)
  {
    case OPERATOR_MOV:
    {
      if(isMem(inst->op[LEFT].type))
        printf("MEM(0x%hX)->", org_dest);
      else
        printf("%s(0x%hX)->", OPERAND_REG[inst->op[LEFT].type], org_dest);
      memcpy(dest, src, 2);
      printf("(0x%hX) ", *dest);
      print_ip();
      printf("\n");
      break;
    }
    case OPERATOR_ADD:
    {
      printf("%s(0x%hX)->", OPERAND_REG[inst->op[LEFT].type], org_dest);
      *dest += *src; 
      printf("(0x%hX) ", *dest);

      setFlag(*dest == 0, FLAG_ZERO);
      setFlag(*dest & 0x8000, FLAG_SIGN);
      setFlag(
        (org_dest > 0 && org_src > 0 && *dest < 0) ||
        (org_dest < 0 && org_src < 0 && *dest > 0), 
        FLAG_OVERFLOW
      );
      setFlag((u32)((u16)org_dest + (u16)org_src) > 0xFFFF, FLAG_CARRY);
      setFlag(getParity(*dest), FLAG_PARITY);
      setFlag((u32)(org_dest & 0xF) + (u32)(org_src & 0xF) > 0xF, FLAG_AUXILIARY_CARRY);
      print_ip();
      print_flags(org_flags);
      printf("\n");

      break; 
    }
    case OPERATOR_SUB:
    {
      printf("%s(0x%hX)->", OPERAND_REG[inst->op[LEFT].type], org_dest);
      *dest -= *src; 
      printf("(0x%hX) ", *dest);
      
      setFlag(*dest == 0, FLAG_ZERO);
      setFlag(*dest & 0x8000, FLAG_SIGN);
      setFlag(
        (org_dest < 0 && org_src > 0 && *dest > 0) ||
        (org_dest > 0 && org_src < 0 && *dest < 0), 
        FLAG_OVERFLOW
      );
      setFlag((u32)((u16)org_dest - (u16)org_src) > 0xFFFF, FLAG_CARRY);
      setFlag(getParity(*dest), FLAG_PARITY);
      setFlag((u32)(org_dest & 0xF) - (u32)(org_src & 0xF) > 0xF, FLAG_AUXILIARY_CARRY);
      print_ip();
      print_flags(org_flags);
      printf("\n");
      
      break; 
    }
    case OPERATOR_CMP:
    {
      i16 tmp = *dest - *src;
      
      setFlag(tmp == 0, FLAG_ZERO);
      setFlag(tmp & 0x8000, FLAG_SIGN);
      setFlag(
        (org_dest < 0 && org_src > 0 && tmp > 0) ||
        (org_dest > 0 && org_src < 0 && tmp < 0), 
        FLAG_OVERFLOW
      );
      setFlag((u32)((u16)org_dest - (u16)org_src) > 0xFFFF, FLAG_CARRY);
      setFlag(getParity(tmp), FLAG_PARITY);
      setFlag((u32)(org_dest & 0xF) - (u32)(org_src & 0xF) > 0xF, FLAG_AUXILIARY_CARRY);
      print_ip();
      print_flags(org_flags);
      printf("\n");
      break; 
    }
  }
}


void exec_all(const char *filename)
{
  #ifdef MODE_8080
    printf("; CPU 8080 -- %s\n", filename);
  #else
    printf("; CPU 8086 -- %s\n", filename);
  #endif
  
  i32 cycles = 0;
  while (ip < ip_end)
  {
    prev_ip = ip;
    Instruction inst = decode();
    print(inst);
    i32 tmp = count_cycles(inst);
    cycles += tmp;
    printf("; Clocks: +%d = %d | ", tmp, cycles);
    if(operandSize(inst.op[LEFT].type) == 1)
      exec8(&inst);
    else
      exec16(&inst);
  }

  printf("\nFinal registers:\n");
  if(registers.ax)
    printf("\tAX:0x%hX (%hu)\n", registers.ax, registers.ax);
  if(registers.bx)
    printf("\tBX:0x%hX (%hu)\n", registers.bx, registers.bx);
  if(registers.cx) 
    printf("\tCX:0x%hX (%hu)\n", registers.cx, registers.cx);
  if(registers.dx) 
    printf("\tDX:0x%hX (%hu)\n", registers.dx, registers.dx);
  if(registers.sp) 
    printf("\tSP:0x%hX (%hu)\n", registers.sp, registers.sp);
  if(registers.bp) 
    printf("\tBP:0x%hX (%hu)\n", registers.bp, registers.bp);
  if(registers.si) 
    printf("\tSI:0x%hX (%hu)\n", registers.si, registers.si);
  if(registers.di)
    printf("\tDI:0x%hX (%hu)\n", registers.di, registers.di);
  if(registers.es)
    printf("\tES:0x%hX (%hu)\n", registers.es, registers.es);
  if(registers.ss) 
    printf("\tSS:0x%hX (%hu)\n", registers.ss, registers.ss);
  if(registers.ds)
    printf("\tDS:0x%hX (%hu)\n", registers.ds, registers.ds);
  if(registers.cs)
    printf("\tCS:0x%hX (%hu)\n", registers.cs, registers.cs);
  printf("\tIP:0x%hX (%hu)\n", (u16)(ip - memory), (u16)(ip - memory)); 
  printf("\n");  
}
