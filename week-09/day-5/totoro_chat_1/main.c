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
    WSADATA wsData;
    int ver = WSAStartup(MAKEWORD(2, 2), &wsData);
    if (WSAStartup(ver, &wsData) != 0)
    {
        printf("\nCannot initialize Winsock. Error Code : %d",WSAGetLastError());
        return 1;
    }



    while (1) {
            if (kbhit()) {
                char command = getch();
                if (command == 'b') {
                    send_discovery_request();

                }

            }
    }

    //Clean up Winsock
    WSACleanup();
}
