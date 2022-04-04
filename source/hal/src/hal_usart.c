#include "hal_usart.h"

void hal_usart_init(uint32_t boadrate)
{
   bsp_usart_com_init(boadrate);
}

void hal_usart_callback(void *cb)
{
	bsp_usart_callback(cb);
}

void hal_usart_data_send(uint8_t* data,uint8_t size)
{
	bsp_usart_data_send(data,size);
}
