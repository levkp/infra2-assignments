#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <display.h>
#include <usart.h>
#include <util/delay.h>
#include <buttonlib.h>
#include "nim.h"

// Todo: replace empty while loops with loop_until_bit_is_set

void nim(void)
{
    int *moves = malloc(10 * sizeof(int));
    int seed;
    int matches_left = START_NUMBER;
    bool player_next;

    initUSART();
    initDisplay();
    initADC_nim();

    printf("\n============== NIM ==============");
    printf("\nTurn the potentiometer to seed rand()!");

    seed = getseed();
    srand(seed);
    player_next = seed % 2;

    printf("\nSeed: %d", seed);
    printf("\nFirst take: %s", player_next ? "player" : "arduino");
    printf("\nPress button 1 to start!");

    //enableButton(0);
    //enableButton(1);

    while (!buttonPushed(0)) { }

    player_next = true;

    while (matches_left != 0) {

        int take = MIN_TAKE;
       
        while (true) {

            writeNumberToSegment(2, matches_left / 10);
            writeNumberToSegment(3, matches_left % 10);
            writeCharToSegment(1, player_next ? 'P' : 'A');

            if (!player_next) {
                printf("\nIt's Arduino's turn. Press button 2 to confirm.");
                while(!buttonPushed(1)) { };
            }

            writeNumberToSegment(0, take);

            if (player_next) {
                if (buttonPushed(0) && take > MIN_TAKE)
                    take--;

                if (buttonPushed(1))
                    break;
            
                if (buttonPushed(2) && take < MAX_TAKE)
                    take++;
            } else {
                take = (matches_left - 1) % (MAX_TAKE - 1);

                if (take == 0)
                    take = (rand() % MAX_TAKE) + 1;
            }
            
        }

        matches_left -= take;
        player_next = !player_next;
    }


    free(moves);

    printf("\n\nEnd");
}


void initADC_nim(void)
{
    ADMUX |= _BV(REFS0);
    ADCSRA |= _BV(ADPS2) | _BV(ADPS1);
    ADCSRA |= _BV(ADEN);
}


int getseed(void)
{
    //_delay_ms(5000);
    ADCSRA |= _BV(ADSC);
    loop_until_bit_is_clear(ADCSRA, ADSC);    
    return ADC;
}

void stats(void)
{

}




