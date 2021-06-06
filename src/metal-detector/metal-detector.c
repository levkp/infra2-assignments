#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <usart.h>
#include <display.h>
#include <buttonlib.h>
#include <ledlib.h>
#include <buzzlib.h>
#include <ledchaos.h>
#include "metal-detector.h"

bool button1_md = false;

ISR(PCINT1_vect)
{
    if (bit_is_clear(PINC, PC1)) {
        _delay_us(1000);
        if (bit_is_clear(PINC, PC1))
            button1_md = true;
    } else {
        button1_md = false;
    }
}

void metal_detector(void)
{
    initDisplay();
    initUSART();
    initADC_md();

    int level = 0, size = 3, seed;
    int frequencies[15] = { 8600, 8200, 7800, 7200, 6800, 6400, 6000, 5600, 5200, 4800, 4400, 4000, 3600, 3200, 2800 };
    bool won = true;

    printf("\n======== [METAL DETECTOR] ========");
    printf("\nTurn the potentiometer to seed rand!");
    seed = getseed_md();

    printf("\nSeed: %d", seed);
    printf("\nPress button 1 to proceed\n");

    sei();
    PCICR |= _BV(PCIE1);
    PCMSK1 |= _BV(PC1);
  
    // TODO: the interrupt isn't detected with an empty while loop. Why???
    // TODO: works without enabling the buttons too. Why?
    enableLed(0);
    while(!button1_md) {
        lightUpLed(0);
    }

    while (level < MAX_LEVEL) {

        bool horizontal = true;
        Field *f = init_field(level, size, seed);

        if (!f) {
            printf("\nError: unable to allocate memory.\n");
            printf("end\n");
            break;
        }

        while (f->moves > 0) {
            
            draw_field(f, true);

            while (true) {

                writeNumberToSegment(0, f->level);
                writeCharToSegment(1, horizontal ? 'H' : 'V');
                writeNumberToSegment(2, f->moves / 10);
                writeNumberToSegment(3, f->moves % 10);
                   
                if (buttonPushed(1)) {
                    while (buttonPushed(1));
                    horizontal = !horizontal;
                }

                if (buttonPushed(0)) {
                    while (buttonPushed(0));
                    if (horizontal && f->player[X] != 0) {
                        move(f, f->player[X] - 1, f->player[Y]);
                        break;
                    } else if (!horizontal && f->player[Y] != 0) {
                        move(f, f->player[X], f->player[Y] - 1);
                        break;
                    }

                } else if (buttonPushed(2)) {
                    while (buttonPushed(2));
                    if (horizontal && f->player[X] != f->size - 1) {
                        move(f, f->player[X] + 1, f->player[Y]);
                        break;
                    } else if (!horizontal && f->player[Y] != f->size - 1) {
                        move(f, f->player[X], f->player[Y] + 1);
                        break;
                    }
                }  
            }

            enableBuzzer();
            playTone(frequencies[distance(f) + 3], 250);
            disableBuzzer();

            // TODO: improve draw_field if treausure is found
            if (f->treasure[Y] == f->player[Y] && f->treasure[X] == f->player[X]) {
                printf("\nLevel completed!");
                draw_field(f, true);
                f->moves++; // To avoid running out of moves in case the player completes the level with the last move
                break;
            }
        }
        
        if (f->moves == 0 ) {
            draw_field(f, true);
            free_field(f);
            won = false;
            break;
        }

        free_field(f);
        level++;
        size++;
    }

    if (won) {
        end_music(won);
        ledchaos(15);
    }

    //end_music(won);

    printf("\n%s\n", won ? "You won! Nice." : "You're out of moves! Next time!");
    printf("end\n");
}

Field *init_field(int level, int size, int seed)
{
    srand(seed);

    Field *f = malloc(sizeof(*f));

    if (f != NULL) {

        f->cells = malloc(size * sizeof(*f->cells));

        if (f->cells != NULL) {

            f->size = size;
            f->level = level;
            f->moves = 2 * f->size;
            f->player[0] = rand() % f->size;
            f->player[1] = rand() % f->size;
            f->treasure[0] = rand() % f->size;
            f->treasure[1] = rand() % f->size;

            for (int i = 0; i < f->size; i++) {

                f->cells[i] = malloc(f->size * sizeof(*f->cells[i]));

                if (f->cells[i] != NULL) {
                    for (int j = 0; j < f->size; j++) {
                        if (i == f->treasure[0] && j == f->treasure[1])
                            f->cells[i][j] = TREASURE;
                        else if (i == f->player[0] && j == f->player[1])
                            f->cells[i][j] = PLAYER;
                        else
                            f->cells[i][j] = EMPTY;
                    }
                } else {
                    f = NULL;
                }
            }

            int walls = level;

            while (walls != 0) {
                
                int x = rand () % size;
                int y = rand () % size;
            
                if (f->cells[y][x] == EMPTY) {
                    f->cells[y][x] = WALL;
                    walls--;
                }
            }
        } else {
            free(f);
            f = NULL;
        }
    }
    return f;
}

void free_field(Field *f)
{
    for (int i = 0; i < f->size; i++)
        free(f->cells[i]);
    free(f->cells);
    free(f);
}

void draw_field(Field *f, bool reveal)
{
    printf("\nLevel %d\n", f->level);
 
    for (int i = 0; i < 2 * f->size + 1; i++)
        printf("─");
    printf("\n");

    for(int i = 0; i < f->size; i++) {
        for(int j = 0; j < f->size; j++) {
            if (f->cells[i][j] == PLAYER)
                printf(" X");
            else if (reveal && f->cells[i][j] == TREASURE) {
                printf(" O");
            }
            else if (f->cells[i][j] == WALL)
                printf(" |");    
            else
                printf(" -");
        }
        printf("\n");
    }
  
    for (int i = 0; i < 2 * f->size + 1; i++)
        printf("─");
    printf("\n");
}

int getseed_md(void)
{
    _delay_ms(PMETER_DELAY);
    ADCSRA |= _BV(ADSC);
    loop_until_bit_is_clear(ADCSRA, ADSC);    
    return ADC;
}

int distance(Field *f)
{
    return abs(f->player[1] - f->treasure[1]) + abs(f->player[0] - f->treasure[0]);
}

void move(Field *f, int new_x, int new_y)
{
    if (!(f->cells[new_y][new_x] == WALL)) {
        f->cells[f->player[Y]][f->player[X]] = EMPTY;
        f->player[X] = new_x;
        f->player[Y] = new_y;
        f->cells[new_y][new_x] = PLAYER;
        f->moves--;
    }
}

void initADC_md(void)
{
    ADMUX |= _BV(REFS0);
    ADCSRA |= _BV(ADPS2) | _BV(ADPS1);
    ADCSRA |= _BV(ADEN);
}

void end_music(bool won)
{
    double notes[7] = { 523.250, 587.330, 659.250, 523.250, 659.250, 698.460, 783.990 };
    int limit = won ? 7 : 0;

    for(int i = won ? 0 : 6; won ? i < limit : i >= limit; won ? i++ : i--) {
        enableBuzzer();
        playTone(notes[i], NOTE_PLAY_DURATION);
        disableBuzzer();
    }
}

void dump_field_data(Field *f)
{
    printf("\n%d\n%d\n%d\n%d,%d\n%d,%d", 
        f->size, f->level, f->moves, f->player[0], f->player[1], f->treasure[0], f->treasure[1]);    
}

void dump_message(char msg[50])
{
    printf("\n%s", msg);
}
