#include <stdbool.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <usart.h>
#include <ledlib.h>
#include <buttonlib.h>
#include "simonsays.h"

bool start_button_pushed = false;
int seed = 0;

ISR(PCINT1_vect)
{
    if (bit_is_clear(PINC, PC1)) {
        _delay_us(1000);
        if (bit_is_clear(PINC, PC1)) {
            start_button_pushed = true;
        }
    }
}

void simonsays(void) 
{

    uint8_t series[PATTERN_LENGTH];

    sei();
    initUSART();
    startup();
    //seedtest();



}

void startup(void)
{
    enableLed(3);
    //Todo: it also works without enabling the button. Why?
    enableButton(0);
    
    PCICR |= _BV(PCIE1);
    PCMSK1 |= _BV(PC1);

    printf("\n\n====== SIMON SAYS ======\nPress button 1 to start!\n");
    
    while(!start_button_pushed) {
        blinkLed(3, 100);
        seed++;
    }
}

void seedtest(void)
{
    for (int i = 0; i < 10; i++) {
        startup();
        start_button_pushed = false;
        srand(seed);
        printf("Seed test no. %d: %d\n", i, rand());
    }
}
void generatePuzzle(uint8_t *series)
{

    for(int i = 0; i < PATTERN_LENGTH; i++) {
        series[i] = (rand() % 4 - 2 + 1) + 2;
    }
    
}



