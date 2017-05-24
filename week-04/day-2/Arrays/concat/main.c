#include <stdio.h>
#include <stdlib.h>

/*
TODO: Implement a function that concatenates 2 strings (dest and source).
The return value should be the concatenated strings.
*/

char *str_concat(char *dest, char *source);

int main()
{
    char test_dest[30] = "Hello";
    char test_source[] = " World. Greetings.";
    char *test_result = str_concat(test_dest, test_source);
    puts(test_result);

    return 0;
}

char *str_concat(char *dest, char *source)
{
    int i;
    for (i = 0; dest[i] != '\0'; i++) {
       ;
    }
    int j;
    for (j = 0; source[j] != '\0'; j++) {
        dest[i + j] = source[j];
    }
    dest[i + j] = '\0';
    return dest;
}
