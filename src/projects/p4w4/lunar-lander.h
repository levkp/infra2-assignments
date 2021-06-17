#include <stdbool.h>

#define STARTING_SPEED 100.0
#define STARTING_DISTANCE 9999
#define TANK_CAPACITY 375
#define STARTING_FUEL 4 * TANK_CAPACITY
#define G 1.622
#define SEC_TO_OVERFLOW 61

typedef struct Log {
    int distance;
    int fuel;
    int burst;
    bool landed;
    float speed;
    struct Log *next;
} Log;

Log *recalc(Log *current);
void lunar_lander(void);
void show_param(Log *current);
void free_list(Log *first);
void init_game_timer(void);
void init_burst_timer(void);
void print_log(Log *first);
void new_situation(void);
