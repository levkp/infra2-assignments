#include <util/delay.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <avr/interrupt.h>
#include <usart.h>
#include <display.h>
#include <ledlib.h>
#include <buttonlib.h>
#include "lunar-lander.h"

int t0_ofcnt = 0;
int t1_ofcnt = 0;
int burst_len = 0;
bool malloc_err = false;
Log *first, *current;

ISR(TIMER0_OVF_vect)
{
    t0_ofcnt++;
    if (t0_ofcnt == T0_OF_TO_SEC) {
        new_situation();
        t0_ofcnt = 0;
    }
}

ISR(TIMER1_OVF_vect)
{
    t1_ofcnt++;
    if (t1_ofcnt == T1_OF_TO_SEC) {
        burst_len++;
        t1_ofcnt = 0;
    }
}

ISR(PCINT0_vect)
{
    printf("Enterred button interrupt");
    // init_burst_timer();
    // while(buttonPushed(0));
    // reset_burst_timer();

    // printf("\nBURST LEN: %d\n", burst_len);
    // burst_len = 0;
}

void lunar_lander(void)
{
    initUSART();
    initDisplay();
    enableLeds(0b00001111);
    lightDownLeds(0b00001111);
    init_btn_interrupt();
    init_game_timer();

    sei();

   
    current = malloc(sizeof(Log));

    if (!current) {
        puts("Memory allocation error");
        return;
    }

    current->distance = STARTING_DISTANCE;
    current->fuel = STARTING_FUEL;
    current->speed = STARTING_SPEED;
    current->burst = 0;
    current->next = NULL;

    first = &*current;
    
    // TODO: add safe landing condition
    while(current->distance > 0) {
        show_param(current);

        if (malloc_err) {
            puts("Memory allocation error");
            return;
        }
    }

    if (current->landed)
        printf("You landed smoothly.");
    else
        printf("You crashed.");    

    current->distance = 0;

   // print_list(first);
    free_list(first);

    printf("\nEnd.");    
}

// Important TODO: implement led blinking for used tanks
void show_param(Log *current)
{
    int n_full_tanks = current->fuel / TANK_CAPACITY;
    int current_tank = current->fuel % TANK_CAPACITY;

    lightDownLeds(0b00001111);

    for (int i = 0; i < n_full_tanks; i++)
        lightUpLed(i);

    writeNumber(current->distance);
    // writeNumberAndWait(current->distance, 10);
}

// TODO: remove else
void new_situation(void) {
    current = recalc(current);
    if (!current)
        malloc_err = true;
    else
        printf("%d %d\n", current->distance, current->fuel);
}

// TODO: change burst value
// TODO: make parameterless, since current is global?
Log *recalc(Log *current)
{
    Log *new = malloc(sizeof(Log));

    if (!new) 
        return NULL;

    new->speed = current->speed + (G - current->burst / 5);
    new->distance = current->distance - current->speed;
    new->fuel = current->fuel - 20; //current->burst;
    new->burst = current->burst;
    new->landed = new->distance <= 3 && new->speed <= 5;
    new->next = NULL;
    
    current->next = new;

    return new;
}

void free_list(Log *first) {
    Log *i = first;
    while (i) {
        Log *next = i->next;
        free(i);
        i = next; 
    }
}

void init_game_timer(void)
{
    // Fast PWM 8 bit - TOP: 256
    TCCR0A |= _BV(WGM00) | _BV(WGM01);

    /*
     * Slowing down timer by 1024, because:
     * 16 MHz / 1024 = 0.015625 MHz = 15.625 kHz = 15625 Hz
     * 1 / 15625 Hz = 64 μs
     * 64 μs * 256 = 16.384 ms
     * 1000 / 16.384 = 61.04 ~= 61
     * That means one second equals to 61 overflow
     */

    TCCR0B |= _BV(CS02) | _BV(CS00);
    TIMSK0 |= _BV(TOIE0);
}

void init_burst_timer(void)
{
    // Fast PWM 10 bit - TOP: 1024
    TCCR1A |= _BV(WGM12) | _BV(WGM11) | _BV(WGM10);

    /*
     * 64 μs * 1024 = 65.536 ms
     * 1000 / 65.536 = 15.26 ~= 15
     * That means one second equals to 15 overflow
     */

    TCCR1B |= _BV(CS12) | _BV(CS10);    
    TIMSK1 |= _BV(TOIE1);
}

void reset_burst_timer(void)
{
    TCCR1A &= 0;
    TCCR1B &= 0;
    TIMSK1 &= 0;
}

void init_btn_interrupt(void)
{
    enableButton(0);
    PCICR |= _BV(PCIE1);
    PCMSK1 |= _BV(PC0);
}

// TODO: fix float printing
void print_list(Log *first)
{
    int i = 0;
    Log *iter;
    for(iter = first, i = 0; iter; iter = iter->next, i++) {
        printf("[%2d] Height: %d m Speed: %d.%3d m/s Fuel: %d l Burst: %d s\n",
            i, 
            iter->distance,
            (int)iter->speed, 
            (abs(iter->speed - (int)iter->speed) * 1000),
            iter->fuel,
            iter->burst);
        print_float(iter->speed);
        printf("\n");
    }
}

// TODO: remove if not used
// From Mr Boedt
void print_float(float f)
{
    printf("%d.", (int)f);
    int dec = (f - (int)f) * 1000;
    printf("%3d",abs(dec));
}
