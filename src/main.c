#include <util/delay.h>
#include <avr/io.h>
#include <ledlib.h>
#include <usart.h>

<<<<<<< HEAD
#define __DELAY_BACKWARD_COMPATIBLE__

=======
>>>>>>> def54da823e08216d43127953f69c04849970f84
//#include "assignments/week-1/led-library/ledlib-test.h"
//#include "assignments/week-1/dimmed-leds/dimled-test.h"
#include "assignments/week-1/led-chaos/ledchaos.h"
#include "assignments/week-1/basic-c/basic-c.h"

<<<<<<< HEAD
#include "projects/week-1/morse-trainer.h";

/*
=======

>>>>>>> def54da823e08216d43127953f69c04849970f84
void writeMask(volatile uint8_t *reg, uint8_t bitmask) 
{
    *reg = bitmask;
}

#define HIGH 1
#define LOW 0

void writePin(volatile uint8_t *reg, uint8_t pin, uint8_t value) 
{
    
}
<<<<<<< HEAD
*/
=======

>>>>>>> def54da823e08216d43127953f69c04849970f84

int main(void)
{

    initUSART();
    //basicC();
<<<<<<< HEAD
    //ledChaos();


    countDownPattern();



    
=======
    ledChaos();
>>>>>>> def54da823e08216d43127953f69c04849970f84

    return 0;
}
