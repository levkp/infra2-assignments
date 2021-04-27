#include <ledlib.h>
#include "dimled-test.h"

void dimledtest(void) {

    //The implementation of dimLed and fadeInLed can be found in lib/ledlib.c

    //Dimming all LEDs for 10 seconds
    /* TODO: It dims significantly longer than 10 seconds. Why?
     * TODO: The change in brightness is clearly visible, but not totally
     * accurate. For example 1% is the same as 10%
     */

    dimLed(0, 20, 1000);
    dimLed(1, 40, 1000);
    dimLed(2, 60, 1000);
    dimLed(3, 80, 1000);

    // TODO: the change of brightness is visible, but not as neat as I expected. Why?
    fadeInLed(0, 10000);
}