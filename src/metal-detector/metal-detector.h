#define MIN_SIZE 3
#define MAX_SIZE 10
#define MAX_LEVEL 10
#define X 1
#define Y 0

typedef enum Cell {
    EMPTY, WALL, TREASURE, PLAYER
} Cell;

typedef struct Field {
    Cell **cells;
    int size, level, moves, player[2], treasure[2];
} Field;

void metal_detector(void);

Field *init_field(int level, int size, int seed);

void initADC_md(void);

void draw_field(Field *f);

void free_field(Field *f);

// Manhattan distance - doesn't take walls into account
int distance(Field *f);

void move(Field *f, int new_x, int new_y);
