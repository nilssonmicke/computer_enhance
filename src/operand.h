#ifndef OPERAND_H
#define OPERAND_H

#include <stdint.h>
#include <stdbool.h>

#define OPERAND_NONE            0x00
#define OPERAND_IMMED_8         0x01
#define OPERAND_IMMED_16        0x02
#define OPERAND_REG_AL          0x03
#define OPERAND_REG_CL          0x04
#define OPERAND_REG_DL          0x05
#define OPERAND_REG_BL          0x06
#define OPERAND_REG_AH          0x07
#define OPERAND_REG_CH          0x08
#define OPERAND_REG_DH          0x09
#define OPERAND_REG_BH          0x0A
#define OPERAND_REG_AX          0x0B
#define OPERAND_REG_CX          0x0C
#define OPERAND_REG_DX          0x0D
#define OPERAND_REG_BX          0x0E
#define OPERAND_REG_SP          0x0F
#define OPERAND_REG_BP          0x10
#define OPERAND_REG_SI          0x11
#define OPERAND_REG_DI          0x12
#define OPERAND_MEM16_D8        0x13
#define OPERAND_MEM16_D16       0x14
#define OPERAND_MEM16_BX_SI     0x15
#define OPERAND_MEM16_BX_DI     0x16
#define OPERAND_MEM16_BP_SI     0x17
#define OPERAND_MEM16_BP_DI     0x18
#define OPERAND_MEM16_SI        0x19
#define OPERAND_MEM16_DI        0x1A
#define OPERAND_MEM16_BX        0x1B
#define OPERAND_MEM16_BX_SI_D8  0x1C
#define OPERAND_MEM16_BX_DI_D8  0x1D
#define OPERAND_MEM16_BP_SI_D8  0x1E
#define OPERAND_MEM16_BP_DI_D8  0x1F
#define OPERAND_MEM16_SI_D8     0x20
#define OPERAND_MEM16_DI_D8     0x21
#define OPERAND_MEM16_BP_D8     0x22
#define OPERAND_MEM16_BX_D8     0x23
#define OPERAND_MEM16_BX_SI_D16 0x24
#define OPERAND_MEM16_BX_DI_D16 0x25
#define OPERAND_MEM16_BP_SI_D16 0x26
#define OPERAND_MEM16_BP_DI_D16 0x27
#define OPERAND_MEM16_SI_D16    0x28
#define OPERAND_MEM16_DI_D16    0x29
#define OPERAND_MEM16_BP_D16    0x2A
#define OPERAND_MEM16_BX_D16    0x2B
#define OPERAND_MEM8_D8         0x2C
#define OPERAND_MEM8_D16        0x2D
#define OPERAND_MEM8_BX_SI      0x2E
#define OPERAND_MEM8_BX_DI      0x2F
#define OPERAND_MEM8_BP_SI      0x30
#define OPERAND_MEM8_BP_DI      0x31
#define OPERAND_MEM8_SI         0x32
#define OPERAND_MEM8_DI         0x33
#define OPERAND_MEM8_BX         0x34
#define OPERAND_MEM8_BX_SI_D8   0x35
#define OPERAND_MEM8_BX_DI_D8   0x36
#define OPERAND_MEM8_BP_SI_D8   0x37
#define OPERAND_MEM8_BP_DI_D8   0x38
#define OPERAND_MEM8_SI_D8      0x39
#define OPERAND_MEM8_DI_D8      0x3A
#define OPERAND_MEM8_BP_D8      0x3B
#define OPERAND_MEM8_BX_D8      0x3C
#define OPERAND_MEM8_BX_SI_D16  0x3D
#define OPERAND_MEM8_BX_DI_D16  0x3E
#define OPERAND_MEM8_BP_SI_D16  0x3F
#define OPERAND_MEM8_BP_DI_D16  0x40
#define OPERAND_MEM8_SI_D16     0x41
#define OPERAND_MEM8_DI_D16     0x42
#define OPERAND_MEM8_BP_D16     0x43
#define OPERAND_MEM8_BX_D16     0x44
#define OPERAND_SEG_CS          0x45
#define OPERAND_SEG_DS          0x46
#define OPERAND_SEG_ES          0x47
#define OPERAND_SEG_SS          0x48
#define OPERAND_SEG_16          0x49
#define OPERAND_JMP_8           0x4A
#define OPERAND_JMP_16          0x4B
#define OPERAND_ERROR           0x4C

const uint8_t RM_TABLE[2][8] = 
{
	{
		OPERAND_MEM8_BX_SI, OPERAND_MEM8_BX_DI, OPERAND_MEM8_BP_SI, 
		OPERAND_MEM8_BP_DI, OPERAND_MEM8_SI, OPERAND_MEM8_DI, 
		OPERAND_MEM8_D16, OPERAND_MEM8_BX
	}, {
		OPERAND_MEM16_BX_SI, OPERAND_MEM16_BX_DI, OPERAND_MEM16_BP_SI, 
		OPERAND_MEM16_BP_DI, OPERAND_MEM16_SI, OPERAND_MEM16_DI, 
		OPERAND_MEM16_D16, OPERAND_MEM16_BX
	},
};
const uint8_t RM_DISP8_TABLE[2][8] = 
{
	{
		OPERAND_MEM8_BX_SI_D8, OPERAND_MEM8_BX_DI_D8, OPERAND_MEM8_BP_SI_D8, 
		OPERAND_MEM8_BP_DI_D8, OPERAND_MEM8_SI_D8, OPERAND_MEM8_DI_D8, 
		OPERAND_MEM8_BP_D8, OPERAND_MEM8_BX_D8
	}, {
		OPERAND_MEM16_BX_SI_D8, OPERAND_MEM16_BX_DI_D8, OPERAND_MEM16_BP_SI_D8, 
		OPERAND_MEM16_BP_DI_D8, OPERAND_MEM16_SI_D8, OPERAND_MEM16_DI_D8, 
		OPERAND_MEM16_BP_D8, OPERAND_MEM16_BX_D8
	}
};

const uint8_t RM_DISP16_TABLE[2][8] = 
{
	{	
		OPERAND_MEM8_BX_SI_D16, OPERAND_MEM8_BX_DI_D16, OPERAND_MEM8_BP_SI_D16, 
		OPERAND_MEM8_BP_DI_D16, OPERAND_MEM8_SI_D16, OPERAND_MEM8_DI_D16, 
		OPERAND_MEM8_BP_D16, OPERAND_MEM8_BX_D16
	}, {	
		OPERAND_MEM16_BX_SI_D16, OPERAND_MEM16_BX_DI_D16, OPERAND_MEM16_BP_SI_D16, 
		OPERAND_MEM16_BP_DI_D16, OPERAND_MEM16_SI_D16, OPERAND_MEM16_DI_D16, 
		OPERAND_MEM16_BP_D16, OPERAND_MEM16_BX_D16
	}
};

const uint8_t REG_TABLE[2][8] = 
{
	{
		OPERAND_REG_AL, OPERAND_REG_CL, OPERAND_REG_DL, 
		OPERAND_REG_BL, OPERAND_REG_AH, OPERAND_REG_CH, 
		OPERAND_REG_DH, OPERAND_REG_BH
	}, {
		OPERAND_REG_AX, OPERAND_REG_CX, OPERAND_REG_DX, 
		OPERAND_REG_BX, OPERAND_REG_SP, OPERAND_REG_BP, 
		OPERAND_REG_SI, OPERAND_REG_DI
	}
};

const uint8_t SEG_TABLE[4] = 
{
	OPERAND_SEG_ES, OPERAND_SEG_CS, OPERAND_SEG_SS, OPERAND_SEG_DS
};

bool isImmed(uint8_t operand)
{
    bool result = false;
    switch (operand)
    {
    	case OPERAND_IMMED_8:
    	case OPERAND_IMMED_16:
        	result = true;
    }
    return result;
}

bool isReg(uint8_t operand)
{
    bool result = false;
    switch (operand)
    {
      case OPERAND_REG_DI:
      case OPERAND_REG_AL:
      case OPERAND_REG_CL:
      case OPERAND_REG_DL:
      case OPERAND_REG_BL:
      case OPERAND_REG_AH:
      case OPERAND_REG_CH:
      case OPERAND_REG_DH:
      case OPERAND_REG_BH:
      case OPERAND_REG_AX:
      case OPERAND_REG_CX:
      case OPERAND_REG_DX:
      case OPERAND_REG_BX:
      case OPERAND_REG_SP:
      case OPERAND_REG_BP:
      case OPERAND_REG_SI:
        	result = true;
    }
    return result;
}

bool isMem(uint8_t operand)
{
    bool result = false;
    switch (operand)
    {
		case OPERAND_MEM16_D8:
		case OPERAND_MEM16_D16:
		case OPERAND_MEM16_BX_SI:
		case OPERAND_MEM16_BX_DI:
		case OPERAND_MEM16_BP_SI:
		case OPERAND_MEM16_BP_DI:
		case OPERAND_MEM16_SI:
		case OPERAND_MEM16_DI:
		case OPERAND_MEM16_BX:
		case OPERAND_MEM16_BX_SI_D8:
		case OPERAND_MEM16_BX_DI_D8:
		case OPERAND_MEM16_BP_SI_D8:
		case OPERAND_MEM16_BP_DI_D8:
		case OPERAND_MEM16_SI_D8:
		case OPERAND_MEM16_DI_D8:
		case OPERAND_MEM16_BP_D8:
		case OPERAND_MEM16_BX_D8:
		case OPERAND_MEM16_BX_SI_D16:
		case OPERAND_MEM16_BX_DI_D16:
		case OPERAND_MEM16_BP_SI_D16:
		case OPERAND_MEM16_BP_DI_D16:
		case OPERAND_MEM16_SI_D16:
		case OPERAND_MEM16_DI_D16:
		case OPERAND_MEM16_BP_D16:
		case OPERAND_MEM16_BX_D16:
		case OPERAND_MEM8_D8:
		case OPERAND_MEM8_D16:
		case OPERAND_MEM8_BX_SI:
		case OPERAND_MEM8_BX_DI:
		case OPERAND_MEM8_BP_SI:
		case OPERAND_MEM8_BP_DI:
		case OPERAND_MEM8_SI:
		case OPERAND_MEM8_DI:
		case OPERAND_MEM8_BX:
		case OPERAND_MEM8_BX_SI_D8:
		case OPERAND_MEM8_BX_DI_D8:
		case OPERAND_MEM8_BP_SI_D8:
		case OPERAND_MEM8_BP_DI_D8:
		case OPERAND_MEM8_SI_D8:
		case OPERAND_MEM8_DI_D8:
		case OPERAND_MEM8_BP_D8:
		case OPERAND_MEM8_BX_D8:
		case OPERAND_MEM8_BX_SI_D16:
		case OPERAND_MEM8_BX_DI_D16:
		case OPERAND_MEM8_BP_SI_D16:
		case OPERAND_MEM8_BP_DI_D16:
		case OPERAND_MEM8_SI_D16:
		case OPERAND_MEM8_DI_D16:
		case OPERAND_MEM8_BP_D16:
		case OPERAND_MEM8_BX_D16:
        result = true;
    }
    return result;
}

uint8_t operandSize(uint8_t operand)
{
    uint8_t result = 1;
    switch (operand)
    {
		case OPERAND_NONE:
		case OPERAND_ERROR:
			result = 0;
		break;
		case OPERAND_IMMED_8:
		case OPERAND_REG_AL:
		case OPERAND_REG_CL:
		case OPERAND_REG_DL:
		case OPERAND_REG_BL:
		case OPERAND_REG_AH:
		case OPERAND_REG_CH:
		case OPERAND_REG_DH:
		case OPERAND_REG_BH:
		case OPERAND_MEM8_D8:
		case OPERAND_MEM8_D16:
		case OPERAND_MEM8_BX_SI:
		case OPERAND_MEM8_BX_DI:
		case OPERAND_MEM8_BP_SI:
		case OPERAND_MEM8_BP_DI:
		case OPERAND_MEM8_SI:
		case OPERAND_MEM8_DI:
		case OPERAND_MEM8_BX:
		case OPERAND_MEM8_BX_SI_D8:
		case OPERAND_MEM8_BX_DI_D8:
		case OPERAND_MEM8_BP_SI_D8:
		case OPERAND_MEM8_BP_DI_D8:
		case OPERAND_MEM8_SI_D8:
		case OPERAND_MEM8_DI_D8:
		case OPERAND_MEM8_BP_D8:
		case OPERAND_MEM8_BX_D8:
		case OPERAND_MEM8_BX_SI_D16:
		case OPERAND_MEM8_BX_DI_D16:
		case OPERAND_MEM8_BP_SI_D16:
		case OPERAND_MEM8_BP_DI_D16:
		case OPERAND_MEM8_SI_D16:
		case OPERAND_MEM8_DI_D16:
		case OPERAND_MEM8_BP_D16:
		case OPERAND_MEM8_BX_D16:
		case OPERAND_JMP_8:
			result = 1;
		break;
		case OPERAND_IMMED_16:
		case OPERAND_REG_AX:
		case OPERAND_REG_CX:
		case OPERAND_REG_DX:
		case OPERAND_REG_BX:
		case OPERAND_REG_SP:
		case OPERAND_REG_BP:
		case OPERAND_REG_SI:
		case OPERAND_REG_DI:
		case OPERAND_MEM16_D8:
		case OPERAND_MEM16_D16:
		case OPERAND_MEM16_BX_SI:
		case OPERAND_MEM16_BX_DI:
		case OPERAND_MEM16_BP_SI:
		case OPERAND_MEM16_BP_DI:
		case OPERAND_MEM16_SI:
		case OPERAND_MEM16_DI:
		case OPERAND_MEM16_BX:
		case OPERAND_MEM16_BX_SI_D8:
		case OPERAND_MEM16_BX_DI_D8:
		case OPERAND_MEM16_BP_SI_D8:
		case OPERAND_MEM16_BP_DI_D8:
		case OPERAND_MEM16_SI_D8:
		case OPERAND_MEM16_DI_D8:
		case OPERAND_MEM16_BP_D8:
		case OPERAND_MEM16_BX_D8:
		case OPERAND_MEM16_BX_SI_D16:
		case OPERAND_MEM16_BX_DI_D16:
		case OPERAND_MEM16_BP_SI_D16:
		case OPERAND_MEM16_BP_DI_D16:
		case OPERAND_MEM16_SI_D16:
		case OPERAND_MEM16_DI_D16:
		case OPERAND_MEM16_BP_D16:
		case OPERAND_MEM16_BX_D16:
		case OPERAND_SEG_CS:
		case OPERAND_SEG_DS:
		case OPERAND_SEG_ES:
		case OPERAND_SEG_SS:
		case OPERAND_SEG_16:
		case OPERAND_JMP_16:
			result = 2;
		break;
    }
    return result;
}


bool isMem8(uint8_t operand)
{
    bool result = false;
    switch (operand)
    {
		case OPERAND_MEM8_D8:
		case OPERAND_MEM8_D16:
		case OPERAND_MEM8_BX_SI:
		case OPERAND_MEM8_BX_DI:
		case OPERAND_MEM8_BP_SI:
		case OPERAND_MEM8_BP_DI:
		case OPERAND_MEM8_SI:
		case OPERAND_MEM8_DI:
		case OPERAND_MEM8_BX:
		case OPERAND_MEM8_BX_SI_D8:
		case OPERAND_MEM8_BX_DI_D8:
		case OPERAND_MEM8_BP_SI_D8:
		case OPERAND_MEM8_BP_DI_D8:
		case OPERAND_MEM8_SI_D8:
		case OPERAND_MEM8_DI_D8:
		case OPERAND_MEM8_BP_D8:
		case OPERAND_MEM8_BX_D8:
		case OPERAND_MEM8_BX_SI_D16:
		case OPERAND_MEM8_BX_DI_D16:
		case OPERAND_MEM8_BP_SI_D16:
		case OPERAND_MEM8_BP_DI_D16:
		case OPERAND_MEM8_SI_D16:
		case OPERAND_MEM8_DI_D16:
		case OPERAND_MEM8_BP_D16:
		case OPERAND_MEM8_BX_D16:
        result = true;
    }
    return result;
}

bool isMem16(uint8_t operand)
{
    bool result = false;
    switch (operand)
    {
		case OPERAND_MEM16_D8:
		case OPERAND_MEM16_D16:
		case OPERAND_MEM16_BX_SI:
		case OPERAND_MEM16_BX_DI:
		case OPERAND_MEM16_BP_SI:
		case OPERAND_MEM16_BP_DI:
		case OPERAND_MEM16_SI:
		case OPERAND_MEM16_DI:
		case OPERAND_MEM16_BX:
		case OPERAND_MEM16_BX_SI_D8:
		case OPERAND_MEM16_BX_DI_D8:
		case OPERAND_MEM16_BP_SI_D8:
		case OPERAND_MEM16_BP_DI_D8:
		case OPERAND_MEM16_SI_D8:
		case OPERAND_MEM16_DI_D8:
		case OPERAND_MEM16_BP_D8:
		case OPERAND_MEM16_BX_D8:
		case OPERAND_MEM16_BX_SI_D16:
		case OPERAND_MEM16_BX_DI_D16:
		case OPERAND_MEM16_BP_SI_D16:
		case OPERAND_MEM16_BP_DI_D16:
		case OPERAND_MEM16_SI_D16:
		case OPERAND_MEM16_DI_D16:
		case OPERAND_MEM16_BP_D16:
		case OPERAND_MEM16_BX_D16:
        result = true;
    }
    return result;
}


bool hasDisp(uint8_t operand)
{
    bool result = false;
    switch (operand)
    {
    case OPERAND_IMMED_8:
    case OPERAND_IMMED_16:
    case OPERAND_MEM8_D8:
    case OPERAND_MEM8_D16:
    case OPERAND_MEM8_BX_SI_D8:
    case OPERAND_MEM8_BX_DI_D8:
    case OPERAND_MEM8_BP_SI_D8:
    case OPERAND_MEM8_BP_DI_D8:
    case OPERAND_MEM8_SI_D8:
    case OPERAND_MEM8_DI_D8:
    case OPERAND_MEM8_BP_D8:
    case OPERAND_MEM8_BX_D8:
    case OPERAND_MEM8_BX_SI_D16:
    case OPERAND_MEM8_BX_DI_D16:
    case OPERAND_MEM8_BP_SI_D16:
    case OPERAND_MEM8_BP_DI_D16:
    case OPERAND_MEM8_SI_D16:
    case OPERAND_MEM8_DI_D16:
    case OPERAND_MEM8_BP_D16:
    case OPERAND_MEM8_BX_D16:
    case OPERAND_MEM16_D8:
    case OPERAND_MEM16_D16:
    case OPERAND_MEM16_BX_SI_D8:
    case OPERAND_MEM16_BX_DI_D8:
    case OPERAND_MEM16_BP_SI_D8:
    case OPERAND_MEM16_BP_DI_D8:
    case OPERAND_MEM16_SI_D8:
    case OPERAND_MEM16_DI_D8:
    case OPERAND_MEM16_BP_D8:
    case OPERAND_MEM16_BX_D8:
    case OPERAND_MEM16_BX_SI_D16:
    case OPERAND_MEM16_BX_DI_D16:
    case OPERAND_MEM16_BP_SI_D16:
    case OPERAND_MEM16_BP_DI_D16:
    case OPERAND_MEM16_SI_D16:
    case OPERAND_MEM16_DI_D16:
    case OPERAND_MEM16_BP_D16:
    case OPERAND_MEM16_BX_D16:   
    case OPERAND_JMP_8:
    case OPERAND_JMP_16:
    case OPERAND_SEG_16:
        result = true;
    }
    return result;
}

bool has8bitDisp(uint8_t operand)
{
    bool result = false;
    switch (operand)
    {
    case OPERAND_IMMED_8:
    case OPERAND_MEM8_D8:
    case OPERAND_MEM8_BX_SI_D8:
    case OPERAND_MEM8_BX_DI_D8:
    case OPERAND_MEM8_BP_SI_D8:
    case OPERAND_MEM8_BP_DI_D8:
    case OPERAND_MEM8_SI_D8:
    case OPERAND_MEM8_DI_D8:
    case OPERAND_MEM8_BP_D8:
    case OPERAND_MEM8_BX_D8:
    case OPERAND_MEM16_D8:
    case OPERAND_MEM16_BX_SI_D8:
    case OPERAND_MEM16_BX_DI_D8:
    case OPERAND_MEM16_BP_SI_D8:
    case OPERAND_MEM16_BP_DI_D8:
    case OPERAND_MEM16_SI_D8:
    case OPERAND_MEM16_DI_D8:
    case OPERAND_MEM16_BP_D8:
    case OPERAND_MEM16_BX_D8:
    case OPERAND_JMP_8:
        result = true;
    }
    return result;
}

bool has16bitDisp(uint8_t operand)
{
    bool result = false;
    switch (operand)
    {
    case OPERAND_IMMED_16:
    case OPERAND_MEM8_D16:
    case OPERAND_MEM8_BX_SI_D16:
    case OPERAND_MEM8_BX_DI_D16:
    case OPERAND_MEM8_BP_SI_D16:
    case OPERAND_MEM8_BP_DI_D16:
    case OPERAND_MEM8_SI_D16:
    case OPERAND_MEM8_DI_D16:
    case OPERAND_MEM8_BP_D16:
    case OPERAND_MEM8_BX_D16:
    case OPERAND_MEM16_D16:
    case OPERAND_MEM16_BX_SI_D16:
    case OPERAND_MEM16_BX_DI_D16:
    case OPERAND_MEM16_BP_SI_D16:
    case OPERAND_MEM16_BP_DI_D16:
    case OPERAND_MEM16_SI_D16:
    case OPERAND_MEM16_DI_D16:
    case OPERAND_MEM16_BP_D16:
    case OPERAND_MEM16_BX_D16:
    case OPERAND_SEG_16:
    case OPERAND_JMP_16:
        result = true;
    }
    return result;
}


const char * OPERAND_REG[] = 
{
"",
"",
"",
"AL",
"CL",
"DL",
"BL",
"AH",
"CH",
"DH",
"BH",
"AX",
"CX",
"DX",
"BX",
"SP",
"BP",
"SI",
"DI",
"",
"",
"BX + SI",
"BX + DI",
"BP + SI",
"BP + DI",
"SI",
"DI",
"BX",
"BX + SI",
"BX + DI",
"BP + SI",
"BP + DI",
"SI",
"DI",
"BP",
"BX",
"BX + SI",
"BX + DI",
"BP + SI",
"BP + DI",
"SI",
"DI",
"BP",
"BX",
"",
"",
"BX + SI",
"BX + DI",
"BP + SI",
"BP + DI",
"SI",
"DI",
"BX",
"BX + SI",
"BX + DI",
"BP + SI",
"BP + DI",
"SI",
"DI",
"BP",
"BX",
"BX + SI",
"BX + DI",
"BP + SI",
"BP + DI",
"SI",
"DI",
"BP",
"BX",
"CS",
"DS",
"ES",
"SS",
"",
"",
"",
"ERROR",
};

#endif
