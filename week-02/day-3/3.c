#include <stdio.h>

/* Write a non void function which returns the value of PI, so the following number:
3.14159
Try it out in the main function by printing out the result of the pi generator function!
*/

float piGenerator();

float pi= 3.14159;

int main(){
    printf("%f", piGenerator());

    return 0;
}

float piGenerator(){
    return pi;
}


