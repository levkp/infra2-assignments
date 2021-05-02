#include <util/delay.h>
#include <avr/io.h>
#include <ledlib.h>
#include <usart.h>

#define __DELAY_BACKWARD_COMPATIBLE__

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

    return 0;
}
