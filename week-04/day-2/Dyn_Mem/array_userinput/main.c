#include <stdio.h>
#include <stdlib.h>

// TODO:
// Please create a program that asks for a count when it starts.
// It should ask for a number count times, then it should print the average of the numbers.
// It should delete any dynamically allocated resource before the program exits.

int main()
{
    int count;
    int avg;
    int sum = 0;
    int num;
    printf("Please provide the count:\n");
    scanf("%d", &count);
    for(int i = 0; i < count; i++) {
        printf("\n%d - Please provide a number: ", i+1);
        scanf("%d", &num);
        sum += num;
    }
    avg = sum / count;
    printf("\nAverage of the provided numbers: %d\n", avg);

    return 0;
}
