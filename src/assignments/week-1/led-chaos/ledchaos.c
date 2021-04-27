#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include <ledlib.h>
#include "ledchaos.h"

#define __DELAY_BACKWARD_COMPATIBLE__

void ledChaos() {

    srand(0);
    enableLeds(0b00001111);

    while(1) {
        /* TODO led 2 and 3 blinks at the beginning, then stay turned on */
        uint8_t leds = rand() % 4;
        printf("%d\n", leds);
        lightUpLeds(leds);
        _delay_ms(rangernd(100, 1000));
        //_no_const_delay_ms(rangernd(100, 1000));
        lightDownLeds(leds);
        //_no_const_delay_ms(100);
        _delay_ms(100);
    }

}

int rangernd(int low, int up) {
    return (rand() % up - low + 1) + low;
}
