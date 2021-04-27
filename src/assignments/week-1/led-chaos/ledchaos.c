#include <stdio.h>
#include <stdlib.h>
<<<<<<< HEAD
#include <util/delay.h>
#include <ledlib.h>
#include "ledchaos.h"

//#define __DELAY_BACKWARD_COMPATIBLE__

=======
#include <ledlib.h>
#include "ledchaos.h"

>>>>>>> def54da823e08216d43127953f69c04849970f84
void ledChaos() {

    srand(0);
    enableLeds(0b00001111);
<<<<<<< HEAD
    lightDownLeds(0b00001111);

    while(1) {
        /* TODO led 2 and 3 blink at the beginning, then stay turned on */
        uint8_t leds = rand() % 4;
        leds += 2;
        printf("%d\n", leds);
        lightUpLeds(leds);
        //_delay_ms(rangernd(100, 1000));
        wrapper_delay_ms(rangernd(100, 1000));
        lightDownLeds(leds);
        _delay_ms(100);
=======

    while(1) {
        /* TODO led 2 and 3 blinks at the beginning, then stay turned on */
        uint8_t leds = rand() % 4;
        printf("%d\n", leds);
        lightUpLeds(leds);
        _no_const_delay_ms(rangernd(100, 1000));
        lightDownLeds(leds);
        _no_const_delay_ms(100);
>>>>>>> def54da823e08216d43127953f69c04849970f84
    }

}

int rangernd(int low, int up) {
    return (rand() % up - low + 1) + low;
}
