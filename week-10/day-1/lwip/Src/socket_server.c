/* Includes ------------------------------------------------------------------*/

#include "socket_server.h"
#include "lcd_log.h"
#include "cmsis_os.h"
#include "app_ethernet.h"
#include "lwip/sockets.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

// TODO:
// Implement this function!
void socket_server_thread(void const *argument)
{
	//init?
	lwip_socket_thread_init();

	//server address init
	struct sockaddr_in addr_in;                                 // Inet address structure definition
	addr_in.sin_family = PF_INET;                               // This address is an internet address
	addr_in.sin_port = htons(SERVER_PORT);                      // Server port
	addr_in.sin_addr.s_addr = inet_addr("10.27.6.29");          // Server IP
	struct sockaddr *addr = (struct sockaddr *)&addr_in;        // Make a struct sockaddr pointer, which points to the address stucture

	//create socket
	int master_sock = lwip_socket(PF_INET, SOCK_STREAM, 0);
	// Check if socket is ok
	if (master_sock < 0)
		printf("Error in creating master socket\n");

	//bind socket
	int flag = lwip_bind(master_sock, addr, sizeof(*addr));
	// Check if the binding is ok
	if (flag < 0)
		printf("Error in bind\n");

	//start listening
	flag = lwip_listen(master_sock, SERVER_QUEUE_SIZE);
	// Check if listening is ok
	if (flag < 0)
		printf("Error in listen\n");

	//printf("Server is initialized\n");

	//create variables that will be used in the do-while loop
	struct sockaddr client_addr;    	// Client address structure
	int slave_sock;              		// Slave socket definition, this will be used to store the incoming socket
	char buff[SERVER_BUFF_LEN];    		// Buffer for incoming and outgoing data
	//printf("Variables for while loop created\n");

	//do-while loop: receive data sent by the client and send it back
			//1. accept the connection and save the incoming socket
	while (1) {
		slave_sock = lwip_accept(master_sock, &client_addr, NULL);
		// Check if the socket is valid
		if (slave_sock < 0)
			printf("Error in creating slave socket\n");

		//check if connection accept was successful
		printf("Connection accepted\n");

		//2. receive the data sent by client
		int received_bytes;
		do {
			received_bytes = lwip_recv(slave_sock, buff, SERVER_BUFF_LEN, 0);
			if (received_bytes <= 0) {
				printf("Connection closed or socket error\n");
			} else {
				// Terminate the string with zero
				buff[received_bytes] = '\0';
				// Print out the received data
				printf("Incoming message: %s \n", buff);
				// Send back the received string
				send(slave_sock, buff, received_bytes, 0);
			}
		} while (received_bytes > 0);
		lwip_close(slave_sock);
		//check if client socket was closed
		printf("Client socket closed\n");
	}
	// Cleaning up used memory
	//printf("Closing server socket\n");
	lwip_close(master_sock);
	lwip_socket_thread_cleanup();

}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
