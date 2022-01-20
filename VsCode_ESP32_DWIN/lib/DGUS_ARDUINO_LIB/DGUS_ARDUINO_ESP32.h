#ifndef DGUS_ARDUINO_ESP32H
#define DGUS_ARDUINO_ESP32H

#include <Arduino.h>


#define countof(obj) (sizeof(obj) / sizeof(obj[0]))


#include "Arduino.h"
#include "DGUS_T5LProtocol.h"
#include "dgus_types.h"


// #ifndef RS485_BUFFER_SIZE
//     #define RS485_BUFFER_SIZE   250
// #endif

#define RS485_WAIT_FOR_ANSWER_MICROS 30000

#pragma pack(push,1) //выравнивание до байта 
// template <int RS485_BUFFER_SIZE> 
class DWIN_RS485_ESP32: public DwinT5LProtocol
{
    private:
    unsigned long baud;
    uint8_t PIN_DE_EN;
    public:
    HardwareSerial *Serialport;
    uint32_t WaitForAnswerMicros;
    
       DWIN_RS485_ESP32(uint16_t _ID, HardwareSerial *_Serialport, unsigned long _baud, uint8_t const _PIN_DE_EN, bool crc_en, uint8_t *__buff,uint8_t BUFFER_SIZE)
       : DwinT5LProtocol( __buff, BUFFER_SIZE, crc_en, _ID ),
       baud(_baud), 
       PIN_DE_EN(_PIN_DE_EN), 
       Serialport(_Serialport),
       WaitForAnswerMicros(RS485_WAIT_FOR_ANSWER_MICROS)
       {
            // Serialport->begin(baud);  
            // pinMode(this->PIN_DE_EN, OUTPUT);
            // digitalWrite(this->PIN_DE_EN, LOW);   

            // PacketCmd.PacketNumber=ID;
       }

       template <class T> 
       DWIN_RS485_ESP32(uint16_t _ID, HardwareSerial *_Serialport, unsigned long _baud, uint8_t const _PIN_DE_EN,bool crc_en, T &__buff):
       DWIN_RS485_ESP32( _ID, _Serialport, _baud,  _PIN_DE_EN, crc_en, __buff, sizeof(T))
       {}
     

    //  void Setup(uint16_t _ID,HardwareSerial *_Serialport,unsigned long _baud, uint8_t const _PIN_DE_EN)
    //  {  
    //      PRINT1LN("DWIN_RS485_ESP32::Setup()");
    //      ID=_ID;
    //      Serialport=_Serialport;
    //      baud=_baud;
    //      PIN_DE_EN=_PIN_DE_EN;
    //      Serialport->begin(baud);  
    //      WaitForRead1byteMicros=((1000000ULL*15ULL)/_baud);
    //      pinMode(this->PIN_DE_EN, OUTPUT);
    //      digitalWrite(this->PIN_DE_EN, LOW);        
    //     //  TMyCommandProtocolSetup( RS485_WAIT_FOR_ANSWER_MICROS,__buffTx, __buffRx, RS485_BUFFER_SIZE,  RS485_BUFFER_SIZE);
    //  }

     uint8_t GetID(void) {return ID;}
     void SetID(uint16_t _ID) { ID=_ID;}


     void begin(void)
     {
      //  Serialport->begin(baud); 
      //  pinMode(this->PIN_DE_EN, OUTPUT);
      //  digitalWrite(this->PIN_DE_EN, LOW);   
        //  Setup(ID,Serialport,baud,PIN_DE_EN);
     }
     
     bool IsOpen(void){ return true ;}

     private:

       void EnableTX(void) 
       {
           digitalWrite(this->PIN_DE_EN, HIGH);
           delayMicroseconds(1000);
       }

       void EnableRX(void) 
       {
          delayMicroseconds(1000);
          digitalWrite(PIN_DE_EN, LOW); 
       }

       int16_t available_rx() { return Serialport->available() ; }

     void FlushRxBuffer()
        {
            // while ( available_rx() ) Serialport->read();     
            #ifdef DWIN_DEBUG
                debug_printf("FlushRxBuffer: ");
                while ( available_rx() ) debug_printf("%02X ", Serialport->read() );   
                debug_printf("\n");
            #else
                while ( available_rx() )  Serialport->read() ;   
            #endif
        }

       uint8_t read(uint8_t *buf, uint8_t len) 
       {    
           unsigned long us= micros(); 
           int8_t cnt=0;

           do
           {
               while (available_rx() && cnt < len )
               {
                   ((uint8_t *)buf)[cnt++] = Serialport->read();
                   us = micros();
               }
            }
            while( (micros() - us < WaitForAnswerMicros  )  && cnt < len );
            
           // FlushRxBuffer();
           
          return cnt; 
       }
 
      uint8_t write(const uint8_t *buf, uint8_t len) 
      { 
          int8_t result=Serialport->write((uint8_t*)buf, len); 
          //EnableRX();
          return result;
            
      }


};


#pragma pack(pop)








#endif