#include <stdio.h>
#include <stdlib.h>

/*
Write a program that reads a number form the standard input,
than prints "Odd" if the number is odd, or "Even" it it is even.
*/
int is_even(int n);

int num;

int main()
{
    printf("Please provide a number:\n");
    scanf("%d", &num);
    if(is_even(num)==1){
        printf("Even\n");
    }
    else{
        printf("Odd\n");
    }


    return 0;
}

int is_even(int n){
    if(n % 2 == 0){
        return 1;
    }
    else{
        return 0;
    }
}
