#include <stdbool.h>
#define MIN_TAKE 1
#define MAX_TAKE 3
#define START_NUMBER 21

void nim(void);
void initADC_nim(void);
int getseed(void);
void stats(void);
void lightUpSegments(int take, int matches_left, bool player_next);
