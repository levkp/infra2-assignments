#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <util/delay.h>
#include <usart.h>
#include <display.h>
#include <buttonlib.h>
#include <ledlib.h>
#include <buzzlib.h>
#include "metal-detector.h"

void metal_detector(void)
{
    initDisplay();
    initUSART();
    //enableBuzzer();

    int level = 1, size = 3, seed;
    int frequencies[15] = { 3600, 3800, 4000, 4200, 4400, 4600, 4800, 5000, 5200, 5400, 5600, 5800, 6000, 6200, 6400 };

    printf("\n===== METAL DETECTOR =====");
    printf("\nTurn the potentiometer to seed rand!");
    seed = getseed_md();

    while (level <= MAX_LEVEL) {

        bool horizontal = true;
        Field *f = init_field(level, size, seed);

        if (!f) {
            printf("\nError: unable to allocate memory.");
            break;
        }

        while (f->moves > 0) {
            
            draw_field(f);

            while (true) {

                writeCharToSegment(0, horizontal ? 'H' : 'V');
                   
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

            // enableBuzzer();
            // playTone(frequencies[distance(f) + 3], 250);
            // disableBuzzer();

            if (f->treasure[Y] == f->player[Y] && f->treasure[X] == f->player[X]) {
                printf("\nLevel completed!");
                break;
            }
        }
        
        if (f->moves == 0) {
            free_field(f);
            printf("You're out of moves!\n");
            break;
        }

        free_field(f);
        level++;
        size++;
    }


    printf("End");
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

            int walls = level - 1;

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

void draw_field(Field *f)
{
    //printf("\n\n\n\n\n\n\n\n\n\n");
    printf("\nLevel %d\n", f->level);
 
    for (int i = 0; i < 2 * f->size + 1; i++)
        printf("─");
    printf("\n");

    for(int i = 0; i < f->size; i++) {
        for(int j = 0; j < f->size; j++) {
            if (f->cells[i][j] == EMPTY)
                printf(" -");
            else if (f->cells[i][j] == TREASURE) {
                printf(" O");
            }
            else if (f->cells[i][j] == WALL)
                printf(" |");    
            else
                printf(" X");
        }
        printf("\n");
    }
  
    for (int i = 0; i < 2 * f->size + 1; i++)
        printf("─");
    printf("\n");
}

void free_field(Field *f)
{
    for (int i = 0; i < f->size; i++)
        free(f->cells[i]);
    free(f->cells);
    free(f);
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

int getseed_md(void)
{
    //_delay_ms(5000);
    ADCSRA |= _BV(ADSC);
    loop_until_bit_is_clear(ADCSRA, ADSC);    
    return ADC;
}
