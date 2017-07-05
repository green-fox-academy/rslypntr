/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SOCKET_CLIENT_H
#define __SOCKET_CLIENT_H

#define SERVER_IP "10.27.6.40"
#define SERVER_PORT 54545

/* Includes ------------------------------------------------------------------*/
#include "stm32746g_discovery_ts.h"
#include "socket_server.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void socket_client_thread(void const *argument);
void connect_to_server(int *client_sock, unsigned int server_port, char *server_ip);
void draw_init(void);
uint32_t color_select(TS_StateTypeDef TS_State);
uint16_t style_select(TS_StateTypeDef TS_State);



#endif /* __SOCKET_CLIENT_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
