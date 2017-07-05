#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include "console.h"
#include "rs232.h"

char command;
int port_selected = -1;
char w_filename[50];
int lp = 0;

void print_menu()
{
	char buffer[255];
	FILE *fp;
	fp = fopen("startup_info.txt", "r");
	fgets(buffer, 255, fp);
	while(!feof(fp)) {
		printf("%s", buffer);
		fgets(buffer, 255, fp);
	}
	fclose(fp);
}


void list_ports()
{
    COMDevice *ports = comEnumerate();            //can be omitted?
    int ports_count = comGetNoPorts();
	printf("size: %d\n", ports_count);                              // to be deleted
	for (int i = 0; i < ports_count; i++) {
        printf("%s\n", comGetPortName(i));
	}
}

int set_port_name()
{
    char portname[25];
    printf("Please choose a port:\n");
    scanf("%s", portname);
    COMDevice *ports = comEnumerate();        // can be omitted?
    int ports_count = comGetNoPorts();
    int match = 0;
    int index;
    for (int i = 0; i < ports_count; i++) {
        if (strcmp(comGetPortName(i), portname) == 0) {
            match = 1;
            index = i;
        }
    }
    if (match != 1) {
        printf("Please select valid port.\n");
        return -1;
    } else {
        return index;
    }
}

char *set_write_filename()
{
    printf("Please enter filename for logging:\n");
    scanf("%s", w_filename);
    strtok(w_filename, ".");
    if (strcmp(strtok(NULL, "\n"), "txt") == 0) {
        return w_filename;
    } else {
        printf("Please enter valid filename. E.g. filename.txt\n");
        return 0;
    }
}

int open_port(int port)
{
    if (port_selected == -1) {
        printf("No port set. Please set port first.\n");
        return 0;
    }
    return (comOpen(port, 115200));     //check value!
}

void close_port(int port)
{
    if (port_selected == -1) {
        printf("No port was open.\n");
    } else {
        comClose(port);
    }
}
/*
void start_stop_log(int port, char filename, int log)
{
    FILE *fp;
    fp = fopen(&filename, "w");
    while(log == 1) {
        char buffer[500];

        //get timestamp and write to buffer
        time_t rawtime;
        struct tm * timeinfo;
        char time_buffer [80];
        time (&rawtime);
        timeinfo = localtime (&rawtime);
        strftime (time_buffer, 21, "Y-%m-%d %H:%M:%S", timeinfo);
        strcat(buffer, time_buffer);
        //get temperature from IC  - read from selected port, convert register content to temperature and add to buffer
        char temp_buffer[255];
        int temp = comRead(port, temp_buffer, 1);
        //strcat(buffer, itoa(temp));
        fprintf(fp, buffer);
        printf("temperature: %d\n", temp);





    }
    if (log == 0)
        fclose(fp);


}
*/







void command_execute(char command)
{
    if (command == 'h') {
        print_menu();
    } else if (command == 'e') {
        exit(0);
    } else if (command == 'l') {
        list_ports();
    } else if (command == 'p') {
       printf("port set: %d\n", set_port_name());  //modify
       port_selected = set_port_name();
    } else if (command == 'w') {
       set_write_filename();
    } else if(command == 'o') {
        open_port(port_selected);
    }
    /*else if(command == 's') {
        if (lp == 0)
            lp = 1;
        else if (lp == 1)
            lp = 0;
         //start_stop_log(port_selected, w_filename, lp);
    }*/

    }




