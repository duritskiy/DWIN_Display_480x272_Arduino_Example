#ifndef dgus_debugH
#define dgus_debugH

#include "Arduino.h"

#define debug_printf Serial.printf

void PrintHex(const uint8_t *Data, size_t Size, size_t Columns=16);


#endif