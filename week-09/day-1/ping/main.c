#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winsock2.h>

//Create a client app that ping the google.com to get than latency, and print it out.

#pragma comment(lib,"ws2_32.lib") //Winsock Library
int WSAAPI getnameinfo(const struct sockaddr*,socklen_t,char*,DWORD,
		       char*,DWORD,int);

int main(int argc , char *argv[])
{

    WSADATA wsa;
    SOCKET s;
    struct sockaddr_in server;

    printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
        return 1;
    }

    printf("Initialised.\n");

    //Create a socket
    if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d" , WSAGetLastError());
    }

    printf("Socket created.\n");

     /*
    server.sin_addr.s_addr = inet_addr("172.217.18.67");
    server.sin_family = AF_INET;
    server.sin_port = htons( 443 );

    //Connect to remote server
    /*if (connect(s , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        puts("connect error");
        return 1;
    }

    puts("Connected");
    */

    int x = system("ping -n 1 216.58.214.227");  //???


    if (x == 0)
        printf("Success\n");
    else
        printf("Server could not be reached\n");

    //closesocket(s);
    //WSACleanup();


    return 0;
}
