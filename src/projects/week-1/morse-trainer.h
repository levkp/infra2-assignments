#define TABLE_LENGTH 36
#define SHORT_BLINK 100
#define LONG_BLINK 1000

typedef struct Morse {
    char ch;
    const char *code;
} Morse;

void morseTrainer();

void fillUpTable(Morse *table);

char *getRandomCode(Morse *table);

void countDownPattern();

char *getCode(char ch);
