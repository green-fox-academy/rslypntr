#include <stdio.h>

int main()
{
    int high_number = 6655;
    int low_number = 2;

    int* high_number_pointer = &low_number;
    int* low_number_pointer = &high_number;
    //TODO:
    // Please fix the problem and swap where the pointers point,
    // without using the "&" operator.
    int *temp_ptr = high_number_pointer;
    high_number_pointer = low_number_pointer;
    low_number_pointer = temp_ptr;

    printf("high_number_pointer points to value: %d\n", *high_number_pointer);
    printf("low_number_pointer points to value: %d\n", *low_number_pointer);



    return 0;
}
