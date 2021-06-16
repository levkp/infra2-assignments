# Infrastructure 1.2 notes

The ATMega328P has 3 ports (B, C, D), each port has 3 registers and 7 or 8 pins.

Leds 1-4 on the Velleman shield are connected to PB2-PB5 (10-13 on the Arduino Uno).

Buttons 1-3 on the Velleman shield are connected to PC1-PC3 (A1-A3 on the Arduino Uno).

## **Basic pre-defined macros**
**Bit Value**

```c
#define _BV(bit) (1 << (bit))
```

**Pins** (same for all)

```c
#define PORTB3 3
#define PB3 PORTB3
```

## **IO registers**

**Data Direction Register**

Indicating output (1) or input (0) on pin

|Register|Bits|Pins
|-|-|-
|DDRB|8|PB0-PB7
|DDRC|8|PC0-PC6
|DDRD|8|PD0-PD7

**Pin Output Register**

Turn on (1) or off (0) voltage on pin

|Register|Bits|Pins
|-|-|-
|PORTB|8|PB0-PB7
|PORTC|8|PC0-PC6
|PORTD|8|PD0-PD7

**Pin Input Register**

Reading input from pin (1 - voltage on pin, 0 - no voltage on pin)

|Register|Bits|Pins
|-|-|-
|PINB|8|PB0-PB7
|PINC|8|PC0-PC6
|PIND|8|PD0-PD7

## **Interrupt registers**

**Pin Change Interrupt Control Register**

Indicate at which port the interrupt will happen

|Register|Bits|Ports|
|-|-|-|
|PCICR|8|PCIE0-PCIE2

**Pin Change Mask Register**

Indicate at which pin the interrupt will happen

|Register|Bits|Pins
|-|-|-
|PCMSK0|8|PB0-PB7
|PCMSK1|8|PC0-PC6
|PCMSK2|8|PD0-PD7


### **Pre-defined macros**

**Pin Change Interrupt Enable**
```c
#define PCIE0 0 //port B
#define PCIE1 1 //port C
#define PCIE2 2 //port D
```

**Interrupt Service Routine** (set up interrupts)
```c
#define ISR(vector, ...)      
    // code I don't understand
```

**Set Enable Interrupt** (enable interrupts globally)
```c
#define sei() //code I don't understand
```   

**Vector macros**

|Vector|Task
|-|-
|PCINT0_vect|References interrupts from port B
|PCINT1_vect|References interrupts from port C
|PCINT2_vect|References interrupts from port D

Todo: finish the rest before exam if I have time

## Timers

|Timer|# of bits|Max value|Config registers|Compare registers|Connected pins|
|-|-|-|-|-|-
|Timer 0|8 bits|255|**TCCR0A/TCCR0B**|**OCR0A/OCR0B**|5 and 6
|Timer 1|16 bits|16635|**TCCR1A/TCCR1B**|**OCR1A/OCR1B**|9 and 10
|Timer 2|8 bits|255|**TCCR2A/TCCR2B**|**OCR2A/OCR2B**|3 and 11

**OCRxx** - **O**utput **C**ompare **R**egister

TCCRxx - 

TIMSK

