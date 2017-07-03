/***********
SERVER
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


void msg_listener_thread()
{
    //Create a socket
    SOCKET MESSAGE = socket(AF_INET, SOCK_STREAM, 0);
    if (MESSAGE == INVALID_SOCKET) {
        printf("\nCannot create socket. Error Code : %d",WSAGetLastError());
        return;
    }

    //Bind the socket to an IP address and port
    struct sockaddr_in in;
    in.sin_family = AF_INET;
    in.sin_port = htons(MSG_PORT);
    in.sin_addr.s_addr = inet_addr(MY_IP);
    int flag = bind(MESSAGE, (struct sockaddr *)&in, sizeof(in)); // bind the above specified port
                                                                //to the previously defined socket
    if (flag == SOCKET_ERROR) {
        printf("\nFailed to bind. Error Code : %d",WSAGetLastError());
        return;
    }
    //Tell Winsock the socket is for listening
    listen(MESSAGE, SOMAXCONN);

    //Wait for connection
    struct sockaddr_in client;
    int client_size = sizeof(client);
    SOCKET client_socket = accept(MESSAGE, (struct sockaddr *)&client, &client_size);
    if (client_socket == INVALID_SOCKET) {
        printf("\nInvalid socket. Error Code : %d",WSAGetLastError());
        return;
    }

    //Close listening socket
    closesocket(MESSAGE);

    //While loop: accept incoming message from client and display it on screen
    char buff[4096];

    while(1) {
        //ZeroMemory(buff, 4096);           needed???
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
        //If message arrives, print "user_name_of_the_sender: message"
        int index;
        for (int i = 0; i < num_clients; i++) {
            if(strcmp(inet_ntoa(client.sin_addr), user_list[i].ip_address) == 0) {
                index = i;
            }
        }
        printf("%s ", user_list[index].name);
        puts(buff);
    }
    //Close the socket
    closesocket(client_socket);
}

void broadcast_listener_thread()
{
    //Create a  UDP socket
    SOCKET BROADCAST = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (BROADCAST == INVALID_SOCKET) {
        printf("\nCannot create socket. Error Code : %d", WSAGetLastError());
        return;
    }
    char opt = '1';

    //Set socket option - set socket to send and receive packets to and from UDP datagram sockets
    setsockopt(BROADCAST, SOL_SOCKET, SO_BROADCAST, &opt, sizeof(int));

    //Bind the socket to an IP address and port
    struct sockaddr_in in;
    in.sin_family = AF_INET;
    in.sin_port = htons(12345);
    in.sin_addr.s_addr = INADDR_ANY;    //my own IP address
    int flag = bind(BROADCAST, (struct sockaddr *)&in, sizeof(in)); // bind the above specified port
                                                                    //to the previously defined socket
    if (flag == SOCKET_ERROR) {
        printf("\nFailed to bind. Error Code : %d",WSAGetLastError());
        return;
    }
    //receive a datagram on the bound socket and send response
    struct sockaddr_in client_addr;
    while(1) {
        int client_addr_size = sizeof(client_addr);
        char incoming_buff[4096];
        //char resp_buff[255];
        //char name[150];
        //strcat(resp_buff, name);
        //strcat(resp_buff, IP_ADDRESS);
        int bytes_received = recvfrom(BROADCAST, incoming_buff, 4096, 0, (struct sockaddr *)&client_addr, &client_addr_size);
        if (bytes_received == SOCKET_ERROR) {
            printf("\nError in recvfrom()\n");
            break;
        }
        if (bytes_received == 0) {
            printf("\nClient disconnected\n");
            break;
        }
        //if message ("TOTORO discovery_port_number") arrives to BROADCAST socket, send a TCP message
        //to ip_of_discovery_request:discovery_port_number with the following message: my_name message_port_number.
        char totoro = *strtok(incoming_buff, " ");
        int port = *strtok(NULL, "\n");

        if (strcmp(&totoro, "TOTORO") == 0)  {
            //create a TCP client socket
            SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
            if (sock == INVALID_SOCKET) {
                printf("\nCannot create socket. Error Code : %d",WSAGetLastError());
                return;
            }
            //Fill in a hint structure - it tells Winsock what server and what port we want to connect to
            //struct sockaddr_in hint;
            //client_addr.sin_family = AF_INET;
            client_addr.sin_port = htons(port);
            //hint.sin_addr.s_addr = inet_addr(ip_address);

            //Connect to server
            int conn_result = connect(sock, (struct sockaddr *)&client_addr, sizeof(client_addr));
            if (conn_result == SOCKET_ERROR) {
                printf("\nCannot connect to client. Error Code : %d",WSAGetLastError());
                closesocket(sock);
                return;
            }
            char resp_buff[100];
            strcat(resp_buff, myname);
            strcat(resp_buff, " ");
            strcat(resp_buff, "55000");    //MSG_PORT
            send(sock, resp_buff, sizeof(resp_buff), 0);
            //printf("TCP message sent");
        }

    }
    //Close listening socket
    //closesocket(BROADCAST);
}


void send_discovery_request()
{
    char user_input[] = "TOTORO ";
    strcat(user_input, "55555");        //DISC_PORT

    //Create a UDP socket
    SOCKET BROADCAST = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (BROADCAST == INVALID_SOCKET) {
        printf("\nCannot create socket. Error Code : %d", WSAGetLastError());
        return;
    }
     //Set socket option - set socket to send and receive packets to and from UDP datagram sockets
    char opt = '1';
    setsockopt(BROADCAST, SOL_SOCKET, SO_BROADCAST, &opt, sizeof(int));

    //Bind the socket to an IP address and port
    struct sockaddr_in in;
    in.sin_family = AF_INET;
    in.sin_port = htons(12345); // specify port
    in.sin_addr.s_addr = inet_addr("255.255.255.255");
    //bind(BROADCAST, (struct sockaddr *)&in, sizeof(in)); // bind the above specified port
                                                            //to the previously defined socket
    //send broadcast message
    //sendto(BROADCAST, user_input, sizeof(user_input), 0);
    //sendto(SendSocket, SendBuf, BufLen, 0, (SOCKADDR *) & RecvAddr, sizeof (RecvAddr));
    sendto(BROADCAST, user_input, sizeof(user_input), 0, (struct sockaddr *)&in, sizeof(in));
    printf("Discovery request sent");

    //Close listening socket
    closesocket(BROADCAST);
}

void discovery_listener_thread()
{
    //Create a TCP socket
    SOCKET DISCOVERY = socket(AF_INET, SOCK_STREAM, 0);
    if (DISCOVERY == INVALID_SOCKET) {
        printf("\nCannot create socket. Error Code : %d",WSAGetLastError());
        return;
    }

    //Bind the socket to an IP address and port
    struct sockaddr_in in;
    in.sin_family = AF_INET;
    in.sin_port = htons(DISC_PORT);
    in.sin_addr.s_addr = inet_addr(MY_IP);
    int flag = bind(DISCOVERY, (struct sockaddr *)&in, sizeof(in));

    if (flag == SOCKET_ERROR) {
        printf("\nFailed to bind. Error Code : %d",WSAGetLastError());
        return;
    }
    //Tell Winsock the socket is for listening
    listen(DISCOVERY, SOMAXCONN);

    //Wait for connection
    struct sockaddr_in client;
    int client_size = sizeof(client);
    SOCKET client_socket = accept(DISCOVERY, (struct sockaddr *)&client, &client_size);
    if (client_socket == INVALID_SOCKET) {
        printf("\nInvalid socket. Error Code : %d",WSAGetLastError());
        return;
    }

    //Close listening socket
    closesocket(DISCOVERY);

    //While loop: accept incoming message from client and save user info
    char buff[4096];

    //char resp_buff[4096];
    while(1) {
        ZeroMemory(buff, 4096);     //needed???
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
        //If message arrives, save user info
        char name = *strtok(buff, " ");
        int msg_port = atoi(strtok(NULL, "\n"));
        strcat(user_list[num_clients].name, &name);
        user_list[num_clients].port = msg_port;
        strcat(user_list[num_clients].ip_address, inet_ntoa(client.sin_addr));
        num_clients++;
        //printf("User info for %s saved", name);
    }

    //Close the socket
    closesocket(client_socket);

}

void send_message()
{
    char msg_buff[255];
    printf("Enter recipient name and message to send: ");
    gets(msg_buff);
    char rec_name = *strtok(msg_buff, " ");
    char message = *strtok(NULL, "\n");

    int index;
    int port;
    char ip_addr;
    for (int i = 0; i < num_clients; i++) {
        if (strcmp(&rec_name, user_list[i].name) == 0) {
            index = i;
        }
    }
    strcat(&ip_addr, user_list[index].ip_address);
    port = user_list[index].port;


    //create a TCP client socket
    SOCKET MESSAGE = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    if (MESSAGE == INVALID_SOCKET) {
            printf("Cannot create socket. Error Code : %d",WSAGetLastError());
            return;
    }

     //Fill in a hint structure
    struct sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    hint.sin_addr.s_addr = inet_addr(&ip_addr);

    //Connect
    int conn_result = connect(MESSAGE, (struct sockaddr *)&hint, sizeof(hint));
    if (conn_result == SOCKET_ERROR) {
        printf("Cannot connect to server. Error Code : %d",WSAGetLastError());
        closesocket(MESSAGE);
        return;
    }
    char resp_buff[255];
    strcat(resp_buff, &rec_name);
    strcat(resp_buff, " ");
    strcat(resp_buff, &message);
    send(MESSAGE, resp_buff, sizeof(resp_buff), 0);
    //printf("Message sent to %s", rec_name);
}


