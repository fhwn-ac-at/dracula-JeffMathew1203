#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

typedef struct {
    float x;
    float y;
} point;

bool is_point_in_circle(point p)
{
    float dx = p.x;
    float dy = p.y;
    return (dx * dx + dy * dy) <= 1;
}

point random_point()
{

    return (point) {
        .x = 1 - 2*(float)rand() / (float)RAND_MAX,
        .y = 1 - 2*(float)rand() / (float)RAND_MAX,
    };
}

point random_point_in_circle()
{
    point p;
    do {
        p = random_point();
    } while (!is_point_in_circle(p));
    return p;
}


int main(void) {

    srand(time(NULL));

    point p = random_point();

    if (is_point_in_circle(p)) {
        printf("The point (%.2f, %.2f) is inside the unit circle.\n", p.x, p.y);
    } else {
        printf("The point (%.2f, %.2f) is NOT inside the unit circle.\n", p.x, p.y);
    }

    return 0;
}