echo off
cls

Prepare_SPIFFS.sh


REM echo on
REM cls
    
REM 1.5mb
C:\Users\duritskiy\.platformio\packages\tool-mkspiffs\mkspiffs_espressif32_arduino.exe -d 5 -c   Data -p 256 -b 4096 -s 1507328 my.spiffs.bin
C:\arduino\portable\Packages\esp32\tools\esptool_py\2.6.1\esptool.exe --chip esp32 --port "COM9" --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_size detect 2686976 my.spiffs.bin

REM 1mb
REM C:\Users\duritskiy\.platformio\packages\tool-mkspiffs\mkspiffs_espressif32_arduino.exe  -c   Data -p 256 -b 4096 -s 0x100000 my.spiffs.bin
REM C:\arduino\portable\Packages\esp32\tools\esptool_py\2.6.1\esptool.exe --chip esp32 --port "COM9" --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_size detect 0x100000  my.spiffs.bin



REM pause