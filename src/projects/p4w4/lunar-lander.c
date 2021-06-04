#include <stdio.h>
#include <stdbool.h>
#include <display.h>
#include <ledlib.h>
#include <buttonlib.h>
#include "lunar-lander.h"

void lunar_lander(void)
{
    initDisplay();
    enableLeds(0b00001111);
    lightDownLeds(0b00001111);

    while(true) {

    }

}

void show_param(int distance, int fuel)
{
    int fuel_burned = STARTING_FUEL - fuel;
    

    writeNumber(distance);
    



}