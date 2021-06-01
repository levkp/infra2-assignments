#!/bin/bash

PROJ_PATH=/home/levkp/Documents/PlatformIO/Projects/infra12-arduino-exercises/
MD_PATH=$PROJ_PATH/src/metal-detector
JFX_PATH=/home/levkp/Libraries/javafx-sdk-11.0.2/lib

# javac --module-path $JFX_PATH --add-modules javafx.base,javafx.controls MetalDetectorGUI.java
# java --module-path $JFX_PATH --add-modules javafx.base,javafx.controls,javafx.media MetalDetectorGUI &

platformio run -d $PROJ_PATH --target upload

if [ $? -eq 0 ]; then
    python3 $MD_PATH/serial-reader.py &
else
    platformio run -d $PROJ_PATH --target clean > /dev/null
    echo "Metal detector failed to start"
fi
