#include "dma.h"

uint16_t lcd_dma_mem_len;//����DMAÿ�����ݴ��͵ĳ��� 	    
//DMA1�ĸ�ͨ������
//����Ĵ�����ʽ�ǹ̶���,���Ҫ���ݲ�ͬ��������޸�
//�Ӵ洢��->����ģʽ/8λ���ݿ��/�洢������ģʽ
//LCD_DMA_CHANNEL:DMAͨ��CHx
//cpar:�����ַ
//cmar:�洢����ַ
//cndtr:���ݴ����� 
void bsp_lcd_dma_picture_init(uint32_t cmar,uint16_t cndtr)
{
	DMA_InitTypeDef DMA_InitStructure;
	
 	RCC_AHBPeriphClockCmd(LCD_DMA_RCU, ENABLE);	//ʹ��DMA����
	
  DMA_DeInit(LCD_DMA_CHANNEL);   //��DMA��ͨ��1�Ĵ�������Ϊȱʡֵ
	lcd_dma_mem_len=cndtr;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&SPI1->DR;  //DMA����ADC����ַ
	DMA_InitStructure.DMA_MemoryBaseAddr = cmar;  //DMA�ڴ����ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;  //���ݴ��䷽�򣬴��ڴ��ȡ���͵�����
	DMA_InitStructure.DMA_BufferSize = cndtr;  //DMAͨ����DMA����Ĵ�С
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //�����ַ�Ĵ�������
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  //�ڴ��ַ�Ĵ�������
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  //���ݿ��Ϊ8λ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; //���ݿ��Ϊ8λ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  //��������������ģʽ
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; //DMAͨ�� xӵ�������ȼ� 
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  //DMAͨ��xû������Ϊ�ڴ浽�ڴ洫��
	DMA_Init(LCD_DMA_CHANNEL, &DMA_InitStructure);  //����DMA_InitStruct��ָ���Ĳ�����ʼ��DMA��ͨ��USART1_Tx_DMA_Channel����ʶ�ļĴ���
	  	
} 

void bsp_lcd_dma_fill_init(uint32_t cmar,uint16_t cndtr)
{
	DMA_InitTypeDef DMA_InitStructure;
	
 	RCC_AHBPeriphClockCmd(LCD_DMA_RCU, ENABLE);	//ʹ��DMA����
	
  DMA_DeInit(LCD_DMA_CHANNEL);   //��DMA��ͨ��1�Ĵ�������Ϊȱʡֵ
	lcd_dma_mem_len=cndtr;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&SPI1->DR;  //DMA����ADC����ַ
	DMA_InitStructure.DMA_MemoryBaseAddr = cmar;  //DMA�ڴ����ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;  //���ݴ��䷽�򣬴��ڴ��ȡ���͵�����
	DMA_InitStructure.DMA_BufferSize = cndtr;  //DMAͨ����DMA����Ĵ�С
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //�����ַ�Ĵ�������
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;  //�ڴ��ַ�Ĵ�������
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;  //���ݿ��Ϊ16λ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; //���ݿ��Ϊ16λ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  //��������������ģʽ
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; //DMAͨ�� xӵ�������ȼ� 
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  //DMAͨ��xû������Ϊ�ڴ浽�ڴ洫��
	DMA_Init(LCD_DMA_CHANNEL, &DMA_InitStructure);  //����DMA_InitStruct��ָ���Ĳ�����ʼ��DMA��ͨ��USART1_Tx_DMA_Channel����ʶ�ļĴ���
} 

//����һ��DMA����
void bsp_lcd_dma_enable(void)
{ 
	DMA_Cmd(LCD_DMA_CHANNEL, DISABLE );
 	DMA_SetCurrDataCounter(LCD_DMA_CHANNEL,lcd_dma_mem_len);
 	DMA_Cmd(LCD_DMA_CHANNEL, ENABLE);
}	  
void bsp_lcd_dma_transfer_finished(void)
{
	while(1)
	{
	  if(DMA_GetFlagStatus(DMA1_FLAG_TC3)!=RESET)//�ȴ�ͨ��4�������
    {
		  DMA_ClearFlag(DMA1_FLAG_TC3);//���ͨ��4������ɱ�־
		  break; 
	  }
	}
}
 

























