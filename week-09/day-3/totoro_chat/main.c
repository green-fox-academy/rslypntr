/***********
MAIN
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

//#pragma comment(lib,"ws2_32.lib") //Winsock Library


int main()
{
    num_clients = 0;

    WSADATA wsData;
    WORD ver = MAKEWORD(2, 2);

    if (WSAStartup(ver, &wsData) != 0)
    {
        printf("\nCannot initialize Winsock. Error Code : %d",WSAGetLastError());
        return 1;
    }
    _beginthread(broadcast_listener_thread, 0, NULL);
    _beginthread(msg_listener_thread, 0, NULL);
    _beginthread(discovery_listener_thread, 0, NULL);

    while (1) {
            if (kbhit()) {
                char command = getch();
                command_interpreter(command);
            }
    }

    //Clean up Winsock
    WSACleanup();
}
