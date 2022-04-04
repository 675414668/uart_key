#include "usart_protocol.h"
#include "version.h"

#define USART_RX_NUM (20)
#define USART_TX_NUM (50)

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
	uint8_t tx_buff[USART_TX_NUM];
}usart_protocol_t;

usart_protocol_t usart_protocol;
static void usart_protocol_data_init(void);
static uint8_t usart_protocol_creat_crc(uint8_t* data,uint8_t size);
static void usart_protocol_data_pack(uint8_t cmd,uint8_t* payload,uint8_t size);
static void usart_get_softwart_version(void);

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
			if(usart_protocol.index==usart_protocol.len+4)
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

void usart_protocol_analyze(void)
{
	if(usart_protocol.rx_over==1)
	{
		if(usart_protocol.rx_buff[usart_protocol.len+3]==usart_protocol_creat_crc(usart_protocol.rx_buff,usart_protocol.len+3))//crc
		{
			switch(usart_protocol.rx_buff[4])//cmd
			{
				case 0x10:{usart_get_softwart_version();break;}
				case 0x11:{break;}
				case 0x12:{break;}
				case 0x13:{break;}
				case 0xA0:{break;}
				case 0xA1:{break;}
				case 0xB0:{break;}
				case 0xB1:{break;}
				default:  {break;}
			}
		}
		else
		{
			//return error
		}
		usart_protocol.rx_over=0;
	}
}

static uint8_t usart_protocol_creat_crc(uint8_t* data,uint8_t size)
{
	uint8_t i,crc=0;
	for(i=0;i<size;i++)
	{
		crc=(crc+data[i])&0xFF;
	}
	return crc;
}

static void usart_protocol_data_pack(uint8_t cmd,uint8_t* payload,uint8_t size)
{
	uint8_t i;
	usart_protocol.tx_buff[0]=0x7A;
	usart_protocol.tx_buff[1]=0x5B;
	usart_protocol.tx_buff[2]=usart_protocol.flag-1;//方向相反
	usart_protocol.tx_buff[3]=size+2;
	usart_protocol.tx_buff[4]=cmd;
	for(i=0;i<size;i++)
	{
		usart_protocol.tx_buff[5+i]=payload[i];
	}
	usart_protocol.tx_buff[5+size]=usart_protocol_creat_crc(usart_protocol.tx_buff,5+size);
}
static void usart_get_softwart_version(void)
{
	uint8_t version[]=SOFTWARE_VERSION;

	usart_protocol_data_pack(0x10,(uint8_t*)version,sizeof(version)-1);
	hal_usart_data_send(usart_protocol.tx_buff,sizeof(version)+5);
}
