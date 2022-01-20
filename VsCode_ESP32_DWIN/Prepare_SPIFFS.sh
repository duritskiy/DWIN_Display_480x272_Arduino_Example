#!/bin/bash


# cat data_dev/css/chartist.min.css data_dev/css/bootstrap.min.css data_dev/css/style.css > data_dev/css/build.css
# cat data_dev/js/chartist.min.js data_dev/js/chart.js > data_dev/js/build.chart.js

#find ./data_dev3 -type f -iname '*.html' -exec sed -i -e 's|\?v\([0-9]\+\).\([0-9]\+\).\([0-9]\+\)|?ver=05.10.2017|g' '{}' \;
#find ./data_dev -iname "*.htm" -type f -exec sed -i 's/vvda$today/v07.06.2017/gi' {} \;


#######################
gzip -vrkf data_dev/*.htm
gzip -vrkf data_dev/*.html
gzip -vrkf data_dev/css/*.css
gzip -vrkf data_dev/js/*.js
# gzip -vrkf data_dev/*.json
gzip -vrkf data_dev/lang/lang.*.json
# gzip -vrkf data_dev/widgets/*.json

mv data_dev/*.htm.gz data/
mv data_dev/*.html.gz data/
mv data_dev/js/*.js.gz data/js
mv data_dev/css/*.css.gz data/css
# mv data_dev/lang/*.json.gz data/lang
# mv data_dev/*.json.gz data/



cp data_dev/*.js data/
cp data_dev/*.json data/
cp data_dev/lang/*.json data/lang/

# rm data/*копия*.*
rm -f -v data/*копия*.*


############################


# rm data_dev/css/build.css
# rm data_dev/js/build.chart.js

# rm data/css/chartist.min.css.gz
# rm data/css/bootstrap.min.css.gz
# rm data/css/style.css.gz
# rm data/js/chartist.min.js.gz
# rm data/js/chart.js.gz
# rm data/js/siema.min.js.gz

# rm .pio/build/esp32doit-devkit-v1/spiffs.bin

#test -f *.generic.bin && cp *.generic.bin build/build.generic_flash_size_1Mb.254Kb_`date '+%G.%m.%d'`.bin


#FILE_SUM=`md5sum Sonoff_WiFi_switch.ino.generic.bin`
#COPY_SUM=`md5sum ./build/$(ls -lt ./build | head -n2 |tail -n1 | awk '{print $9}')`
#if [ "$FILE_SUM" != "$COPY_SUM" ]
#then
#cp Sonoff_WiFi_switch.ino.generic.bin build/build.0x00000_flash_size_1Mb.256Kb_`date '+%G.%m.%d'`.bin
#fi
#cp /tmp/arduino_build_*/Sonoff_WiFi_switch.spiffs.bin ./build/spiffs.0xBB000_flash_size_1Mb.256Kb_`date '+%G.%m.%d'`.bin


# FILENAME=data/analog.json.gz
# FILESIZE=$(stat -c%s "$FILENAME")
# echo "Size of $FILENAME = $FILESIZE bytes."


# ls --help > ls.txt
# ls --group-directories-first -sa data_dev


# read -p "Press [Enter] key to start backup..."