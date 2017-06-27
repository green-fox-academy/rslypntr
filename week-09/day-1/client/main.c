/***********
CLIENT
************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winsock2.h>
#include <stdio.h>
#include <ws2tcpip.h> //necessary?



#pragma comment(lib,"ws2_32.lib") //Winsock Library

// Create Server and Client Applications that send and receive messages.

int WSAAPI getnameinfo(const struct sockaddr*,socklen_t,char*,DWORD, //check if needed here
		       char*,DWORD,int);



int main()
{
    char ip_address[] = "127.0.0.1";  //localhost - IP address of the server
    int port = 54000;               //listening port on the server

    //Initialize Winsock
    WSADATA data;
    WORD ver = MAKEWORD(2, 2);  //I want version 2 of Winsock
    int ws_result = WSAStartup(ver, &data);
    if (ws_result != 0)
    {
        printf("\nCannot initialize Winsock. Error Code : %d",WSAGetLastError());
        return 1;
    }

    //Create socket
    SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    if (s == INVALID_SOCKET) {
        printf("\nCannot create socket. Error Code : %d",WSAGetLastError());
        return 1;
    }

    //Fill in a hint structure - it tells Winsock what server and what port we want to connect to
    struct sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    //InetPton(AF_INET, ip_address, &hint.sin_addr);  //add the address - how can this be done on Windows??
    hint.sin_addr.s_addr = inet_addr(ip_address);




    //Connect to server  - little similar to binding on server side
    int conn_result = connect(s, (struct sockaddr *)&hint, sizeof(hint));
    if (conn_result == SOCKET_ERROR) {
        printf("\nCannot connect to server. Error Code : %d",WSAGetLastError());
        closesocket(s);
        WSACleanup();
        return 1;
    }


    //Do-while loop to send and receive data
    char buffer[4096];
    char user_input[4096];
    do {
            //Prompt the user for some text
            printf("Please enter text to send:\n");
            gets(user_input);
            if (sizeof(user_input) > 0) {

            //Send the text
                int send_result = send(s, user_input, sizeof(user_input) + 1, 0);
                if (send_result != SOCKET_ERROR) {
            //Wait for response
                    ZeroMemory(buffer, 4096);
                    int bytes_received = recv(s, buffer, 4096, 0);
                    buffer[bytes_received] = 0;
                    if (bytes_received > 0) {
            //Echo response to console
                        puts(buffer);     //check
                    }
                }
            }
    } while(sizeof(user_input) > 0);

    //Close down everything
    closesocket(s);
    WSACleanup();
}