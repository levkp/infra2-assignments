#include "metal-detector.c"

int main(void)
{

    Field *f = init_field(0, 5, 180);
    
    draw_field(f);
  

    free_field(f);

    return 0;
}