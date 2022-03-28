#include "task_key.h"
#include "task_lcd.h"

key_ctrl_t key_ctrl;

static void key_null(void);
static void key1_short(void);
static void key1_long(void);
static void key2_short(void);
static void key2_long(void);
static void key3_short(void);
static void key3_long(void);
static void key_default(void);

void task_key_scan(void)
{
	switch(hal_get_key_press())
	{
		case KEY_NULL:{ key_null();      break;};
		case KEY1_S:  { key1_short();    break;};
		case KEY1_L:  { key1_long();     break;};
		case KEY2_S:  { key2_short();    break;};
		case KEY2_L:  { key2_long();     break;};
		case KEY3_S:  { key3_short();    break;};
		case KEY3_L:  { key3_long();     break;};
		default :     { key_default();   break;};
	}
}

static void key_null(void)
{
	
}

static void key1_short(void)
{
	if(lcd_display.real_state==LCD_DISPLAY_INIT)
	{
		lcd_display.state=LCD_DISPLAY_MENU;//will turn to gif
		lcd_display.real_state=LCD_DISPLAY_MENU;
		key_ctrl.up_down=0;
		hal_lcd_fill(LCD_X1,LCD_Y1,LCD_X2,LCD_Y2,BLACK);
	}
	else if(lcd_display.real_state==LCD_DISPLAY_MENU)
	{
		if(key_ctrl.up_down<(MENU_OPTIONS_NUM-1)) key_ctrl.up_down++;
		else key_ctrl.up_down=0;
		lcd_display.state=LCD_DISPLAY_MENU;
	}
	else if(lcd_display.real_state==LCD_DISPLAY_LASER_CTRL)
	{
		if(laser_ctrl.mode_value==2)
		{
			if(laser_ctrl.state_value==0)      laser_ctrl.state_value=1;
			else if(laser_ctrl.state_value==1) laser_ctrl.state_value=0;
		}
		else
		{
			if(key_ctrl.up_down<(LASER_CTRL_OPTIONS_NUM-1)) key_ctrl.up_down++;
		  else key_ctrl.up_down=0;
		}
		lcd_display.state=LCD_DISPLAY_LASER_CTRL;
	}
	else if(lcd_display.real_state==LCD_DISPLAY_LASER_CTRL_SET)
	{
		if(lcd_display.laser_set==1)
		{
			if(key_ctrl.up_down<(LASER_CTRL_MODE_SET_NUM-1)) key_ctrl.up_down++;
		  else key_ctrl.up_down=0;
		  lcd_display.state=LCD_DISPLAY_LASER_CTRL_SET;
		}
		else if(lcd_display.laser_set==2)
		{
			if(key_ctrl.up_down<(LASER_CTRL_STATE_SET_NUM-1)) key_ctrl.up_down++;
		  else key_ctrl.up_down=0;
		  lcd_display.state=LCD_DISPLAY_LASER_CTRL_SET;
		}
	}
	else if(lcd_display.real_state==LCD_DISPLAY_SYSTEM)
	{
		if(key_ctrl.up_down<(LASER_CTRL_SYSTEM_NUM-1)) key_ctrl.up_down++;
		else key_ctrl.up_down=0;
		lcd_display.state=LCD_DISPLAY_SYSTEM;
	}
	else if(lcd_display.real_state==LCD_DISPLAY_SYSTEM_SET)
	{
		if(lcd_display.system_set==1)
		{
			if(key_ctrl.up_down<(LASER_CTRL_MODE_SET_NUM-1)) key_ctrl.up_down++;
		  else key_ctrl.up_down=0;
		  lcd_display.state=LCD_DISPLAY_SYSTEM_SET;
		}
	}
	else if(lcd_display.real_state==LCD_DISPLAY_SYSTEM_ABOUT)
	{
		lcd_display.state=LCD_DISPLAY_SYSTEM;//will turn to gif
	  lcd_display.real_state=LCD_DISPLAY_SYSTEM;
		hal_lcd_fill(LCD_X1,LCD_X1,LCD_X2,LCD_Y2,BLACK);
	}
	else if(lcd_display.real_state==LCD_DISPLAY_STOPWATCH)
	{
		if(key_ctrl.up_down<(LASER_CTRL_STOPWATCH_NUM-1)) key_ctrl.up_down++;
		else key_ctrl.up_down=0;
		lcd_display.state=LCD_DISPLAY_STOPWATCH;
	}
	hal_set_key_press(KEY_NULL);
}

static void key1_long(void)
{

}

static void key2_short(void)
{
	if(lcd_display.real_state==LCD_DISPLAY_INIT)
	{
		lcd_display.state=LCD_DISPLAY_MENU;//will turn to gif
		lcd_display.real_state=LCD_DISPLAY_MENU;
		key_ctrl.up_down=0;
		hal_lcd_fill(LCD_X1,LCD_Y1,LCD_X2,LCD_Y2,BLACK);
	}
	else if(lcd_display.real_state==LCD_DISPLAY_MENU)
	{
		lcd_display.state=LCD_DISPLAY_MENU;
		lcd_display.real_state=LCD_DISPLAY_MENU;
	}
	else if(lcd_display.real_state==LCD_DISPLAY_LASER_CTRL)
	{
      lcd_display.state=LCD_DISPLAY_MENU;//will turn to gif
		  lcd_display.real_state=LCD_DISPLAY_MENU;
		  key_ctrl.up_down=0;
		  hal_lcd_fill(LCD_X1,LCD_Y1,LCD_X2,LCD_Y2,BLACK);
	}
	else if(lcd_display.real_state==LCD_DISPLAY_LASER_CTRL_SET)
	{
		lcd_display.state=LCD_DISPLAY_LASER_CTRL;//will turn to gif
		lcd_display.real_state=LCD_DISPLAY_LASER_CTRL;
		hal_lcd_fill(SET_RECTANGLE_X1,SET_RECTANGLE_Y1,SET_RECTANGLE_X2+1,SET_RECTANGLE_Y2+1,BLACK);
		key_ctrl.up_down=0;
		lcd_display.laser_set=0;
	}
	else if(lcd_display.real_state==LCD_DISPLAY_SYSTEM)
	{
		lcd_display.state=LCD_DISPLAY_MENU;//will turn to gif
		lcd_display.real_state=LCD_DISPLAY_MENU;
		key_ctrl.up_down=0;
		hal_lcd_fill(LCD_X1,LCD_Y1,LCD_X2,LCD_Y2,BLACK);
	}
	else if(lcd_display.real_state==LCD_DISPLAY_SYSTEM_SET)
	{
		lcd_display.state=LCD_DISPLAY_SYSTEM;//will turn to gif
		lcd_display.real_state=LCD_DISPLAY_SYSTEM;
		hal_lcd_fill(SET_RECTANGLE_X1,SET_RECTANGLE_Y1,SET_RECTANGLE_X2+1,SET_RECTANGLE_Y2+1,BLACK);
		key_ctrl.up_down=0;
		lcd_display.system_set=0;
	}
	else if(lcd_display.real_state==LCD_DISPLAY_SYSTEM_ABOUT)
	{
		lcd_display.state=LCD_DISPLAY_SYSTEM;//will turn to gif
	  lcd_display.real_state=LCD_DISPLAY_SYSTEM;
		hal_lcd_fill(LCD_X1,LCD_X1,LCD_X2,LCD_Y2,BLACK);
	}
	else if(lcd_display.real_state==LCD_DISPLAY_STOPWATCH)
	{
		lcd_display.state=LCD_DISPLAY_MENU;//will turn to gif
		lcd_display.real_state=LCD_DISPLAY_MENU;
		key_ctrl.up_down=0;
		hal_lcd_fill(LCD_X1,LCD_Y1,LCD_X2,LCD_Y2,BLACK);
	}
	else if(lcd_display.real_state==LCD_DISPLAY_ULTRASOUND)
	{
		lcd_display.state=LCD_DISPLAY_MENU;//will turn to gif
		lcd_display.real_state=LCD_DISPLAY_MENU;
		key_ctrl.up_down=0;
		hal_lcd_fill(LCD_X1,LCD_Y1,LCD_X2,LCD_Y2,BLACK);
	}
	hal_set_key_press(KEY_NULL);
}

static void key2_long(void)
{
	lcd_display.state=LCD_DISPLAY_MENU;//will turn to gif
	lcd_display.real_state=LCD_DISPLAY_MENU;
	key_ctrl.up_down=0;
	hal_lcd_fill(LCD_X1,LCD_X1,LCD_X2,LCD_Y2,BLACK);

	hal_set_key_press(KEY_NULL);
}

static void key3_short(void)
{
	if(lcd_display.real_state==LCD_DISPLAY_INIT)
	{
		lcd_display.state=LCD_DISPLAY_MENU;//will turn to gif
		lcd_display.real_state=LCD_DISPLAY_MENU;
		key_ctrl.up_down=0;
		hal_lcd_fill(LCD_X1,LCD_Y1,LCD_X2,LCD_Y2,BLACK);
	}
	else if(lcd_display.real_state==LCD_DISPLAY_MENU)
	{
		if(key_ctrl.up_down==0)
		{
			lcd_display.state=LCD_DISPLAY_LASER_CTRL;//will turn to gif
		  lcd_display.real_state=LCD_DISPLAY_LASER_CTRL;
		  key_ctrl.up_down=0;
		  hal_lcd_fill(LCD_X1,LCD_Y1,LCD_X2,LCD_Y2,BLACK);
		}
		else if(key_ctrl.up_down==3)
		{
			lcd_display.state=LCD_DISPLAY_ULTRASOUND;//will turn to gif
		  lcd_display.real_state=LCD_DISPLAY_ULTRASOUND;
		  key_ctrl.up_down=0;
		  hal_lcd_fill(LCD_X1,LCD_Y1,LCD_X2,LCD_Y2,BLACK);
		}
		else if(key_ctrl.up_down==4)
		{
			lcd_display.state=LCD_DISPLAY_STOPWATCH;//will turn to gif
		  lcd_display.real_state=LCD_DISPLAY_STOPWATCH;
		  key_ctrl.up_down=0;
		  hal_lcd_fill(LCD_X1,LCD_Y1,LCD_X2,LCD_Y2,BLACK);
		}
		else if(key_ctrl.up_down==5)
		{
			lcd_display.state=LCD_DISPLAY_SYSTEM;//will turn to gif
		  lcd_display.real_state=LCD_DISPLAY_SYSTEM;
		  key_ctrl.up_down=0;
		  hal_lcd_fill(LCD_X1,LCD_Y1,LCD_X2,LCD_Y2,BLACK);
		}
	}
	else if(lcd_display.real_state==LCD_DISPLAY_LASER_CTRL)
	{
		if(key_ctrl.up_down==2)
		{
			lcd_display.state=LCD_DISPLAY_MENU;//will turn to gif
			lcd_display.real_state=LCD_DISPLAY_MENU;
			hal_lcd_fill(LCD_X1,LCD_X1,LCD_X2,LCD_Y2,BLACK);
		}
		else
		{
			lcd_display.state=LCD_DISPLAY_LASER_CTRL_SET;//will turn to gif
		  lcd_display.real_state=LCD_DISPLAY_LASER_CTRL_SET;
		  lcd_display.laser_set=key_ctrl.up_down+1;
		}
		key_ctrl.up_down=0;
	}
	else if(lcd_display.real_state==LCD_DISPLAY_LASER_CTRL_SET)
	{
		if(lcd_display.laser_set==1 && key_ctrl.up_down!=(LASER_CTRL_MODE_SET_NUM-1))
		{
			lcd_display.state=LCD_DISPLAY_LASER_CTRL;//will turn to gif
			lcd_display.real_state=LCD_DISPLAY_LASER_CTRL;
			hal_lcd_fill(BELONG_WORD_X,BELONG_WORD_Y,BELONG_WORD_X+100,BELONG_WORD_Y+BELONG_WORD_SIZE,BLACK);
			hal_lcd_fill(SET_RECTANGLE_X1,SET_RECTANGLE_Y1,SET_RECTANGLE_X2+1,SET_RECTANGLE_Y2+1,BLACK);
			laser_ctrl.mode_value=key_ctrl.up_down;
			key_ctrl.up_down=0;
			lcd_display.laser_set=0;
		}
		else if(lcd_display.laser_set==2 && key_ctrl.up_down!=(LASER_CTRL_STATE_SET_NUM-1))
		{
			lcd_display.state=LCD_DISPLAY_LASER_CTRL;//will turn to gif
			lcd_display.real_state=LCD_DISPLAY_LASER_CTRL;
			hal_lcd_fill(SET_RECTANGLE_X1,SET_RECTANGLE_Y1,SET_RECTANGLE_X2+1,SET_RECTANGLE_Y2+1,BLACK);
			laser_ctrl.state_value=key_ctrl.up_down;
			key_ctrl.up_down=0;
			lcd_display.laser_set=0;
		}
		if(key_ctrl.up_down==(LASER_CTRL_MODE_SET_NUM-1)||key_ctrl.up_down==(LASER_CTRL_STATE_SET_NUM-1))
		{
			lcd_display.state=LCD_DISPLAY_LASER_CTRL;//will turn to gif
			lcd_display.real_state=LCD_DISPLAY_LASER_CTRL;
			hal_lcd_fill(SET_RECTANGLE_X1,SET_RECTANGLE_Y1,SET_RECTANGLE_X2+1,SET_RECTANGLE_Y2+1,BLACK);
			key_ctrl.up_down=0;
			lcd_display.laser_set=0;
		}
	}
	else if(lcd_display.real_state==LCD_DISPLAY_SYSTEM)
	{
		if(key_ctrl.up_down==0)
		{
			lcd_display.state=LCD_DISPLAY_SYSTEM_SET;//will turn to gif
		  lcd_display.real_state=LCD_DISPLAY_SYSTEM_SET;
		  lcd_display.system_set=key_ctrl.up_down+1;
		}
		else if(key_ctrl.up_down==1)
		{
			lcd_display.state=LCD_DISPLAY_SYSTEM_ABOUT;//will turn to gif
			lcd_display.real_state=LCD_DISPLAY_SYSTEM_ABOUT;
			hal_lcd_fill(LCD_X1,LCD_X1,LCD_X2,LCD_Y2,BLACK);
		}
		else if(key_ctrl.up_down==2)
		{
			lcd_display.state=LCD_DISPLAY_MENU;//will turn to gif
			lcd_display.real_state=LCD_DISPLAY_MENU;
			hal_lcd_fill(LCD_X1,LCD_X1,LCD_X2,LCD_Y2,BLACK);
		}
		else
		{
//			lcd_display.state=LCD_DISPLAY_LASER_CTRL_SET;//will turn to gif
//		  lcd_display.real_state=LCD_DISPLAY_LASER_CTRL_SET;
//		  lcd_display.laser_set=key_ctrl.up_down+1;
		}
		key_ctrl.up_down=0;
	}
	else if(lcd_display.real_state==LCD_DISPLAY_SYSTEM_SET)
	{
		if(lcd_display.system_set==1 && key_ctrl.up_down!=(LASER_CTRL_LANGUAGE_SET_NUM-1))
		{
			lcd_display.state=LCD_DISPLAY_SYSTEM;//will turn to gif
			lcd_display.real_state=LCD_DISPLAY_SYSTEM;
			hal_lcd_fill(LCD_X1,LCD_X1,LCD_X2,LCD_Y2,BLACK);
			lcd_display.language_value=key_ctrl.up_down;
			hal_set_user_data(CHAR_LANGUAGE_DATA,lcd_display.language_value);
			key_ctrl.up_down=0;
			lcd_display.system_set=0;
		}
		if(key_ctrl.up_down==(LASER_CTRL_LANGUAGE_SET_NUM-1))
		{
			lcd_display.state=LCD_DISPLAY_SYSTEM;//will turn to gif
			lcd_display.real_state=LCD_DISPLAY_SYSTEM;
      hal_lcd_fill(SET_RECTANGLE_X1,SET_RECTANGLE_Y1,SET_RECTANGLE_X2+1,SET_RECTANGLE_Y2+1,BLACK);
			key_ctrl.up_down=0;
			lcd_display.laser_set=0;
		}
	}
	else if(lcd_display.real_state==LCD_DISPLAY_SYSTEM_ABOUT)
	{
		lcd_display.state=LCD_DISPLAY_SYSTEM;//will turn to gif
	  lcd_display.real_state=LCD_DISPLAY_SYSTEM;
		hal_lcd_fill(LCD_X1,LCD_X1,LCD_X2,LCD_Y2,BLACK);
	}
	else if(lcd_display.real_state==LCD_DISPLAY_STOPWATCH)
	{
		if(key_ctrl.up_down==0)
		{
			lcd_display.state=LCD_DISPLAY_STOPWATCH;
		  lcd_display.real_state=LCD_DISPLAY_STOPWATCH;
			if(lcd_display.stopwatch_ctrl==0)
			{
				lcd_display.stopwatch_ctrl=1;
				hal_stopwatch_ctrl(BEGIN);
			}
			else if(lcd_display.stopwatch_ctrl==1)
			{
				lcd_display.stopwatch_ctrl=2;
				hal_stopwatch_ctrl(STOP);
			}
			else if(lcd_display.stopwatch_ctrl==2)
			{
				lcd_display.stopwatch_ctrl=1;
				hal_stopwatch_ctrl(BEGIN);
			}
		}
		else if(key_ctrl.up_down==1)
		{
			lcd_display.state=LCD_DISPLAY_STOPWATCH;
		  lcd_display.real_state=LCD_DISPLAY_STOPWATCH;
			lcd_display.stopwatch_ctrl=0;
			hal_stopwatch_ctrl(STOP);
			hal_stopwatch_timebuff_clear();
		}
		else if(key_ctrl.up_down==2)
		{
			lcd_display.state=LCD_DISPLAY_MENU;//will turn to gif
		  lcd_display.real_state=LCD_DISPLAY_MENU;
			hal_lcd_fill(LCD_X1,LCD_X1,LCD_X2,LCD_Y2,BLACK);
		}
		key_ctrl.up_down=0;
	}
	hal_set_key_press(KEY_NULL);
}

static void key3_long(void)
{

}

static void key_default(void)
{
	
}

