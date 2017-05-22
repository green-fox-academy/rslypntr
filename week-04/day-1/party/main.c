#include <stdio.h>
#include <stdlib.h>

// Write a program that asks for two numbers
// The first number represents the number of girls that comes to a party, the
// second the boys.

// It should print "The party is excellent!" if the the number of girls and
// boys are equal and there are more people coming than 20

// It should print "Quite cool party!"
// if there are more than 20 people coming but the girl - boy ratio is not 1-1

// It should print: "Average party..."
// if there are less people coming than 20

// It should print: "Sausage party"
// if no girls are coming, regardless the count of the people
int girls_count;
int boys_count;

int main()
{
    printf("How many girls are coming?\n");
    scanf("%d", &girls_count);
    printf("How many boys are coming?\n");
    scanf("%d", &boys_count);
    if(girls_count ==0){
        printf("Sausage party\n");
    }else if(girls_count + boys_count >= 20){
        if(girls_count == boys_count){
            printf("The party is excellent!\n");
        }
        else{
            printf("Quite cool party!\n");
        }
    }else{
        printf("Average party...\n");
    }


    return 0;
}
