#include <util/delay.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <usart.h>
#include <display.h>
#include <buttonlib.h>
#include <ledlib.h>
#include "metal-detector.h"

void metal_detector(void)
{
    initDisplay();
    initUSART();

    int level = 1;
    int size = 3;

    while (level <= MAX_LEVEL) {

        bool horizontal = true;
        Field *f = init_field(level, size, 100);

        if (!f) {
            printf("\nError: unable to allocate memory.");
            break;
        }

        printf("\nLevel %d", level);

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

            if (f->treasure[Y] == f->player[Y] && f->treasure[X] == f->player[X]) {
                printf("\nLevel completed!");
                break;
            }
        }

        free_field(f);
 
        if (f->moves == 0) {
            printf("You're out of moves!\n");
            break;
        }

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
    printf("\n");
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
