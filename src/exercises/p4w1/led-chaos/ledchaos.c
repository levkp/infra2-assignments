#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include <ledlib.h>
#include "ledchaos.h"

void ledChaos(int iterations) {

    srand(0);
    enableLeds(0b00001111);
    lightDownLeds(0b00001111);

    for (int i = 1; i <= iterations; i++) {
        /* TODO led 2 and 3 blink at the beginning, then stay turned on */
        uint8_t leds = rand() % 4;
        leds += 2;
        //printf("%d\n", leds);
        lightUpLeds(leds);
        _delay_ms(rangernd(100, 1000));
        //wrapper_delay_ms(rangernd(100, 1000));
        lightDownLeds(leds);
        _delay_ms(100);
    }
}

int rangernd(int low, int up) {
    return rand() % (up + 1 - low) + low;
}
