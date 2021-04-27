#include <ledlib.h>
#include <util/delay.h>
#include <avr/io.h>
#include <usart.h>
#include <stdio.h>

<<<<<<< HEAD
#define __DELAY_BACKWARD_COMPATIBLE__

=======
>>>>>>> def54da823e08216d43127953f69c04849970f84
void enableLed (int lednumber)
{
    if (lednumber >= 0 && lednumber < NUMBER_OF_LEDS) {
        DDRB |= (1 << (PB2 + lednumber));
    }
}

void lightUpLed (int lednumber)
{
    if (lednumber >= 0 && lednumber < NUMBER_OF_LEDS) {
        PORTB &= ~(1 << (PB2 + lednumber)); 
    }
}

void lightDownLed (int lednumber)
{
    if (lednumber >= 0 && lednumber < NUMBER_OF_LEDS) {
        PORTB |= (1 << (PB2 + lednumber));
    }
}
    
void enableLeds(uint8_t leds)
{
    for (int i = 0; i < 4; i++) {
        if (leds & 1) {
            enableLed(i);
        }
        leds >>= 1;
    }
}

void lightUpLeds(uint8_t leds)
{
    for (int i = 0; i < 4; i++) {
        if (leds & 1) {
            lightUpLed(i);
        }
        leds >>= 1;
    }
}

void lightDownLeds(uint8_t leds) 
{
    for (int i = 0; i < 4; i++) {
        if (leds & 1) {
            lightDownLed(i);
        }
        leds >>= 1;
    }
}

void blinkLed(int lednumber, int duration) 
{
    lightUpLed(lednumber);
<<<<<<< HEAD
    wrapper_delay_ms(duration);
    lightDownLed(lednumber);
    wrapper_delay_ms(100);
=======
    _no_const_delay_ms(duration);
    lightDownLed(lednumber);
    _no_const_delay_ms(100);
>>>>>>> def54da823e08216d43127953f69c04849970f84
}

void dimLed(int lednumber, int percentage, double duration) 
{
    enableLed(lednumber);

    double onTime = ((double)percentage / 100.0);
    double offTime = 1 - onTime;
    
    while(duration > 0) {
        
        lightUpLed(lednumber);
<<<<<<< HEAD
        wrapper_delay_ms(onTime);

        lightDownLed(lednumber);
        wrapper_delay_ms(offTime);
=======
        _no_const_delay_ms(onTime);

        lightDownLed(lednumber);
        _no_const_delay_ms(offTime);
>>>>>>> def54da823e08216d43127953f69c04849970f84

        duration -= (onTime + offTime);
    }
}

void fadeInLed(int lednumber, int duration) 
{
    for (int i = 1; i <= 100; i++) {
        //printf("%f\n", (double)duration / 100.0);
        dimLed(lednumber, i, (double)duration / 100.0);
    }
}

<<<<<<< HEAD
void wrapper_delay_ms(double duration)
=======
void _no_const_delay_ms(double duration)
>>>>>>> def54da823e08216d43127953f69c04849970f84
{
    while (duration > 0) {
        _delay_ms(1);
        duration--;
    }
}
