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


    int x = system("ping -n 1 216.58.214.227");  //???


    if (x == 0)
        printf("Success\n");
    else
        printf("Server could not be reached\n");


    return 0;
}
