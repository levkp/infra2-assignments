#include <inttypes.h>

#define NUMBER_OF_LEDS 4

void enableLed (int lednumber);

void lightUpLed (int lednumber);

void lightDownLed (int lednumber);

void enableLeds(uint8_t leds);

void lightUpLeds(uint8_t leds);

void lightDownLeds(uint8_t leds);

void dimLed(int lednumber, int percentage, double duration);

void fadeInLed(int lednumber, int duration);

void _no_const_delay_ms(double duration);
