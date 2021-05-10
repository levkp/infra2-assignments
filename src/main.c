#include <util/delay.h>
#include <avr/io.h>
#include <ledlib.h>
#include <usart.h>
#include <display.h>
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include <buttonlib.h>
#include "assignments/p4w2/button-library/buttonlib-test.h"

int main()
{

    initUSART();
    
    buttonlibTest();

    

    return 0;
}