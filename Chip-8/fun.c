#include "fun.h"

extern uint8_t RAM[];

int loadROM(void)
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
    fclose(f);
    return i;
}