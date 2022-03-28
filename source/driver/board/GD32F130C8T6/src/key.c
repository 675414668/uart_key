#include "key.h"
#include "lcd.h"
#include "echo.h"

typedef  struct 
{
	uint16_t key1_count;
	uint16_t key2_count;
	uint16_t key3_count;
	uint16_t press;
}key_crl_t;
key_crl_t key_crl;

static void bsp_key_gpio_init(void);
static void bsp_key_tim_init(void);
static void bsp_key_scan(void);

void bsp_key_init(void)
{
	bsp_key_gpio_init();
	bsp_key_tim_init();
}

static void bsp_key_gpio_init(void)
{
	rcu_periph_clock_enable(KEY_RCC);	 //使能A端口时钟

	gpio_mode_set(LCD_CONTROL_PORT,GPIO_MODE_INPUT,GPIO_PUPD_PULLUP,KEY1_PIN|KEY2_PIN|KEY3_PIN);

	gpio_bit_reset(KEY_PORT,KEY1_PIN|KEY2_PIN|KEY3_PIN);
}

static void bsp_key_tim_init(void)
{
	timer_parameter_struct timer_initpara;

    rcu_periph_clock_enable(KEY_TIM_RCC);

    timer_deinit(KEY_TIM);

    timer_initpara.prescaler         = KEY_TIM_PRESCALER;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = KEY_TIM_PERIOD;
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(KEY_TIM,&timer_initpara);

		nvic_priority_group_set(NVIC_PRIGROUP_PRE1_SUB3);//1 bit抢占优先级,3 bit子优先级，数值越小，优先级越高
		nvic_irq_enable(KEY_TIM_IRQN, 0, 1);//中断优先级使能
		timer_interrupt_enable(KEY_TIM, TIMER_INT_UP);
	
    timer_auto_reload_shadow_enable(KEY_TIM);//自动重装载影子比较器使能
    timer_enable(KEY_TIM);//使能定时器
}	

static void bsp_key_scan(void)
{
	if(gpio_input_bit_get(KEY_PORT,KEY1_PIN)==0)
	{
		key_crl.key1_count++;		
	}
	else
	{
		if(key_crl.key1_count<KEY_L_TIM && key_crl.key1_count>KEY_S_TIM)       key_crl.press = KEY1_S;
		else if(key_crl.key1_count>KEY_L_TIM)  key_crl.press = KEY1_L;
		key_crl.key1_count=0;
	}
	if(gpio_input_bit_get(KEY_PORT,KEY2_PIN)==0)
	{
		key_crl.key2_count++;
	}
	else
	{
		if(key_crl.key2_count<KEY_L_TIM && key_crl.key2_count>KEY_S_TIM)       key_crl.press = KEY2_S;
		else if(key_crl.key2_count>KEY_L_TIM)  key_crl.press = KEY2_L;
		key_crl.key2_count=0;
	}
	if(gpio_input_bit_get(KEY_PORT,KEY3_PIN)==0)
	{
		key_crl.key3_count++;		
	}
	else
	{
		if(key_crl.key3_count<KEY_L_TIM && key_crl.key3_count>KEY_S_TIM)       key_crl.press = KEY3_S;
		else if(key_crl.key3_count>KEY_L_TIM)  key_crl.press = KEY3_L;
		key_crl.key3_count=0;
	}
}

uint8_t bsp_get_key_press(void)
{
	return key_crl.press;
}

void bsp_set_key_press(uint8_t state)
{
	key_crl.press=state;
}

void KEY_TIM_IRQHANDLER(void)
{
	if(timer_interrupt_flag_get(KEY_TIM,TIMER_INT_FLAG_UP)==SET)
	{
		bsp_key_scan();
		lcd_astronaut_image_change();
		lcd_waiting_time_change();
		bsp_timer_stopwatch();
		bsp_echo_get_time();
		timer_interrupt_flag_clear(KEY_TIM,TIMER_INT_FLAG_UP);
	}
}

