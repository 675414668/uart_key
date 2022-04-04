#include "usart_protocol.h"

#define USART_RX_NUM (20)

enum
{
	USART_HEAD_H=0,
	USART_HEAD_L,
	USART_FLAG,
	USART_LEN,
	USART_DATA,
};

typedef struct
{
	uint8_t rx_buff[USART_RX_NUM];
	uint8_t rx_state;
	uint8_t index;
	uint8_t flag;
	uint8_t len;
	uint8_t rx_over;
}usart_protocol_t;

usart_protocol_t usart_protocol;
static void usart_protocol_data_init(void);

void usart_protocol_init(void)
{
	usart_protocol_data_init();
}

static void usart_protocol_data_init(void)
{
	usart_protocol.rx_state=USART_HEAD_H;
	usart_protocol.index=0;
	usart_protocol.flag=0;
	usart_protocol.len=0;
	usart_protocol.rx_over=0;
	memset(usart_protocol.rx_buff,0,sizeof(usart_protocol.rx_buff));
}

void usart_rx_protocol(uint8_t rx_data)
{
	usart_protocol.rx_buff[usart_protocol.index]=rx_data;
	switch(usart_protocol.rx_state)
	{
		case USART_HEAD_H:
		{
			if(rx_data==0x7A)
			{
				usart_protocol.rx_state=USART_HEAD_L;
				usart_protocol.index++;
			}
			else
			{
				usart_protocol.rx_state=USART_HEAD_H;
			  usart_protocol.index=0;
			}
			break;
		}
		case USART_HEAD_L:
		{
			if(rx_data==0x5B)
			{
				usart_protocol.rx_state=USART_FLAG;
				usart_protocol.index++;
			}
			else
			{
				usart_protocol.rx_state=USART_HEAD_H;
			  usart_protocol.index=0;
			}
			break;
		}
		case USART_FLAG:
		{
			usart_protocol.flag=rx_data;
			usart_protocol.rx_state=USART_LEN;
			usart_protocol.index++;
			break;
		}
		case USART_LEN:
		{
			usart_protocol.len=rx_data;
			usart_protocol.rx_state=USART_DATA;
			usart_protocol.index++;
			break;
		}
		case USART_DATA:
		{
			usart_protocol.index++;
			if(usart_protocol.index==usart_protocol.len+3)
			{
				usart_protocol.rx_state=USART_HEAD_H;
				usart_protocol.index=0;
				usart_protocol.rx_over=1;
			}
			break;
		}
		default :
		{
			usart_protocol.rx_state=USART_HEAD_H;
			usart_protocol.index=0;
			break;
		}
	}
}


