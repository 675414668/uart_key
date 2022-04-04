#include "usart.h"

typedef struct {
	void (*callback_fun)();
}usart_t;

usart_t usart;
static void bsp_usart_gpio_init(void);
static void bsp_usart_driver_init(uint32_t boadrate);

void bsp_usart_com_init(uint32_t boadrate)
{
  bsp_usart_gpio_init();
	bsp_usart_driver_init(boadrate);
}
void bsp_usart_callback(void *cb)
{
	usart.callback_fun=cb;
}
static void bsp_usart_gpio_init(void)
{
	rcu_periph_clock_enable(RCU_USART_COM_PORT);//USART_COM_PORT时钟使能
	gpio_af_set(USART_COM_PORT, GPIO_AF_0, GPIO_PIN_6|GPIO_PIN_7);

	gpio_mode_set(USART_COM_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP,USART_COM_TX_PIN);//PB6配置成多功能
	gpio_output_options_set(USART_COM_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ,GPIO_PIN_6);

	gpio_mode_set(USART_COM_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP,USART_COM_RX_PIN);//PB7配置成多功能
	gpio_output_options_set(USART_COM_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ,GPIO_PIN_7);
}
static void bsp_usart_driver_init(uint32_t boadrate)
{
    rcu_periph_clock_enable(USART_COM_RCU);

    usart_deinit(USART_COM);
    usart_baudrate_set(USART_COM,boadrate);
		usart_word_length_set(USART_COM, USART_WL_8BIT); //8位数据位
		usart_stop_bit_set(USART_COM, USART_STB_1BIT);   //1位停止位
		usart_parity_config(USART_COM, USART_PM_NONE);   //无奇偶校验
		usart_hardware_flow_rts_config(USART_COM, USART_RTS_DISABLE);
		usart_hardware_flow_cts_config(USART_COM, USART_CTS_DISABLE);
    usart_transmit_config(USART_COM, USART_TRANSMIT_ENABLE);//发送使能
    usart_receive_config(USART_COM, USART_RECEIVE_ENABLE);//接收使能
	
	  nvic_irq_enable(USART_COM_IRQn, 0, 1);
    usart_interrupt_enable(USART_COM, USART_INT_RBNE);//接收中断打开
	
	  usart_enable(USART_COM);//USART_COM使能
}

int fputc(int ch, FILE *f)
{
    usart_data_transmit(USART_COM, (uint8_t)ch);
    while(RESET == usart_flag_get(USART_COM, USART_FLAG_TBE));
    return ch;
}

void USART0_IRQHandler(void)
{
	uint8_t rx_data=0;
	
    if(RESET != usart_interrupt_flag_get(USART_COM, USART_INT_FLAG_RBNE)){
			rx_data=usart_data_receive(USART_COM);
			usart.callback_fun(rx_data);
    }

}
