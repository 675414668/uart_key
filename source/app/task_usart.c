#include "task_usart.h"
#include "usart_protocol.h"

static void task_usart_callback(uint8_t rx_data);

void task_usart_init(void)
{
	  usart_protocol_init();
		hal_usart_callback(task_usart_callback);
		hal_usart_init(115200);

}

static void task_usart_callback(uint8_t rx_data)
{
	usart_rx_protocol(rx_data);
}

void task_usart(void)
{
	usart_protocol_analyze();
}

