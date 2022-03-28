#include "laser.h"

static void bsp_laser_gpio_init(void);

void bsp_laser_init(void)
{
   bsp_laser_gpio_init();
	 bsp_laser_control(LASER,LASER_OFF);
}

static void bsp_laser_gpio_init(void)
{
    rcu_periph_clock_enable(LASER_RCC);//GPIOBÊ±ÖÓ´ò¿ª
    gpio_mode_set(LASER_PORT, GPIO_MODE_OUTPUT, GPIO_OSPEED_50MHZ, LASER_PIN);
}

uint8_t bsp_laser_control(uint8_t laser,uint8_t state)
{
	if(laser==1 && state==1)
	{
		gpio_bit_set(LASER_PORT,LASER_PIN);
		
		return 1;
	}
	else if(laser==1 && state==0)
	{
		gpio_bit_reset(LASER_PORT,LASER_PIN);
		return 1;
	}
	else
	{
		return 0;
	}
}
