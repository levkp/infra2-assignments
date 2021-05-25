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

    Field *f = init_field(3, 10, 100);

    bool horizontal = true;


    while (f->moves > 0) {

        draw_field(f);

        while (true) {

            writeCharToSegment(0, horizontal ? 'H' : 'V');
            
            if (buttonPushed(1))
                horizontal = !horizontal;

            if (buttonPushed(0)) {
                
                if (horizontal && f->player[X] != 0) {
                    f->cells[f->player[Y]][f->player[X]] = EMPTY;
                    f->player[X]--;
                    f->cells[f->player[Y]][f->player[X]] = PLAYER;
                    break;

                } else if (!horizontal && f->player[Y] != 0) {
                    f->cells[f->player[Y]][f->player[X]] = EMPTY;
                    f->player[Y]--;
                    f->cells[f->player[Y]][f->player[X]] = PLAYER;
                    break;
                }

            } else if (buttonPushed(2)) {

                if (horizontal && f->player[X] != f->size - 1) {
                    f->cells[f->player[Y]][f->player[X]] = EMPTY;
                    f->player[X]++;
                    f->cells[f->player[Y]][f->player[X]] = PLAYER;
                    break;
                } else if (!horizontal && f->player[Y] != f->size - 1) {
                    f->cells[f->player[Y]][f->player[X]] = EMPTY;
                    f->player[Y]++;
                    f->cells[f->player[Y]][f->player[X]] = PLAYER;
                    break;
                }
            }  
        }

        f->moves--;

    }

    free_field(f);
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

void draw_field(Field *f)
{
    for (int i = 0; i < 2 * f->size + 1; i++)
        printf("─");
    printf("\n");

    for(int i = 0; i < f->size; i++) {
        for(int j = 0; j < f->size; j++) {
            if (f->cells[i][j] == EMPTY)
                printf(" -");
            else if (f->cells[i][j] == TREASURE)
                printf(" O");
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
    // Manhattan distance - doesn't take walls into account
    return abs(f->player[1] - f->treasure[1]) + abs(f->player[0] - f->treasure[0]);
}

// void setnew(Field *f, int x, int y)
// {
//     if (!(f->cells[Y][X] == WALL)) {
//         f->cells[f->player[Y]][f->player[X]] = EMPTY;
//         f->player[X] = x;
//         f->player[Y] = y;
//         f->cells[y][x] = PLAYER;
//     }
// }

// void init_field2(Field *f, int level, int size, int seed)
// {
//     srand(seed);

//     f = malloc(sizeof(*f));

//     if (f != NULL) {

//         f->cells = malloc(size * sizeof(*f->cells));

//         if (f->cells != NULL) {

//             f->size = size > MAX_SIZE ? MAX_SIZE : size;
//             f->level = level > MAX_LEVEL ? MAX_LEVEL : level;
//             f->moves = 2 * f->size;
//             f->player[0] = rand() % f->size;
//             f->player[1] = rand() % f->size;
//             f->treasure[0] = rand() % f->size;
//             f->treasure[1] = rand() % f->size;

//             for (int i = 0; i < f->size; i++) {

//                 f->cells[i] = malloc(f->size * sizeof(*f->cells[i]));

//                 if (f->cells[i] != NULL) {
//                     for (int j = 0; j < f->size; j++) {
//                         f->cells[i][j] = EMPTY;
//                     }
//                 }
//             }
//         }
//     }
// }
