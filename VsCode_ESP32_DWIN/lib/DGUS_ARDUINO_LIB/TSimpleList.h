#ifndef TSimpleListH
#define TSimpleListH


#include "Arduino.h"



template <class T>
class TSimpleList
{
    public:
    T** List;
    size_t Count;
    size_t Add(T *obj)
    {
        if (List == 0)List = (T **)malloc(sizeof(T *) * (Count + 1));
        else					List = (T **)realloc(List, sizeof(T *) * (Count + 1));
        if (List) 		List[Count++] = obj;
        return Count;
    }

    T *Find(uint16_t VP)
    {
        // T *res(0);

        // debug_printf("VP=%04X  Count=%d\n", VP,Count);
        for (size_t i = 0; i < Count; i++)
        {
            // debug_printf("List[i]->VP=%04X\n", List[i]->VP);
            if (List[i]->VP == VP) 
            {
                // debug_printf("List[%d]->VP==%04X\n",i, List[i]->VP);
                return List[i];
            }
        }
        // debug_printf("return 0;\n");
        return (T*) 0;
    }

    TSimpleList():
    List(0),
    Count(0)
    {};
};



#endif