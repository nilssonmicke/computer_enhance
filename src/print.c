#include "print.h"
#include "operator.h"
#include "operand.h"
#include "decoder.h"

#include <stdio.h>

void print(Instruction inst)
{
  const char *segement = "";
  if (inst.attributes)
  {
    if (inst.attributes & LOCK_ATTR)
      printf("LOCK ");
    if (inst.attributes & REP_ATTR)
      printf("REP ");
    if (inst.attributes & CS_ATTR)
      segement = "CS:";
    if (inst.attributes & ES_ATTR)
      segement = "ES:";
    if (inst.attributes & SS_ATTR)
      segement = "SS:";
    if (inst.attributes & DS_ATTR)
      segement = "DS:";
  }

  printf("%s ", MNEMONIC[inst.mnemonic]);

  if (inst.mnemonic == OPERATOR_XLAT || inst.mnemonic == OPERATOR_MOVSB || inst.mnemonic == OPERATOR_CMPSB ||
      inst.mnemonic == OPERATOR_SCASB || inst.mnemonic == OPERATOR_LODSB || inst.mnemonic == OPERATOR_MOVSW ||
      inst.mnemonic == OPERATOR_CMPSW || inst.mnemonic == OPERATOR_SCASW || inst.mnemonic == OPERATOR_LODSW ||
      inst.mnemonic == OPERATOR_STOSB || inst.mnemonic == OPERATOR_STOSW)
  {
    return;
  }

  if (isMem(inst.op[LEFT].type))
  {
    const char *size_specifier = "";
    if (isMem8(inst.op[LEFT].type)) // && (isImmed(inst.op[RIGHT].type) || inst.op[RIGHT].type == OPERAND_NONE))
      size_specifier = "byte ";
    else if (isMem16(inst.op[LEFT].type)) // && (isImmed(inst.op[RIGHT].type) || inst.op[RIGHT].type == OPERAND_NONE))
      size_specifier = "word ";

    printf("%s%s[%s", size_specifier, segement, OPERAND_REG[inst.op[LEFT].type]);
    if (has8bitDisp(inst.op[LEFT].type))
    {
      i8 disp = inst.op[LEFT].data_lo;
      if ((inst.op[LEFT].type == OPERAND_MEM16_D8 || inst.op[LEFT].type == OPERAND_MEM8_D8) && disp > 0)
        printf("%hd", disp);
      else if (disp > 0)
        printf(" + %hd", disp);
      else if (disp < 0)
        printf(" - %hd", -disp);
    }
    else if (has16bitDisp(inst.op[LEFT].type))
    {
      i16 disp = ((i16)inst.op[LEFT].data_hi) << 8 | ((i16)inst.op[LEFT].data_lo);
      if ((inst.op[LEFT].type == OPERAND_MEM16_D16 || inst.op[LEFT].type == OPERAND_MEM8_D16) && disp > 0)
        printf("%hd", disp);
      else if (disp > 0)
        printf(" + %hd", disp);
      else if (disp < 0)
        printf(" - %hd", -disp);
    }
    printf("]");
  }
  else if (inst.op[LEFT].type == OPERAND_JMP_8)
  {
    printf("$+2+%hd", (i8)inst.op[LEFT].data_lo);
  }
  else if (inst.op[LEFT].type == OPERAND_JMP_16)
  {
    printf("%hu", ((u16)(ip - memory)) + (((u16)inst.op[LEFT].data_hi) << 8 | ((u16)inst.op[LEFT].data_lo)));
  }
  else if (inst.op[LEFT].type == OPERAND_SEG_16)
  {
    u16 seg = ((u16)inst.op[LEFT].data_hi) << 8 | ((u16)inst.op[LEFT].data_lo);
    printf("%hu:", seg);
  }
  else if (isImmed(inst.op[LEFT].type))
  {
    if (has8bitDisp(inst.op[LEFT].type))
    {
      u8 disp = inst.op[LEFT].data_lo;
      printf("%hd", disp);
    }
    else if (has16bitDisp(inst.op[LEFT].type))
    {
      i16 disp = ((i16)inst.op[LEFT].data_hi) << 8 | ((i16)inst.op[LEFT].data_lo);
      printf("%hd", disp);
    }
  }
  else if (inst.op[LEFT].type != OPERAND_NONE)
  {
    printf("%s", OPERAND_REG[inst.op[LEFT].type]);
    if (hasDisp(inst.op[LEFT].type))
      printf(" + %hd", inst.op[LEFT].data_lo);
  }
  else
  {
    // printf("ERROR!!!");
  }

  if (isMem(inst.op[RIGHT].type))
  {
    printf(", %s[%s", segement, OPERAND_REG[inst.op[RIGHT].type]);
    if (has8bitDisp(inst.op[RIGHT].type))
    {
      i8 disp = inst.op[RIGHT].data_lo;
      if ((inst.op[RIGHT].type == OPERAND_MEM16_D8 || inst.op[RIGHT].type == OPERAND_MEM8_D8) && disp > 0)
        printf("%hd", disp);
      else if (disp > 0)
        printf(" + %hd", disp);
      else if (disp < 0)
        printf(" - %hd", -disp);
    }
    else if (has16bitDisp(inst.op[RIGHT].type))
    {
      i16 disp = ((i16)inst.op[RIGHT].data_hi) << 8 | ((i16)inst.op[RIGHT].data_lo);
      if ((inst.op[RIGHT].type == OPERAND_MEM16_D16 || inst.op[RIGHT].type == OPERAND_MEM8_D16) && disp > 0)
        printf("%hd", disp);
      else if (disp > 0)
        printf(" + %hd", disp);
      else if (disp < 0)
        printf(" - %hd", -disp);
    }
    printf("]");
  }
  else if (isImmed(inst.op[RIGHT].type))
  {
    if (has8bitDisp(inst.op[RIGHT].type))
    {
      if(operandSize(inst.op[LEFT].type) == 2)
      {
        i8 disp = inst.op[RIGHT].data_lo;
        printf(", %hd", disp);
      }
      else
      {
        u8 disp = inst.op[RIGHT].data_lo;
        printf(", %hu", disp);
      }
    }
    else if (has16bitDisp(inst.op[RIGHT].type))
    {
      i16 disp = ((i16)inst.op[RIGHT].data_hi) << 8 | ((i16)inst.op[RIGHT].data_lo);
      if(inst.op[LEFT].type != OPERAND_SEG_16)
        printf(", %hd", disp);
      else
        printf("%hd", disp);       
    }
  }
  else if (inst.op[RIGHT].type != OPERAND_NONE)
  {
    printf(", %s ", OPERAND_REG[inst.op[RIGHT].type]);
    if (hasDisp(inst.op[RIGHT].type))
      printf(" + %hu", inst.op[RIGHT].data_lo);
  }
  else
  {
    // printf("ERROR!!!");
  }
}

void print_all(const char *filename)
{
  printf("; %s\n", filename);
  printf("bits 16\n");
  while (ip < ip_end)
  {
    Instruction inst = decode();
    print(inst);
    printf("\n");
  }
}

void print_flags(u8 org_flags)
{
  if(flags != 0 ||  org_flags != 0)
  {
    printf("flags:");
    if(org_flags & FLAG_ZERO)
      printf("Z");
    if(org_flags & FLAG_SIGN)
      printf("S");
    if(org_flags & FLAG_OVERFLOW)
      printf("O");
    if(org_flags & FLAG_CARRY)
      printf("C");
    if(org_flags & FLAG_PARITY)
      printf("P");
    if(org_flags & FLAG_AUXILIARY_CARRY)
      printf("A");
      
    printf("->");

    if(flags & FLAG_ZERO)
      printf("Z");
    if(flags & FLAG_SIGN)
      printf("S");
    if(flags & FLAG_OVERFLOW)
      printf("O");
    if(flags & FLAG_CARRY)
      printf("C");
    if(flags & FLAG_PARITY)
      printf("P");
    if(flags & FLAG_AUXILIARY_CARRY)
      printf("A");
  }
}
