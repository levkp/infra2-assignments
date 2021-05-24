#define MIN_SIZE 3
#define MAX_SIZE 10
#define MAX_LEVEL 9

typedef enum Cell {
    EMPTY, WALL, TREASURE, PLAYER
} Cell;

typedef struct Field {
    Cell **cells;
    int size;
    int level;
    int moves;
    int player[2];
    int treasure[2];
} Field;

void metal_detector(void);
Field *init_field(int level, int size, int seed);
void initADC_md(void);

void draw_field(Field *f);

void free_field(Field *f);

