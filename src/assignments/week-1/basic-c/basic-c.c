#include <stdio.h>
#include <util/delay.h>
#include <ledlib.h>
#include "basic-c.h"

void basicC(void) {

    //task1();

    //task2();

    //task3(1, 20);

    //task4(3);

    int arr[] = { 0, 1, 2, 3, 3, 2, 1, 0, 2, 2 };
    task5(arr);

   //task6();

    

}

void task1(void) 
{
    for (int i = 0; i < 4; i++) {
        enableLed(i);
        lightUpLed(i);
        _delay_ms(100);
        lightDownLed(i);
    }
}

void task2()
{
    int led = 0;
    enableLed(led);

    for (int i = 0; i < 10; i++) {
        lightUpLed(led);
        _delay_ms(100);
        lightDownLed(led);
        _delay_ms(100);
    }
}

void task3(int led, int flashes) 
{
    enableLed(led);

    for (int i = 0; i < flashes; i++) {
        lightUpLed(led);
        _delay_ms(100);
        lightDownLed(led);
        _delay_ms(100);
    }
}

void task4(int led) 
{
    enableLed(led);

    for (int i = 10; i <= 1000; i += 50) {
        blinkLed(led, i);
    }
}

void task5(int arr[]) 
{
    enableLeds(0b00001111);

    for (int i = 0; i < 10; i++) {
        int led = arr[i];
        blinkLed(led, 1000);
    }
}

void task6(void) 
{
    const int length = 1000 / 50;
    int arr[length];
    int value = 10, led = 0;

    enableLed(led);

    for (int i = 0; i < length; i++, value += 50) {
        arr[i] = value;
        // Not much use of the array, but the exercise asks for it
        blinkLed(led, arr[i]);
    }    
}
