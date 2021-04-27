#include <stdlib.h>
#include <util/delay.h>
#include <avr/io.h>
#include <ledlib.h>
#include "morse-trainer.h"

void morseTrainer() 
{

    Morse table[TABLE_LENGTH];
    fillUpTable(table);
    countDownPattern();

    for (int i = 0; i < 10; i++) {
        blinkCode(getRandomCode(table));
    }


}

char *getRandomCode(Morse *table) 
{
    srand(0);
    return table[rand() % 36].code;
}

void blinkCode(char *code) 
{

    enableLeds(0b00001111);
    

    for (int i = 0; i < strlen(code); i++) {
        


    }
}

void countDownPattern() 
{
    enableLeds(0b00001111);
    _delay_ms(1000);

    for (int i = 0; i < 4; i++) {
        lightDownLed(i);
        _delay_ms(1000);
    }
}

void fillUpTable(Morse *table) 
{
    int next_letter = 65;
    int next_number = 48;
    const int endOfLetters = 25;

    for (int i = 0; i < TABLE_LENGTH; i++) {
        
        if (i <= endOfLetters) {
            table[i].ch = next_letter++;
        } else {
            table[i].ch = next_number++;
        }

        table[i].code = getCode(table[i].ch);
        
    }
}

char *getCode(char ch) 
{

    switch(ch) {

        case 'A': return ".-";
        case 'B': return "-...";
        case 'C': return "-.-.";
        case 'D': return "-..";
        case 'E': return ".";
        case 'F': return "..-.";
        case 'G': return "--.";
        case 'H': return "....";
        case 'I': return "..";
        case 'J': return ".---";
        case 'K': return "-.-";
        case 'L': return ".-..";
        case 'M': return "--";
        case 'N': return "-.";
        case 'O': return "---";
        case 'P': return ".--.";
        case 'Q': return "--.-";
        case 'R': return ".-.";
        case 'S': return "...";
        case 'T': return "-";
        case 'U': return "..-";
        case 'V': return "...-";
        case 'W': return ".--";
        case 'X': return "-..-";
        case 'Y': return "-.--";
        case 'Z': return "--..";
        case '0': return "-----";
        case '1': return ".----";
        case '2': return "..---";
        case '3': return "...--";
        case '4': return "....-";
        case '5': return ".....";
        case '6': return "-....";
        case '7': return "--...";
        case '8': return "---..";
        default: return "----.";
    }
}
