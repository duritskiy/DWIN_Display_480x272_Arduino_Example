echo on
cls

chcp 1251
echo Русский текст


rd /s /q .\data

mkdir .\data\css\
mkdir .\data\img\
mkdir .\data\js\
mkdir .\data\lang\


xcopy /y /o /e "data_dev\css\*.*" "data\css"
xcopy /y /o /e "data_dev\img\*.*" "data\img"
xcopy /y /o /e "data_dev\js\*.*" "data\js"
xcopy /y /o /e "data_dev\lang\*.*" "data\lang"

xcopy /y /o /e "data_dev\*.html" "data\"
xcopy /y /o /e "data_dev\*.json" "data\"
xcopy /y /o /e "data_dev\*.js" "data\"

del .\data\*копия*.*
del .\data\js\*копия*.*


gzip -rf ./data/css/
gzip -rf ./data/img/
gzip -rf ./data/js/
gzip -rf ./data/lang/

    
REM 1.5mb
%USERPROFILE%\.platformio\packages\tool-mkspiffs\mkspiffs_espressif32_arduino.exe -d 5 -c   Data -p 256 -b 4096 -s 1507328 my.spiffs.bin

esptool.exe --chip esp32 --port "COM9" --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_size detect 2686976 my.spiffs.bin

rem C:\arduino\portable\Packages\esp32\tools\esptool_py\2.6.1\esptool.exe --chip esp32 --port "COM9" --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_size detect 2686976 my.spiffs.bin

REM 1mb
REM C:\Users\duritskiy\.platformio\packages\tool-mkspiffs\mkspiffs_espressif32_arduino.exe  -c   Data -p 256 -b 4096 -s 0x100000 my.spiffs.bin
REM C:\arduino\portable\Packages\esp32\tools\esptool_py\2.6.1\esptool.exe --chip esp32 --port "COM9" --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_size detect 0x100000  my.spiffs.bin


rem pause