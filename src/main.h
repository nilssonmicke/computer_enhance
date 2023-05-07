#ifndef MAIN_H
#define MAIN_H

#define STATIC_ASSERT(COND,MSG) typedef char static_assertion_##MSG[(COND)?1:-1]

#include "binary.h"
#include <stdint.h>
#include <stdbool.h>

#define LEFT  0
#define RIGHT 1

#define SIZE_8 0
#define SIZE_16 1

#define REG_RIGHT 0
#define REG_LEFT 1

#define FLAG_ZERO             BIN(00000001)
#define FLAG_SIGN             BIN(00000010)
#define FLAG_OVERFLOW         BIN(00000100)
#define FLAG_CARRY            BIN(00001000)
#define FLAG_PARITY           BIN(00010000)
#define FLAG_AUXILIARY_CARRY  BIN(00100000)

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

// Attribute flags 
// LOCK, REP, X, X, DS, SS, ES, CS 
#define LOCK_ATTR  BIN(10000000)
#define REP_ATTR   BIN(01000000)
#define DS_ATTR    BIN(00001000)
#define SS_ATTR    BIN(00000100)
#define ES_ATTR    BIN(00000010)
#define CS_ATTR    BIN(00000001)

union Instruction
{
    struct
    {
        u8 mnemonic;
        u8 attributes;
        struct
        {
            u8 type;
          	u8 data_lo;
          	u8 data_hi;
        } op[2];
    };
    u64 bytecode;
};

typedef union Instruction Instruction;

STATIC_ASSERT(sizeof(Instruction) == sizeof(u64), Intermidiate_bytecode_should_be_64_bits_per_instruction);

struct registers
{
	union
	{
		u16 ax;
		struct
		{
			u8 al;
			u8 ah;		
		};
	};	

	union
	{
		u16 cx;
		struct
		{
			u8 cl;
			u8 ch;		
		};
	};	

	union
	{
		u16 dx;
		struct
		{
			u8 dl;
			u8 dh;		
		};
	};

	union
	{
		u16 bx;
		struct
		{
			u8 bl;
			u8 bh;		
		};
	};

	u16 sp;
	u16 bp;
	u16 si;
	u16 di;

	u16 ds;
	u16 ss;
	u16 es;
	u16 cs;
};

extern u8 memory[1024 * 1024];
extern u8 * ip;
extern u8 * ip_end;
extern struct registers registers;
extern u8 flags;

uint8_t read_8();
void setFlag(bool condition, u8 flag);
bool getParity(u8 n);

#endif
