#include "task_laser.h"
#include "task_lcd.h"

static uint8_t laser_last_state=0;

void task_laser_init(void)
{
	hal_laser_init();

}

void task_laser(void)
{
	if(laser_ctrl.state_value!=laser_last_state)
  {
		if(laser_ctrl.state_value==1)
		{
			hal_laser_control(LASER,LASER_ON);
		}
		else if(laser_ctrl.state_value==0)
		{
			hal_laser_control(LASER,LASER_OFF);
		}
		laser_last_state=laser_ctrl.state_value;
  }

}



