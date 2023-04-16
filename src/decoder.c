#include "decoder.h"
#include "operator.h"
#include "operand.h"

void ModRegRm(Instruction *inst, u8 width, u8 dir)
{
  const u8 code = read_8();
  const u8 mod = code >> 6;
  const u8 reg = (code >> 3) & BIN(00000111);
  const u8 rm = code & BIN(00000111);

  switch (mod)
  {
  case BIN(00000000):
    inst->op[dir].type = RM_TABLE[width][rm];
    break;
  case BIN(00000001):
    inst->op[dir].type = RM_DISP8_TABLE[width][rm];
    break;
  case BIN(00000010):
    inst->op[dir].type = RM_DISP16_TABLE[width][rm];
    break;
  case BIN(00000011):
    inst->op[dir].type = REG_TABLE[width][rm];
    break;
  }
  inst->op[dir ^ 0x01].type = REG_TABLE[width][reg];
}

void ModSrRm(Instruction *inst, u8 width, u8 dir)
{
  const u8 code = read_8();
  const u8 mod = code >> 6;
  const u8 sr = (code >> 3) & BIN(00000111);
  const u8 rm = code & BIN(00000111);

  switch (mod)
  {
  case BIN(00000000):
    inst->op[dir].type = RM_TABLE[width][rm];
    break;
  case BIN(00000001):
    inst->op[dir].type = RM_DISP8_TABLE[width][rm];
    break;
  case BIN(00000010):
    inst->op[dir].type = RM_DISP16_TABLE[width][rm];
    break;
  case BIN(00000011):
    inst->op[dir].type = REG_TABLE[width][rm];
    break;
  }
  if (sr > 3)
    inst->op[dir ^ 0x01].type = OPERAND_ERROR;
  else
    inst->op[dir ^ 0x01].type = SEG_TABLE[sr];
}

void ModRm(Instruction *inst, u8 code, u8 width, u8 right_operand)
{
  const u8 mod = code >> 6;
  const u8 rm = code & BIN(00000111);

  switch (mod)
  {
  case BIN(00000000):
    inst->op[LEFT].type = RM_TABLE[width][rm];
    break;
  case BIN(00000001):
    inst->op[LEFT].type = RM_DISP8_TABLE[width][rm];
    break;
  case BIN(00000010):
    inst->op[LEFT].type = RM_DISP16_TABLE[width][rm];
    break;
  case BIN(00000011):
    inst->op[LEFT].type = REG_TABLE[width][rm];
    break;
  }
  inst->op[RIGHT].type = right_operand;
}

void DataDisp(Instruction *inst, u8 pos)
{
  if (hasDisp(inst->op[pos].type))
    inst->op[pos].data_lo = read_8();
  if (has16bitDisp(inst->op[pos].type))
    inst->op[pos].data_hi = read_8();
}

Instruction decode()
{
  u8 opcode = read_8();
  //printf(";%s\n", BinaryString[opcode]);
  Instruction inst = {0};
  switch (opcode)
  {
  case BIN(00000000):
    inst.mnemonic = OPERATOR_ADD;
    ModRegRm(&inst, SIZE_8, REG_RIGHT);
    DataDisp(&inst, LEFT);
    break;
  case BIN(00000001):
    inst.mnemonic = OPERATOR_ADD;
    ModRegRm(&inst, SIZE_16, REG_RIGHT);
    DataDisp(&inst, LEFT);
    break;
  case BIN(00000010):
    inst.mnemonic = OPERATOR_ADD;
    ModRegRm(&inst, SIZE_8, REG_LEFT);
    DataDisp(&inst, RIGHT);
    break;
  case BIN(00000011):
    inst.mnemonic = OPERATOR_ADD;
    ModRegRm(&inst, SIZE_16, REG_LEFT);
    DataDisp(&inst, RIGHT);
    break;
  case BIN(00000100):
    inst.mnemonic = OPERATOR_ADD;
    inst.op[LEFT].type = OPERAND_REG_AL;
    inst.op[RIGHT].type = OPERAND_IMMED_8;
    DataDisp(&inst, RIGHT);
    break;
  case BIN(00000101):
    inst.mnemonic = OPERATOR_ADD;
    inst.op[LEFT].type = OPERAND_REG_AX;
    inst.op[RIGHT].type = OPERAND_IMMED_16;
    DataDisp(&inst, RIGHT);
    break;
  case BIN(00000110):
    inst.mnemonic = OPERATOR_PUSH;
    inst.op[LEFT].type = OPERAND_SEG_ES;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(00000111):
    inst.mnemonic = OPERATOR_POP;
    inst.op[LEFT].type = OPERAND_SEG_ES;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(00001000):
    inst.mnemonic = OPERATOR_OR;
    ModRegRm(&inst, SIZE_8, REG_RIGHT);
    DataDisp(&inst, LEFT);
    break;
  case BIN(00001001):
    inst.mnemonic = OPERATOR_OR;
    ModRegRm(&inst, SIZE_16, REG_RIGHT);
    DataDisp(&inst, LEFT);
    break;
  case BIN(00001010):
    inst.mnemonic = OPERATOR_OR;
    ModRegRm(&inst, SIZE_8, REG_LEFT);
    DataDisp(&inst, RIGHT);
    break;
  case BIN(00001011):
    inst.mnemonic = OPERATOR_OR;
    ModRegRm(&inst, SIZE_16, REG_LEFT);
    DataDisp(&inst, RIGHT);
    break;
  case BIN(00001100):
    inst.mnemonic = OPERATOR_OR;
    inst.op[LEFT].type = OPERAND_REG_AL;
    inst.op[RIGHT].type = OPERAND_IMMED_8;
    DataDisp(&inst, RIGHT);
    break;
  case BIN(00001101):
    inst.mnemonic = OPERATOR_OR;
    inst.op[LEFT].type = OPERAND_REG_AX;
    inst.op[RIGHT].type = OPERAND_IMMED_16;
    DataDisp(&inst, RIGHT);
    break;
  case BIN(00001110):
    inst.mnemonic = OPERATOR_PUSH;
    inst.op[LEFT].type = OPERAND_SEG_CS;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(00001111):
    inst.mnemonic = OPERATOR_UNK;
    break;
  case BIN(00010000):
    inst.mnemonic = OPERATOR_ADC;
    ModRegRm(&inst, SIZE_8, REG_RIGHT);
    DataDisp(&inst, LEFT);
    break;
  case BIN(00010001):
    inst.mnemonic = OPERATOR_ADC;
    ModRegRm(&inst, SIZE_16, REG_RIGHT);
    DataDisp(&inst, LEFT);
    break;
  case BIN(00010010):
    inst.mnemonic = OPERATOR_ADC;
    ModRegRm(&inst, SIZE_8, REG_LEFT);
    DataDisp(&inst, RIGHT);
    break;
  case BIN(00010011):
    inst.mnemonic = OPERATOR_ADC;
    ModRegRm(&inst, SIZE_16, REG_LEFT);
    DataDisp(&inst, RIGHT);
    break;
  case BIN(00010100):
    inst.mnemonic = OPERATOR_ADC;
    inst.op[LEFT].type = OPERAND_REG_AL;
    inst.op[RIGHT].type = OPERAND_IMMED_8;
    DataDisp(&inst, RIGHT);
    break;
  case BIN(00010101):
    inst.mnemonic = OPERATOR_ADC;
    inst.op[LEFT].type = OPERAND_REG_AX;
    inst.op[RIGHT].type = OPERAND_IMMED_16;
    DataDisp(&inst, RIGHT);
    break;
  case BIN(00010110):
    inst.mnemonic = OPERATOR_PUSH;
    inst.op[LEFT].type = OPERAND_SEG_SS;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(00010111):
    inst.mnemonic = OPERATOR_POP;
    inst.op[LEFT].type = OPERAND_SEG_SS;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(00011000):
    inst.mnemonic = OPERATOR_SBB;
    ModRegRm(&inst, SIZE_8, REG_RIGHT);
    DataDisp(&inst, LEFT);
    break;
  case BIN(00011001):
    inst.mnemonic = OPERATOR_SBB;
    ModRegRm(&inst, SIZE_16, REG_RIGHT);
    DataDisp(&inst, LEFT);
    break;
  case BIN(00011010):
    inst.mnemonic = OPERATOR_SBB;
    ModRegRm(&inst, SIZE_8, REG_LEFT);
    DataDisp(&inst, RIGHT);
    break;
  case BIN(00011011):
    inst.mnemonic = OPERATOR_SBB;
    ModRegRm(&inst, SIZE_16, REG_LEFT);
    DataDisp(&inst, RIGHT);
    break;
  case BIN(00011100):
    inst.mnemonic = OPERATOR_SBB;
    inst.op[LEFT].type = OPERAND_REG_AL;
    inst.op[RIGHT].type = OPERAND_IMMED_8;
    DataDisp(&inst, RIGHT);
    break;
  case BIN(00011101):
    inst.mnemonic = OPERATOR_SBB;
    inst.op[LEFT].type = OPERAND_REG_AX;
    inst.op[RIGHT].type = OPERAND_IMMED_16;
    DataDisp(&inst, RIGHT);
    break;
  case BIN(00011110):
    inst.mnemonic = OPERATOR_PUSH;
    inst.op[LEFT].type = OPERAND_SEG_DS;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(00011111):
    inst.mnemonic = OPERATOR_POP;
    inst.op[LEFT].type = OPERAND_SEG_DS;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(00100000):
    inst.mnemonic = OPERATOR_AND;
    ModRegRm(&inst, SIZE_8, REG_RIGHT);
    DataDisp(&inst, LEFT);
    break;
  case BIN(00100001):
    inst.mnemonic = OPERATOR_AND;
    ModRegRm(&inst, SIZE_16, REG_RIGHT);
    DataDisp(&inst, LEFT);
    break;
  case BIN(00100010):
    inst.mnemonic = OPERATOR_AND;
    ModRegRm(&inst, SIZE_8, REG_LEFT);
    DataDisp(&inst, RIGHT);
    break;
  case BIN(00100011):
    inst.mnemonic = OPERATOR_AND;
    ModRegRm(&inst, SIZE_16, REG_LEFT);
    DataDisp(&inst, RIGHT);
    break;
  case BIN(00100100):
    inst.mnemonic = OPERATOR_AND;
    inst.op[LEFT].type = OPERAND_REG_AL;
    inst.op[RIGHT].type = OPERAND_IMMED_8;
    DataDisp(&inst, RIGHT);
    break;
  case BIN(00100101):
    inst.mnemonic = OPERATOR_AND;
    inst.op[LEFT].type = OPERAND_REG_AX;
    inst.op[RIGHT].type = OPERAND_IMMED_16;
    DataDisp(&inst, RIGHT);
    break;
  case BIN(00100110):
    inst = decode();
    inst.attributes |= ES_ATTR;
    break;
  case BIN(00100111):
    inst.mnemonic = OPERATOR_DAA;
    inst.op[LEFT].type = OPERAND_NONE;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(00101000):
    inst.mnemonic = OPERATOR_SUB;
    ModRegRm(&inst, SIZE_8, REG_RIGHT);
    DataDisp(&inst, LEFT);
    break;
  case BIN(00101001):
    inst.mnemonic = OPERATOR_SUB;
    ModRegRm(&inst, SIZE_16, REG_RIGHT);
    DataDisp(&inst, LEFT);
    break;
  case BIN(00101010):
    inst.mnemonic = OPERATOR_SUB;
    ModRegRm(&inst, SIZE_8, REG_LEFT);
    DataDisp(&inst, RIGHT);
    break;
  case BIN(00101011):
    inst.mnemonic = OPERATOR_SUB;
    ModRegRm(&inst, SIZE_16, REG_LEFT);
    DataDisp(&inst, RIGHT);
    break;
  case BIN(00101100):
    inst.mnemonic = OPERATOR_SUB;
    inst.op[LEFT].type = OPERAND_REG_AL;
    inst.op[RIGHT].type = OPERAND_IMMED_8;
    DataDisp(&inst, RIGHT);
    break;
  case BIN(00101101):
    inst.mnemonic = OPERATOR_SUB;
    inst.op[LEFT].type = OPERAND_REG_AX;
    inst.op[RIGHT].type = OPERAND_IMMED_16;
    DataDisp(&inst, RIGHT);
    break;
  case BIN(00101110):
    inst = decode();
    inst.attributes |= CS_ATTR;
    break;
  case BIN(00101111):
    inst.mnemonic = OPERATOR_DAS;
    inst.op[LEFT].type = OPERAND_NONE;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(00110000):
    inst.mnemonic = OPERATOR_XOR;
    ModRegRm(&inst, SIZE_8, REG_RIGHT);
    DataDisp(&inst, LEFT);
    break;
  case BIN(00110001):
    inst.mnemonic = OPERATOR_XOR;
    ModRegRm(&inst, SIZE_16, REG_RIGHT);
    DataDisp(&inst, LEFT);
    break;
  case BIN(00110010):
    inst.mnemonic = OPERATOR_XOR;
    ModRegRm(&inst, SIZE_8, REG_LEFT);
    DataDisp(&inst, RIGHT);
    break;
  case BIN(00110011):
    inst.mnemonic = OPERATOR_XOR;
    ModRegRm(&inst, SIZE_16, REG_LEFT);
    DataDisp(&inst, RIGHT);
    break;
  case BIN(00110100):
    inst.mnemonic = OPERATOR_XOR;
    inst.op[LEFT].type = OPERAND_REG_AL;
    inst.op[RIGHT].type = OPERAND_IMMED_8;
    DataDisp(&inst, RIGHT);
    break;
  case BIN(00110101):
    inst.mnemonic = OPERATOR_XOR;
    inst.op[LEFT].type = OPERAND_REG_AX;
    inst.op[RIGHT].type = OPERAND_IMMED_16;
    DataDisp(&inst, RIGHT);
    break;
  case BIN(00110110):
    inst = decode();
    inst.attributes |= SS_ATTR;
    break;
  case BIN(00110111):
    inst.mnemonic = OPERATOR_AAA;
    inst.op[LEFT].type = OPERAND_NONE;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(00111000):
    inst.mnemonic = OPERATOR_CMP;
    ModRegRm(&inst, SIZE_8, REG_RIGHT);
    DataDisp(&inst, LEFT);
    break;
  case BIN(00111001):
    inst.mnemonic = OPERATOR_CMP;
    ModRegRm(&inst, SIZE_16, REG_RIGHT);
    DataDisp(&inst, LEFT);
    break;
  case BIN(00111010):
    inst.mnemonic = OPERATOR_CMP;
    ModRegRm(&inst, SIZE_8, REG_LEFT);
    DataDisp(&inst, RIGHT);
    break;
  case BIN(00111011):
    inst.mnemonic = OPERATOR_CMP;
    ModRegRm(&inst, SIZE_16, REG_LEFT);
    DataDisp(&inst, RIGHT);
    break;
  case BIN(00111100):
    inst.mnemonic = OPERATOR_CMP;
    inst.op[LEFT].type = OPERAND_REG_AL;
    inst.op[RIGHT].type = OPERAND_IMMED_8;
    DataDisp(&inst, RIGHT);
    break;
  case BIN(00111101):
    inst.mnemonic = OPERATOR_CMP;
    inst.op[LEFT].type = OPERAND_REG_AX;
    inst.op[RIGHT].type = OPERAND_IMMED_16;
    DataDisp(&inst, RIGHT);
    break;
  case BIN(00111110):
    inst = decode();
    inst.attributes |= DS_ATTR;
    break;
  case BIN(00111111):
    inst.mnemonic = OPERATOR_AAS;
    inst.op[LEFT].type = OPERAND_NONE;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(01000000):
    inst.mnemonic = OPERATOR_INC;
    inst.op[LEFT].type = OPERAND_REG_AX;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(01000001):
    inst.mnemonic = OPERATOR_INC;
    inst.op[LEFT].type = OPERAND_REG_CX;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(01000010):
    inst.mnemonic = OPERATOR_INC;
    inst.op[LEFT].type = OPERAND_REG_DX;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(01000011):
    inst.mnemonic = OPERATOR_INC;
    inst.op[LEFT].type = OPERAND_REG_BX;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(01000100):
    inst.mnemonic = OPERATOR_INC;
    inst.op[LEFT].type = OPERAND_REG_SP;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(01000101):
    inst.mnemonic = OPERATOR_INC;
    inst.op[LEFT].type = OPERAND_REG_BP;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(01000110):
    inst.mnemonic = OPERATOR_INC;
    inst.op[LEFT].type = OPERAND_REG_SI;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(01000111):
    inst.mnemonic = OPERATOR_INC;
    inst.op[LEFT].type = OPERAND_REG_DI;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(01001000):
    inst.mnemonic = OPERATOR_DEC;
    inst.op[LEFT].type = OPERAND_REG_AX;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(01001001):
    inst.mnemonic = OPERATOR_DEC;
    inst.op[LEFT].type = OPERAND_REG_CX;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(01001010):
    inst.mnemonic = OPERATOR_DEC;
    inst.op[LEFT].type = OPERAND_REG_DX;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(01001011):
    inst.mnemonic = OPERATOR_DEC;
    inst.op[LEFT].type = OPERAND_REG_BX;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(01001100):
    inst.mnemonic = OPERATOR_DEC;
    inst.op[LEFT].type = OPERAND_REG_SP;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(01001101):
    inst.mnemonic = OPERATOR_DEC;
    inst.op[LEFT].type = OPERAND_REG_BP;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(01001110):
    inst.mnemonic = OPERATOR_DEC;
    inst.op[LEFT].type = OPERAND_REG_SI;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(01001111):
    inst.mnemonic = OPERATOR_DEC;
    inst.op[LEFT].type = OPERAND_REG_DI;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(01010000):
    inst.mnemonic = OPERATOR_PUSH;
    inst.op[LEFT].type = OPERAND_REG_AX;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(01010001):
    inst.mnemonic = OPERATOR_PUSH;
    inst.op[LEFT].type = OPERAND_REG_CX;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(01010010):
    inst.mnemonic = OPERATOR_PUSH;
    inst.op[LEFT].type = OPERAND_REG_DX;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(01010011):
    inst.mnemonic = OPERATOR_PUSH;
    inst.op[LEFT].type = OPERAND_REG_BX;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(01010100):
    inst.mnemonic = OPERATOR_PUSH;
    inst.op[LEFT].type = OPERAND_REG_SP;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(01010101):
    inst.mnemonic = OPERATOR_PUSH;
    inst.op[LEFT].type = OPERAND_REG_BP;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(01010110):
    inst.mnemonic = OPERATOR_PUSH;
    inst.op[LEFT].type = OPERAND_REG_SI;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(01010111):
    inst.mnemonic = OPERATOR_PUSH;
    inst.op[LEFT].type = OPERAND_REG_DI;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(01011000):
    inst.mnemonic = OPERATOR_POP;
    inst.op[LEFT].type = OPERAND_REG_AX;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(01011001):
    inst.mnemonic = OPERATOR_POP;
    inst.op[LEFT].type = OPERAND_REG_CX;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(01011010):
    inst.mnemonic = OPERATOR_POP;
    inst.op[LEFT].type = OPERAND_REG_DX;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(01011011):
    inst.mnemonic = OPERATOR_POP;
    inst.op[LEFT].type = OPERAND_REG_BX;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(01011100):
    inst.mnemonic = OPERATOR_POP;
    inst.op[LEFT].type = OPERAND_REG_SP;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(01011101):
    inst.mnemonic = OPERATOR_POP;
    inst.op[LEFT].type = OPERAND_REG_BP;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(01011110):
    inst.mnemonic = OPERATOR_POP;
    inst.op[LEFT].type = OPERAND_REG_SI;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(01011111):
    inst.mnemonic = OPERATOR_POP;
    inst.op[LEFT].type = OPERAND_REG_DI;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(01100000):
  case BIN(01100001):
  case BIN(01100010):
  case BIN(01100011):
  case BIN(01100100):
  case BIN(01100101):
  case BIN(01100110):
  case BIN(01100111):
  case BIN(01101000):
  case BIN(01101001):
  case BIN(01101010):
  case BIN(01101011):
  case BIN(01101100):
  case BIN(01101101):
  case BIN(01101110):
  case BIN(01101111):
    inst.mnemonic = OPERATOR_UNK;
    break;
  case BIN(01110000):
    inst.mnemonic = OPERATOR_JO;
    inst.op[LEFT].type = OPERAND_JMP_8;
    inst.op[RIGHT].type = OPERAND_NONE;
    DataDisp(&inst, LEFT);
    break;
  case BIN(01110001):
    inst.mnemonic = OPERATOR_JNO;
    inst.op[LEFT].type = OPERAND_JMP_8;
    inst.op[RIGHT].type = OPERAND_NONE;
    DataDisp(&inst, LEFT);
    break;
  case BIN(01110010):
    inst.mnemonic = OPERATOR_JB;
    inst.op[LEFT].type = OPERAND_JMP_8;
    inst.op[RIGHT].type = OPERAND_NONE;
    DataDisp(&inst, LEFT);
    break;
  case BIN(01110011):
    inst.mnemonic = OPERATOR_JAE;
    inst.op[LEFT].type = OPERAND_JMP_8;
    inst.op[RIGHT].type = OPERAND_NONE;
    DataDisp(&inst, LEFT);
    break;
  case BIN(01110100):
    inst.mnemonic = OPERATOR_JE;
    inst.op[LEFT].type = OPERAND_JMP_8;
    inst.op[RIGHT].type = OPERAND_NONE;
    DataDisp(&inst, LEFT);
    break;
  case BIN(01110101):
    inst.mnemonic = OPERATOR_JNE;
    inst.op[LEFT].type = OPERAND_JMP_8;
    inst.op[RIGHT].type = OPERAND_NONE;
    DataDisp(&inst, LEFT);
    break;
  case BIN(01110110):
    inst.mnemonic = OPERATOR_JBE;
    inst.op[LEFT].type = OPERAND_JMP_8;
    inst.op[RIGHT].type = OPERAND_NONE;
    DataDisp(&inst, LEFT);
    break;
  case BIN(01110111):
    inst.mnemonic = OPERATOR_JA;
    inst.op[LEFT].type = OPERAND_JMP_8;
    inst.op[RIGHT].type = OPERAND_NONE;
    DataDisp(&inst, LEFT);
    break;
  case BIN(01111000):
    inst.mnemonic = OPERATOR_JS;
    inst.op[LEFT].type = OPERAND_JMP_8;
    inst.op[RIGHT].type = OPERAND_NONE;
    DataDisp(&inst, LEFT);
    break;
  case BIN(01111001):
    inst.mnemonic = OPERATOR_JNS;
    inst.op[LEFT].type = OPERAND_JMP_8;
    inst.op[RIGHT].type = OPERAND_NONE;
    DataDisp(&inst, LEFT);
    break;
  case BIN(01111010):
    inst.mnemonic = OPERATOR_JP;
    inst.op[LEFT].type = OPERAND_JMP_8;
    inst.op[RIGHT].type = OPERAND_NONE;
    DataDisp(&inst, LEFT);
    break;
  case BIN(01111011):
    inst.mnemonic = OPERATOR_JNP;
    inst.op[LEFT].type = OPERAND_JMP_8;
    inst.op[RIGHT].type = OPERAND_NONE;
    DataDisp(&inst, LEFT);
    break;
  case BIN(01111100):
    inst.mnemonic = OPERATOR_JL;
    inst.op[LEFT].type = OPERAND_JMP_8;
    inst.op[RIGHT].type = OPERAND_NONE;
    DataDisp(&inst, LEFT);
    break;
  case BIN(01111101):
    inst.mnemonic = OPERATOR_JGE;
    inst.op[LEFT].type = OPERAND_JMP_8;
    inst.op[RIGHT].type = OPERAND_NONE;
    DataDisp(&inst, LEFT);
    break;
  case BIN(01111110):
    inst.mnemonic = OPERATOR_JLE;
    inst.op[LEFT].type = OPERAND_JMP_8;
    inst.op[RIGHT].type = OPERAND_NONE;
    DataDisp(&inst, LEFT);
    break;
  case BIN(01111111):
    inst.mnemonic = OPERATOR_JG;
    inst.op[LEFT].type = OPERAND_JMP_8;
    inst.op[RIGHT].type = OPERAND_NONE;
    DataDisp(&inst, LEFT);
    break;
  case BIN(10000000):
  {
    const u8 code = read_8();
    const u8 op = (code >> 3) & BIN(00000111);
    switch (op)
    {
    case BIN(00000000):
      inst.mnemonic = OPERATOR_ADD;
      break;
    case BIN(00000001):
      inst.mnemonic = OPERATOR_OR;
      break;
    case BIN(00000010):
      inst.mnemonic = OPERATOR_ADC;
      break;
    case BIN(00000011):
      inst.mnemonic = OPERATOR_SBB;
      break;
    case BIN(00000100):
      inst.mnemonic = OPERATOR_AND;
      break;
    case BIN(00000101):
      inst.mnemonic = OPERATOR_SUB;
      break;
    case BIN(00000110):
      inst.mnemonic = OPERATOR_XOR;
      break;
    case BIN(00000111):
      inst.mnemonic = OPERATOR_CMP;
      break;
    }
    ModRm(&inst, code, SIZE_8, OPERAND_IMMED_8);
    DataDisp(&inst, LEFT);
    DataDisp(&inst, RIGHT);
  }
  break;
  case BIN(10000001):
  {
    const u8 code = read_8();
    const u8 op = (code >> 3) & BIN(00000111);
    switch (op)
    {
    case BIN(00000000):
      inst.mnemonic = OPERATOR_ADD;
      break;
    case BIN(00000001):
      inst.mnemonic = OPERATOR_OR;
      break;
    case BIN(00000010):
      inst.mnemonic = OPERATOR_ADC;
      break;
    case BIN(00000011):
      inst.mnemonic = OPERATOR_SBB;
      break;
    case BIN(00000100):
      inst.mnemonic = OPERATOR_AND;
      break;
    case BIN(00000101):
      inst.mnemonic = OPERATOR_SUB;
      break;
    case BIN(00000110):
      inst.mnemonic = OPERATOR_XOR;
      break;
    case BIN(00000111):
      inst.mnemonic = OPERATOR_CMP;
      break;
    }
    ModRm(&inst, code, SIZE_16, OPERAND_IMMED_16);
    DataDisp(&inst, LEFT);
    DataDisp(&inst, RIGHT);
  }
  break;
  case BIN(10000010):
  {
    const u8 code = read_8();
    const u8 op = (code >> 3) & BIN(00000111);
    switch (op)
    {
    case BIN(00000000):
      inst.mnemonic = OPERATOR_ADD;
      break;
    case BIN(00000001):
      inst.mnemonic = OPERATOR_UNK;
      break;
    case BIN(00000010):
      inst.mnemonic = OPERATOR_ADC;
      break;
    case BIN(00000011):
      inst.mnemonic = OPERATOR_SBB;
      break;
    case BIN(00000100):
      inst.mnemonic = OPERATOR_UNK;
      break;
    case BIN(00000101):
      inst.mnemonic = OPERATOR_SUB;
      break;
    case BIN(00000110):
      inst.mnemonic = OPERATOR_UNK;
      break;
    case BIN(00000111):
      inst.mnemonic = OPERATOR_CMP;
      break;
    }
    if (inst.mnemonic != OPERATOR_UNK)
    {
      ModRm(&inst, code, SIZE_8, OPERAND_IMMED_8);
      DataDisp(&inst, LEFT);
      DataDisp(&inst, RIGHT);
    }
  }
  break;
  case BIN(10000011):
  {
    const u8 code = read_8();
    const u8 op = (code >> 3) & BIN(00000111);
    switch (op)
    {
    case BIN(00000000):
      inst.mnemonic = OPERATOR_ADD;
      break;
    case BIN(00000001):
      inst.mnemonic = OPERATOR_UNK;
      break;
    case BIN(00000010):
      inst.mnemonic = OPERATOR_ADC;
      break;
    case BIN(00000011):
      inst.mnemonic = OPERATOR_SBB;
      break;
    case BIN(00000100):
      inst.mnemonic = OPERATOR_UNK;
      break;
    case BIN(00000101):
      inst.mnemonic = OPERATOR_SUB;
      break;
    case BIN(00000110):
      inst.mnemonic = OPERATOR_UNK;
      break;
    case BIN(00000111):
      inst.mnemonic = OPERATOR_CMP;
      break;
    }
    if (inst.mnemonic != OPERATOR_UNK)
    {
      ModRm(&inst, code, SIZE_16, OPERAND_IMMED_8);
      DataDisp(&inst, LEFT);
      DataDisp(&inst, RIGHT);
    }
  }
  break;
  case BIN(10000100):
    inst.mnemonic = OPERATOR_TEST;
    ModRegRm(&inst, SIZE_8, REG_RIGHT);
    DataDisp(&inst, LEFT);
    break;
  case BIN(10000101):
    inst.mnemonic = OPERATOR_TEST;
    ModRegRm(&inst, SIZE_16, REG_RIGHT);
    DataDisp(&inst, LEFT);
    break;
  case BIN(10000110):
    inst.mnemonic = OPERATOR_XCHG;
    ModRegRm(&inst, SIZE_8, REG_LEFT);
    DataDisp(&inst, RIGHT);
    break;
  case BIN(10000111):
    inst.mnemonic = OPERATOR_XCHG;
    ModRegRm(&inst, SIZE_16, REG_LEFT);
    DataDisp(&inst, RIGHT);
    break;
  case BIN(10001000):
    inst.mnemonic = OPERATOR_MOV;
    ModRegRm(&inst, SIZE_8, REG_RIGHT);
    DataDisp(&inst, LEFT);
    break;
  case BIN(10001001):
    inst.mnemonic = OPERATOR_MOV;
    ModRegRm(&inst, SIZE_16, REG_RIGHT);
    DataDisp(&inst, LEFT);
    break;
  case BIN(10001010):
    inst.mnemonic = OPERATOR_MOV;
    ModRegRm(&inst, SIZE_8, REG_LEFT);
    DataDisp(&inst, RIGHT);
    break;
  case BIN(10001011):
    inst.mnemonic = OPERATOR_MOV;
    ModRegRm(&inst, SIZE_16, REG_LEFT);
    DataDisp(&inst, RIGHT);
    break;
  case BIN(10001100):
    inst.mnemonic = OPERATOR_MOV;
    ModSrRm(&inst, SIZE_16, REG_RIGHT);
    DataDisp(&inst, LEFT);
    break;
  case BIN(10001101):
    inst.mnemonic = OPERATOR_LEA;
    ModRegRm(&inst, SIZE_16, REG_LEFT);
    DataDisp(&inst, RIGHT);
    break;
  case BIN(10001110):
    inst.mnemonic = OPERATOR_MOV;
    ModSrRm(&inst, SIZE_16, REG_LEFT);
    DataDisp(&inst, RIGHT);
    break;
  case BIN(10001111):
  {
    const u8 code = read_8();
    const u8 op = (code >> 3) & BIN(00000111);
    if (op == BIN(00000000))
    {
      inst.mnemonic = OPERATOR_POP;
      ModRm(&inst, code, SIZE_16, OPERAND_NONE);
      DataDisp(&inst, LEFT);
    }
    else
      inst.mnemonic = OPERATOR_UNK;
  }
  break;
  case BIN(10010000):
    inst.mnemonic = OPERATOR_NOP;
    inst.op[LEFT].type = OPERAND_NONE;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(10010001):
    inst.mnemonic = OPERATOR_XCHG;
    inst.op[LEFT].type = OPERAND_REG_AX;
    inst.op[RIGHT].type = OPERAND_REG_CX;
    break;
  case BIN(10010010):
    inst.mnemonic = OPERATOR_XCHG;
    inst.op[LEFT].type = OPERAND_REG_AX;
    inst.op[RIGHT].type = OPERAND_REG_DX;
    break;
  case BIN(10010011):
    inst.mnemonic = OPERATOR_XCHG;
    inst.op[LEFT].type = OPERAND_REG_AX;
    inst.op[RIGHT].type = OPERAND_REG_BX;
    break;
  case BIN(10010100):
    inst.mnemonic = OPERATOR_XCHG;
    inst.op[LEFT].type = OPERAND_REG_AX;
    inst.op[RIGHT].type = OPERAND_REG_SP;
    break;
  case BIN(10010101):
    inst.mnemonic = OPERATOR_XCHG;
    inst.op[LEFT].type = OPERAND_REG_AX;
    inst.op[RIGHT].type = OPERAND_REG_BP;
    break;
  case BIN(10010110):
    inst.mnemonic = OPERATOR_XCHG;
    inst.op[LEFT].type = OPERAND_REG_AX;
    inst.op[RIGHT].type = OPERAND_REG_SI;
    break;
  case BIN(10010111):
    inst.mnemonic = OPERATOR_XCHG;
    inst.op[LEFT].type = OPERAND_REG_AX;
    inst.op[RIGHT].type = OPERAND_REG_DI;
    break;
  case BIN(10011000):
    inst.mnemonic = OPERATOR_CBW;
    inst.op[LEFT].type = OPERAND_NONE;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(10011001):
    inst.mnemonic = OPERATOR_CWD;
    inst.op[LEFT].type = OPERAND_NONE;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(10011010):
    inst.mnemonic = OPERATOR_CALL;
    inst.op[LEFT].type = OPERAND_SEG_16;
    inst.op[RIGHT].type = OPERAND_IMMED_16;
    DataDisp(&inst, RIGHT);    
    DataDisp(&inst, LEFT);
    break;
  case BIN(10011011):
    inst.mnemonic = OPERATOR_WAIT;
    inst.op[LEFT].type = OPERAND_NONE;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(10011100):
    inst.mnemonic = OPERATOR_PUSHF;
    inst.op[LEFT].type = OPERAND_NONE;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(10011101):
    inst.mnemonic = OPERATOR_POPF;
    inst.op[LEFT].type = OPERAND_NONE;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(10011110):
    inst.mnemonic = OPERATOR_SAHF;
    inst.op[LEFT].type = OPERAND_NONE;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(10011111):
    inst.mnemonic = OPERATOR_LAHF;
    inst.op[LEFT].type = OPERAND_NONE;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(10100000):
    inst.mnemonic = OPERATOR_MOV;
    inst.op[LEFT].type = OPERAND_REG_AL;
    inst.op[RIGHT].type = OPERAND_MEM8_D16;
    DataDisp(&inst, RIGHT);
    break;
  case BIN(10100001):
    inst.mnemonic = OPERATOR_MOV;
    inst.op[LEFT].type = OPERAND_REG_AX;
    inst.op[RIGHT].type = OPERAND_MEM16_D16;
    DataDisp(&inst, RIGHT);
    break;
  case BIN(10100010):
    inst.mnemonic = OPERATOR_MOV;
    inst.op[LEFT].type = OPERAND_MEM8_D16;
    inst.op[RIGHT].type = OPERAND_REG_AL;
    DataDisp(&inst, LEFT);
    break;
  case BIN(10100011):
    inst.mnemonic = OPERATOR_MOV;
    inst.op[LEFT].type = OPERAND_MEM16_D16;
    inst.op[RIGHT].type = OPERAND_REG_AX; // TODO: AL in documentation ???
    DataDisp(&inst, LEFT);
    break;
    // DEST_STR8 = DI
    // SRC-STR8 = SI
  case BIN(10100100):
    inst.mnemonic = OPERATOR_MOVSB;
    inst.op[LEFT].type = OPERAND_REG_DI;
    inst.op[RIGHT].type = OPERAND_REG_SI;
    DataDisp(&inst, LEFT);
    break;
  case BIN(10100101):
    inst.mnemonic = OPERATOR_MOVSW;
    inst.op[LEFT].type = OPERAND_REG_DI;
    inst.op[RIGHT].type = OPERAND_REG_SI;
    DataDisp(&inst, LEFT);
    break;
  case BIN(10100110):
    inst.mnemonic = OPERATOR_CMPSB;
    inst.op[LEFT].type = OPERAND_REG_DI;
    inst.op[RIGHT].type = OPERAND_REG_SI;
    DataDisp(&inst, LEFT);
    break;
  case BIN(10100111):
    inst.mnemonic = OPERATOR_CMPSW;
    inst.op[LEFT].type = OPERAND_REG_DI;
    inst.op[RIGHT].type = OPERAND_REG_SI;
    DataDisp(&inst, LEFT);
    break;
  case BIN(10101000):
    inst.mnemonic = OPERATOR_TEST;
    inst.op[LEFT].type = OPERAND_REG_AL;
    inst.op[RIGHT].type = OPERAND_IMMED_8;
    DataDisp(&inst, RIGHT);
    break;
  case BIN(10101001):
    inst.mnemonic = OPERATOR_TEST;
    inst.op[LEFT].type = OPERAND_REG_AX;
    inst.op[RIGHT].type = OPERAND_IMMED_16;
    DataDisp(&inst, RIGHT);
    break;
  case BIN(10101010):
    inst.mnemonic = OPERATOR_STOSB;
    inst.op[LEFT].type = OPERAND_REG_DI;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(10101011):
    inst.mnemonic = OPERATOR_STOSW;
    inst.op[LEFT].type = OPERAND_REG_DI;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(10101100):
    inst.mnemonic = OPERATOR_LODSB;
    inst.op[LEFT].type = OPERAND_REG_DI;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(10101101):
    inst.mnemonic = OPERATOR_LODSW;
    inst.op[LEFT].type = OPERAND_REG_DI;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(10101110):
    inst.mnemonic = OPERATOR_SCASB;
    inst.op[LEFT].type = OPERAND_REG_DI;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(10101111):
    inst.mnemonic = OPERATOR_SCASW;
    inst.op[LEFT].type = OPERAND_REG_DI;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(10110000):
    inst.mnemonic = OPERATOR_MOV;
    inst.op[LEFT].type = OPERAND_REG_AL;
    inst.op[RIGHT].type = OPERAND_IMMED_8;
    DataDisp(&inst, RIGHT);
    break;
  case BIN(10110001):
    inst.mnemonic = OPERATOR_MOV;
    inst.op[LEFT].type = OPERAND_REG_CL;
    inst.op[RIGHT].type = OPERAND_IMMED_8;
    DataDisp(&inst, RIGHT);
    break;
  case BIN(10110010):
    inst.mnemonic = OPERATOR_MOV;
    inst.op[LEFT].type = OPERAND_REG_DL;
    inst.op[RIGHT].type = OPERAND_IMMED_8;
    DataDisp(&inst, RIGHT);
    break;
  case BIN(10110011):
    inst.mnemonic = OPERATOR_MOV;
    inst.op[LEFT].type = OPERAND_REG_BL;
    inst.op[RIGHT].type = OPERAND_IMMED_8;
    DataDisp(&inst, RIGHT);
    break;
  case BIN(10110100):
    inst.mnemonic = OPERATOR_MOV;
    inst.op[LEFT].type = OPERAND_REG_AH;
    inst.op[RIGHT].type = OPERAND_IMMED_8;
    DataDisp(&inst, RIGHT);
    break;
  case BIN(10110101):
    inst.mnemonic = OPERATOR_MOV;
    inst.op[LEFT].type = OPERAND_REG_CH;
    inst.op[RIGHT].type = OPERAND_IMMED_8;
    DataDisp(&inst, RIGHT);
    break;
  case BIN(10110110):
    inst.mnemonic = OPERATOR_MOV;
    inst.op[LEFT].type = OPERAND_REG_DH;
    inst.op[RIGHT].type = OPERAND_IMMED_8;
    DataDisp(&inst, RIGHT);
    break;
  case BIN(10110111):
    inst.mnemonic = OPERATOR_MOV;
    inst.op[LEFT].type = OPERAND_REG_BH;
    inst.op[RIGHT].type = OPERAND_IMMED_8;
    DataDisp(&inst, RIGHT);
    break;
  case BIN(10111000):
    inst.mnemonic = OPERATOR_MOV;
    inst.op[LEFT].type = OPERAND_REG_AX;
    inst.op[RIGHT].type = OPERAND_IMMED_16;
    DataDisp(&inst, RIGHT);
    break;
  case BIN(10111001):
    inst.mnemonic = OPERATOR_MOV;
    inst.op[LEFT].type = OPERAND_REG_CX;
    inst.op[RIGHT].type = OPERAND_IMMED_16;
    DataDisp(&inst, RIGHT);
    break;
  case BIN(10111010):
    inst.mnemonic = OPERATOR_MOV;
    inst.op[LEFT].type = OPERAND_REG_DX;
    inst.op[RIGHT].type = OPERAND_IMMED_16;
    DataDisp(&inst, RIGHT);
    break;
  case BIN(10111011):
    inst.mnemonic = OPERATOR_MOV;
    inst.op[LEFT].type = OPERAND_REG_BX;
    inst.op[RIGHT].type = OPERAND_IMMED_16;
    DataDisp(&inst, RIGHT);
    break;
  case BIN(10111100):
    inst.mnemonic = OPERATOR_MOV;
    inst.op[LEFT].type = OPERAND_REG_SP;
    inst.op[RIGHT].type = OPERAND_IMMED_16;
    DataDisp(&inst, RIGHT);
    break;
  case BIN(10111101):
    inst.mnemonic = OPERATOR_MOV;
    inst.op[LEFT].type = OPERAND_REG_BP;
    inst.op[RIGHT].type = OPERAND_IMMED_16;
    DataDisp(&inst, RIGHT);
    break;
  case BIN(10111110):
    inst.mnemonic = OPERATOR_MOV;
    inst.op[LEFT].type = OPERAND_REG_SI;
    inst.op[RIGHT].type = OPERAND_IMMED_16;
    DataDisp(&inst, RIGHT);
    break;
  case BIN(10111111):
    inst.mnemonic = OPERATOR_MOV;
    inst.op[LEFT].type = OPERAND_REG_DI;
    inst.op[RIGHT].type = OPERAND_IMMED_16;
    DataDisp(&inst, RIGHT);
    break;
  case BIN(11000000):
  case BIN(11000001):
    inst.mnemonic = OPERATOR_UNK;
    break;
  case BIN(11000010):
    inst.mnemonic = OPERATOR_RET;
    inst.op[LEFT].type = OPERAND_IMMED_16;
    inst.op[RIGHT].type = OPERAND_NONE;
    DataDisp(&inst, LEFT);
    break;
  case BIN(11000011):
    inst.mnemonic = OPERATOR_RET;
    inst.op[LEFT].type = OPERAND_NONE;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(11000100):
    inst.mnemonic = OPERATOR_LES;
    ModRegRm(&inst, SIZE_16, REG_LEFT);
    DataDisp(&inst, RIGHT);
    break;
  case BIN(11000101):
    inst.mnemonic = OPERATOR_LDS;
    ModRegRm(&inst, SIZE_16, REG_LEFT);
    DataDisp(&inst, RIGHT);
    break;
  case BIN(11000110):
  {
    const u8 code = read_8();
    const u8 op = (code >> 3) & BIN(00000111);
    if (op == BIN(00000000))
    {
      inst.mnemonic = OPERATOR_MOV;
      ModRm(&inst, code, SIZE_8, OPERAND_IMMED_8);
      DataDisp(&inst, LEFT);
      DataDisp(&inst, RIGHT);
    }
    else
      inst.mnemonic = OPERATOR_UNK;
  }
  break;
  case BIN(11000111):
  {
    const u8 code = read_8();
    const u8 op = (code >> 3) & BIN(00000111);
    if (op == BIN(00000000))
    {
      inst.mnemonic = OPERATOR_MOV;
      ModRm(&inst, code, SIZE_16, OPERAND_IMMED_16);
      DataDisp(&inst, LEFT);
      DataDisp(&inst, RIGHT);
    }
    else
      inst.mnemonic = OPERATOR_UNK;
  }
  break;
  case BIN(11001000):
  case BIN(11001001):
    inst.mnemonic = OPERATOR_UNK;
    break;
  case BIN(11001010):
    inst.mnemonic = OPERATOR_RETF;
    inst.op[LEFT].type = OPERAND_IMMED_16;
    inst.op[RIGHT].type = OPERAND_NONE;
    DataDisp(&inst, LEFT);
    break;
  case BIN(11001011):
    inst.mnemonic = OPERATOR_RETF;
    inst.op[LEFT].type = OPERAND_NONE;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(11001100):
    inst.mnemonic = OPERATOR_INT3;
    inst.op[LEFT].type = OPERAND_NONE;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(11001101):
    inst.mnemonic = OPERATOR_INT;
    inst.op[LEFT].type = OPERAND_IMMED_8;
    inst.op[RIGHT].type = OPERAND_NONE;
    DataDisp(&inst, LEFT);
    break;
  case BIN(11001110):
    inst.mnemonic = OPERATOR_INTO;
    inst.op[LEFT].type = OPERAND_NONE;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(11001111):
    inst.mnemonic = OPERATOR_IRET;
    inst.op[LEFT].type = OPERAND_NONE;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(11010000):
  {
    const u8 code = read_8();
    const u8 op = (code >> 3) & BIN(00000111);
    switch (op)
    {
    case BIN(00000000):
      inst.mnemonic = OPERATOR_ROL;
      break;
    case BIN(00000001):
      inst.mnemonic = OPERATOR_ROR;
      break;
    case BIN(00000010):
      inst.mnemonic = OPERATOR_RCL;
      break;
    case BIN(00000011):
      inst.mnemonic = OPERATOR_RCR;
      break;
    case BIN(00000100):
      inst.mnemonic = OPERATOR_SAL;
      break;
    case BIN(00000101):
      inst.mnemonic = OPERATOR_SHR;
      break;
    case BIN(00000110):
      inst.mnemonic = OPERATOR_UNK;
      break;
    case BIN(00000111):
      inst.mnemonic = OPERATOR_SAR;
      break;
    }
    if (inst.mnemonic != OPERATOR_UNK)
    {
      ModRm(&inst, code, SIZE_8, OPERAND_IMMED_8);
      DataDisp(&inst, LEFT);
      inst.op[RIGHT].data_lo = 1;
    }
  }
  break;
  case BIN(11010001):
  {
    const u8 code = read_8();
    const u8 op = (code >> 3) & BIN(00000111);
    switch (op)
    {
    case BIN(00000000):
      inst.mnemonic = OPERATOR_ROL;
      break;
    case BIN(00000001):
      inst.mnemonic = OPERATOR_ROR;
      break;
    case BIN(00000010):
      inst.mnemonic = OPERATOR_RCL;
      break;
    case BIN(00000011):
      inst.mnemonic = OPERATOR_RCR;
      break;
    case BIN(00000100):
      inst.mnemonic = OPERATOR_SAL;
      break;
    case BIN(00000101):
      inst.mnemonic = OPERATOR_SHR;
      break;
    case BIN(00000110):
      inst.mnemonic = OPERATOR_UNK;
      break;
    case BIN(00000111):
      inst.mnemonic = OPERATOR_SAR;
      break;
    }
    if (inst.mnemonic != OPERATOR_UNK)
    {
      ModRm(&inst, code, SIZE_16, OPERAND_IMMED_16);
      DataDisp(&inst, LEFT);
      inst.op[RIGHT].data_lo = 1;
      inst.op[RIGHT].data_hi = 0;
    }
  }
  break;
  case BIN(11010010):
  {
    const u8 code = read_8();
    const u8 op = (code >> 3) & BIN(00000111);
    switch (op)
    {
    case BIN(00000000):
      inst.mnemonic = OPERATOR_ROL;
      break;
    case BIN(00000001):
      inst.mnemonic = OPERATOR_ROR;
      break;
    case BIN(00000010):
      inst.mnemonic = OPERATOR_RCL;
      break;
    case BIN(00000011):
      inst.mnemonic = OPERATOR_RCR;
      break;
    case BIN(00000100):
      inst.mnemonic = OPERATOR_SAL;
      break;
    case BIN(00000101):
      inst.mnemonic = OPERATOR_SHR;
      break;
    case BIN(00000110):
      inst.mnemonic = OPERATOR_UNK;
      break;
    case BIN(00000111):
      inst.mnemonic = OPERATOR_SAR;
      break;
    }
    if (inst.mnemonic != OPERATOR_UNK)
    {
      ModRm(&inst, code, SIZE_8, OPERAND_REG_CL);
      DataDisp(&inst, LEFT);
    }
  }
  break;
  case BIN(11010011):
  {
    const u8 code = read_8();
    const u8 op = (code >> 3) & BIN(00000111);
    switch (op)
    {
    case BIN(00000000):
      inst.mnemonic = OPERATOR_ROL;
      break;
    case BIN(00000001):
      inst.mnemonic = OPERATOR_ROR;
      break;
    case BIN(00000010):
      inst.mnemonic = OPERATOR_RCL;
      break;
    case BIN(00000011):
      inst.mnemonic = OPERATOR_RCR;
      break;
    case BIN(00000100):
      inst.mnemonic = OPERATOR_SAL;
      break;
    case BIN(00000101):
      inst.mnemonic = OPERATOR_SHR;
      break;
    case BIN(00000110):
      inst.mnemonic = OPERATOR_UNK;
      break;
    case BIN(00000111):
      inst.mnemonic = OPERATOR_SAR;
      break;
    }
    if (inst.mnemonic != OPERATOR_UNK)
    {
      ModRm(&inst, code, SIZE_16, OPERAND_REG_CL);
      DataDisp(&inst, LEFT);
    }
  }
  break;
  case BIN(11010100):
  {
    const u8 code = read_8();
    if (code == BIN(00001010))
      inst.mnemonic = OPERATOR_AAM;
    else
      inst.mnemonic = OPERATOR_UNK;
    inst.op[LEFT].type = OPERAND_NONE;
    inst.op[RIGHT].type = OPERAND_NONE;
  }
  break;
  case BIN(11010101):
  {
    const u8 code = read_8();
    if (code == BIN(00001010))
      inst.mnemonic = OPERATOR_AAD;
    else
      inst.mnemonic = OPERATOR_UNK;
    inst.op[LEFT].type = OPERAND_NONE;
    inst.op[RIGHT].type = OPERAND_NONE;
  }
  break;
  case BIN(11010110):
    inst.mnemonic = OPERATOR_UNK;
    inst.op[LEFT].type = OPERAND_NONE;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
    // Source table BX
  case BIN(11010111):
    inst.mnemonic = OPERATOR_XLAT;
    inst.op[LEFT].type = OPERAND_REG_BX;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(11011000):
  {
    // TODO: write raw implementation
    // Write all cases
    // XXX first 3 bits of esc
    // YYY second 3 bits of esc
    const u8 code = read_8();
    // const u8 op   = code & BIN(00111000);
    inst.mnemonic = OPERATOR_ESC;
    ModRm(&inst, code, SIZE_16, OPERAND_NONE);
    DataDisp(&inst, LEFT);
  }
  break;
  case BIN(11011111):
    // TODO: find instruction!
    break;
  case BIN(11100000):
    inst.mnemonic = OPERATOR_LOOPNZ;
    inst.op[LEFT].type = OPERAND_JMP_8;
    inst.op[RIGHT].type = OPERAND_NONE;
    DataDisp(&inst, LEFT);
    break;
  case BIN(11100001):
    inst.mnemonic = OPERATOR_LOOPE;
    inst.op[LEFT].type = OPERAND_JMP_8;
    inst.op[RIGHT].type = OPERAND_NONE;
    DataDisp(&inst, LEFT);
    break;
  case BIN(11100010):
    inst.mnemonic = OPERATOR_LOOP;
    inst.op[LEFT].type = OPERAND_JMP_8;
    inst.op[RIGHT].type = OPERAND_NONE;
    DataDisp(&inst, LEFT);
    break;
  case BIN(11100011):
    inst.mnemonic = OPERATOR_JCXZ;
    inst.op[LEFT].type = OPERAND_JMP_8;
    inst.op[RIGHT].type = OPERAND_NONE;
    DataDisp(&inst, LEFT);
    break;
  case BIN(11100100):
    inst.mnemonic = OPERATOR_IN;
    inst.op[LEFT].type = OPERAND_REG_AL;
    inst.op[RIGHT].type = OPERAND_IMMED_8;
    DataDisp(&inst, RIGHT);
    break;
  case BIN(11100101):
    inst.mnemonic = OPERATOR_IN;
    inst.op[LEFT].type = OPERAND_REG_AX;
    inst.op[RIGHT].type = OPERAND_IMMED_16;
    DataDisp(&inst, RIGHT);
    break;
  case BIN(11100110):
    inst.mnemonic = OPERATOR_OUT;
    inst.op[LEFT].type = OPERAND_IMMED_8;
    inst.op[RIGHT].type = OPERAND_REG_AL;
    DataDisp(&inst, LEFT);
    break;
  case BIN(11100111):
    inst.mnemonic = OPERATOR_OUT;
    inst.op[LEFT].type = OPERAND_IMMED_8;
    inst.op[RIGHT].type = OPERAND_REG_AX;
    DataDisp(&inst, LEFT);
    break;
  case BIN(11101000):
    inst.mnemonic = OPERATOR_CALL;
    inst.op[LEFT].type = OPERAND_JMP_16;
    inst.op[RIGHT].type = OPERAND_NONE;
    DataDisp(&inst, LEFT);
    break;
  case BIN(11101001):
    inst.mnemonic = OPERATOR_JMP;
    inst.op[LEFT].type = OPERAND_JMP_16;
    inst.op[RIGHT].type = OPERAND_NONE;
    DataDisp(&inst, LEFT);
    break;
  case BIN(11101010):
    inst.mnemonic = OPERATOR_JMP;
    inst.op[LEFT].type = OPERAND_SEG_16;
    inst.op[RIGHT].type = OPERAND_IMMED_16;
    DataDisp(&inst, RIGHT);
    DataDisp(&inst, LEFT);
    break;
  case BIN(11101011):
    inst.mnemonic = OPERATOR_JMP;
    inst.op[LEFT].type = OPERAND_JMP_8;
    inst.op[RIGHT].type = OPERAND_NONE;
    DataDisp(&inst, LEFT);
    break;
  case BIN(11101100):
    inst.mnemonic = OPERATOR_IN;
    inst.op[LEFT].type = OPERAND_REG_AL;
    inst.op[RIGHT].type = OPERAND_REG_DX;
    break;
  case BIN(11101101):
    inst.mnemonic = OPERATOR_IN;
    inst.op[LEFT].type = OPERAND_REG_AX;
    inst.op[RIGHT].type = OPERAND_REG_DX;
    break;
  case BIN(11101110):
    inst.mnemonic = OPERATOR_OUT;
    inst.op[LEFT].type = OPERAND_REG_DX;
    inst.op[RIGHT].type = OPERAND_REG_AL;
    break;
  case BIN(11101111):
    inst.mnemonic = OPERATOR_OUT;
    inst.op[LEFT].type = OPERAND_REG_AX;
    inst.op[RIGHT].type = OPERAND_REG_DX;
    break;
  case BIN(11110000):
    inst = decode();
    inst.attributes |= LOCK_ATTR;
    if(inst.mnemonic == OPERATOR_XCHG)
    {
      Instruction tmp = {0};
      memcpy(&tmp.op[0], &inst.op[0], 3);
      memcpy(&inst.op[0], &inst.op[1], 3);     
      memcpy(&inst.op[1], &tmp.op[0], 3);     
    }
    break;
  case BIN(11110001):
    inst.mnemonic = OPERATOR_UNK;
    inst.op[LEFT].type = OPERAND_NONE;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(11110010):
    inst.mnemonic = OPERATOR_REPNE;
    inst.op[LEFT].type = OPERAND_NONE;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(11110011):
    inst = decode();
    inst.attributes |= REP_ATTR;
    break;
  case BIN(11110100):
    inst.mnemonic = OPERATOR_HLT;
    inst.op[LEFT].type = OPERAND_NONE;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(11110101):
    inst.mnemonic = OPERATOR_CMC;
    inst.op[LEFT].type = OPERAND_NONE;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(11110110):
  {
    const u8 code = read_8();
    const u8 op = (code >> 3) & BIN(00000111);
    switch (op)
    {
    case BIN(00000000):
      inst.mnemonic = OPERATOR_TEST;
      ModRm(&inst, code, SIZE_8, OPERAND_IMMED_8);
      DataDisp(&inst, LEFT);
      DataDisp(&inst, RIGHT);
      break;
    case BIN(00000001):
      inst.mnemonic = OPERATOR_UNK;
      break;
    case BIN(00000010):
      inst.mnemonic = OPERATOR_NOT;
      break;
    case BIN(00000011):
      inst.mnemonic = OPERATOR_NEG;
      break;
    case BIN(00000100):
      inst.mnemonic = OPERATOR_MUL;
      break;
    case BIN(00000101):
      inst.mnemonic = OPERATOR_IMUL;
      break;
    case BIN(00000110):
      inst.mnemonic = OPERATOR_DIV;
      break;
    case BIN(00000111):
      inst.mnemonic = OPERATOR_IDIV;
      break;
    }
    if (inst.mnemonic != OPERATOR_UNK && inst.mnemonic != OPERATOR_TEST)
    {
      ModRm(&inst, code, SIZE_8, OPERAND_NONE);
      DataDisp(&inst, LEFT);
    }
  }
  break;
  case BIN(11110111):
  {
    const u8 code = read_8();
    const u8 op = (code >> 3) & BIN(00000111);
    switch (op)
    {
    case BIN(00000000):
      inst.mnemonic = OPERATOR_TEST;
      ModRm(&inst, code, SIZE_16, OPERAND_IMMED_16);
      DataDisp(&inst, LEFT);
      DataDisp(&inst, RIGHT);
      break;
    case BIN(00000001):
      inst.mnemonic = OPERATOR_UNK;
      break;
    case BIN(00000010):
      inst.mnemonic = OPERATOR_NOT;
      break;
    case BIN(00000011):
      inst.mnemonic = OPERATOR_NEG;
      break;
    case BIN(00000100):
      inst.mnemonic = OPERATOR_MUL;
      break;
    case BIN(00000101):
      inst.mnemonic = OPERATOR_IMUL;
      break;
    case BIN(00000110):
      inst.mnemonic = OPERATOR_DIV;
      break;
    case BIN(00000111):
      inst.mnemonic = OPERATOR_IDIV;
      break;
    }
    if (inst.mnemonic != OPERATOR_UNK && inst.mnemonic != OPERATOR_TEST)
    {
      ModRm(&inst, code, SIZE_16, OPERAND_NONE);
      DataDisp(&inst, LEFT);
    }
  }
  break;
  case BIN(11111000):
    inst.mnemonic = OPERATOR_CLC;
    inst.op[LEFT].type = OPERAND_NONE;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(11111001):
    inst.mnemonic = OPERATOR_STC;
    inst.op[LEFT].type = OPERAND_NONE;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(11111010):
    inst.mnemonic = OPERATOR_CLI;
    inst.op[LEFT].type = OPERAND_NONE;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(11111011):
    inst.mnemonic = OPERATOR_STI;
    inst.op[LEFT].type = OPERAND_NONE;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(11111100):
    inst.mnemonic = OPERATOR_CLD;
    inst.op[LEFT].type = OPERAND_NONE;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(11111101):
    inst.mnemonic = OPERATOR_STD;
    inst.op[LEFT].type = OPERAND_NONE;
    inst.op[RIGHT].type = OPERAND_NONE;
    break;
  case BIN(11111110):
  {
    const u8 code = read_8();
    const u8 op = (code >> 3) & BIN(00000111);
    switch (op)
    {
    case BIN(00000000):
      inst.mnemonic = OPERATOR_INC;
      ModRm(&inst, code, SIZE_8, OPERAND_NONE);
      DataDisp(&inst, LEFT);
      break;
    case BIN(00000001):
      inst.mnemonic = OPERATOR_DEC;
      ModRm(&inst, code, SIZE_8, OPERAND_NONE);
      DataDisp(&inst, LEFT);
      break;
    case BIN(00000010):
    case BIN(00000011):
    case BIN(00000100):
    case BIN(00000101):
    case BIN(00000110):
    case BIN(00000111):
      inst.mnemonic = OPERATOR_UNK;
      break;
    }
  }
  break;
  case BIN(11111111):
  {
    const u8 code = read_8();
    const u8 op = (code >> 3) & BIN(00000111);
    switch (op)
    {
    case BIN(00000000):
      inst.mnemonic = OPERATOR_INC;
      break;
    case BIN(00000001):
      inst.mnemonic = OPERATOR_DEC;
      break;
    case BIN(00000010):
      inst.mnemonic = OPERATOR_CALL;
      break;
    case BIN(00000011):
      inst.mnemonic = OPERATOR_CALLF;
      break;
    case BIN(00000100):
      inst.mnemonic = OPERATOR_JMP;
      break;
    case BIN(00000101):
      inst.mnemonic = OPERATOR_JMPF;
      break;
    case BIN(00000110):
      inst.mnemonic = OPERATOR_PUSH;
      break;
    case BIN(00000111):
      inst.mnemonic = OPERATOR_UNK;
      break;
    }
    if (inst.mnemonic != OPERATOR_UNK)
    {
      ModRm(&inst, code, SIZE_16, OPERAND_NONE);
      DataDisp(&inst, LEFT);
    }
  }
  break;
  }
  return inst;
}
