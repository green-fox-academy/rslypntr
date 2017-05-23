#include <stdio.h>
#include <stdlib.h>

// TODO:
// Create a function which receives a string as parameter, and returns
// the numbers of characters in the string.
// Don't use the strlen() function!

int str_length(char string[]);

int main()
{
    char test_array[] = "Apple tree";
    printf("%d", str_length(test_array));

    return 0;
}

int str_length(char string[])
{
    int length = 0;
    int i = 0;
    while(string[i] != '\0'){
        length++;
        i++;
    }
    return length;
}
