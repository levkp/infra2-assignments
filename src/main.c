#include <util/delay.h>
#include <avr/io.h>
#include <ledlib.h>
#include <usart.h>

//#include "assignments/week-1/led-library/ledlib-test.h"
//#include "assignments/week-1/dimmed-leds/dimled-test.h"
#include "assignments/week-1/led-chaos/ledchaos.h"

int main(void)
{

    initUSART();
    ledChaos();
    



    return 0;
}
