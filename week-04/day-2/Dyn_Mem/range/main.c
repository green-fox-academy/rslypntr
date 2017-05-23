#include <stdio.h>
#include <stdlib.h>

/** TODO:
 * Create a function called "range" that creates a new array and returns a pointer to it.
 * It should fill the array with numbers based on its parameters.
 * It should take 3 parameters:
 * int from: the first number in the array
 * int to: it will fill the array till it would reach this number (so this number is not in the array)
 * int step: the step between the numbers
 *
 * Examples:
 * range(0, 10, 2) -> {0, 2, 4, 6, 8}
 * range(1, -8, -3) -> {1, -2, -5}
 *
 * It should delete any dynamically allocated resource before the program exits.
 */

 int *range(int from, int to, int step);

int main()
{
    int *test_array = range(0, 10, 2);
    int *test_array_2 = range(1, -8, -3);
    for(int i = 0; i < 5; i++) {
        printf("%d\t", test_array[i]);
    }
    printf("\n");
    for(int i = 0; i < 3; i++) {
        printf("%d\t", test_array_2[i]);
    }
    return 0;
}


 int *range(int from, int to, int step)
 {
     int size = (to - from) / step;
     int *result = (int*) malloc(size * sizeof(int));
     int num = from;
     result[0] = num;
     for(int i = 1; i < size; i++) {
        num += step;
        result[i] = num;
     }
     return result;

 }
