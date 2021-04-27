#define TABLE_LENGTH 36
#define SHORT_BLINK 100
#define LONG_BLINK 1000
#define LEDS 0b00001111

typedef struct Morse {
    char ch;
    const char *code;
} Morse;

void morseTrainer();

void fillUpTable(Morse *table);

void countDownPattern();

int getRandomIndex(Morse *table);

void blinkCode(const char *code);

char *getCode(char ch);

void frivolousLedDance();
