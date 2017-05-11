#include <stdio.h>

int main() {
    char buffer[255];   // Buffer variable for user input

    //TODO:
    // Get the user's name with gets
    puts("Please enter your name:");
    gets(buffer);

    //TODO:
    // Print it out with puts
    puts("Your name is:");
    puts( buffer);

    //TODO:
    // Get the user's pet name with getch
    puts("\nPlease enter your pet's name:");
    // solution using gets
    gets(buffer);

    //TODO:
    // Print it out
    puts("Your pet's name is:");
    puts(buffer);

    return 0;
}
