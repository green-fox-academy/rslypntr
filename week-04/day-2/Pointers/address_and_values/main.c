#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Print out the addresses with and without pointer
print out the values with and without pointer
 */


int main()
{
    int number = 2017;
    float Pi = 3.14;
    char letter = 't';
    //printing the addresses without pointers
    printf("Address of number: %p\n", &number);
    printf("Address of Pi: %p\n", &Pi);
    printf("Address of letter: %p\n", &letter);
    printf("\n");

    //printing the addresses with pointers
    int *number_ptr = &number;
    float *Pi_ptr = &Pi;
    char *letter_ptr = &letter;
    printf("Address of number: %p\n", number_ptr);
    printf("Address of Pi: %p\n", Pi_ptr);
    printf("Address of letter: %p\n", letter_ptr);


    return 0;
}
