#include <util/delay.h>
#include <avr/io.h>
#include <ledlib.h>
#include <usart.h>

#define __DELAY_BACKWARD_COMPATIBLE__

//#include "assignments/week-1/led-library/ledlib-test.h"
//#include "assignments/week-1/dimmed-leds/dimled-test.h"
#include "assignments/week-1/led-chaos/ledchaos.h"
#include "assignments/week-1/basic-c/basic-c.h"

#include "projects/week-1/morse-trainer.h";

/*
void writeMask(volatile uint8_t *reg, uint8_t bitmask) 
{
    *reg = bitmask;
}

#define HIGH 1
#define LOW 0

void writePin(volatile uint8_t *reg, uint8_t pin, uint8_t value) 
{
    
}
*/

int main(void)
{

    initUSART();
    //basicC();
    //ledChaos();


    countDownPattern();



    

    return 0;
}
