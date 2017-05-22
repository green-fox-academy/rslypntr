#include <stdio.h>
#include <stdlib.h>

/* Write a function which is called "get_fibonacci_number". It returns the "N"th
 * Fibonacci number, where "N" is received as a paramter.
 * For example:
 *  - get_fibonacci_number(1) returns 0
 *  - get_fibonacci_number(2) returns 1
 *  - get_fibonacci_number(3) returns 1
 *  - get_fibonacci_number(4) returns 2
 *  - get_fibonacci_number(5) returns 3
 *  - get_fibonacci_number(6) returns 5
 *
 *  If the function gets invalid parameter it returns -1.
 */

/*
Using that function create a program, which gets a number from the user, and
prints out the "N"th Fibonacci number, where "N" is the user given number.

Alert the user if he/she entered invalid value.
*/
int get_fibonacci_number(int N);

int num;

int main()
{
    printf("Please enter a number:\n");
    scanf("%d", &num);
    if(get_fibonacci_number(num) == -1){
        printf("You provided an invalid value!");
    }
    else{
        printf("The %d - th Fibonacci number is: %d\n", num, get_fibonacci_number(num));
    }

    return 0;
}

int get_fibonacci_number(int N){
    if(N < 1){
        return -1;
    }
    else if(N == 1){
        return 0;
    }
    else if(N == 2){
        return 1;
    }
    else{
        return get_fibonacci_number(N - 1) + get_fibonacci_number(N - 2);
    }
}
