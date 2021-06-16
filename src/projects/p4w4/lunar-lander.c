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
        show_param(5000, TANK_CAPACITY * 3 - 1);
    }
    
}

//TODO: implement flashing faster as tank gets emptier

void show_param(int distance, int fuel)
{

    int tank0, tank1, tank2, tank3;

    tank0 = fuel - 3 * TANK_CAPACITY;

    if (tank0 > 0) {

        tank1 = tank2 = tank3 = TANK_CAPACITY;
        tank0 == TANK_CAPACITY ? lightUpLed(0) : blinkLed(0, 200);
        lightUpLeds(0b00000111);

    } else {

        lightDownLed(0);

        tank1 = fuel - 2 * TANK_CAPACITY;
        
        if (tank1 > 0) {

            tank2 = tank3 = TANK_CAPACITY;
            tank1 == TANK_CAPACITY ? lightUpLed(1) : blinkLed(1, 200);
            lightUpLeds(0b00000011);
            
        } else {

            lightDownLed(1);

            tank2 = fuel - TANK_CAPACITY;

            if (tank2 > 0) {

                tank3 = TANK_CAPACITY;
                tank2 == TANK_CAPACITY ? lightUpLed(2) : blinkLed(2, 200);
                lightUpLed(3);

            } else {

                lightDownLed(2);

                tank3 = fuel;
                tank3 == TANK_CAPACITY ? lightUpLed(3) : blinkLed(3, 200);
            }
        }
    }



   // int fuel_burned = STARTING_FUEL - fuel;    
    writeNumber(distance);


    
}
