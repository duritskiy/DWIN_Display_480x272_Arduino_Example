#ifndef dgus_Widgeth
#define dgus_Widgeth

#include "Arduino.h"
#include "DGUS_T5LProtocol.h"

template <class VPClass,class SPClass>
class idgusWidget
{
public:

  uint16_t VP;
  uint16_t VP_Data_Size;
  union
  {
      VPClass VP_Data;
      union
      {
          // uint16_t uint16;
          // uint32_t uint32;
          int16_t  int16[sizeof(VPClass)/sizeof(int16_t)];
          int32_t  int32[sizeof(VPClass)/sizeof(int32_t)];
          // char *String;
          char String[sizeof(VPClass)];
      } VP_DataAs;
  };
  
  uint16_t SP;
  union
  {
      SPClass *SP_Data_p;
      union
      {
          uint16_t *uint16;
          int16_t *int16;
      } SP_DataAs;
  };

  DwinT5LProtocol &dgus;   
  

  private:
  
  template <class T>
  void   Free(T& ptr) 
  { 
    
    if(ptr) 
    {
      delete ptr;
      ptr = 0;
    }
  }

public:

  // size_t VP_Data_Size { return sizeof(VPClass); }
  size_t SP_Data_Size() { return sizeof(SPClass); }
  // void VP_Data_Free() { Free(VP_Data); }
  void SP_Data_Free() { Free(SP_Data_p); }


private:

template <class T>
bool Read_RAM(uint16_t Adr, T *Data) //Data is pointer to object
  {
      size_t size = sizeof(T);
      TAnswer0x83 *Answer0x83;

      if (Adr != 0xFFFF && Adr != 0 && (Answer0x83 = dgus.Read_VPs(Adr, size / 2)))
      {
          memcpy(Data, Answer0x83->VPData_BigEndian, Answer0x83->VPCount * 2);
          return 1;
    }
    return 0;
  }

	template <class T>
	bool Write_RAM(uint16_t Adr, T *Data)
  {
    if(Adr!=0xFFFF && Adr!=0 && dgus.Write_VPs(Adr, (uint8_t*)Data, sizeof(T)))  return 1;
    else                                                                         return 0;
  }

public:	
  bool SP_Read(void)
  {
      if (!SP_Data_p) SP_Data_p = new SPClass;
			return Read_RAM(SP, SP_Data_p);
  }
  bool VP_Read(void)
  {
			return Read_RAM(VP, &VP_Data);
  }
	
  bool SP_Write(void)
  {
      if (SP_Data_p == 0) return 0;
      return Write_RAM(SP, SP_Data_p);
  }
	
	bool VP_Write()
  {
		return Write_RAM(VP, &VP_Data);
  }


  idgusWidget(DwinT5LProtocol &_dgus, uint16_t _VP, uint16_t _SP):
	VP(_VP),
  VP_Data_Size(sizeof(VPClass)),
	// VP_Data(0),
	SP(_SP),
	SP_Data_p(0),
  dgus(_dgus)
	{
    memset(&VP_Data,0,VP_Data_Size);
	}
	
};


#endif