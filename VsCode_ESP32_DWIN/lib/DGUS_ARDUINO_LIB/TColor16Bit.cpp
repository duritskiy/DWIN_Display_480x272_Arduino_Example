
#include "display/TColor16Bit.h"

    //max color value is 255    
    uint16_t RGB24to16(uint8_t _red, uint8_t _green, uint8_t _blue)
    {
        return  (((31*((uint16_t)_red+4))/255)<<11) |
        				(((63*((uint16_t)_green+2))/255)<<5) |
        				((31*((uint16_t)_blue+4))/255);

        // uint8_t Red = (31 * ((uint16_t)_red + 4)) / 255;
        // uint8_t Green = (63 * ((uint16_t)_green + 2)) / 255;
        // uint8_t Blue = (31 * ((uint16_t)_blue + 4)) / 255;
        // return RGB(Red, Green, Blue);
    }
