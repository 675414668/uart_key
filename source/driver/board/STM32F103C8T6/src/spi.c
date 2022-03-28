#include "spi.h"



void bsp_lcd_spi_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef SPI_InitStructure;

	RCC_APB2PeriphClockCmd(LCD_SPI_RCU, ENABLE);//ʹ��LCD_SPI
	RCC_APB2PeriphClockCmd(LCD_SPI_GPIO_RCU, ENABLE);//ʹ��LCD_SPI_GPIO_PORT

	GPIO_InitStructure.GPIO_Pin =LCD_SPI_SCK_PIN|LCD_SPI_MISO_PIN|LCD_SPI_MOSI_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//�ٶ�50MHz
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	 //�����������
	GPIO_Init(LCD_SPI_GPIO_PORT, &GPIO_InitStructure); //��ʼ��LCD_SPI_GPIO_PORT
	GPIO_SetBits(LCD_SPI_GPIO_PORT,LCD_SPI_SCK_PIN|LCD_SPI_MISO_PIN|LCD_SPI_MOSI_PIN);

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;//ȫ˫��ģʽ
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;//����SPI����ģʽ������ģʽ
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;//����SPI���ݴ�С��8λ֡�ṹ
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;//����ͬ��ʱ�ӿ���ʱSCLKλ�ߵ�ƽ
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;//����ͬ��ʱ�ӿյڶ���ʱ���ز���
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;//NSS�ź����������
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;//������Ԥ��Ƶֵ��������Ԥ��ƵֵΪ4
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;//���ݴ����λ����
	SPI_InitStructure.SPI_CRCPolynomial = 7;//CRCֵ����Ķ���ʽ
	SPI_Init(LCD_SPI,&SPI_InitStructure);//��ʼ��SPI
	SPI_Cmd(LCD_SPI, ENABLE);//ʹ��SPI
}



//SPIx ��дһ���ֽ�
//TxData:Ҫд����ֽ�
//����ֵ:��ȡ�����ֽ�
uint8_t bsp_lcd_spi_rw_byte(uint8_t TxData)
{		
	uint8_t retry=0;				 	
	while (SPI_I2S_GetFlagStatus(LCD_SPI, SPI_I2S_FLAG_TXE) == RESET) //���ָ����SPI��־λ�������:���ͻ���ձ�־λ
		{
		retry++;
		if(retry>200)return 0;
		}			  
	SPI_I2S_SendData(LCD_SPI, TxData); //ͨ������SPIx����һ������
	retry=0;

	while (SPI_I2S_GetFlagStatus(LCD_SPI, SPI_I2S_FLAG_RXNE) == RESET) //���ָ����SPI��־λ�������:���ܻ���ǿձ�־λ
		{
		retry++;
		if(retry>200)return 0;
		}	  						    
	return SPI_I2S_ReceiveData(LCD_SPI); //����ͨ��SPIx������յ�����					    
}

void bsp_lcd_spi_transfer_8bit(void)
{
	SPI_DataSizeConfig(LCD_SPI,SPI_DataSize_8b);
}
void bsp_lcd_spi_transfer_16bit(void)
{
   SPI_DataSizeConfig(LCD_SPI,SPI_DataSize_16b);
}
void bsp_lcd_spi_enable(void)
{
	SPI_Cmd(LCD_SPI, ENABLE);//ʹ��SPI
}

void bsp_lcd_spi_dma_enable(void)
{
	SPI_I2S_DMACmd(LCD_SPI,SPI_I2S_DMAReq_Tx,ENABLE);
}
