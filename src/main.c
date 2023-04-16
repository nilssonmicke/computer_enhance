#include "main.h"
#include "operator.h"
#include "operand.h"
#include "decoder.h"
#include "print.h"
#include "sim.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

u8 memory[1024 * 1024] = {0};
u8 * ip = memory;
u8 * ip_end = &memory[1024 * 1024];
struct registers registers = {0};
u8 flags = 0;

uint8_t read_8()
{
  if(ip >= ip_end)
    exit(-1);
  return *(ip++);
}

void setFlag(bool condition, u8 flag)
{
  if(condition)
    flags |= flag;
  else 
    flags &= ~flag;
}

bool getParity(u8 n)
{
    bool parity = true;
    while (n)
    {
        parity = !parity;
        n = n & (n - 1);
    }    
    return parity;
}

#include "decoder.c"
#include "print.c"
#include "sim.c"

int main(int argc, char **argv)
{
  if(argc != 3)
  {
    printf("Invalid number of args, use sim8086 <mode> <filename>\n");
    return -1;
  }

  FILE * file = fopen(argv[2], "r");
  assert(file);
      
  const size_t rsize = fread(ip, 1, 1024 * 1024, file);
  ip_end = &ip[rsize];
  fclose(file);

  if(strcmp(argv[1], "exec") == 0)
  	exec_all(argv[2]);
  else
	  print_all(argv[2]);
  return 0;
}
