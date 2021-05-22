#include <stdint.h>
#define NUMBER_OF_LEDS 4

void enableLed (int lednumber);

void lightUpLed (int lednumber);

void lightDownLed (int lednumber);

void enableLeds(uint8_t leds);

void lightUpLeds(uint8_t leds);

void lightDownLeds(uint8_t leds);

void blinkLed(int lednumber, int duration);

void dimLed(int lednumber, int percentage, double duration);

void fadeInLed(int lednumber, int duration);

void wrapper_delay_ms(double duration);


// Todo: implement later
int isEnabled(int led);
