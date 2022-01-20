#ifndef dgus_display_DataVariableH
#define dgus_display_DataVariableH


#include "Arduino.h"
#include "display/dgus_display.h"
#include "utils/dtostrf.h"
#include "utils/swap_endian.h"
#include "idgusWidget.h"


#pragma pack(push, 1)
typedef struct dgus_display_DataVariable_SPData 
{

    uint16_t_BigEndian VP;
    dgus_control_position Pos;
    uint16_t_BigEndian Color;
    uint8_t Font_ID;   // Index in the FLASH memory of the ASCII Font to use.
    uint8_t Font_Width; //Font width, in pixels.
    
    /*
    0x00: Left-alignment.
    0x01: Right-alignment.
    0x02: Center- alignment.
    */
    uint8_t Alignment; 
    uint8_t Integer_Digits; //Number of digits to the left of the decimal separator.
    uint8_t Decimal_Digits; //Number of digits to the right of the decimal separator.

    /*
    Value Memory Size.
    0x00: 16-bit Integer (2 bytes). Range: -32768 ~ 32767
    0x01: 32-bit Integer (4 bytes). Range: -2147483648 ~2147483647
    0x02: 8-bit Unsigned Integer in High Byte of the VP. Range: 0 ~255
    0x03: 0x03: 8-bit Unsigned Integer in Low Byte of the VP.Range: 0 ~ 255
    0x04: 64-bit Integer (8 bytes). Range: -9223372036854775808 ~ 9223372036854775807
    0x05: 16-bit Unsigned Integer (2 bytes). Range: 0 ~ 65535
    0x06: 32-bit Unsigned Integer (4 bytes). Range: 0 ~ 4294967295
    */    
    uint8_t VP_Mode;
    uint8_t Len_unit; //Length of text to append after the digits, in characters. range 0-11.
    uint8_t String_Unit[11]; //Text to append after the digits. ASCII code.
 

    void Print(void)
    {
              debug_printf("VP=0x%04X\n",  VP.Get_Swaped() );
              debug_printf("Pos.x=%d\n",   Pos.x.Get_Swaped() );
              debug_printf("Pos.y=%d\n",   Pos.y.Get_Swaped() );
              debug_printf("Color=0x%04X\n",Color.Get_Swaped() );
              debug_printf("Font_ID=%d\n", Font_ID );
              debug_printf("Font_Width=%d\n",Font_Width );
              debug_printf("Alignment=%d\n",Alignment );
              debug_printf("Integer_Digits=%d\n",Integer_Digits );
              debug_printf("Decimal_Digits=%d\n",Decimal_Digits );
              debug_printf("VP_Mode=%d\n",VP_Mode );
              debug_printf("Len_unit=%d\n",Len_unit );
              debug_printf("String_Unit=%11s\n",String_Unit );
    }

} dgus_display_DataVariable_SPData; /**< Register layout for the text SP register */
#pragma pack(pop)


/*
sizeof(dgus_display_DataVariable_SPData) = 26bytes = 13Words = 0x0D Words
*/
template <typename VPType>
class dgus_display_DataVariable  
{
public:
  idgusWidget<VPType, dgus_display_DataVariable_SPData> Regs;

public:

  VPType Get(void) 
  {
     return swap_endian(Regs.VP_Data); 
  }

  VPType Set(VPType value) 
  { 
    Regs.VP_Data=swap_endian(value);
    return value;
  }

  bool Read()
  {
    return Regs.VP_Read();
  }

  bool Write(VPType value)
  {
        Regs.VP_Data = swap_endian(value);
        return Regs.VP_Write();
  }

  dgus_display_DataVariable(DwinT5LProtocol &_dgus, uint16_t _VP, uint16_t _SP)
  :  Regs(_dgus, _VP, _SP)
  {
      Regs.dgus.ListNum.Add((idgusWidget<uint16_t, void>*)&Regs);
  };
  ~dgus_display_DataVariable()
  {
    // Regs.VP_Data_Free();
    Regs.SP_Data_Free();
  };


};



#endif