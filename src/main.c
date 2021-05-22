#include <util/delay.h>
#include <avr/io.h>
#include <usart.h>
#include <display.h>

#include "projects/p4w3/nim.h"

int main()
{

    //initUSART();
    initDisplay();
    nim();
    

    
    
    return 0;
}