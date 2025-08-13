#include <stdint.h>
#include <stdio.h>

volatile uint32_t* DOODLE   = (uint32_t*) 0x40000000;


uint64_t incrementer(uint32_t* var, uint32_t b){
   return (uint64_t)(var + b);
}

int main()
{
   uint64_t X = 0;
   uint32_t b = 4;
   X = incrementer(DOODLE, b);
	printf("0x%X\n", X);
   return 0;
}
