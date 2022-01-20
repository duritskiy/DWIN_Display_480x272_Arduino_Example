#ifndef dtostrfH
#define dtostrfH

// #include <stdio.h>
// #include <stdlib.h>
// #include <stdint.h>
// #include <string.h>
#include <arduino.h>

char *_dtostrf(double val, signed char width, unsigned char prec, char *sout);

#endif