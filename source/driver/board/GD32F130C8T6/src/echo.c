#include "echo.h"

typedef struct
{
	uint32_t tim_count;
	uint8_t distance_buff[7];
	float distance;
	uint8_t flag;
}echo_ctrl_t;
echo_ctrl_t echo_ctrl;

static void bsp_echo_gpio_init(void);
	
void bsp_echo_init(void)
{
	bsp_echo_gpio_init();
}

static void bsp_echo_gpio_init(void)
{
	rcu_periph_clock_enable(ECHO_RCC);	 //使能A端口时钟

	gpio_mode_set(ECHO_PORT,GPIO_MODE_INPUT,GPIO_PUPD_PULLDOWN,ECHO_PIN);
	gpio_bit_reset(ECHO_PORT,ECHO_PIN);
  gpio_mode_set(ECHO_PORT, GPIO_MODE_OUTPUT, GPIO_OSPEED_50MHZ, TRIG_PIN);
  gpio_bit_reset(ECHO_PORT,TRIG_PIN);
}

void bsp_echo_get_time(void)
{
	if(echo_ctrl.flag==0)
	{
		gpio_bit_set(ECHO_PORT,TRIG_PIN);
	  echo_ctrl.flag=1;
	}
	else
	{
		gpio_bit_reset(ECHO_PORT,TRIG_PIN);
	}
	if(gpio_input_bit_get(ECHO_PORT,ECHO_PIN)==1)
	{
		echo_ctrl.tim_count++;
	}
	else if(gpio_input_bit_get(ECHO_PORT,ECHO_PIN)==0)
	{
		if(echo_ctrl.tim_count>0)
		{
			echo_ctrl.distance=(float)echo_ctrl.tim_count/200*SOUND_SPEED;//cm
		  echo_ctrl.tim_count=0;
			echo_ctrl.flag=0;
		}
	}
}

void bsp_echo_lcd_get_distance(uint8_t *data)
{
	uint16_t distance;
	distance=echo_ctrl.distance*10;//小数点后两位
	if(distance<45000)
	{
		echo_ctrl.distance_buff[0]=91;
		echo_ctrl.distance_buff[1]=distance/1000+0x30; 
		echo_ctrl.distance_buff[2]=(distance/100)%10+0x30;
		echo_ctrl.distance_buff[3]=(distance/10)%10+0x30;
		echo_ctrl.distance_buff[4]=46;
		echo_ctrl.distance_buff[5]=distance%10+0x30;
		echo_ctrl.distance_buff[6]=93;
		memcpy(data,echo_ctrl.distance_buff,7);
	}
}

