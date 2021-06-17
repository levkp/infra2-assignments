#!/bin/bash

echo "Metal detector runner started"

PROJ_PATH=/home/levkp/Documents/PlatformIO/Projects/infra12-arduino-exercises
MD_PATH=$PROJ_PATH/src/metal-detector

# JFX_PATH=/home/levkp/Libraries/javafx-sdk-11.0.2/lib
# JCOMM_PATH2=/home/levkp/Libraries/javacomm-2.0/comm.jar
# JCOMM_PATH3=/home/levkp/Libraries/javacomm-3.0/jar/comm.jar
# export CLASSPATH=$CLASSPATH:$JCOMM_PATH2
# javac --module-path $JFX_PATH --add-modules javafx.base,javafx.controls $MD_PATH/SerialReader.java
# java --module-path $JFX_PATH --add-modules javafx.base,javafx.controls,javafx.media $MD_PATH/SerialReader

platformio run -d $PROJ_PATH --target upload

if [ $? -eq 0 ]; then
    python3 $MD_PATH/serial-reader.py
else
    platformio run -d $PROJ_PATH --target clean > /dev/null
    echo "Metal detector failed to start"
fi

echo "Metal detector runner ended"
