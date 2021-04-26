#include <stdio.h>
#include <util/delay.h>
#include <ledlib.h>
#include "basic-c.h"

void basicC(void) {

    //task1();
    //task2();
    task3(1, 20);
}

void task1(void) {
    for (int i = 0; i < 4; i++) {
        enableLed(i);
        lightUpLed(i);
        _delay_ms(100);
        lightDownLed(i);
    }
}

void task2() {

    int led = 0;
    enableLed(led);

    for (int i = 0; i < 10; i++) {
        lightUpLed(led);
        _delay_ms(100);
        lightDownLed(led);
        _delay_ms(100);
    }
}

void task3(int led, int flashes) {

    enableLed(led);

    for (int i = 0; i < flashes; i++) {
        lightUpLed(led);
        _delay_ms(100);
        lightDownLed(led);
        _delay_ms(100);
    }
}
