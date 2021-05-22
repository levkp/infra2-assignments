#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <display.h>
#include <usart.h>
#include <util/delay.h>
#include <buttonlib.h>
#include "nim.h"

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

    while (matches_left != 0) {

        int take = MIN_TAKE;
       
        while (true) {

            lightUpSegments(take, matches_left, player_next);

            if (player_next) {
                if (buttonPushed(0) && take > MIN_TAKE) {
                    _delay_ms(500);
                    take--;
                }

                if (buttonPushed(1)) {
                    _delay_ms(500);
                    break;
                }
            
                if (buttonPushed(2) && take < MAX_TAKE) {
                    _delay_ms(500);
                    take++;
                }

            } else {

                printf("\nIt's Arduino's turn. Press button 2 to confirm.");
                
                while(!buttonPushed(1)) { 
                    lightUpSegments(take, matches_left, player_next); 
                };

                _delay_ms(500);

                take = (matches_left - 1) % (MAX_TAKE - 1);

                if (take == 0)
                    take = (rand() % MAX_TAKE) + 1;

                printf("\n Arduino takes %d. Press button 2 to confirm.", take);
                while(!buttonPushed(1)) { 
                    lightUpSegments(take, matches_left, player_next);
                };  

                _delay_ms(500);  

                break;
            }
            
        }

        matches_left -= take;
        player_next = !player_next;

        printf("\nNext player: %s", player_next ? "Player" : "Arduino");

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

void lightUpSegments(int take, int matches_left, bool player_next)
{
    writeNumberToSegment(0, take);
    writeCharToSegment(1, player_next ? 'P' : 'A');
    writeNumberToSegment(2, matches_left / 10);
    writeNumberToSegment(3, matches_left % 10);
}




