#include <stdio.h>
#include <stdlib.h>
/*
Create a program which ask for a name and an age.
From the age it tells the user when he or she will be 100 years old.
You should only take care of the years (don't bother with the months or days).
*/

char name [256];
int age;
int hundred_years;

int main()
{   printf("Please enter your name:\n");
    scanf("%s", name);
    printf("Please enter your age:\n");
    scanf("%d", &age);
    hundred_years = 2017 - age + 100;
    printf("%s, you will be 100 years old in %d\n", name, hundred_years);


    return 0;
}
