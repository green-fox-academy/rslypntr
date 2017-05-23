#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} point_t;

// TODO:
// Create a function that constructs a Point (returns a pointer to a new point)
// It should take its x and y coordinate as parameter

// TODO:
// Create a function that takes 2 Points as a pointer and returns the distance between them
point_t *point_maker(int a, int b);

int main()
{
    point_t *test_point = point_maker(10, 2);
    printf("x coordinate: %d\n", test_point->x);
    printf("y coordinate: %d\n", test_point->y);

    return 0;
}

point_t *point_maker(int a, int b)
{
    point_t *result;
    result = (point_t*) malloc(2* sizeof(int));
    result->x = a;
    result->y = b;
    return result;

}
