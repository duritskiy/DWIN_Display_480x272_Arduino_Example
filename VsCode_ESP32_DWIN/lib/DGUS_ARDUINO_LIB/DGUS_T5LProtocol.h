#ifndef DwinT5LProtocolh
#define DwinT5LProtocolh

#include "utils/dgus_debug.h"
#include "utils/swap_endian.h"
#include "TSimpleList.h"
#include <Arduino.h>

// RAM:   [          ]   4.9% (used 15940 bytes from 327680 bytes)
// Flash: [==        ]  16.8% (used 219601 bytes from 1310720 bytes)
#include "FastCRC.h"
extern FastCRC16 CRC16;
// RAM:   [          ]   4.9% (used 15956 bytes from 327680 bytes)
// Flash: [==        ]  16.8% (used 219649 bytes from 1310720 bytes)

#define CRC_ENABLE  1
#define CRC_DISABLE 0
#define COMPARE_OK  0

#ifndef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif

#ifndef MAX
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif

// #include "stdint.h"


#pragma pack(push, 1) //выравнивание до байта
struct TAnswer0x83
{
    uint16_t FrameHeader;
    uint8_t ByteCount;
    uint8_t Cmd;
    uint16_t VP;
    uint8_t VPCount;

    union
    {
        uint16_t VPData_BigEndian[];
        uint8_t Bytes[];
    };

    // void PrintWithCRC(void)
    // {
    //     // debug_printf(("rx: 0x%04X [0x%02X] 0x%02X 0x%04X: 0x%02X 0x%04X\n"),ID,ByteCount,Cmd,VP,Length,Crc);
    // }

    // void PrintWithoutCRC(void)
    // {
    //     debug_printf(("rx: 0x%04X [0x%02X] 0x%02X 0x%04X: 0x%02X\n"),ID,ByteCount,Cmd,VP,Length);
    // }
};
#pragma pack(pop)


template <class VPClass,class SPClass>
class idgusWidget;
class dgus_Commands;
typedef void(dgusCallBackFunc)(uint8_t* Data,size_t Size);


// RAM:   [          ]   4.9% (used 15924 bytes from 327680 bytes)
// RAM:   [          ]   4.9% (used 15908 bytes from 327680 bytes)
class DwinT5LProtocol //: public DGUS_VirtualDataAddress
{
  private:
    uint8_t *buff;
    uint8_t buff_Size;

  public:
    bool CRC_Enable;
    uint16_t ID;

    TSimpleList <idgusWidget<uint16_t, void>> ListText;
    TSimpleList <idgusWidget<uint16_t, void>> ListTextAsNum;
    TSimpleList <idgusWidget<uint16_t, void>> ListNum;
    TSimpleList <dgus_Commands>      ListCallBackFunc;


    unsigned long LastSendTime;
    // uint32_t WaitForAnswerMicros;
    const static int32_t DecimalCoef[10];

    // private:
    virtual int16_t available_rx()
    { 
        /*IF_MCP_SERIAL_DEBUG_ARDUINO( PRINT1LN("err: available_rx() not defined")); */
        return 0;
    };
    virtual uint8_t read(uint8_t *buf, uint8_t len)
    { 
        /*IF_MCP_SERIAL_DEBUG_ARDUINO( PRINT1LN("err: read() not defined")); */
        return 0;
    };
    virtual uint8_t write(const uint8_t *buf, uint8_t len)
    { 
        /* IF_MCP_SERIAL_DEBUG_ARDUINO( PRINT1LN("err: write() not defined")); */
        return 0;
    };
    virtual void EnableTX(void){};
    virtual void EnableRX(void){};
    virtual void FlushRxBuffer(){};
    virtual bool IsOpen(void) { return 0; };
    virtual uint8_t requestFrom(void) { return 1; }

  public:
    ///////////////

    void (*beforePoll)();
    void (*afterPoll)();
    // void (*onReceive)();
    // void (*onWrite)();
    // void (*onRead)();
    // void (*onReceive_NO_CRC)();

    bool Write_VPs(uint16_t VP, const uint8_t *data, uint8_t size);

    template <typename T> bool Write_VPs(uint16_t VP, T &obj)
    {
        uint8_t size = sizeof(T);
        return Write_VPs(VP, (uint8_t *)&obj, size);
    };


    TAnswer0x83 *Read_VPs(uint16_t VP, uint8_t WORD_Count);
    private:
    TAnswer0x83 *Read_Answer0x83(void);
    public:

    // Data is object like struct or class
    template <class T> bool Read_RAM(uint16_t Adr, T &Data)
    {
        size_t size = sizeof(Data);

        // printf("size=%d\n", sizeof(T));

        TAnswer0x83 *Answer0x83 = 0;

        if (&Data && Adr != 0xFFFF && Adr != 0 && (Answer0x83 = Read_VPs(Adr, size / 2)))
        {

            memcpy(&Data, Answer0x83->VPData_BigEndian, Answer0x83->VPCount * 2);
            return 1;
        }
        return 0;
    }

    template <typename T> bool Write_VP_16Bit(uint16_t VP, T _Value, uint8_t DecimalCount = 0)
    {
        int16_t Value = _Value * DecimalCoef[DecimalCount];
        Value = swap_endian(Value);
        return Write_VPs(VP, (uint8_t *)&Value, sizeof(int16_t));
    }

    template <typename T> bool Write_VP_32Bit(uint16_t VP, T _Value, uint8_t DecimalCount = 0)
    {
        int32_t Value = _Value * DecimalCoef[DecimalCount];
        Value = swap_endian(Value);
        return Write_VPs(VP, (uint8_t *)&Value, sizeof(int32_t));
    }

    bool Poll(void (*_beforePoll)(), void (*_afterPoll)());
    bool Poll(void) { return Poll(beforePoll, afterPoll); };

    DwinT5LProtocol(uint8_t *_buff, uint8_t _buff_Size, bool crc_Enable, uint16_t _ID)
        : 
        buff(_buff), 
        buff_Size(_buff_Size), 
        CRC_Enable(crc_Enable), 
        ID(_ID)
    {
    }

    ~DwinT5LProtocol(){};
};

#endif