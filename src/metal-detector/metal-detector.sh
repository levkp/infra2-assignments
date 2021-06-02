#!/bin/bash

echo "Metal detector runner started"

PROJ_PATH=/home/levkp/Documents/PlatformIO/Projects/infra12-arduino-exercises/
MD_PATH=$PROJ_PATH/src/metal-detector

platformio run -d $PROJ_PATH --target upload

if [ $? -eq 0 ]; then
    python3 $MD_PATH/serial-reader.py
else
    platformio run -d $PROJ_PATH --target clean > /dev/null
    echo "Metal detector failed to start"
fi

echo "Metal detector runner ended"
