#include <stdbool.h>
#define MIN_TAKE 1
#define MAX_TAKE 3
#define START_NUMBER 21
#define BUTTON_DELAY 500

void nim(void);
void initADC_nim(void);
int getseed(void);
void stats(int *moves, int moves_len, bool player_starts);
void lightUpSegments(int take, int matches_left, bool player_next);
