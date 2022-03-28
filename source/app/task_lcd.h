#ifndef __TASK_LCD_H
#define __TASK_LCD_H

#include "hal_lcd.h"
#include "hal_lcd_api.h"
#include "hal_lcd_font.h"
#include "lcd_config.h"
#include "hal_flash.h"

enum
{
	LCD_DISPLAY_INIT=0,
	LCD_DISPLAY_ASTRONAUT,
	LCD_DISPLAY_MENU,
	LCD_DISPLAY_LASER_CTRL,
	LCD_DISPLAY_LASER_CTRL_SET,
	LCD_DISPLAY_SYSTEM,
	LCD_DISPLAY_SYSTEM_SET,
	LCD_DISPLAY_SYSTEM_ABOUT,
	LCD_DISPLAY_STOPWATCH,
	LCD_DISPLAY_ULTRASOUND,
};

enum 
{
	STOP=0,
	BEGIN,
};

typedef struct 
{
	uint8_t state;
	uint8_t real_state;
	uint8_t astronaut_num;
	uint8_t point_num;
	uint8_t laser_set;//1 mode 2 state
	uint8_t system_set;//1 language 
	uint8_t language_value;
	uint8_t stopwatch_timebuff[15];
	uint8_t stopwatch_ctrl;//0 stop 1 begin
	uint8_t mcu_type;
	uint8_t ultrasound_buff[8];
}lcd_display_t;

typedef  struct
{
	uint8_t mode_value;
	uint8_t state_value;
}laser_ctrl_t;

extern laser_ctrl_t laser_ctrl;
extern lcd_display_t lcd_display;

void task_lcd_init(void);
void task_lcd_display(void);
#endif 
