#include "metal-detector.c"

int main(void)
{
    int walls = 0;
    for(int i = 3; i < 10; i++) {

        Field *f = init_field(walls, i, 100);
        draw_field(f);
        printf("Distance: %d\n\n", distance(f));
        free_field(f);
        walls++;

    }

    return 0;
}