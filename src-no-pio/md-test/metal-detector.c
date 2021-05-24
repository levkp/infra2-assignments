#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//#include <usart.h>
//#include <display.h>
//#include <buttonlib.h>
//#include <ledlib.h>
#include "metal-detector.h"

// void metal_detector(void)
// {

//     initDisplay();
//     initUSART();

// }

Field *init_field(int level, int size, int seed)
{
    srand(seed);

    Field *f = malloc(sizeof(*f));

    if (f != NULL) {

        f->cells = malloc(size * sizeof(*f->cells));

        if (f->cells != NULL) {

            f->size = size > MAX_SIZE ? MAX_SIZE : size;
            f->level = level > MAX_LEVEL ? MAX_LEVEL : level;
            f->moves = 2 * f->size;
            f->player[0] = rand() % f->size;
            f->player[1] = rand() % f->size;
            f->treasure[0] = rand() % f->size;
            f->treasure[1] = rand() % f->size;

            for (int i = 0; i < f->size; i++) {

                f->cells[i] = malloc(f->size * sizeof(*f->cells[i]));

                if (f->cells[i] != NULL) {
                    for (int j = 0; j < f->size; j++) {
                        if (i == f->treasure[0] && j == f->treasure[j]) {
                            f->cells[i][j] = TREASURE;
                        } else if (i == f->player[0] && j == f->player[j]) {
                            f->cells[i][j] = PLAYER;
                        } else {
                            f->cells[i][j] = EMPTY;
                        }
                    }
                }
            }
        }
    }

    return f;
}

void draw_field(Field *f)
{

    for (int i = 0; i < 2 * f->size; i++)
        printf("-");
    printf("\n");

    for(int i = 0; i < f->size; i++) {
        for(int j = 0; j < f->size; j++) {
            if (f->cells[i][j] == EMPTY) {
                printf(" -");
            } else if (f->cells[i][j] == TREASURE) {
                printf(" O");
            } else {
                printf(" X");
            }
        }
        printf("\n");
    }
  

    for (int i = 0; i < 2 * f->size; i++)
        printf("-");
}

void free_field(Field *f)
{
    for (int i = 0; i < f->size; i++)
        free(f->cells[i]);
    free(f->cells);
    free(f);
}





// void init_field(Field *int level, int size, int seed)
// {
//     srand(seed);

//     Field *f = malloc(sizeof(*f));

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

//     return f;
// }