#include <stdbool.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <usart.h>
#include <ledlib.h>
#include <buttonlib.h>
#include "simonsays.h"

bool button1_pushed = false;
bool button2_pushed = false;
bool button3_pushed = false;

ISR(PCINT1_vect)
{
    // Todo: why do I really need double ifs?

    if (bit_is_clear(PINC, PC1)) {
        _delay_us(1000);
        if (bit_is_clear(PINC, PC1))
            button1_pushed = true;
    } else {
        button1_pushed = false;
    }

    if (bit_is_clear(PINC, PC2)) {
        _delay_us(1000);
        if (bit_is_clear(PINC, PC2))
            button2_pushed = true;
    } else {
        button2_pushed = false;
    }

    if (bit_is_clear(PINC, PC3)) {
        _delay_us(1000);
        if (bit_is_clear(PINC, PC3))
            button3_pushed = true;
    } else {
        button3_pushed = false;
    }
}

void simonsays(void) 
{
    uint8_t series[PATTERN_LENGTH];
    enableLeds(0b00001111);
    lightDownLeds(0b00001111);
    
    sei();
    initUSART();
    startup();
    //seedtest();
    generate(series);
    if (play(series))
        printf("\nCongratulations, you are the Simon Master!");
    else
        printf("\nRestart to try again!");
}

void startup(void)
{
    // Todo: it also works without enabling the buttons. Why?
    /*
    enableButton(0);
    enableButton(1);
    enableButton(2);
    */
    
    PCICR |= _BV(PCIE1);
    PCMSK1 |= _BV(PC1);
    PCMSK1 |= _BV(PC2);
    PCMSK1 |= _BV(PC3);

    printf("\n\n========= SIMON SAYS =========\nPress button 1 to start!\n");
    
    int seed = 0;

    // Todo: why does it take so long to detect the first button press?
    while(!button1_pushed) {
        blinkLed(3, 500);
        seed++;
    }

    srand(seed);

    printf("\nGet ready!");
}

void seedtest(void)
{
    for (int i = 0; i < 10; i++) {
        startup();
        printf("Seed test no. %d: %d\n", i, rand());
    }
}

void generate(uint8_t *series)
{
    for(int i = 0; i < PATTERN_LENGTH; i++)
        series[i] = rand() % 3;
}

void printPuzzle(uint8_t series[], int length)
{
    printf("[ ");
    for(int i = 0; i < length; i++)
        printf("%d ", series[i] + 1);
    printf("]");
}

bool play(uint8_t series[])
{
    for (int i = 1; i <= PATTERN_LENGTH; i++) {

        printf("\n\n========== Level %d ==========\nWatch the pattern!", i);

        /*
        printf("\(Solution): ");
        printPuzzle(series, i);
        printf("\n");
        */

        for(int j = 0; j < i; j++) {
            _delay_ms(PATTERN_DELAY);
            lightUpLed(series[j]);
            _delay_ms(PATTERN_DELAY);
            lightDownLed(series[j]);
        }

        printf("\nOK, now you!");
    
        if (readInput(series, i)) {
            blinkLed(3, 100);
            blinkLed(3, 100);
            blinkLed(3, 100);
            printf("\nCorrect pattern, we go to level %d!", i + 1);
        } else {
            lightUpLeds(0b00001111);
            printf("\nWrong, the correct pattern was: ");
            printPuzzle(series, i);
            return false;
        }        
    }
    return true;
}

/* Todo: improve this method by printing the outputs somewhere else and decreasing repetitive code 
 * (and make a solution without interrupts?) 
 */

bool readInput(uint8_t series[], int patternLength)
{
    int next = 0;

    while(true) {

        if (button1_pushed && series[next] == 0) {
            printf("\nYou pressed button 1, correct!");
            button1_pushed = false;
            next++;
        } else if (button2_pushed && series[next] == 1) {
            printf("\nYou pressed button 2, correct!");
            button2_pushed = false;
            next++;
        } else if (button3_pushed && series[next] == 2) {
            printf("\nYou pressed button 3, correct!");
            button3_pushed = false;
            next++;
        } else if(button1_pushed) {
            printf("\nYou pressed button 1, wrong!");
            return false;
        } else if(button2_pushed) {
            printf("\nYou pressed button 2, wrong!");
            return false;
        } else if(button3_pushed) {
            printf("\nYou pressed button 3, wrong!");
            return false;
        }

        if (next == patternLength)
            return true;
    }
}
