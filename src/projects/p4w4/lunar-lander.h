#include <stdbool.h>

#define STARTING_SPEED 100.0
// TODO: set back to 9999
#define STARTING_DISTANCE 8000
#define TANK_CAPACITY 375
#define STARTING_FUEL 4 * TANK_CAPACITY
#define G 1.622
#define T0_OF_TO_SEC 61
#define T1_OF_TO_SEC 15

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
void reset_burst_timer(void);
void print_list(Log *first);
void new_situation(void);
void print_float(float f);
void init_btn_interrupt(void);


void print_entry(Log *entry);
