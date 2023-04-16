#!/bin/bash

#tested with gcc and clang-15 on linux
CC=gcc
mkdir -p test
$CC -g -O3 -Wall -Werror -pedantic -std=c11 src/main.c -o test/sim8086

test/sim8086 decode perfaware/part1/listing_0037_single_register_mov > test/test_0037.asm
nasm test/test_0037.asm
diff perfaware/part1/listing_0037_single_register_mov test/test_0037

test/sim8086 decode perfaware/part1/listing_0038_many_register_mov > test/test_0038.asm
nasm test/test_0038.asm
diff perfaware/part1/listing_0038_many_register_mov test/test_0038

test/sim8086 decode perfaware/part1/listing_0039_more_movs > test/test_0039.asm
nasm test/test_0039.asm
diff perfaware/part1/listing_0039_more_movs test/test_0039

test/sim8086 decode perfaware/part1/listing_0040_challenge_movs > test/test_0040.asm
nasm test/test_0040.asm
diff perfaware/part1/listing_0040_challenge_movs test/test_0040

test/sim8086 decode perfaware/part1/listing_0041_add_sub_cmp_jnz > test/test_0041.asm
nasm test/test_0041.asm
diff perfaware/part1/listing_0041_add_sub_cmp_jnz test/test_0041

#test/sim8086 perfaware/part1/listing_0042_completionist_decode > test/test_0042.asm
#nasm test/test_0042.asm
#diff perfaware/part1/listing_0042_completionist_decode test/test_0042

test/sim8086 decode perfaware/part1/listing_0043_immediate_movs > test/test_0043.asm
nasm test/test_0043.asm
diff perfaware/part1/listing_0043_immediate_movs test/test_0043

test/sim8086 exec perfaware/part1/listing_0043_immediate_movs

test/sim8086 decode perfaware/part1/listing_0044_register_movs > test/test_0044.asm
nasm test/test_0044.asm
diff perfaware/part1/listing_0044_register_movs test/test_0044

test/sim8086 exec perfaware/part1/listing_0044_register_movs

test/sim8086 decode perfaware/part1/listing_0045_challenge_register_movs > test/test_0045.asm
nasm test/test_0045.asm
diff perfaware/part1/listing_0045_challenge_register_movs test/test_0045

test/sim8086 exec perfaware/part1/listing_0045_challenge_register_movs

test/sim8086 decode perfaware/part1/listing_0046_add_sub_cmp > test/test_0046.asm
nasm test/test_0046.asm
diff perfaware/part1/listing_0046_add_sub_cmp test/test_0046

test/sim8086 exec perfaware/part1/listing_0046_add_sub_cmp

test/sim8086 decode perfaware/part1/listing_0047_challenge_flags > test/test_0047.asm
nasm test/test_0047.asm
diff perfaware/part1/listing_0047_challenge_flags test/test_0047

test/sim8086 exec perfaware/part1/listing_0047_challenge_flags

test/sim8086 decode perfaware/part1/listing_0048_ip_register > test/test_0048.asm
nasm test/test_0048.asm
diff perfaware/part1/listing_0048_ip_register test/test_0048

test/sim8086 exec perfaware/part1/listing_0048_ip_register

test/sim8086 decode perfaware/part1/listing_0049_conditional_jumps > test/test_0049.asm
nasm test/test_0049.asm
diff perfaware/part1/listing_0049_conditional_jumps test/test_0049

test/sim8086 exec perfaware/part1/listing_0049_conditional_jumps

test/sim8086 decode perfaware/part1/listing_0050_challenge_jumps > test/test_0050.asm
nasm test/test_0050.asm
diff perfaware/part1/listing_0050_challenge_jumps test/test_0050

test/sim8086 exec perfaware/part1/listing_0050_challenge_jumps

#test/sim8086 data/test > test/test.asm
#nasm test/test.asm
#diff data/test test/test

