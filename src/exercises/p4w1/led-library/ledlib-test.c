#include <util/delay.h>
#include <ledlib.h>
#include "ledlib-test.h"

void ledlibTest(void) {

    //The LED library implementation can be found in lib/ledlib.c

    uint8_t testleds = 0b0001111;
    enableLeds(testleds);
    lightUpLeds(testleds);
    _delay_ms(1000);
    lightDownLeds(testleds);
    
}