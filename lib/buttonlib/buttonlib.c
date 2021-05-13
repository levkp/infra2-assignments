#include <avr/io.h>
#include <buttonlib.h>

void enableButton(int button) 
{
    if (button >= 0 && button <= NUMBER_OF_BUTTONS) {
        DDRC &= ~(1 << (PC1 + button));
        PORTC |= (1 << (PC1 + button));
    }
}

int buttonPushed(int button) {
    return (PINC & (1 << (PC1 + button))) == 0 ? 1 : 0;
}

int buttonReleased(int button) {
    return buttonPushed(button) ? 0 : 1;
}
