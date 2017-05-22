#include <stdio.h>
#include <stdlib.h>

/*
Create a program which writes down the following sentence 100 times:
"I won't cheat on the test!"

Do it with:
    - for loop
    - while loop
    - do while loop

Also create a funtion which does the same.
*/
void no_cheat();

int main()
{

    //solution with for loop
    for(int i=0; i < 100; i++){
        printf("I won't cheat on the test!\n");
    }
    printf("--------------------------\n");

    //solution with while loop
    int i=0;
    while(i < 100){
        printf("I won't cheat on the test!\n");
        i++;
    }
    printf("--------------------------\n");

    //solution with do-while loop
    int j = 0;
    do{
        printf("I won't cheat on the test!\n");
        j++;
    }while(j < 100);
    printf("--------------------------\n");
    no_cheat();


    return 0;
}

void no_cheat(){
    for(int i=0; i < 100; i++){
        printf("I won't cheat on the test!\n");
    }
    return 0;
}
