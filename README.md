# DWIN Display 480x272 Project + DGUS Arduino Library 


#### [PowerPointImage.ppt](https://github.com/duritskiy/DWIN_Display_480x272_Arduino_Example/blob/main/PowerPointImage.ppt) - это проект скринов созданный в PowerPoint

#### [DWIN_SET](https://github.com/duritskiy/DWIN_Display_480x272_Arduino_Example/tree/main/DWIN_SET) - папка с файлами для загрузки файлов в Дисплей.
достаточно загрузить только (наверное)
- 13TouchFile.bin
- 14ShowFile.bin
- 22_Config.bin
- T5L_OS_DGUS2_V10(no RX8130).BIN
- T5L_UI_DGUS2_V45_20211231.BIN
- T5LCFG_DMG48270C043_03WTC_460800bps CRC.CFG  или  T5LCFG_DMG48270C043_03WTC_460800bps noCRC.CFG 
- 0_DWIN_ASC.HZK
- 24Image.icl
- 26_Icon.icl



 #### [VsCode_ESP32_DWIN](https://github.com/duritskiy/DWIN_Display_480x272_Arduino_Example/tree/main/VsCode_ESP32_DWIN) - это папка с VSCode-проектом.
Как уже сказал пример написан в среде VSCode, с использованием framework = arduino, под контроллер ESP32.
Что бы пример заработал в Arduino IDE его придется немного адаптировать. 
 
 
 
 #### [/VsCode_ESP32_DWIN/lib/DGUS_ARDUINO_LIB](https://github.com/duritskiy/DWIN_Display_480x272_Arduino_Example/tree/main/VsCode_ESP32_DWIN/lib/DGUS_ARDUINO_LIB) - библиотека для связи Arduino и DWIN дисплея.
 
 #### [DGUS_ARDUINO_ESP32.h](https://github.com/duritskiy/DWIN_Display_480x272_Arduino_Example/blob/main/VsCode_ESP32_DWIN/lib/DGUS_ARDUINO_LIB/DGUS_ARDUINO_ESP32.h) - драйвер привязывающий библиотеку к ардуине на ESP32. С AVR`ами не проверял, дамаю на основе DGUS_ARDUINO_ESP32.h можно написать avr-адаптацию DGUS_ARDUINO_AVR.h. Но у меня пока нет желания это делать. Если кто сделает, поделитесь - я добавлю в библиотеку.
