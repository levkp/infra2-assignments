#define STARTING_SPEED 100
#define STARTING_DISTANCE 9999
#define STARTING_FUEL 1500
#define TANK_CAPACITY 375
#define G 1.622

typedef struct LogEntry {
    char *data;
    int second;
} LogEntry;

typedef struct Log {
    LogEntry *entries;
    int length;
} Log;

void lunar_lander(void);
void show_param(int distance, int fuel);
