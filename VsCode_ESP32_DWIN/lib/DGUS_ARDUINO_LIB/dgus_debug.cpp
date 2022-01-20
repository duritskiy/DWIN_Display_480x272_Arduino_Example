#include "Utils\dgus_debug.h"

void PrintHex(const uint8_t *Data, size_t Size, size_t Columns)
{
// for (int i = 0; i < Size;i++) debug_printf("%02X ", Data[i]);

    for (int i = 0; i < Size; i++) 
		{
			if(i%Columns==0 && i)  debug_printf("\n");
			debug_printf("%02X ", Data[i]);
		}


}
