#include "hal_laser.h"

void hal_laser_init(void)
{
   bsp_laser_init();
}

uint8_t hal_laser_control(uint8_t laser,uint8_t state)
{
	return bsp_laser_control(laser,state);
}

