#include <stdio.h>

int main() {
    int high_number = 2;
    int low_number = 6655;

    int* hight_number_pointer = &high_number;
    int* low_number_pointer = &low_number;

    printf("BEFORE:\n");
    printf("Value of hight_number_pointer is: %x", hight_number_pointer);
    printf("\nValue pointed at by hight_number_pointer is: %d", *hight_number_pointer);

    printf("\nValue of lowt_number_pointer is: %x", low_number_pointer);
    printf("\nValue pointed at by low_number_pointer is: %d", *low_number_pointer);
    printf("\n");



    //TODO:
    // Please fix the problem and swap the value of the variables,
    // without using the "high_number" and the "low_number" variables.
    int temp = hight_number_pointer;
    hight_number_pointer = low_number_pointer;
    low_number_pointer = temp;
    printf("\nAFTER:\n");
    printf("Value of hight_number_pointer is: %x", hight_number_pointer);
    printf("\nValue pointed at by hight_number_pointer is: %d", *hight_number_pointer);

    printf("\nValue of low_number_pointer is: %x", low_number_pointer);
    printf("\nValue pointed at by low_number_pointer is: %d", *low_number_pointer);

     printf("\n");



    return 0;
}
