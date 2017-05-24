#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
float point_distance(point_t *a, point_t *b);

int main()
{
    point_t *test_point = point_maker(10, 2);
    point_t *test_point_2 = point_maker(5, 5);
    printf("x coordinate: %d\n", test_point->x);
    printf("y coordinate: %d\n", test_point->y);

    printf("Distance of the two points is: %f", point_distance(test_point, test_point_2));





    return 0;
}

point_t *point_maker(int a, int b)
{
    point_t *result;
    result = (point_t*) malloc(sizeof(point_t));
    result->x = a;
    result->y = b;
    return result;
}

float point_distance(point_t *a, point_t *b)
{
    float distance = sqrt(pow((b->x - a->x), 2) + pow((b->y - a->y), 2));
    return distance;
}
