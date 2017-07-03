/***********
USER INPUT
************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winsock2.h>
#include <stdio.h>
#include <ws2tcpip.h>
#include <process.h>
#include <conio.h>
#include "server.h"
#include "user_input.h"


void command_interpreter(char ch)
{
    switch(ch) {
    case 'h':
        //clrscr();     //supposed to be in conio.h..
        print_menu();
        break;
    case 'e':
        exit(0);
        break;
    case 'n':
        printf("\nenter your name: ");
        gets(myname);
        break;
    case 'l':
        printf("\nIP              port           name\n");
        for (int i = 0; i < num_clients; i++) {
            printf("%s              %d      %s\n", user_list[i].ip_address, user_list[i].port, user_list[i].name);
        }
        break;
    case 'd':
        send_discovery_request();
        break;
    case 'm':
        send_message();
        break;
    }
}


void print_menu()
{
    char buffer[255];
    FILE *fp;
    fp = fopen("menu.txt", "r");
    fgets(buffer, 255, fp);
    while(!feof(fp)) {
        printf("%s", buffer);
        fgets(buffer, 255, fp);
    }
    fclose(fp);
}


