#!/bin/bash

#tested with gcc and clang-15 on linux
CC=gcc
mkdir -p test
$CC -g -O3 -Wall -Werror -pedantic -std=c11 src/main.c -o test/sim8086
$CC -g -O3 -Wall -Werror -pedantic -std=c11 src/main.c -DMODE_8080 -o test/sim8080

test/sim8086 decode perfaware/part1/listing_0037_single_register_mov > test/test_0037.asm
nasm test/test_0037.asm
diff perfaware/part1/listing_0037_single_register_mov test/test_0037 || exit 1

test/sim8086 decode perfaware/part1/listing_0038_many_register_mov > test/test_0038.asm
nasm test/test_0038.asm
diff perfaware/part1/listing_0038_many_register_mov test/test_0038 || exit 1

test/sim8086 decode perfaware/part1/listing_0039_more_movs > test/test_0039.asm
nasm test/test_0039.asm
diff perfaware/part1/listing_0039_more_movs test/test_0039 || exit 1

test/sim8086 decode perfaware/part1/listing_0040_challenge_movs > test/test_0040.asm
nasm test/test_0040.asm
diff perfaware/part1/listing_0040_challenge_movs test/test_0040 || exit 1

test/sim8086 decode perfaware/part1/listing_0041_add_sub_cmp_jnz > test/test_0041.asm
nasm test/test_0041.asm
diff perfaware/part1/listing_0041_add_sub_cmp_jnz test/test_0041 || exit 1

test/sim8086 decode perfaware/part1/listing_0042_completionist_decode > test/test_0042.asm
nasm test/test_0042.asm
diff perfaware/part1/listing_0042_completionist_decode test/test_0042 || exit 1

test/sim8086 decode perfaware/part1/listing_0043_immediate_movs > test/test_0043.asm
nasm test/test_0043.asm
diff perfaware/part1/listing_0043_immediate_movs test/test_0043 || exit 1

#test/sim8086 exec perfaware/part1/listing_0043_immediate_movs

test/sim8086 decode perfaware/part1/listing_0044_register_movs > test/test_0044.asm
nasm test/test_0044.asm
diff perfaware/part1/listing_0044_register_movs test/test_0044 || exit 1

#test/sim8086 exec perfaware/part1/listing_0044_register_movs

test/sim8086 decode perfaware/part1/listing_0045_challenge_register_movs > test/test_0045.asm
nasm test/test_0045.asm
diff perfaware/part1/listing_0045_challenge_register_movs test/test_0045 || exit 1

#test/sim8086 exec perfaware/part1/listing_0045_challenge_register_movs

test/sim8086 decode perfaware/part1/listing_0046_add_sub_cmp > test/test_0046.asm
nasm test/test_0046.asm
diff perfaware/part1/listing_0046_add_sub_cmp test/test_0046 || exit 1

#test/sim8086 exec perfaware/part1/listing_0046_add_sub_cmp

test/sim8086 decode perfaware/part1/listing_0047_challenge_flags > test/test_0047.asm
nasm test/test_0047.asm
diff perfaware/part1/listing_0047_challenge_flags test/test_0047 || exit 1

#test/sim8086 exec perfaware/part1/listing_0047_challenge_flags

test/sim8086 decode perfaware/part1/listing_0048_ip_register > test/test_0048.asm
nasm test/test_0048.asm
diff perfaware/part1/listing_0048_ip_register test/test_0048 || exit 1

#test/sim8086 exec perfaware/part1/listing_0048_ip_register

test/sim8086 decode perfaware/part1/listing_0049_conditional_jumps > test/test_0049.asm
nasm test/test_0049.asm
diff perfaware/part1/listing_0049_conditional_jumps test/test_0049 || exit 1

#test/sim8086 exec perfaware/part1/listing_0049_conditional_jumps

test/sim8086 decode perfaware/part1/listing_0050_challenge_jumps > test/test_0050.asm
nasm test/test_0050.asm
diff perfaware/part1/listing_0050_challenge_jumps test/test_0050 || exit 1

#test/sim8086 exec perfaware/part1/listing_0050_challenge_jumps

test/sim8086 decode perfaware/part1/listing_0051_memory_mov > test/test_0051.asm
nasm test/test_0051.asm
diff perfaware/part1/listing_0051_memory_mov test/test_0051 || exit 1

#test/sim8086 exec perfaware/part1/listing_0051_memory_mov

test/sim8086 decode perfaware/part1/listing_0052_memory_add_loop > test/test_0052.asm
nasm test/test_0052.asm
diff perfaware/part1/listing_0052_memory_add_loop test/test_0052 || exit 1

#test/sim8086 exec perfaware/part1/listing_0052_memory_add_loop

test/sim8086 decode perfaware/part1/listing_0053_add_loop_challenge > test/test_0053.asm
nasm test/test_0053.asm
diff perfaware/part1/listing_0053_add_loop_challenge test/test_0053 || exit 1

#test/sim8086 exec perfaware/part1/listing_0053_add_loop_challenge

test/sim8086 decode perfaware/part1/listing_0054_draw_rectangle > test/test_0054.asm
nasm test/test_0054.asm
diff perfaware/part1/listing_0054_draw_rectangle test/test_0054 || exit 1

#test/sim8086 exec perfaware/part1/listing_0054_draw_rectangle

test/sim8086 decode perfaware/part1/listing_0055_challenge_rectangle > test/test_0055.asm
nasm test/test_0055.asm
diff perfaware/part1/listing_0055_challenge_rectangle test/test_0055 || exit 1

#test/sim8086 exec dump perfaware/part1/listing_0055_challenge_rectangle

test/sim8086 decode perfaware/part1/listing_0056_estimating_cycles > test/test_0056.asm
nasm test/test_0056.asm
diff perfaware/part1/listing_0056_estimating_cycles test/test_0056 || exit 1

#test/sim8086 exec perfaware/part1/listing_0056_estimating_cycles
#test/sim8080 exec perfaware/part1/listing_0056_estimating_cycles

test/sim8086 decode perfaware/part1/listing_0057_challenge_cycles > test/test_0057.asm
nasm test/test_0057.asm
diff perfaware/part1/listing_0057_challenge_cycles test/test_0057 || exit 1

#test/sim8086 exec perfaware/part1/listing_0057_challenge_cycles
#test/sim8080 exec perfaware/part1/listing_0057_challenge_cycles

test/sim8086 decode perfaware/part1/listing_0059_SingleScalar > test/test_0059.asm
nasm test/test_0059.asm
diff perfaware/part1/listing_0059_SingleScalar test/test_0059 || exit 1

#test/sim8086 exec perfaware/part1/listing_0059_SingleScalar
#test/sim8080 exec perfaware/part1/listing_0059_SingleScalar

test/sim8086 decode perfaware/part1/listing_0060_Unroll2Scalar > test/test_0060.asm
nasm test/test_0060.asm
diff perfaware/part1/listing_0060_Unroll2Scalar test/test_0060 || exit 1

#test/sim8086 exec perfaware/part1/listing_0060_Unroll2Scalar
#test/sim8080 exec perfaware/part1/listing_0060_Unroll2Scalar

test/sim8086 decode perfaware/part1/listing_0061_DualScalar > test/test_0061.asm
nasm test/test_0061.asm
diff perfaware/part1/listing_0061_DualScalar test/test_0061 || exit 1

#test/sim8086 exec perfaware/part1/listing_0061_DualScalar
#test/sim8080 exec perfaware/part1/listing_0061_DualScalar

test/sim8086 decode perfaware/part1/listing_0062_QuadScalar > test/test_0062.asm
nasm test/test_0062.asm
diff perfaware/part1/listing_0062_QuadScalar test/test_0062 || exit 1

#test/sim8086 exec perfaware/part1/listing_0062_QuadScalar
#test/sim8080 exec perfaware/part1/listing_0062_QuadScalar

test/sim8086 decode perfaware/part1/listing_0063_QuadScalarPtr > test/test_0063.asm
nasm test/test_0063.asm
diff perfaware/part1/listing_0063_QuadScalarPtr test/test_0063 || exit 1

#test/sim8086 exec perfaware/part1/listing_0063_QuadScalarPtr
#test/sim8080 exec perfaware/part1/listing_0063_QuadScalarPtr

test/sim8086 decode perfaware/part1/listing_0064_TreeScalarPtr > test/test_0064.asm
nasm test/test_0064.asm
diff perfaware/part1/listing_0064_TreeScalarPtr test/test_0064 || exit 1

test/sim8086 exec perfaware/part1/listing_0064_TreeScalarPtr
#test/sim8080 exec perfaware/part1/listing_0064_TreeScalarPtr

