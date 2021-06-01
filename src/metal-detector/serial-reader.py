# Script idea (#1 answer): https://stackoverflow.com/questions/40480737/how-to-write-data-to-a-text-file-on-arduino#43440343
# Other source: https://pyserial.readthedocs.io/en/latest/pyserial_api.html

import serial

# Bit (baud) rate is 9600 by default

file = open("field.txt", "w+")
ser = serial.Serial("/dev/ttyACM0")

print("\nStarted reading from serial")

while True: 

    try:
        line = ser.readline()
        try:
            line = line.decode("utf-8")
        except UnicodeDecodeError:
            print("Unicode decode error")
            break

        print(line)
        file.write(line)
        if line == "end\n":
            break

    except KeyboardInterrupt:
        print("Interrupted")
        break

print("Stopped reading from serial")    
