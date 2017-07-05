#ifndef CONSOLE_H
#define CONSOLE_H

void print_menu();
void command_execute(char command);
void list_ports();
int set_port_name();
char *set_write_filename();
int open_port(int port);
void close_port(int port);
//void start_stop_log(int port, char filename, int log);











#endif // CONSOLE_H
