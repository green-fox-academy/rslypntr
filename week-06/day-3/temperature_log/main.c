#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <conio.h>
#include "console.h"
#include "rs232.h"

char command;               // global variables OK like this??
int port_selected = -1;
char w_filename[50];
//int lp = 0;               //???



int main(void)
{
	print_menu();
	while(1) {
	    command = getch();
	    printf("%c\n", command);
	    command_execute(command);
	     int temp_buffer[255];
	    //int temp = comRead(port_selected, temp_buffer, 1);
//        printf("temperature: %d\n", temp);

	}

}

