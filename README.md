# Infrastructure 1.2 notes

## ATMega 328P/PA registers

### **IO registers**

This microcontroller has 3 ports (B, C, D), each port has 3 registers and 7 or 8 pins.

Led 1-4 on the Velleman shield are connected to PB2-PB5 (10-13 on the Arduino Uno)

Button 1-3 on the Velleman shield are connected to PC1-PC3 (A1-A3 on the Arduino Uno)

**Data Direction Register**

Indicating output (1) or input (0) on pin

|Register|Bits|Pins|
|-|-|-|
|DDRB|8|PB0-PB7
|DDRC|8|PC0-PC6
|DDRD|8|PD0-PD7

**Pin Output Register**

Turn on (1) or off (0) voltage on pin

|Register|Bits|Pins|
|-|-|-|
|PORTB|8|PB0-PB7
|PORTC|8|PC0-PC6
|PORTD|8|PD0-PD7

**Pin Input Register**

Reading input from pin (1 - voltage on pin, 0 - no voltage on pin)

|Register|Bits|Pins|
|-|-|-|
|PINB|8|PB0-PB7
|PINC|8|PC0-PC6
|PIND|8|PD0-PD7

### **Interrupt registers**

**Pin Change Interrupt Control Register**




### Timers

|Timer|# of bits|Max value|Config registers|Compare registers|Connected pins|
|-|-|-|-|-|-
|Timer 0|8 bits|255|**TCCR0A/TCCR0B**|**OCR0A/OCR0B**|5 and 6
|Timer 1|16 bits|16635|**TCCR1A/TCCR1B**|**OCR1A/OCR1B**|9 and 10
|Timer 2|8 bits|255|**TCCR2A/TCCR2B**|**OCR2A/OCR2B**|3 and 11

**OCRxx** - **O**utput **C**ompare **R**egister

TCCRxx - 

TIMSK



## Pre-defined macros

```c
#define _BV(bit) (1 << (bit))
```
