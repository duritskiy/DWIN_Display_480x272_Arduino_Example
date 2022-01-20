#ifndef swap_endianH
#define swap_endianH

#include "Arduino.h"

// #include "stdint.h"

template < typename T>
T swap_endian(T u)
{
    // static_assert (CHAR_BIT == 8, "CHAR_BIT != 8");
    union
    {
        T u;
        unsigned char u8[sizeof(T)];
    } source, dest;
    source.u = u;
    for (size_t k = 0; k < sizeof(T); k++) dest.u8[k] = source.u8[sizeof(T) - k - 1];
    return dest.u;
}

#pragma pack(push, 1)
class   uint16_t_BigEndian 
{
  private:
  uint16_t value;

  public:
  uint16_t Get_Swaped(void)
  {
    return swap_endian(value);
  };

  void Set_Swaped(uint16_t _value)
  {
     value=swap_endian(_value);
  };

};



class  uint32_t_BigEndian
{
  private:
  uint32_t value;

  public:
  uint32_t Get_Swaped(void)
  {
    return swap_endian(value);
  };

  void Set_Swaped(uint32_t _value)
  {
     value=swap_endian(_value);
  };

};




class  int16_t_BigEndian
{
  private:
  int16_t value;

  public:
  int16_t Get_Swaped(void)
  {
    return swap_endian(value);
  };

  void Set_Swaped(int16_t _value)
  {
     value=swap_endian(_value);
  };

};



class  int32_t_BigEndian
{
  private:
  int32_t value;

  public:
  int32_t Get_Swaped(void)
  {
    return swap_endian(value);
  };

  void Set_Swaped(int32_t _value)
  {
     value=swap_endian(_value);
  };

};
#pragma pack(pop)

#endif