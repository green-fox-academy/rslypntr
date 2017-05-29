#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "todo.h"

int main()
{   list_t *todo_list = list_init();
    print_menu();
    char input[255];
    char instruction[255];
    while(1) {
        gets(input);
        if (strcmp(input, "") != 0) {
            strcpy(instruction, get_instruction(input));
            command_execution(instruction, input, todo_list);
        } else {
            printf("\nNo input. Please select from the below list.\n\n");
            print_menu();
        }
        printf("\nCurrent length of list:%d\n", todo_list->len);
    }
    return 0;
}
