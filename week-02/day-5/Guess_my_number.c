#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


int number;
int rng;
int * pt_rng = &rng;
int life =5;
int guess;
int * pt_guess = &guess;
bool guessed = false;



int main()
{
    srand(time(NULL));
    printf("Please provide a range starting from 0\n");
    scanf("%d", pt_rng);
    number = rand()%(rng+1);

    printf("I have a number between 0 and %d. You have 5 lives\nPlease make a guess\n", *pt_rng);

    while(guessed == false && life >=0){
        scanf("%d", pt_guess);
        if(guess < number){
            printf("Too low. You have %d lives left\n", life );
            life--;
        }
        else if(guess > number){
            printf("Too high. You have %d lives left\n", life );
            life--;
        }
        else{
            printf("Congratulations! You won");
            guessed = true;
        }
    }

    return 0;
}
