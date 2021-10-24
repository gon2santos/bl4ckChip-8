#include "stdio.h"
#include "stdlib.h"

#define uint8_t unsigned char
#define uint16_t unsigned short
#define uint32_t unsigned int

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

int main()
{
	FILE *f;
	f = fopen("ROM", "rb");

	int i = 0;

	while (1)
	{
		RAM[i] = fgetc(f);
		if (feof(f))
		{
			break;
		}
		i++;
	}

	for (int c = 0; c < i; c++)
	{
		printf("%02X ", RAM[c]);
	}
	fclose(f);

	return 0;
}
