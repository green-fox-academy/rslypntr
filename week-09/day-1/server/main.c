/***********
SERVER
************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winsock2.h>
#include <stdio.h>
#include <ws2tcpip.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

// Create Server and Client Applications that send and receive messages.

int WSAAPI getnameinfo(const struct sockaddr*,socklen_t,char*,DWORD,
		       char*,DWORD,int);

int main()
{
    //Initialize Winsock
    WSADATA wsData;
    WORD ver = MAKEWORD(2, 2);  //I want version 2 of Winsock

    if (WSAStartup(ver, &wsData) != 0)
    {
        printf("\nCannot initialize Winsock. Error Code : %d",WSAGetLastError());
        return 1;
    }

    //Create a socket
    SOCKET listening = socket(AF_INET, SOCK_STREAM, 0); //IPv4 address, using TCP
    if (listening == INVALID_SOCKET) {
        printf("\nCannot create socket. Error Code : %d",WSAGetLastError());
        return 1;
    }

    //Bind the socket to an IP address and port
    struct sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(54000); // specify port
    hint.sin_addr.s_addr = inet_addr("127.0.0.1");
    bind(listening, (struct sockaddr *)&hint, sizeof(hint)); // bind the above specified port
                                                            //on any address to the previously defined socket

    //Tell Winsock the socket is for listening
    listen(listening, SOMAXCONN);

    //Wait for connection
    struct sockaddr_in client;
    int client_size = sizeof(client);
    SOCKET client_socket = accept(listening, (struct sockaddr *)&client, &client_size);
    if (client_socket == INVALID_SOCKET) {
        printf("\nInvalid socket. Error Code : %d",WSAGetLastError());
        return 1;
    }
    char host[NI_MAXHOST];      //client's remote name - if applicable
    char service[NI_MAXHOST];   //port the client is connected on
    ZeroMemory(host, NI_MAXHOST);   //same as memset()
    ZeroMemory(service, NI_MAXHOST);    //same as memset()
    if (getnameinfo((struct sockaddr *)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0) {
        printf("\nHost %s connected on port %s", host, service);
    } else {
        printf("\nOmitted print\n");
        printf("\nHost %s connected on port %d", host, ntohs(client.sin_port));
    }

    //Close listening socket
    closesocket(listening);

    //While loop: accept and echo message back to client
    char buff[4096];
    while(1) {
        ZeroMemory(buff, 4096); //same as memset()

        //Wait for client to send data
        int bytes_received = recv(client_socket, buff, 4096, 0);
        if (bytes_received == SOCKET_ERROR) {
            printf("\nError in recv()\n");
            break;
        }
        if (bytes_received == 0) {
            printf("\nClient disconnected\n");
            break;
        }

        //Echo message back to client
       send(client_socket, buff, bytes_received, 0);
       ZeroMemory(buff, 4096);
    }

    //Close the socket
    closesocket(client_socket);

    //Clean up Winsock
    WSACleanup();
}
