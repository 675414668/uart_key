#include "laser.h"

static void bsp_laser_gpio_init(void);

void bsp_laser_init(void)
{
   bsp_laser_gpio_init();
	 bsp_laser_control(LASER,LASER_OFF);
}

static void bsp_laser_gpio_init(void)
{
    
}

uint8_t bsp_laser_control(uint8_t laser,uint8_t state)
{
	if(laser==1 && state==1)
	{
		
		
		return 1;
	}
	else if(laser==1 && state==0)
	{
		
		return 1;
	}
	else
	{
		return 0;
	}
}
