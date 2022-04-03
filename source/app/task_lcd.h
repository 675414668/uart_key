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
};

enum 
{
	STOP=0,
	BEGIN,
};

void task_lcd_init(void);
void task_lcd_display(void);
#endif 
