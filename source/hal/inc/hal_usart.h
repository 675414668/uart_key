#ifndef __HAL_USART_H
#define __HAL_USART_H

#include "usart.h"

void hal_usart_init(uint32_t boadrate);
void hal_usart_callback(void *cb);
void hal_usart_data_send(uint8_t* data,uint8_t size);
#endif 


