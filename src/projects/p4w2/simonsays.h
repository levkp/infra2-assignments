#include <stdint.h>
#include <stdbool.h>

#define PATTERN_LENGTH 10
#define PATTERN_DELAY 500

void simonsays(void);
void startup(void);
void seedtest(void);
void generate(uint8_t series[]);
void printPuzzle(uint8_t series[], int length);
bool play(uint8_t series[]);
bool readInput(uint8_t series[], int patternLength);
