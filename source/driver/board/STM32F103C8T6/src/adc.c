#include "adc.h"


static void bsp_adc_driver_init(void);

void bsp_adc_init(void)
{
  bsp_adc_driver_init();
}

static void bsp_adc_driver_init(void)
{
	ADC_InitTypeDef ADC_InitStructure;                                                    
	GPIO_InitTypeDef GPIO_InitStructure;                                                          
	
	RCC_ADCCLKConfig(ADC_FOR_PWM_CLK_DIV) ;   //ʱ�ӷ�Ƶ72M/8=9M ���ʱ�Ӳ�����14M

	
	GPIO_InitStructure.GPIO_Pin = ADC_FOR_PWM_GPIO_PIN;                                             
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                                     
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;                                         
	GPIO_Init(ADC_FOR_PWM_GPIO_PORT, &GPIO_InitStructure);                                                
	
  ADC_DeInit(ADC_FOR_PWM);                                                                        
  ADC_DMACmd(ADC_FOR_PWM, DISABLE);
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;    	//ADC ��������ģʽ                               
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;  	        //�Ƿ�ɨ��_��ͨ��                                      
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;     //�Ƿ�����_����                           
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;    //�����ⲿ�������������ת�� 
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;   	             //�����Ҷ���                             
	ADC_InitStructure.ADC_NbrOfChannel = 1;                                //ADC-ͨ������_��ͨ��                                   
	ADC_Init(ADC_FOR_PWM, &ADC_InitStructure);                                                   
	
	ADC_RegularChannelConfig(ADC_FOR_PWM, ADC_FOR_PWM_CH, 1, ADC_FOR_PWM_SAMOLE_TIME);     //�������ݺ�ADC����ľ���ԽӺ���   (ADC�˿� ,ADCͨ�� ,ת�����-�ڼ���ת�� ,ת��������)            
	
	ADC_Cmd(ADC_FOR_PWM,ENABLE); 
  ADC_ResetCalibration(ADC_FOR_PWM);   //ADC�Ĵ�����λУ׼����	
	while(ADC_GetResetCalibrationStatus(ADC_FOR_PWM)); //�ȴ���һ�����
  ADC_StartCalibration(ADC_FOR_PWM);//��ʼָ��ADC��У׼״̬
  while(ADC_GetCalibrationStatus(ADC_FOR_PWM)); //�ȴ���һ�����               
}

uint32_t bsp_read_adc_data(ADC_TypeDef* ADCx)
{
	uint32_t data=0;                                                                                                                                                                                                                                                                                                                                                               
	
	ADC_SoftwareStartConvCmd(ADCx,ENABLE);       //����_ADC�������-����    ״̬�Ĵ���Ϊ0                                                                  
				
	while(!ADC_GetFlagStatus(ADCx,ADC_FLAG_EOC));   //�ȴ�ת������             �Ĵ�����1                                                                            
			
	data=ADC_GetConversionValue(ADCx);                                                                                                              
	
	return data;                                                                            
	//���ص�ѹֵ                                          
}

float bsp_read_adc_data_voltage(ADC_TypeDef* ADCx)
{
	float data=0;                                                                                                                                                                                                                                                                                                                                                               
	
	ADC_SoftwareStartConvCmd(ADCx,ENABLE);       //����_ADC�������-����    ״̬�Ĵ���Ϊ0                                                                  
				
	while(!ADC_GetFlagStatus(ADCx,ADC_FLAG_EOC));   //�ȴ�ת������             �Ĵ�����1                                                                            
			
	data=(3.3*(((float)ADC_GetConversionValue(ADCx)/4096)));                                
	//�ٷֱ�ֵת���ɵ�ѹֵ��    ��Ϊ��ȡ�����ݼĴ�����״̬�Ĵ����Զ���0                                                                                    
	
	return data;                                                                            
	//���ص�ѹֵ                                          
}

