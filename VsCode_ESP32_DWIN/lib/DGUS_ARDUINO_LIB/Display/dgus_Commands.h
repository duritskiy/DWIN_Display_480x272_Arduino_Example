#ifndef dgus_CommandsH
#define dgus_CommandsH


#include "Arduino.h"
#include "display/dgus_display.h"
#include "utils/dtostrf.h"
#include "utils/swap_endian.h"
// #include "idgusWidget.h"


#include "DGUS_T5LProtocol.h"


// typedef void(*TFuncU16)(uint16_t _Param);
// typedef void(*TFuncText)(char*   _Param);





class dgus_Commands  
{
public:
  // idgusWidgetCMD<VPType, void> Regs;
  DwinT5LProtocol &dgus;
  uint16_t VP;
  dgusCallBackFunc *Func;

  dgus_Commands(DwinT5LProtocol &_dgus, uint16_t _VP, dgusCallBackFunc *_Func ):
    dgus(_dgus),
    VP(_VP),
    Func(_Func)
    {
        dgus.ListCallBackFunc.Add(this);
    }

  // dgus_Commands(DwinT5LProtocol &_dgus, uint16_t _VP ):
  //   dgus(_dgus),
  //   VP(_VP)
    
  //   {
        
  //   }


public:

};




// template <class T>
// class TSimpleList
// {
//     public:
//     T** List;
//     size_t Count;
//     size_t Add(T *obj)
//     {
//         if (List == 0)List = (T **)malloc(sizeof(T *) * (Count + 1));
//         else					List = (T **)realloc(List, sizeof(T *) * (Count + 1));
//         if (List) 		List[Count++] = obj;
//         return Count;
//     }

//     T *Find(uint16_t VP)
//     {
//         T *res(0);

//         debug_printf("VP=%04X  Count=%d\n", VP,Count);
//         for (size_t i = 0; i < Count; i++)
//         {
//             debug_printf("List[i]->VP=%04X\n", List[i]->VP);
//             // if (List[i]->VP == VP) 
//             {
//                 debug_printf("List[%d]->VP==%04X\n",i, List[i]->VP);
//                 // return List[i];
//             }
//         }
//         return res;
//     }

//     TSimpleList():
//     List(0),
//     Count(0)
//     {};
// };



#endif