#include <stdio.h>

int main() {
    int high_number = 6655;
    int low_number = 2;

    int* hight_number_pointer = &low_number;
    int* low_number_pointer = &high_number;
    //TODO:
    // Please fix the problem and swap where the pointers point,
    // without using the "&" operator.
    int temp;
    temp = hight_number_pointer;
    hight_number_pointer = low_number_pointer;
    low_number_pointer = temp;

    printf("Value of hight_number_pointer: %x", hight_number_pointer);
    printf("\nValue of high_number: %d", *hight_number_pointer);

    printf("\nValue of low_number_pointer: %x", low_number_pointer);
    printf("\nValue of low_number: %d", *low_number_pointer);

    return 0;
}
