# Infrastructure 1.2 notes

Short overview for registers and macros we learnt

The ATMega328P has 3 ports (B, C, D), each port has 3 registers and 7 or 8 pins.

Leds 1-4 are connected to `PB2`-`PB5` (10-13 on the Arduino Uno).

Buttons 1-3 are connected to `PC1`-`PC3` (A1-A3 on the Arduino Uno).

The buzzer is connected to `PD3`

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

## **Interrupts**

### **Registers**

**Port Change Interrupt Control Register**

Indicate at which port the interrupt will happen

|Register|Bits|Ports
|-|-|-
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
    // ... code I don't understand
```

**Set Enable Interrupt** (enable interrupts globally)
```c
#define sei() // ... code I don't understand
```   

**Vector macros - to be passed to `ISR`**

|Macro|Task
|-|-
|PCINT0_vect|References interrupts from port B
|PCINT1_vect|References interrupts from port C
|PCINT2_vect|References interrupts from port D

## **Potentiometer**

### **Registers**

|Register|Bits|Task
|-|-|-
|ADMUX|8|Setting reference voltage
|ADCSRA|8|Setting sample rate

### **Pre-defined macros**

Don't feel like going in-depth for the rest

## **Timers**

### **Registers**

**Timer Counter Control Register and Output Compare Register**

Indicating waveform and speed

|TCCRxx|OCRxx|Bits|Max. value|Timer|Pins
|-|-|-|-|-|-
|TCCR0A|OCR0A|8|255|Timer 0|5 and 6
|TCCR0B|OCR0B|8|255|Timer 0|5 and 6
|TCCR1A|OCR1A|16|16635|Timer 1|9 and 10
|TCCR1B|OCR1B|16|16635|Timer 1|9 and 10
|TCCR2A|OCR2A|8|255|Timer 2|3 and 11
|TCCR2B|OCR2A|8|255|Timer 2|3 and 11

**Time Interrupt Mask Register**

Setting up interrupts for timers

|TIMSKx|Bits|Timer
|-|-|-
|TIMSK0|8|Timer 0
|TIMSK1|8|Timer 1
|TIMSK2|8|Timer 2

### **Pre-defined macros**

**Wave Generation Mode**
```c
#define WGM00 0
#define WGM01 1
#define WGM02 3
```

**Clock Speed**
```c
#define CS00 0
#define CS01 1
#define CS02 2
```

|CS02|CS01|CS00|Factor
|-|-|-|-
|0|0|0|No counting
|0|0|1|1
|0|1|0|8
|0|1|1|64
|1|0|1|1024
|1|1|0|External
|1|1|1|External


Wave generation modes from ermicro.com:

![WGMs](http://www.ermicro.com/blog/wp-content/uploads/2009/01/m168lcd_07.jpg)


**Example:** setting fast PWM for timer 0

**TCCR0A**

|Bit|7|6|5|4|3|2|1|0
|-|-|-|-|-|-|-|-|-
|Name|||||||WGM01|WGM00

**TCCR0B**

|Bit|7|6|5|4|3|2|1|0
|-|-|-|-|-|-|-|-|-
|Name||||​​​​​​​|WGM02|CS02|CS01|CS00

```c
TCCR0A |= _BV(WGM00) | _BV(WGM01);
```

**Example:** slowing down timer 0 by 1024


```c
TCCR0B |= _BV(CS02) | _BV(CS00);
```

**Timer Counter**

|Macro|Task
|-|-
|TCNT0|Counter for timer 0
|TCNT1|Counter for timer 1
|TCNT2|Counter for timer 2

**Vector macros - to be passed to `ISR`**

|Macro|Task
|-|-
|TIMER0_COMPA_vect|Interrupt if the value in OCRA equals to TCNT0
|TIMER0_OVF_vect|Interrupt if TCNT0 equals the TOP value of timer 0

Don't feel like going in-depth for the rest
