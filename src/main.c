#include <stdlib.h>
#include <util/delay.h>
#include <avr/io.h>
#include <usart.h>
#include <display.h>
#include <ledlib.h>
#include <buzzlib.h>

#include <avr/interrupt.h>

#include "metal-detector/metal-detector.h"
#include "projects/p4w4/lunar-lander.h"

int main()
{   

   
    lunar_lander();
    //metal_detector();

    return 0;
}
