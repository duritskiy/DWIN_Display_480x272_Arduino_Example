#ifndef TColor16BitH
#define TColor16BitH

#include "Arduino.h"

#define RGB(r,g,b)          ((uint32_t)(((uint8_t)(r)|((uint16_t)((uint8_t)(g))<<8))|(((uint32_t)(uint8_t)(b))<<16)))


/* some RGB color definitions                                                 */
#define COLOR16_Black           0x0000      /*   0,   0,   0 */
#define COLOR16_Navy            0x000F      /*   0,   0, 128 */
#define COLOR16_DarkGreen       0x03E0      /*   0, 128,   0 */
#define COLOR16_DarkCyan        0x03EF      /*   0, 128, 128 */
#define COLOR16_Maroon          0x7800      /* 128,   0,   0 */
#define COLOR16_Purple          0x780F      /* 128,   0, 128 */
#define COLOR16_Olive           0x7BE0      /* 128, 128,   0 */
#define COLOR16_LightGrey       0xC618      /* 192, 192, 192 */
#define COLOR16_DarkGrey        0x7BEF      /* 128, 128, 128 */
#define COLOR16_Blue            0x001F      /*   0,   0, 255 */
#define COLOR16_Green           0x07E0      /*   0, 255,   0 */
#define COLOR16_Cyan            0x07FF      /*   0, 255, 255 */
#define COLOR16_Red             0xF800      /* 255,   0,   0 */
#define COLOR16_Magenta         0xF81F      /* 255,   0, 255 */
#define COLOR16_Yellow          0xFFE0      /* 255, 255,   0 */
#define COLOR16_White           0xFFFF      /* 255, 255, 255 */
#define COLOR16_Orange          0xFD20      /* 255, 165,   0 */
#define COLOR16_GreenYellow     0xAFE5      /* 173, 255,  47 */
#define COLOR16_Pink            0xF81F


//max color value is 255
uint16_t RGB24to16(uint8_t _red, uint8_t _green, uint8_t _blue);

class TColor16
{
  public:

// /* some RGB color definitions        */
//     enum
//     {
//         Black=0x0000,       /*   0,   0,   0 */
//         Navy=0x000F,        /*   0,   0, 128 */
//         DarkGreen=0x03E0,   /*   0, 128,   0 */
//         DarkCyan= 0x03EF,    /*   0, 128, 128 */
//         Maroon=0x7800,      /* 128,   0,   0 */
//         Purple=0x780F,      /* 128,   0, 128 */
//         Olive=0x7BE0,       /* 128, 128,   0 */
//         LightGrey=0xC618,   /* 192, 192, 192 */
//         DarkGrey=0x7BEF,    /* 128, 128, 128 */
//         Blue=0x001F  ,      /*   0,   0, 255 */
//         Green=0x07E0 ,      /*   0, 255,   0 */
//         Cyan=0x07FF   ,     /*   0, 255, 255 */
//         Red=0xF800     ,    /* 255,   0,   0 */
//         Magenta=0xF81F  ,   /* 255,   0, 255 */
//         Yellow=0xFFE0   ,   /* 255, 255,   0 */
//         White=0xFFFF    ,   /* 255, 255, 255 */
//         Orange=0xFD20   ,   /* 255, 165,   0 */
//         GreenYellow =0xAFE5, /* 173, 255,  47 */
//         Pink=0xF81F
//     };

    union
    {
        uint16_t Color16;
        struct
        {
            // Max Red is 31
            unsigned int RedChannel : 5;
            // Max Green is 63
            unsigned int GreenChannel : 6;
            // Max Blue is 31
            unsigned int BlueChannel : 5;
        };
    };

    // max color value is 255
    uint16_t SetAsRGB24(uint8_t _red, uint8_t _green, uint8_t _blue)
    {
        Color16=(((31*((uint16_t)_red+4))/255)<<11) |
        		(((63*((uint16_t)_green+2))/255)<<5) |
        		((31*((uint16_t)_blue+4))/255);

        return Color16;

        //  RedChannel = (31 * ((uint16_t)_red + 4)) / 255;
        //  GreenChannel = (63 * ((uint16_t)_green + 2)) / 255;
        //  BlueChannel = (31 * ((uint16_t)_blue + 4)) / 255;
        // return Color16;
    }

    uint32_t GetAsRGB24(void)
    {
				uint8_t r  = (RedChannel * 255) / 31  ;
				uint8_t g  = (GreenChannel * 255) / 63  ;
				uint8_t b  = (BlueChannel * 255) / 31  ;
                return RGB(r, g, b);
    }


};





#endif