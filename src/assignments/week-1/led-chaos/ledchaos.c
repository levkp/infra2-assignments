#include <util/delay.h>
#include <avr/io.h>
#include <stdlib.h>
#include <ledlib.h>

#include "ledchaos.h"

void ledChaos() {

    srand(0);
    enableLeds(0b00001111);

    while(1) {
        uint8_t leds = rand() % 4;
        lightUpLeds(leds);
        _no_const_delay_ms(rangernd(100, 1000));
        lightDownLeds(leds);
    }

}

int rangernd(int low, int up) {
    return (rand() % up - low + 1) + low;
}