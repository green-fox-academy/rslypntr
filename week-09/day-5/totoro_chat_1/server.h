#ifndef _SERVER_H_
#define _SERVER_H_


#define DISC_PORT 55555
#define MSG_PORT 55000
#define MY_IP "10.27.6.73"

struct client{
    char name[255];
    int port;
    char ip_address[255];
};

struct client user_list[50];
struct client my_user;
int num_clients;
char myname[100];

void msg_listener_thread();
void broadcast_listener_thread();
void discovery_listener_thread();
void send_discovery_request();
void send_message();












#endif // _SERVER_H_
