#ifndef __USART_PROTOCOL_H
#define __USART_PROTOCOL_H

#include "hal_usart.h"


void usart_protocol_init(void);
void usart_rx_protocol(uint8_t rx_data);
void usart_protocol_analyze(void);
#endif 
