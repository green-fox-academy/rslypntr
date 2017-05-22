#include <stdio.h>
#include <stdlib.h>


//make it work
int ans;
int number;

int main(){
    srand(time(NULL));
    number = rand() %100;
    printf("\t**********\n\tHello User\n\t**********\nYou have an integer named 'number'\n");
    printf("- for its memory address please press 1\n");
    printf("- for its current value please press 2\n");
    printf("- to double its value please press 3\n");
    scanf("%d", &ans);
    switch(ans){
    case 1:
        printf("%p", &number);
        break;
    case 2:
        printf("%d", number);
        break;
    case 3:
        number*=2;
        break;
    default:
        printf("Invalid input\n");
        break;
    }
return 0;
}

