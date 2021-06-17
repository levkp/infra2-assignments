#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <usart.h>
#include <display.h>
#include <ledlib.h>
#include <buttonlib.h>
#include "lunar-lander.h"

void lunar_lander(void)
{
    initUSART();
    initDisplay();
    enableLeds(0b00001111);
    lightDownLeds(0b00001111);

    Log *first, *current;

    // TODO: check memory allocation success
    current = malloc(sizeof(Log));
    current->distance = STARTING_DISTANCE;
    current->fuel = STARTING_FUEL;
    current->speed = STARTING_SPEED;
    current->burst = 0;
    current->next = NULL;

    first = &*current;
    
    while(current->distance > 0) {
        show_param(current);
        current = recalc(current);
    }

    if (current->landed)
        printf("You landed smoothly.");
    else 
        printf("You crashed.");    

    free_list(first);

    printf("End.");    
}

// Important TODO: implement led blinking for used tanks
void show_param(Log *current)
{
    int n_full_tanks = current->fuel / TANK_CAPACITY;
    // int current_tank = fuel % TANK_CAPACITY;

    lightDownLeds(0b00001111);

    for (int i = 0; i < n_full_tanks; i++)
        lightUpLed(i);

    writeNumber(current->distance);
}

// Important TODO: check memory allocation success
// TODO: change burst value
Log *recalc(Log *current)
{
    Log *new = malloc(sizeof(Log));
    new->speed = current->speed + (G - current->burst / 5);
    new->distance = current->distance - current->speed;
    new->fuel = current->fuel - current->burst;
    new->burst = current->burst;
    new->landed = new->distance <= 3 && new->speed <= 5;
    new->next = NULL;
    
    current->next = new;

    return new;
}

void free_list(Log *first) {
    Log *i = first;
    while (i) {
        Log *next = i->next;
        free(i);
        i = next; 
    }
}

