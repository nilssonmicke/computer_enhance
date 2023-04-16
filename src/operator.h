#ifndef OPERATOR_H
#define OPERATOR_H

#include "main.h"

#define OPERATOR_UNK    0x00
#define OPERATOR_AAA    0x01
#define OPERATOR_AAD    0x02
#define OPERATOR_AAM    0x03
#define OPERATOR_AAS    0x04
#define OPERATOR_ADC    0x05
#define OPERATOR_ADD    0x06
#define OPERATOR_AND    0x07
#define OPERATOR_CALL   0x08
#define OPERATOR_CBW    0x09
#define OPERATOR_CLC    0x0A
#define OPERATOR_CLD    0x0B
#define OPERATOR_CLI    0x0C
#define OPERATOR_CMC    0x0D
#define OPERATOR_CMP    0x0E
#define OPERATOR_CMPSB  0x0F
#define OPERATOR_CMPSW  0x10
#define OPERATOR_CWD    0x11
#define OPERATOR_DAA    0x12
#define OPERATOR_DAS    0x13
#define OPERATOR_DEC    0x14
#define OPERATOR_DIV    0x15
#define OPERATOR_ESC    0x16
#define OPERATOR_HLT    0x17
#define OPERATOR_IDIV   0x18
#define OPERATOR_IMUL   0x19
#define OPERATOR_IN     0x1A
#define OPERATOR_INC    0x1B
#define OPERATOR_INT    0x1C
#define OPERATOR_INTO   0x1D
#define OPERATOR_IRET   0x1E
#define OPERATOR_JA     0x1F // JNBE
#define OPERATOR_JAE    0x20 // JNB
#define OPERATOR_JB     0x21 // JNAE
#define OPERATOR_JBE    0x22 // JNA
#define OPERATOR_JC     0x23
#define OPERATOR_JCXZ   0x24
#define OPERATOR_JE     0x25 // JZ
#define OPERATOR_JG     0x26 // JNLE
#define OPERATOR_JGE    0x27 // JNL
#define OPERATOR_JL     0x28 // JNGE
#define OPERATOR_JLE    0x29 // JNG
#define OPERATOR_JMP    0x2A
#define OPERATOR_JNC    0x2B
#define OPERATOR_JNE    0x2C // JNZ
#define OPERATOR_JNO    0x2D
#define OPERATOR_JNS    0x2E
#define OPERATOR_JNP    0x2F // JPO
#define OPERATOR_JO     0x30
#define OPERATOR_JP     0x31 // JPE
#define OPERATOR_JS     0x32
#define OPERATOR_LAHF   0x33
#define OPERATOR_LDS    0x34
#define OPERATOR_LEA    0x35
#define OPERATOR_LES    0x36
#define OPERATOR_LOCK   0x37
#define OPERATOR_LODSB  0x38
#define OPERATOR_LODSW  0x39
#define OPERATOR_LOOP   0x3A
#define OPERATOR_LOOPE  0x3B // LOOPZ
#define OPERATOR_LOOPNZ 0x3C // LOOPNE
#define OPERATOR_MOV    0x3D
#define OPERATOR_MOVSB  0x3E
#define OPERATOR_MOVSW  0x3F
#define OPERATOR_MUL    0x40
#define OPERATOR_NEG    0x41
#define OPERATOR_NOP    0x42
#define OPERATOR_NOT    0x43
#define OPERATOR_OR     0x44
#define OPERATOR_OUT    0x45
#define OPERATOR_POP    0x46
#define OPERATOR_POPF   0x47
#define OPERATOR_PUSH   0x48
#define OPERATOR_PUSHF  0x49
#define OPERATOR_RCL    0x4A
#define OPERATOR_RCR    0x4B
#define OPERATOR_REP    0x4C // REPE / REPZ
#define OPERATOR_REPNE  0x4D
#define OPERATOR_RET    0x4E
#define OPERATOR_ROL    0x4F
#define OPERATOR_ROR    0x50
#define OPERATOR_SAHF   0x51
#define OPERATOR_SAL    0x52 // SHL
#define OPERATOR_SAR    0x53
#define OPERATOR_SBB    0x54
#define OPERATOR_SCASB  0x55
#define OPERATOR_SCASW  0x56
#define OPERATOR_SHR    0x57
#define OPERATOR_STC    0x58
#define OPERATOR_STD    0x59
#define OPERATOR_STI    0x5A
#define OPERATOR_STOSB  0x5B
#define OPERATOR_STOSW  0x5C
#define OPERATOR_SUB    0x5D
#define OPERATOR_TEST   0x5E
#define OPERATOR_WAIT   0x5F
#define OPERATOR_XCHG   0x60
#define OPERATOR_XLAT   0x61 // XLATB
#define OPERATOR_XOR    0x62
#define OPERATOR_ES     0x63
#define OPERATOR_CS     0x64
#define OPERATOR_SS     0x65
#define OPERATOR_DS     0x66
#define OPERATOR_INT3   0x67
#define OPERATOR_RETF   0x68
#define OPERATOR_CALLF  0x69
#define OPERATOR_JMPF   0x6A


const char * MNEMONIC[0x6B] = 
{
    "UNK","AAA","AAD","AAM","AAS","ADC","ADD","AND","CALL","CBW","CLC","CLD",
    "CLI","CMC","CMP","CMPSB","CMPSW","CWD","DAA","DAS","DEC","DIV","ESC",
    "HLT","IDIV","IMUL","IN","INC","INT","INTO","IRET","JA","JAE","JB","JBE",
    "JC","JCXZ","JE","JG","JGE","JL","JLE","JMP","JNC","JNE","JNO","JNS",
    "JNP","JO","JP","JS","LAHF","LDS","LEA","LES","LOCK","LODSB","LODSW",
    "LOOP","LOOPE","LOOPNZ","MOV","MOVSB","MOVSW","MUL","NEG","NOP","NOT",
    "OR","OUT","POP","POPF","PUSH","PUSHF","RCL","RCR","REP","REPNE","RET",
    "ROL","ROR","SAHF","SAL","SAR","SBB","SCASB","SCASW","SHR","STC","STD",
    "STI","STOSB","STOSW","SUB","TEST","WAIT","XCHG","XLAT","XOR","ES",
    "CS","SS","DS","INT3","RETF","CALL FAR", "JMP FAR"
};

bool isSegment(u8 opcode)
{
    bool result = false;
    switch (opcode)
    {
    	case OPERATOR_ES:
    	case OPERATOR_CS:
    	case OPERATOR_SS:
    	case OPERATOR_DS:
        	result = true;
    }
    return result;
}

#endif

