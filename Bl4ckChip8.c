#include "stdio.h"
#include "stdlib.h"

#define unsigned char uint8_t
#define unsigned short uint16_t
#define unsigned int uint32_t

//16 registros de 8 bits V0 al VF
uint8_t V0,V1,V2,V3,V4,V5,V6,V7,V8,V9,VA,VB,VC,VD,VE,VF;

//registro indice de 16 bits
uint16_t I;

//Stack de 64 bytes con stack pointer de 8 bits, almacena direcciones de 16 bits

uint16_t stack[64];
uint8_t stckPtr;

//RAM 4KB
uint8_t RAM[4096];

int main(){
	printf("%d",sizeof(idx));
		return 0;
			}
			