#include "fun.h"

//16 registros de 8 bits V0 al VF
uint8_t V0, V1, V2, V3, V4, V5, V6, V7, V8, V9, VA, VB, VC, VD, VE, VF;

//registro indice de 16 bits
uint16_t I;

//Stack de 64 bytes con stack pointer de 8 bits, almacena direcciones de 16 bits

uint16_t stack[64];
uint8_t stckPtr;

//RAM 4KB, cada instruccion es de 2 bytes,
//se carga 1 byte por indice, se accede con el indice a la posicion de memoria
uint8_t RAM[4096];


int main(int argc, char *argv[])
{

	int ROMsize = loadROM();

	for (int c = 0; c < ROMsize; c++)
	{
		printf("%02X ", RAM[c]);
	}

	printf("\nSize of the ROM loaded: %d bytes\n", ROMsize);
	printf("\nSuccess! :)\n");

	return 0;
}
