#include <stdio.h>

int main()
{
    int high_number = 2;
    int low_number = 6655;

    int* high_number_pointer = &high_number;
    int* low_number_pointer = &low_number;
    //TODO:
    // Please fix the problem and swap the value of the variables,
    // without using the "high_number" and the "low_number" variables.

    int *tmp_pointer;
    tmp_pointer = high_number_pointer;
    high_number_pointer = low_number_pointer;
    low_number_pointer = tmp_pointer;

    printf("high_number_pointer points to value: %d\n", *high_number_pointer);
    printf("low_number_pointer points to value: %d\n", *low_number_pointer);


    return 0;
}
