#include <stdio.h>

int main() {
    char char_array[] = {'a', 'b', 'c', 'd'};
    char char_array_the_same[] = "abcd";

	//TODO:
    // Print out the two arrays character-by-character
    for(int i=0; i< sizeof(char_array); i++){
        printf("%c\t", char_array[i]);
    }
    printf("\n");
    for(int i=0; i< sizeof(char_array_the_same); i++){
        printf("%c\t", char_array_the_same[i]);
    }
    // 0 at the end is visible when printing as decimal numbers
    /*for(int i=0; i< sizeof(char_array_the_same); i++){
        printf("%d\t", char_array_the_same[i]);
    }
    */

	//TODO:
    // What is the difference between the arrays?
    printf("\nThe difference is that the length of \"char_array\" is %d\nwhile the length of \"char_array_the same\" is %d",sizeof(char_array),sizeof(char_array_the_same));

    return 0;
}
