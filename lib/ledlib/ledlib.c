#include <ledlib.h>
#include <util/delay.h>
#include <avr/io.h>
#include <usart.h>
#include <stdio.h>

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

void dimLed(int lednumber, int percentage, double duration) 
{
    enableLed(lednumber);

    double onTime = ((double)percentage / 100.0);
    double offTime = 1 - onTime;
    
    while(duration > 0) {
        
        lightUpLed(lednumber);
        _no_const_delay_ms(onTime);

        lightDownLed(lednumber);
        _no_const_delay_ms(offTime);

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

void _no_const_delay_ms(double duration)
{
    while (duration > 0) {
        _delay_ms(1);
        duration--;
    }
}
