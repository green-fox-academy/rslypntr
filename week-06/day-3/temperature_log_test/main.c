#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <conio.h>
#include "console.h"
#include "rs232.h"



int temp_buffer[255];

int main(void)
{
    while(1) {
    COMDevice *ports = comEnumerate();
    int ports_count = comGetNoPorts();
	printf("size: %d\n", ports_count);
	for (int i = 0; i < ports_count; i++) {
        printf("%s\n", comGetPortName(i));
	}
	printf("------------\n");
    int port_index = comFindPort("COM4");
    printf("port index: %d\n", port_index);
    int opened_status = comOpen(port_index, 115200);
    printf("opened status: %d\n", opened_status);

    char temp_buffer[1];
    int temp = comRead(port_index, &temp_buffer, sizeof(temp_buffer));
    printf("temperature: %d\n", temp);
    }
}


