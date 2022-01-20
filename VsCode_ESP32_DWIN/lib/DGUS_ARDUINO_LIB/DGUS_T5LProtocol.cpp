#include "DGUS_T5LProtocol.h"
#include "idgusWidget.h"

#include "Display\dgus_Commands.h"

FastCRC16 CRC16;

const  int32_t DwinT5LProtocol::DecimalCoef[10] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};

TAnswer0x83 *DwinT5LProtocol::Read_VPs(uint16_t VP, uint8_t VP_Count)
{
    uint8_t buf_tx[9];

    buf_tx[0] = highByte(ID);
    buf_tx[1] = lowByte(ID);
    uint8_t VP_CountMax;

    uint8_t crc_size;
    if (CRC_Enable)
        crc_size = 2;
    else
        crc_size = 0;

    buf_tx[2] = 4 + crc_size; // ByteCount
    VP_CountMax = (buff_Size - (uint8_t)4 - crc_size) / 2;

    VP_Count = MIN(VP_Count, VP_CountMax); // Number of VPs (words) to read

    buf_tx[3] = 0x83;
    buf_tx[4] = highByte(VP);
    buf_tx[5] = lowByte(VP);
    buf_tx[6] = VP_Count;

    uint16_t crc;
    if (CRC_Enable)
    {
        crc = CRC16.modbus(buf_tx + 3, sizeof(buf_tx) - 3 - 2);
        memcpy(buf_tx + 7, &crc, 2);
    }

    write(buf_tx, 7 + crc_size); // request
#ifdef DWIN_DEBUG
    debug_printf("\n\ntx: ");
    PrintHex(buf_tx, (sizeof(buf_tx) - 2) + crc_size);
    debug_printf("\n");
#endif

    LastSendTime = micros();

    uint8_t *buf_rx_OK = buf_tx;
    uint8_t Answer0x83_Size;

    buf_rx_OK[2] = VP_Count * 2 + 4 + crc_size; // ByteCount
    Answer0x83_Size = buf_rx_OK[2] + 3;

    // debug_printf("Answer0x83_Size=%d\n",Answer0x83_Size);

    TAnswer0x83 *Answer0x83 = (TAnswer0x83 *)buff;

    if (read((uint8_t *)Answer0x83, 7) == 7)
    {
#ifdef DWIN_DEBUG
        debug_printf("rx: ");
        PrintHex((uint8_t *)Answer0x83, 7);
        debug_printf("\n");
#endif

        size_t readSize = 0;
        if (memcmp(Answer0x83, buf_rx_OK, 7) == COMPARE_OK)
        {
            readSize = read((uint8_t *)Answer0x83->VPData_BigEndian, VP_Count * 2 + crc_size);

            if (CRC_Enable)
            {
                crc = CRC16.modbus((uint8_t *)Answer0x83 + 3, (uint16_t)Answer0x83_Size - 3 - 2);

								// debug_printf("crc=%04X  %04X\n",crc,Answer0x83->VPData_BigEndian[VP_Count]);

								if(crc==Answer0x83->VPData_BigEndian[VP_Count]) 
								{
									#ifdef DWIN_DEBUG
									PrintHex(Answer0x83->Bytes, readSize);
									debug_printf("CRC_OK\n");
									#endif									
								}
								else 
								{
									#ifdef DWIN_DEBUG
									PrintHex(Answer0x83->Bytes, readSize);
									debug_printf("CRC_BAD\n");
									#endif									

									FlushRxBuffer();
									return 0;
								}

            }
            else
            {
								#ifdef DWIN_DEBUG
                PrintHex(Answer0x83->Bytes, readSize);
                debug_printf("\n");
								#endif
            }

            if (readSize == VP_Count * 2 + crc_size)
            {
                Answer0x83->FrameHeader = swap_endian(Answer0x83->FrameHeader);
                Answer0x83->VP = swap_endian(Answer0x83->VP);
                return Answer0x83;
            }
        }
        else FlushRxBuffer();
    }

    return 0;
}


TAnswer0x83 *DwinT5LProtocol::Read_Answer0x83(void)
{
    uint8_t crc_size;
    if (CRC_Enable) crc_size = 2;
    else						crc_size = 0;

      TAnswer0x83 *Answer0x83 = (TAnswer0x83 *)buff;

    if (read((uint8_t *)Answer0x83, 7) == 7)
    {
#ifdef DWIN_DEBUG
        debug_printf("rx: ");
        PrintHex((uint8_t *)Answer0x83, 7);
        debug_printf("\n");
#endif

        size_t readSize = 0;
				if (Answer0x83->FrameHeader == swap_endian(ID) && Answer0x83->Cmd==0x83 )
        {
            uint8_t toReadSize = MIN(Answer0x83->VPCount * 2 + crc_size, buff_Size);

            readSize = read((uint8_t *)Answer0x83->VPData_BigEndian, toReadSize);

            if (CRC_Enable)
            {
							
               uint16_t crc = CRC16.modbus( buff + 3, Answer0x83->ByteCount-2);
								// debug_printf("crc=%04X\n",crc);
								// debug_printf("CRC=%04X\n",Answer0x83->VPData_BigEndian[Answer0x83->VPCount]);

								if(crc==Answer0x83->VPData_BigEndian[Answer0x83->VPCount]) 
								{
									#ifdef DWIN_DEBUG
									PrintHex(Answer0x83->Bytes, readSize);
									debug_printf("CRC_OK\n\n");
									#endif									
								}
								else 
								{
									#ifdef DWIN_DEBUG
									PrintHex(Answer0x83->Bytes, readSize);
									debug_printf("CRC_BAD\n\n");
									#endif									

									FlushRxBuffer();
									return 0;
								}

            }
            else
            {
								#ifdef DWIN_DEBUG
                PrintHex(Answer0x83->Bytes, readSize);
                debug_printf("\n");
								#endif
            }

            // debug_printf("readSize =%d  Answer0x83->VP*2 + crc_size=%d\n", readSize, Answer0x83->VPCount * 2 + crc_size);

            if (readSize == toReadSize)
            {
                Answer0x83->FrameHeader = swap_endian(Answer0x83->FrameHeader);
                Answer0x83->VP = swap_endian(Answer0x83->VP);
                return Answer0x83;
            }
        }
        else FlushRxBuffer();
    }

    return 0;
}



// // Compute the MODBUS RTU CRC
// uint16_t ModRTU_CRC(byte* buf, int len)
// {
//     uint16_t crc = 0xffff;
//     for (int pos = 0; pos < len; pos++)
//     {
//         // XOR byte into least sig. byte of crc
//         crc ^= (uint16_t)buf[pos];
//         for (int i = 8; i != 0; i--) // Loop over each bit
//         {
//             if ((crc & 0x0001) != 0) // If the LSB is set
//             {
//                 crc >>= 1; // shift right and XOR 0xA001
//                 crc ^= 0xA001;
//             }
//             else           // Else LSB is not set
//                 crc >>= 1; // Just shift right
//         }
//     }
//     // Swap high and low bytes
//     crc = ((crc & 0Xff00) >> 8) | ((crc & 0x00FF) << 8);
//     return crc;
// }

bool DwinT5LProtocol::Write_VPs(uint16_t VP, const uint8_t *data, uint8_t size)
    {
			if(data==0) return 0;
			
        uint8_t buf_tx[6];

        buf_tx[0] = highByte(ID);
		buf_tx[1] = lowByte(ID);

    if (CRC_Enable)   
		{
			  size=MIN(size, 255-5);
				buf_tx[2] = size+5; 		//ByteCount
		}
    else 
		{
				size=MIN(size, 255-3);
				buf_tx[2] = size+3; 		//ByteCount
		}       			

    buf_tx[3] = 0x82;
    buf_tx[4] = highByte(VP);
		buf_tx[5] = lowByte(VP);

	  write(buf_tx, 6); // preambula
		write(data, size); 

		uint16_t crc;

	  if (CRC_Enable)   
		{
            crc = CRC16.modbus(buf_tx+3, 6-3);
            crc = CRC16.modbus_upd(data, size);
            write((const uint8_t *)&crc, 2);
		}

// [10:14:36.212]->S: 5a a5 07 82 50 20 aa bb 72 07 
// tx: 								5A A5 07 82 50 20 AA BB  crc=67F2

  // uint8_t b[] = {0x5A, 0xA5 , 0x07 , 0x82 , 0x50 , 0x20 , 0xAA , 0xBB};
	// uint8_t b[] = 										 {  0x82 , 0x50 , 0x20 , 0xAA , 0xBB};

  // debug_printf("ModRTU_CRC=%04X\n",ModRTU_CRC(b, sizeof(b)));

#ifdef DWIN_DEBUG
	 			debug_printf("\n\ntx: ");
        PrintHex(buf_tx, sizeof(buf_tx));
				PrintHex(data, size);
				if (CRC_Enable) PrintHex((const uint8_t*)&crc, sizeof(crc));
				debug_printf("\n");
		#endif	

		uint8_t buf_rx[6]={0};
		const uint8_t buf_rx_OK[6]={0x5A,0xA5 ,0x03,0x82 ,0x4F ,0x4B};
		const uint8_t buf_rx_OK_crc[8]={0x5A,0xA5 ,0x05,0x82 ,0x4F ,0x4B,0xA5 ,0xEF};
			
		
	  if (CRC_Enable)   
		{
			read(buf_rx, 8); 
			if( memcmp(buf_rx,buf_rx_OK_crc,8)==COMPARE_OK ) 
			{
				#ifdef DWIN_DEBUG
					debug_printf("rx: ");
					PrintHex(((uint8_t*)&buf_rx), 8);
					debug_printf(" CRC_OK\n");
					debug_printf("\n");
				#endif	
				return 1;
			}
			else 
			{
				#ifdef DWIN_DEBUG
					debug_printf("rx: ");
					PrintHex(((uint8_t*)&buf_rx), 8);
					debug_printf(" CRC_BAD\n");
					debug_printf("\n");
				#endif	
			}
		} 
		else 
		{
			read(buf_rx, 6); 
			#ifdef DWIN_DEBUG
				debug_printf("rx: ");
				PrintHex(((uint8_t*)&buf_rx), 6);
				debug_printf("\n");
			#endif	

			if( memcmp(buf_rx,buf_rx_OK,6)==COMPARE_OK ) return 1;
		}
		
		return 0;		
}





bool DwinT5LProtocol::Poll(void (*_beforePoll)(),void (*_afterPoll)() )
{
	
  if(_beforePoll)beforePoll = _beforePoll;
  if(_afterPoll) afterPoll = _afterPoll;

  if (IsOpen()==0 || available_rx()<7 ) return 0;

  TAnswer0x83 *Answer;
	bool found = 0;

  if(Answer=Read_Answer0x83())
	{

      // if (onRead) onRead();
      // if (*onReceive_NO_CRC) onReceive_NO_CRC();
      // if (*onReceive) onReceive();
     

  if (*beforePoll) beforePoll();

  idgusWidget<uint16_t, void> *Widget = 0;
  dgus_Commands *WidgetCMD;
  

  uint16_t _Adr = Answer->VP;

  if ((Widget = ListNum.Find(_Adr)) && Widget->VP_Data_Size >= Answer->VPCount*2)
  {
      memcpy(&Widget->VP_Data, Answer->VPData_BigEndian, Answer->VPCount*2);
      found = 1;
        }
    else if ( (Widget = ListTextAsNum.Find(_Adr) )  )
		{
						// защита от пустого ввода текста
            if (Answer->VPCount == 1 && Answer->VPData_BigEndian[0] == 0xFFFF) 
						{
							memset(&Widget->VP_Data, 0,Widget->VP_Data_Size);
							strcpy((char*)&Widget->VP_Data, "0");
							Write_VPs(Widget->VP, (const uint8_t *)&Widget->VP_Data, Widget->VP_Data_Size);
						}
            else memcpy(&Widget->VP_Data, Answer->VPData_BigEndian, MIN(Answer->VPCount*2,Widget->VP_Data_Size));
						found = 1;
		}
    else if ( (Widget = ListText.Find(_Adr) ) )
		{
						memcpy(&Widget->VP_Data, Answer->VPData_BigEndian, MIN(Answer->VPCount*2,Widget->VP_Data_Size));
						found = 1;
		}

		// delay(1);
		if (  WidgetCMD=ListCallBackFunc.Find(_Adr) ) 
		{
			// debug_printf("4\n");
			WidgetCMD->Func(Answer->Bytes, Answer->VPCount*2);
			found = 1;
		}

	}

    if(found)
    {
			if (*afterPoll) afterPoll();
			return 1;		
    }
		else 
		{
			#ifdef DWIN_DEBUG
			debug_printf(("DGUS_ERR_GET_VIRTUAL_ADDRESS\n"));
			#endif
			return 0;
		}
		






	
  // if(_beforePoll)beforePoll = _beforePoll;
  // if(_afterPoll) afterPoll = _afterPoll;
  // if (IsOpen()==0 || available_rx()<7 ) return 0;

  // uint16_t crc_Size=0;
  // if (CRC_Enable) crc_Size = 2;

  // memset(buff, 0, 7);

  // uint8_t r=read(buff, 7);
	// #ifdef DWIN_DEBUG
	// 	debug_printf("\npoll:\n ");
	// 	PrintHex(buff, 7);
	// 	debug_printf("\n");
  // #endif	
		
	// uint8_t &ByteCount = buff[2];
	// uint8_t &cmd = buff[3];
  // uint16_t _ID = swap_endian (((uint16_t *)buff)[0]);
	// uint16_t _Adr = swap_endian (((uint16_t *)buff)[2]);
	// uint16_t DataLength =((uint16_t)buff[6])*2;
	// uint8_t *Data = &buff[7];

  // if (ID != _ID || cmd!=0x83 || r < 7 ) 
	// {
  //       FlushRxBuffer();
  //       return 0;
	// }

  // r = read(Data, DataLength + crc_Size);
	// #ifdef DWIN_DEBUG
	// 	PrintHex(Data, DataLength + crc_Size);
	// 	debug_printf("\n");
  // #endif	

  // if (r < DataLength + crc_Size) {FlushRxBuffer(); return 0; }
	// if(CRC_Enable)
	// {
	// 	uint16_t crc = CRC16.modbus(buff+3,  ByteCount - 2);
	// 	debug_printf("crc=%04X  %04X\n",crc, buff );
	// }

  // // if (onRead) onRead();
  // // if (*onReceive_NO_CRC) onReceive_NO_CRC();
  //   // if (*onReceive) onReceive();

  //   if (*beforePoll) beforePoll();

  //   idgusWidget<uint16_t, void> *Widget=0 ;
	// 	dgus_Commands *WidgetCMD;
  //   bool found = 0;
		
  //   if ( (Widget = ListNum.Find(_Adr) ) && Widget->VP_Data_Size>=DataLength )
	// 	{
  //           memcpy(&Widget->VP_Data, Data, DataLength);
  //           found = 1;
  //       }
  //   else if ( (Widget = ListTextAsNum.Find(_Adr) )  )
	// 	{
	// 					// защита от пустого ввода текста
  //           if (DataLength == 2 && ((uint16_t*)Data)[0] == 0xFFFF) 
	// 					{
	// 						memset(&Widget->VP_Data, 0,Widget->VP_Data_Size);
	// 						strcpy((char*)&Widget->VP_Data, "0");
	// 						Write_VPs(Widget->VP, (const uint8_t *)&Widget->VP_Data, Widget->VP_Data_Size);
	// 					}
  //           else memcpy(&Widget->VP_Data, Data, MIN(DataLength,Widget->VP_Data_Size));
	// 					found = 1;
	// 	}
  //   else if ( (Widget = ListText.Find(_Adr) ) )
	// 	{
			
	// 					memcpy(&Widget->VP_Data, Data, MIN(DataLength,Widget->VP_Data_Size));
	// 					found = 1;
	// 	}

	// 	delay(100);
	// 	if (  WidgetCMD=ListCallBackFunc.Find(_Adr) ) 
	// 	{
	// 		// debug_printf("4\n");
	// 		WidgetCMD->Func(Data, DataLength);
	// 		found = 1;
	// 	}

  //   if(found)
  //   {
	// 		if (*afterPoll) afterPoll();
	// 		return 1;		
  //   }
	// 	else 
	// 	{
	// 		#ifdef DWIN_DEBUG
	// 		debug_printf(("DGUS_ERR_GET_VIRTUAL_ADDRESS\n"));
	// 		#endif
	// 		return 0;
	// 	}
		
/**/
		
}


