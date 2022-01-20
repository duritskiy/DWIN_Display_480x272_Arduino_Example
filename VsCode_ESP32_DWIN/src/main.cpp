#include "Arduino.h"
// #include "elapsedMillis.h"
#include "DGUS_ARDUINO_ESP32.h"

#define RXD2 17
#define TXD2 16

#define RS485_DEFAULT_DE_PIN 255 //not used
#define DWIN_ID 0x5AA5

uint8_t buff[255];
// DWIN_RS485_ESP32 dgus(DWIN_ID, &Serial2,  460800, RS485_DEFAULT_DE_PIN, CRC_ENABLE, buff );
DWIN_RS485_ESP32 dgus(DWIN_ID, &Serial2,  460800, RS485_DEFAULT_DE_PIN, CRC_DISABLE, buff );


//Системные регистры
DGUS_SystemVariableInterface DGUS_Sys(dgus);



////////////////////////////////////////////////////////////////////////////////////////////
//объект с функциями записи и чтения.
//А также он добавляет внутренник колбек в Poll()
dgus_display_DataVariable<int16_t> Num_int16(dgus,0x5020,0x5030);

// Дополнительный колбек для Num_int16 оформленный в виде лямбда-функции
dgus_Commands Show_Num_int16_Callback(dgus, 0x5020, [](uint8_t* Data,size_t Size)
{
      int16_t num = swap_endian(*(uint16_t *)Data);
      Serial.printf("\n\nShow_Num_int16_Callback lambda()\n" );
      Serial.printf("Num_int16=%d\n\n", num);
});


////////////////////////////////////////////////////////////////////////////////////////////
dgus_display_DataVariable<int32_t> Num_int32(dgus,0x5040,0x5050);



////////////////////////////////////////////////////////////////////////////////////////////
dgus_display_Text <12,AS_NUMBER> text1(dgus,0x5000,0x5010);
dgus_Commands PasswordCheck_text1_Callback(dgus, 0x5000, [](uint8_t* Data,size_t Size)
{
  const char* pass = "12345";
  size_t sizeMin=MIN(text1.Regs.VP_Data_Size,Size);
  sizeMin=MIN(sizeMin,strlen(pass));
  if(strncmp( (char*)Data, pass , sizeMin  )==0)
  {
      Serial.printf("\n\nPasswordCheck_text1_Callback() lambda\n" );
  }
});


////////////////////////////////////////////////////////////////////////////////////////////
dgus_display_Text <10,AS_TEXT>   text2(dgus,0x5100,0x5120);
dgus_Commands PopupMenu1_Callback(dgus, 0x001D, [](uint8_t* Data,size_t Size)
{
  if(Size==2) 
  {
      uint16_t keyCode = swap_endian(*(uint16_t *)Data);
      Serial.printf("\n\nPopupMenu1_Callback(%d)\n" , keyCode);

      switch (keyCode)
      {
      case 1: text2.WriteAsText("Popup1"); break;
      case 2: text2.WriteAsText("Popup2"); break;
      case 3: text2.WriteAsText("Popup3"); break;
      case 4: text2.WriteAsText("Popup4"); break;
      }
      
  }
});




////////////////////////////////////////////////////////////////////////////////////////////
void Button1_Button3Callback(uint8_t *Data, size_t Size)
{
  if(Size==2) 
  {
      int page = swap_endian(*(uint16_t *)Data);
      Serial.printf("\n\nButton1Callback()\n" );
      Serial.printf("Current Page=%d\n\n", page);
  }
};
dgus_Commands Button1_Button3(dgus, 0x001A, &Button1_Button3Callback);

////////////////////////////////////////////////////////////////////////////////////////////
void SlidePageCallback(uint8_t *Data, size_t Size)
{
  if(Size==2) 
  {
      int page = swap_endian(*(uint16_t *)Data);
      Serial.printf("\n\nSlidePageCallback()\n" );
      Serial.printf("Current Page=%d\n\n", page);
  }
};
dgus_Commands SlidePage(dgus, 0x0014, &SlidePageCallback);





////////////////////////////////////////////////////////////////////////////////////////////
void DGUS_Setup(void);

void setup()
{

    // delay(1000);
    Serial.begin(SERIAL_BAUD);
    Serial2.begin(460800, SERIAL_8N1, RXD2, TXD2);
    // MyRS485.begin();
    Serial.println("\n\nvoid setup()");

    DGUS_Setup();

    // if (text1.Read()) printf("text1=%s\n\n", text1.GetAsText());
    // if (text2.Read()) printf("text2=%s\n\n", text2.GetAsText());
    // if (Num_int16.Read()) printf("Num_int16=%d\n", Num_int16.Get());
    // if (Num_int32.Read()) printf("Num_int32=%d\n", Num_int32.Get());

    // for (int i = 0; i < dgus.ListText.Count; i++) printf("ListText[%d]=%04X \n", i, dgus.ListText.List[i]->VP);
    // for (int i = 0; i < dgus.ListNum.Count; i++)
    // {
    //     if (dgus.ListNum.List[i]->VP_Data_Size == sizeof(int16_t)) printf("ListNum[%d]=%04X : %d\n", i, dgus.ListNum.List[i]->VP,swap_endian(dgus.ListNum.List[i]->VP_DataAs.int16));
    //     if (dgus.ListNum.List[i]->VP_Data_Size == sizeof(int32_t)) printf("ListNum[%d]=%04X : %ld\n", i, dgus.ListNum.List[i]->VP,swap_endian(dgus.ListNum.List[i]->VP_DataAs.int32));
    // }
}




void loop()
{

    // if(Serial2.available())
    // {
    //    while(Serial2.available()) printf("%02X ",Serial2.read()) ;
    //    printf("\n\n");
    // }

  if(dgus.Poll())
  {
      // static uint32_t t;
      // printf("PollTime=%d\n", millis()-t);
      // t = millis();

        //   printf("Num_int16=%d\n", Num_int16.Get());
        //   printf("Num_int32=%d\n", Num_int32.Get());
        // //   text1.Read();
        // //   printf("text1=%s\n\n",   text1.GetAsText());
        //   printf("text1=%f\n\n",   text1.GetAsFloat());

  }


  static uint32_t t1;
  if (millis()-t1 > 1400)
  {
      t1 = millis();

      static int i = 0;

      // dgus.Read_VPs(0x14, 16);
    //   dgus.Read_VPs(0xB4, 36);
      // dgus.Read_VPs(0x5050, 10);

      // if(i==0)
      // {
      //      if(text1.Regs.SP_Read())
      //     {
      // text1.Regs.SP_Data_p->Print();

      //         // text1.Regs.SP_Data_p->Pos.x.Set_Swaped(312);
      //         // text1.Regs.SP_Data_p->Pos.y.Set_Swaped(26);
      //         // text1.Regs.SP_Data_p->size.x_top.Set_Swaped(312);
      //         // text1.Regs.SP_Data_p->size.y_top.Set_Swaped(25);
      //         // text1.Regs.SP_Data_p->size.x_bottom.Set_Swaped(430);
      //         // text1.Regs.SP_Data_p->size.y_bottom.Set_Swaped(25+22);
      //         // text1.Regs.SP_Data_p->font_0_id =0;
      //         // text1.Regs.SP_Data_p->font_1_id = 1;

      //         // text1.Regs.SP_Data_p->hor_distance = 0;
      //         // text1.Regs.SP_Data_p->ver_distance = 0;
      //         // text1.Regs.SP_Data_p->encode_mode_SpacingMode = 0;

      //         // text1.Regs.SP_Data_p->font_x_dots = 22;
      //         // text1.Regs.SP_Data_p->font_y_dots = 22;
      //         // // text1.Regs.SP_Data_p->Color.Set_Swaped(0xFF00);
      //         // text1.Regs.SP_Write();
      //     }
      // }

      // switch ( (i++) % 4 )
      // {
      // case 0:  text1.WriteAsFloat(12345.678);              break;
      // case 1:
      //         if(text1.Read())text1.WriteAsFloat(text1.GetAsFloat()+1);
      //      break;
      // case 2:  text1.WriteAsINT32(54321);                  break;
      // case 3:  text1.WriteAsText("ThisIsText");            break;
      // };
     

      // Serial.printf("\ntext1.ReadAsText=%s\n\n",  text1.GetAsText());

      // if(text2.Regs.SP_Read()) text2.Regs.SP_Data_p->Print();
      //  if (text2.Read()) Serial.printf("text2.GetAsText=%s\n", text2.GetAsText());

      //  if(Num_int16.Regs.SP_Read()) Num_int16.Regs.SP_Data_p->Print();
      //  if(Num_int16.Read())Serial.printf("Num_int16=%u\n",Num_int16.Get());
      //  Num_int16.Write(Num_int16.Get()+1);

      //  if(Num_int32.Regs.SP_Read()) Num_int32.Regs.SP_Data_p->Print();
      //  if(Num_int32.Read())Serial.printf("Num_int32=%u\n",Num_int32.Get());
      //  Num_int32.Write(Num_int32.Get()+1);

      //  Serial.printf("ESP.getFreeHeap()=%d\n", ESP.getFreeHeap());


      // if(text1.Regs.SP_Read())
      // {
      //     text1.Regs.SP_Data_p->Print();
      //     // text1.Regs.SP_Data_p->encode_mode_Font_encoding = 1;
      //     // static TColor16 c;
      //     // c.RedChannel+=15+rand();
      //     // // text_display.Color.Set_Swaped(RGB24to16(255,255,b)) ;
      //     // text1.Regs.SP_Data_p->Color.Set_Swaped(c.Color16) ;
      //     // text1.Regs.SP_Data_p->font_y_dots = 32;
      //     // text1.Regs.SP_Data_p->Pos.x.Set_Swaped(250);
      //     // text1.Regs.SP_Data_p->VP.Set_Swaped(0x5000);
      //     // text1.Regs.SP_Write();
      // }



    }

}






void DGUS_Setup(void)
{

// DGUS_Sys.system_reset(0);

if(DGUS_Sys.Setup_CRC_Mode()) Serial.printf("Auto: CRC Mode=%d\n",dgus.CRC_Enable) ;
else Serial.printf("Manual: CRC Mode=%d\n",dgus.CRC_Enable) ;

dgus_cmd_system_config config;
if (DGUS_Sys.get_system_config(config))
{
    config.Print();
    // config.backight_standby = 1;
    // config.screen_orientation = 2;
    // DGUS_Sys.set_system_config(config);
    }

    //  uint16_t page;
    //  if(DGUS_Sys.set_page(2)) 
    //  {
    //     if(DGUS_Sys.get_page(page)) Serial.printf("page=%d\n", page);
    //  }
         
    dgus_cmd_led_config led_config;
    if(DGUS_Sys.get_LedConfig(led_config))
    {
        led_config.Print();
        led_config.dim_wait_multiple10ms.Set_Swaped (1000);
        led_config.backlight_brightness_running = 100;
        led_config.backlight_brightness_idle = 20;
        DGUS_Sys.set_LedConfig(led_config);
    }

}