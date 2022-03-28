#include "task_lcd.h"
#include "task_key.h"
#include "hal_usart.h"
#include "hal_echo.h"
//#include "pic.h"

laser_ctrl_t laser_ctrl;
lcd_display_t lcd_display;

static void lcd_data_init(void);
static void lcd_show_init(void);
//static void lcd_waiting_point(void);
static void lcd_press_any_key_to_continuet(void);
static void lcd_show_astronaut(void);
static void lcd_show_menu(void);
static void lcd_show_cursor(uint8_t x,uint8_t y,uint8_t key_num);
static void lcd_show_laser_control(void);
static void lcd_show_laser_control_set(void);
static void lcd_show_system(void);
static void lcd_show_system_set(void);
static void lcd_show_system_about(void);
static void lcd_show_stopwatch(void);
static void lcd_show_ultrasound(void);

void task_lcd_init(void)
{
	hal_lcd_init();
	hal_key_init();
	lcd_data_init();
	hal_lcd_fill(LCD_X1,LCD_X1,LCD_X2,LCD_Y2,BLACK);
}

static void lcd_data_init(void)
{
	lcd_display.state=LCD_DISPLAY_INIT;
	lcd_display.real_state=LCD_DISPLAY_INIT;
	lcd_display.language_value=hal_get_user_data(CHAR_LANGUAGE_DATA);
	lcd_display.mcu_type=hal_get_user_data(CHAR_MCU_TYPE);

}
void task_lcd_display(void)
{
	switch(lcd_display.state)
	{
		case LCD_DISPLAY_INIT:          { lcd_show_init();              break ;}
		case LCD_DISPLAY_ASTRONAUT:     { lcd_show_astronaut();         break ;}
		case LCD_DISPLAY_MENU:          { lcd_show_menu();              break ;}
		case LCD_DISPLAY_LASER_CTRL:    { lcd_show_laser_control();     break ;}
		case LCD_DISPLAY_LASER_CTRL_SET:{ lcd_show_laser_control_set(); break ;}
		case LCD_DISPLAY_SYSTEM:        { lcd_show_system();            break ;}
		case LCD_DISPLAY_SYSTEM_SET:    { lcd_show_system_set();        break ;}
		case LCD_DISPLAY_SYSTEM_ABOUT:  { lcd_show_system_about();      break ;}
		case LCD_DISPLAY_STOPWATCH:     { lcd_show_stopwatch();         break ;}
		case LCD_DISPLAY_ULTRASOUND:    { lcd_show_ultrasound();      break ;}
		default: {break;}
			
	}
}

static void lcd_show_init(void)
{
	if(lcd_display.language_value==0)
	{
		hal_lcd_show_string(SHOW_WORD_X,SHOW_WORD_Y,(uint8_t *)"system begin",BRRED,BLACK,SHOW_WORD_SIZE,COVER_MODE);
		hal_lcd_show_string(SHOW_WORD_X,SHOW_WORD_Y+SHOW_WORD_SIZE,(uint8_t *)"system clock init",BRRED,BLACK,SHOW_WORD_SIZE,COVER_MODE);
		if(lcd_display.mcu_type==1)
		{
			hal_lcd_show_string(SHOW_WORD_X,SHOW_WORD_Y+2*SHOW_WORD_SIZE,(uint8_t *)"mcu type:stm32f401rct6",BRRED,BLACK,SHOW_WORD_SIZE,COVER_MODE);
		  hal_lcd_show_string(SHOW_WORD_X,SHOW_WORD_Y+3*SHOW_WORD_SIZE,(uint8_t *)"mcu frequency:84M HZ",BRRED,BLACK,SHOW_WORD_SIZE,COVER_MODE);
		}
		else if (lcd_display.mcu_type==2)
		{
			hal_lcd_show_string(SHOW_WORD_X,SHOW_WORD_Y+2*SHOW_WORD_SIZE,(uint8_t *)"mcu type:gd32f130c8t6",BRRED,BLACK,SHOW_WORD_SIZE,COVER_MODE);
		  hal_lcd_show_string(SHOW_WORD_X,SHOW_WORD_Y+3*SHOW_WORD_SIZE,(uint8_t *)"mcu frequency:72M HZ",BRRED,BLACK,SHOW_WORD_SIZE,COVER_MODE);
		}
		hal_lcd_show_string(SHOW_WORD_X,SHOW_WORD_Y+4*SHOW_WORD_SIZE,(uint8_t *)"usart init baudrate:115200",BRRED,BLACK,SHOW_WORD_SIZE,COVER_MODE);
		hal_lcd_show_string(SHOW_WORD_X,SHOW_WORD_Y+5*SHOW_WORD_SIZE,(uint8_t *)"lcd init",BRRED,BLACK,SHOW_WORD_SIZE,COVER_MODE);
		hal_lcd_show_string(SHOW_WORD_X,SHOW_WORD_Y+6*SHOW_WORD_SIZE,(uint8_t *)"keyboard init",BRRED,BLACK,SHOW_WORD_SIZE,COVER_MODE);
		hal_lcd_show_string(SHOW_WORD_X,SHOW_WORD_Y+7*SHOW_WORD_SIZE,(uint8_t *)"laser init",BRRED,BLACK,SHOW_WORD_SIZE,COVER_MODE);
		hal_lcd_show_string(SHOW_WORD_X,SHOW_WORD_Y+8*SHOW_WORD_SIZE,(uint8_t *)"user data init",BRRED,BLACK,SHOW_WORD_SIZE,COVER_MODE);
		hal_lcd_show_string(SHOW_WORD_X,SHOW_WORD_Y+9*SHOW_WORD_SIZE,(uint8_t *)"hardware version:V1.0.0",BRRED,BLACK,SHOW_WORD_SIZE,COVER_MODE);
		hal_lcd_show_string(SHOW_WORD_X,SHOW_WORD_Y+10*SHOW_WORD_SIZE,(uint8_t *)"software version:V1.0.0",BRRED,BLACK,SHOW_WORD_SIZE,COVER_MODE);
	}
	else if(lcd_display.language_value==1)
	{
		hal_lcd_font_GB2312_string(SHOW_WORD_X,SHOW_WORD_Y,SHOW_WORD_SIZE_C,(uint8_t *)"ϵͳ����",BRRED,BLACK);
		hal_lcd_font_GB2312_string(SHOW_WORD_X,SHOW_WORD_Y+SHOW_WORD_SIZE,SHOW_WORD_SIZE_C,(uint8_t *)"ϵͳʱ�ӳ�ʼ�����",BRRED,BLACK);
		if(lcd_display.mcu_type==1)
		{
			hal_lcd_font_GB2312_string(SHOW_WORD_X,SHOW_WORD_Y+2*SHOW_WORD_SIZE,SHOW_WORD_SIZE_C,(uint8_t *)"оƬ�ͺ�",BRRED,BLACK);hal_lcd_show_string(SHOW_WORD_X+4*SHOW_WORD_SIZE_C,SHOW_WORD_Y+2*SHOW_WORD_SIZE,(uint8_t *)":stm32f401rct6",BRRED,BLACK,SHOW_WORD_SIZE_C,COVER_MODE);
		  hal_lcd_font_GB2312_string(SHOW_WORD_X,SHOW_WORD_Y+3*SHOW_WORD_SIZE,SHOW_WORD_SIZE_C,(uint8_t *)"����Ƶ��",BRRED,BLACK);hal_lcd_show_string(SHOW_WORD_X+4*SHOW_WORD_SIZE_C,SHOW_WORD_Y+3*SHOW_WORD_SIZE,(uint8_t *)":84M HZ",BRRED,BLACK,SHOW_WORD_SIZE_C,COVER_MODE);
		}
		else if(lcd_display.mcu_type==2)
		{
			hal_lcd_font_GB2312_string(SHOW_WORD_X,SHOW_WORD_Y+2*SHOW_WORD_SIZE,SHOW_WORD_SIZE_C,(uint8_t *)"оƬ�ͺ�",BRRED,BLACK);hal_lcd_show_string(SHOW_WORD_X+4*SHOW_WORD_SIZE_C,SHOW_WORD_Y+2*SHOW_WORD_SIZE,(uint8_t *)":gd32f130c8t6",BRRED,BLACK,SHOW_WORD_SIZE_C,COVER_MODE);
		  hal_lcd_font_GB2312_string(SHOW_WORD_X,SHOW_WORD_Y+3*SHOW_WORD_SIZE,SHOW_WORD_SIZE_C,(uint8_t *)"����Ƶ��",BRRED,BLACK);hal_lcd_show_string(SHOW_WORD_X+4*SHOW_WORD_SIZE_C,SHOW_WORD_Y+3*SHOW_WORD_SIZE,(uint8_t *)":72M HZ",BRRED,BLACK,SHOW_WORD_SIZE_C,COVER_MODE);

		}
		hal_lcd_font_GB2312_string(SHOW_WORD_X,SHOW_WORD_Y+4*SHOW_WORD_SIZE,SHOW_WORD_SIZE_C,(uint8_t *)"���ڲ�����",BRRED,BLACK);hal_lcd_show_string(SHOW_WORD_X+5*SHOW_WORD_SIZE_C,SHOW_WORD_Y+4*SHOW_WORD_SIZE,(uint8_t *)":115200",BRRED,BLACK,SHOW_WORD_SIZE_C,COVER_MODE);
		hal_lcd_font_GB2312_string(SHOW_WORD_X,SHOW_WORD_Y+5*SHOW_WORD_SIZE,SHOW_WORD_SIZE_C,(uint8_t *)"��Ļ��ʼ�����",BRRED,BLACK);
		hal_lcd_font_GB2312_string(SHOW_WORD_X,SHOW_WORD_Y+6*SHOW_WORD_SIZE,SHOW_WORD_SIZE_C,(uint8_t *)"���̳�ʼ�����",BRRED,BLACK);
		hal_lcd_font_GB2312_string(SHOW_WORD_X,SHOW_WORD_Y+7*SHOW_WORD_SIZE,SHOW_WORD_SIZE_C,(uint8_t *)"�����ʼ�����",BRRED,BLACK);
		hal_lcd_font_GB2312_string(SHOW_WORD_X,SHOW_WORD_Y+8*SHOW_WORD_SIZE,SHOW_WORD_SIZE_C,(uint8_t *)"�û����ݳ�ʼ�����",BRRED,BLACK);
		hal_lcd_font_GB2312_string(SHOW_WORD_X,SHOW_WORD_Y+9*SHOW_WORD_SIZE,SHOW_WORD_SIZE_C,(uint8_t *)"Ӳ���汾��",BRRED,BLACK);hal_lcd_show_string(SHOW_WORD_X+5*SHOW_WORD_SIZE_C,SHOW_WORD_Y+9*SHOW_WORD_SIZE,(uint8_t *)":V1.0.0",BRRED,BLACK,SHOW_WORD_SIZE_C,COVER_MODE);
		hal_lcd_font_GB2312_string(SHOW_WORD_X,SHOW_WORD_Y+10*SHOW_WORD_SIZE,SHOW_WORD_SIZE_C,(uint8_t *)"����汾��",BRRED,BLACK);hal_lcd_show_string(SHOW_WORD_X+5*SHOW_WORD_SIZE_C,SHOW_WORD_Y+10*SHOW_WORD_SIZE,(uint8_t *)":V1.0.0",BRRED,BLACK,SHOW_WORD_SIZE_C,COVER_MODE);
	}
	lcd_display.state=LCD_DISPLAY_ASTRONAUT;
}

static void lcd_press_any_key_to_continuet(void)
{
	lcd_display.point_num=hal_lcd_get_waiting_time();
	if(lcd_display.real_state==LCD_DISPLAY_INIT)
	{
		if(lcd_display.language_value==0)
		{
			switch (lcd_display.point_num)
			{
				case 1:{hal_lcd_show_string(PRESS_KEY_X,PRESS_KEY_Y,(uint8_t *)"press any key",BRRED,BLACK,PRESS_KEY_SIZE,COVER_MODE); hal_lcd_show_string(PRESS_KEY_X,PRESS_KEY_Y+PRESS_KEY_SIZE,(uint8_t *)"to continue",BRRED,BLACK,PRESS_KEY_SIZE,COVER_MODE); break;}
				case 2:{hal_lcd_show_string(PRESS_KEY_X,PRESS_KEY_Y,(uint8_t *)"press any key",BRRED,BLACK,PRESS_KEY_SIZE,COVER_MODE); hal_lcd_show_string(PRESS_KEY_X,PRESS_KEY_Y+PRESS_KEY_SIZE,(uint8_t *)"to continue",BRRED,BLACK,PRESS_KEY_SIZE,COVER_MODE); break;}
				case 3:{hal_lcd_show_string(PRESS_KEY_X,PRESS_KEY_Y,(uint8_t *)"             ",BRRED,BLACK,PRESS_KEY_SIZE,COVER_MODE); hal_lcd_show_string(PRESS_KEY_X,PRESS_KEY_Y+PRESS_KEY_SIZE,(uint8_t *)"           ",BRRED,BLACK,PRESS_KEY_SIZE,COVER_MODE);break;}
				default:{break;}
			}
		}
		else if(lcd_display.language_value==1)
		{
			switch (lcd_display.point_num)
			{
				case 1:{hal_lcd_font_GB2312_string(PRESS_KEY_X,PRESS_KEY_Y,PRESS_KEY_SIZE_C,(uint8_t *)"��ѹ���ⰴ������",BRRED,BLACK);  break;}
				case 2:{hal_lcd_font_GB2312_string(PRESS_KEY_X,PRESS_KEY_Y,PRESS_KEY_SIZE_C,(uint8_t *)"��ѹ���ⰴ������",BRRED,BLACK);  break;}
				case 3:{hal_lcd_fill(PRESS_KEY_X,PRESS_KEY_Y,PRESS_KEY_X+PRESS_KEY_SIZE*6,PRESS_KEY_Y+PRESS_KEY_SIZE*2,BLACK);break;}
				default:{break;}
			}
		}

		lcd_display.point_num=0;
	}
}
static void lcd_show_astronaut(void)
{
	lcd_display.astronaut_num=hal_lcd_get_astronaut_image_num();
//	switch (lcd_display.astronaut_num)
//	{
//		case 1: {hal_lcd_show_picture(ASTRONAUT_IMAGE_X1,ASTRONAUT_IMAGE_Y1,ASTRONAUT_IMAGE_X_SIZE,ASTRONAUT_IMAGE_Y_SIZE,gImage_0); break;}
//		case 2: {hal_lcd_show_picture(ASTRONAUT_IMAGE_X1,ASTRONAUT_IMAGE_Y1,ASTRONAUT_IMAGE_X_SIZE,ASTRONAUT_IMAGE_Y_SIZE,gImage_1); break;}
//		case 3: {hal_lcd_show_picture(ASTRONAUT_IMAGE_X1,ASTRONAUT_IMAGE_Y1,ASTRONAUT_IMAGE_X_SIZE,ASTRONAUT_IMAGE_Y_SIZE,gImage_2); break;}
//		case 4: {hal_lcd_show_picture(ASTRONAUT_IMAGE_X1,ASTRONAUT_IMAGE_Y1,ASTRONAUT_IMAGE_X_SIZE,ASTRONAUT_IMAGE_Y_SIZE,gImage_3); break;}
//		case 5: {hal_lcd_show_picture(ASTRONAUT_IMAGE_X1,ASTRONAUT_IMAGE_Y1,ASTRONAUT_IMAGE_X_SIZE,ASTRONAUT_IMAGE_Y_SIZE,gImage_4); break;}
//		case 6: {hal_lcd_show_picture(ASTRONAUT_IMAGE_X1,ASTRONAUT_IMAGE_Y1,ASTRONAUT_IMAGE_X_SIZE,ASTRONAUT_IMAGE_Y_SIZE,gImage_5); break;}
//		case 7: {hal_lcd_show_picture(ASTRONAUT_IMAGE_X1,ASTRONAUT_IMAGE_Y1,ASTRONAUT_IMAGE_X_SIZE,ASTRONAUT_IMAGE_Y_SIZE,gImage_6); break;}
//		case 8: {hal_lcd_show_picture(ASTRONAUT_IMAGE_X1,ASTRONAUT_IMAGE_Y1,ASTRONAUT_IMAGE_X_SIZE,ASTRONAUT_IMAGE_Y_SIZE,gImage_7); break;}
//		case 9: {hal_lcd_show_picture(ASTRONAUT_IMAGE_X1,ASTRONAUT_IMAGE_Y1,ASTRONAUT_IMAGE_X_SIZE,ASTRONAUT_IMAGE_Y_SIZE,gImage_8); break;}
//		case 10:{hal_lcd_show_picture(ASTRONAUT_IMAGE_X1,ASTRONAUT_IMAGE_Y1,ASTRONAUT_IMAGE_X_SIZE,ASTRONAUT_IMAGE_Y_SIZE,gImage_9); break;}
//		case 11:{hal_lcd_show_picture(ASTRONAUT_IMAGE_X1,ASTRONAUT_IMAGE_Y1,ASTRONAUT_IMAGE_X_SIZE,ASTRONAUT_IMAGE_Y_SIZE,gImage_10); break;}
//		case 12:{hal_lcd_show_picture(ASTRONAUT_IMAGE_X1,ASTRONAUT_IMAGE_Y1,ASTRONAUT_IMAGE_X_SIZE,ASTRONAUT_IMAGE_Y_SIZE,gImage_11); break;}
//		case 13:{hal_lcd_show_picture(ASTRONAUT_IMAGE_X1,ASTRONAUT_IMAGE_Y1,ASTRONAUT_IMAGE_X_SIZE,ASTRONAUT_IMAGE_Y_SIZE,gImage_12); break;}
//		case 14:{hal_lcd_show_picture(ASTRONAUT_IMAGE_X1,ASTRONAUT_IMAGE_Y1,ASTRONAUT_IMAGE_X_SIZE,ASTRONAUT_IMAGE_Y_SIZE,gImage_13); break;}
//		default:{break;}
//	}
	lcd_press_any_key_to_continuet();
	lcd_display.astronaut_num=0;
}

static void lcd_show_menu(void)
{
	if(lcd_display.language_value==0)
	{
		hal_lcd_show_string(MENU_TITLE_X,MENU_TITLE_Y,(uint8_t *)"MENU",BRRED,BLACK,TITLE_SIZE,COVER_MODE);
		hal_lcd_show_string(MAIN_WORD_X,MAIN_WORD_Y,(uint8_t *)"laser control",BRRED,BLACK,MAIN_WORD_SIZE,COVER_MODE);
		hal_lcd_show_string(MAIN_WORD_X,MAIN_WORD_Y+MAIN_WORD_SIZE,(uint8_t *)"rgb led control",BRRED,BLACK,MAIN_WORD_SIZE,COVER_MODE);
		hal_lcd_show_string(MAIN_WORD_X,MAIN_WORD_Y+2*MAIN_WORD_SIZE,(uint8_t *)"wifi connection",BRRED,BLACK,MAIN_WORD_SIZE,COVER_MODE);
		hal_lcd_show_string(MAIN_WORD_X,MAIN_WORD_Y+3*MAIN_WORD_SIZE,(uint8_t *)"ultrasound",BRRED,BLACK,MAIN_WORD_SIZE,COVER_MODE);
		hal_lcd_show_string(MAIN_WORD_X,MAIN_WORD_Y+4*MAIN_WORD_SIZE,(uint8_t *)"stopwatch",BRRED,BLACK,MAIN_WORD_SIZE,COVER_MODE);
		hal_lcd_show_string(MAIN_WORD_X,MAIN_WORD_Y+5*MAIN_WORD_SIZE,(uint8_t *)"game",BRRED,BLACK,MAIN_WORD_SIZE,COVER_MODE);
		hal_lcd_show_string(MAIN_WORD_X,MAIN_WORD_Y+6*MAIN_WORD_SIZE,(uint8_t *)"system set",BRRED,BLACK,MAIN_WORD_SIZE,COVER_MODE);
	}
	else if(lcd_display.language_value==1)
	{
		hal_lcd_font_GB2312_string(LCD_X2/2-TITLE_SIZE*2/2,MENU_TITLE_Y,TITLE_SIZE,(uint8_t *)"�˵�",BRRED,BLACK);
		hal_lcd_font_GB2312_string(MAIN_WORD_X,MAIN_WORD_Y,MAIN_WORD_SIZE_C,(uint8_t *)"�������",BRRED,BLACK);
		hal_lcd_font_GB2312_string(MAIN_WORD_X,MAIN_WORD_Y+MAIN_WORD_SIZE,MAIN_WORD_SIZE_C,(uint8_t *)"��Χ�ƿ���",BRRED,BLACK);
		hal_lcd_font_GB2312_string(MAIN_WORD_X,MAIN_WORD_Y+2*MAIN_WORD_SIZE,MAIN_WORD_SIZE_C,(uint8_t *)"��������",BRRED,BLACK);
		hal_lcd_font_GB2312_string(MAIN_WORD_X,MAIN_WORD_Y+3*MAIN_WORD_SIZE,MAIN_WORD_SIZE_C,(uint8_t *)"������",BRRED,BLACK);
		hal_lcd_font_GB2312_string(MAIN_WORD_X,MAIN_WORD_Y+4*MAIN_WORD_SIZE,MAIN_WORD_SIZE_C,(uint8_t *)"���",BRRED,BLACK);
		hal_lcd_font_GB2312_string(MAIN_WORD_X,MAIN_WORD_Y+5*MAIN_WORD_SIZE,MAIN_WORD_SIZE_C,(uint8_t *)"��Ϸ",BRRED,BLACK);
		hal_lcd_font_GB2312_string(MAIN_WORD_X,MAIN_WORD_Y+6*MAIN_WORD_SIZE,MAIN_WORD_SIZE_C,(uint8_t *)"ϵͳ����",BRRED,BLACK);
	}
	
	lcd_show_cursor(CURSOR_X,CURSOR_Y,key_ctrl.up_down);
	lcd_display.state=LCD_DISPLAY_ASTRONAUT;
}
static void lcd_show_cursor(uint8_t x,uint8_t y,uint8_t key_num)
{
  if(lcd_display.language_value==0)
	{
		if(lcd_display.real_state==LCD_DISPLAY_MENU)
		{
			hal_lcd_fill(x,y,x+CURSOR_SIZE,y+CURSOR_SIZE*MENU_OPTIONS_NUM,BLACK);
			hal_lcd_show_string(x,y+key_num*CURSOR_SIZE,(uint8_t *)"->",BRRED,BLACK,CURSOR_SIZE,COVER_MODE);
		}
		else if(lcd_display.real_state==LCD_DISPLAY_LASER_CTRL)
		{
			hal_lcd_fill(x,y,x+CURSOR_SIZE,y+CURSOR_SIZE*LASER_CTRL_OPTIONS_NUM,BLACK);
			hal_lcd_show_string(x,y+key_num*CURSOR_SIZE,(uint8_t *)"->",BRRED,BLACK,CURSOR_SIZE,COVER_MODE);
		}
		else if(lcd_display.real_state==LCD_DISPLAY_LASER_CTRL_SET)
		{
			if(lcd_display.laser_set==1)
			{
				hal_lcd_fill(x,y,x+CURSOR_SIZE,y+CURSOR_SIZE*LASER_CTRL_MODE_SET_NUM,BLACK);
				hal_lcd_show_string(x,y+key_num*CURSOR_SIZE,(uint8_t *)"->",BRRED,BLACK,CURSOR_SIZE,COVER_MODE);
			}
			else if(lcd_display.laser_set==2)
			{
				hal_lcd_fill(x,y,x+CURSOR_SIZE,y+CURSOR_SIZE*LASER_CTRL_STATE_SET_NUM,BLACK);
				hal_lcd_show_string(x,y+key_num*CURSOR_SIZE,(uint8_t *)"->",BRRED,BLACK,CURSOR_SIZE,COVER_MODE);
			}
		}
		else if(lcd_display.real_state==LCD_DISPLAY_SYSTEM)
		{
			hal_lcd_fill(x,y,x+CURSOR_SIZE,y+CURSOR_SIZE*LASER_CTRL_SYSTEM_NUM,BLACK);
			hal_lcd_show_string(x,y+key_num*CURSOR_SIZE,(uint8_t *)"->",BRRED,BLACK,CURSOR_SIZE,COVER_MODE);
		}
		else if(lcd_display.real_state==LCD_DISPLAY_SYSTEM_SET)
		{
			if(lcd_display.system_set==1)
			{
				hal_lcd_fill(x,y,x+CURSOR_SIZE,y+CURSOR_SIZE*LASER_CTRL_LANGUAGE_SET_NUM,BLACK);
				hal_lcd_show_string(x,y+key_num*CURSOR_SIZE,(uint8_t *)"->",BRRED,BLACK,CURSOR_SIZE,COVER_MODE);
			}
		}
		else if(lcd_display.real_state==LCD_DISPLAY_STOPWATCH)
		{	
			if(key_num==0)
			{
				hal_lcd_fill(STOPWATCH_WORD_X+90-32,STOPWATCH_WORD_Y,STOPWATCH_WORD_X+90,STOPWATCH_WORD_Y+STOPWATCH_WORD_SIZE,BLACK);
			  hal_lcd_fill(STOPWATCH_WORD_X+190-32,STOPWATCH_WORD_Y,STOPWATCH_WORD_X+190,STOPWATCH_WORD_Y+STOPWATCH_WORD_SIZE,BLACK);
				hal_lcd_show_string(STOPWATCH_WORD_X-32,STOPWATCH_WORD_Y,(uint8_t *)"->",BRRED,BLACK,CURSOR_SIZE,COVER_MODE);
			}
			else if(key_num==1)
			{
				hal_lcd_fill(STOPWATCH_WORD_X-32,STOPWATCH_WORD_Y,STOPWATCH_WORD_X,STOPWATCH_WORD_Y+STOPWATCH_WORD_SIZE,BLACK);
			  hal_lcd_fill(STOPWATCH_WORD_X+190-32,STOPWATCH_WORD_Y,STOPWATCH_WORD_X+190,STOPWATCH_WORD_Y+STOPWATCH_WORD_SIZE,BLACK);
				hal_lcd_show_string(STOPWATCH_WORD_X+90-32,STOPWATCH_WORD_Y,(uint8_t *)"->",BRRED,BLACK,CURSOR_SIZE,COVER_MODE);
			}
			else if(key_num==2)
			{
				hal_lcd_fill(STOPWATCH_WORD_X-32,STOPWATCH_WORD_Y,STOPWATCH_WORD_X,STOPWATCH_WORD_Y+STOPWATCH_WORD_SIZE,BLACK);
			  hal_lcd_fill(STOPWATCH_WORD_X+90-32,STOPWATCH_WORD_Y,STOPWATCH_WORD_X+90,STOPWATCH_WORD_Y+STOPWATCH_WORD_SIZE,BLACK);
				hal_lcd_show_string(STOPWATCH_WORD_X+190-32,STOPWATCH_WORD_Y,(uint8_t *)"->",BRRED,BLACK,CURSOR_SIZE,COVER_MODE);
			}
		}
	}
	else if(lcd_display.language_value==1)
	{
		if(lcd_display.real_state==LCD_DISPLAY_MENU)
		{
			hal_lcd_fill(x,y,x+CURSOR_SIZE,y+CURSOR_SIZE*MENU_OPTIONS_NUM,BLACK);
			hal_lcd_show_string(x,y+key_num*CURSOR_SIZE,(uint8_t *)"->",BRRED,BLACK,CURSOR_SIZE_C,COVER_MODE);
		}
		else if(lcd_display.real_state==LCD_DISPLAY_LASER_CTRL)
		{
			hal_lcd_fill(x,y,x+CURSOR_SIZE,y+CURSOR_SIZE*LASER_CTRL_OPTIONS_NUM,BLACK);
			hal_lcd_show_string(x,y+key_num*CURSOR_SIZE,(uint8_t *)"->",BRRED,BLACK,CURSOR_SIZE_C,COVER_MODE);
		}
		else if(lcd_display.real_state==LCD_DISPLAY_LASER_CTRL_SET)
		{
			if(lcd_display.laser_set==1)
			{
				hal_lcd_fill(x,y,x+CURSOR_SIZE,y+CURSOR_SIZE*LASER_CTRL_MODE_SET_NUM,BLACK);
				hal_lcd_show_string(x,y+key_num*CURSOR_SIZE,(uint8_t *)"->",BRRED,BLACK,CURSOR_SIZE_C,COVER_MODE);
			}
			else if(lcd_display.laser_set==2)
			{
				hal_lcd_fill(x,y,x+CURSOR_SIZE,y+CURSOR_SIZE*LASER_CTRL_STATE_SET_NUM,BLACK);
				hal_lcd_show_string(x,y+key_num*CURSOR_SIZE,(uint8_t *)"->",BRRED,BLACK,CURSOR_SIZE_C,COVER_MODE);
			}
		}
		else if(lcd_display.real_state==LCD_DISPLAY_SYSTEM)
		{
			hal_lcd_fill(x,y,x+CURSOR_SIZE,y+CURSOR_SIZE*LASER_CTRL_SYSTEM_NUM,BLACK);
			hal_lcd_show_string(x,y+key_num*CURSOR_SIZE,(uint8_t *)"->",BRRED,BLACK,CURSOR_SIZE_C,COVER_MODE);
		}
		else if(lcd_display.real_state==LCD_DISPLAY_SYSTEM_SET)
		{
			if(lcd_display.system_set==1)
			{
				hal_lcd_fill(x,y,x+CURSOR_SIZE,y+CURSOR_SIZE*LASER_CTRL_LANGUAGE_SET_NUM,BLACK);
				hal_lcd_show_string(x,y+key_num*CURSOR_SIZE,(uint8_t *)"->",BRRED,BLACK,CURSOR_SIZE_C,COVER_MODE);
			}
		}
		else if(lcd_display.real_state==LCD_DISPLAY_STOPWATCH)
		{	
			if(key_num==0)
			{
				hal_lcd_fill(STOPWATCH_WORD_X+90-32,STOPWATCH_WORD_Y,STOPWATCH_WORD_X+90,STOPWATCH_WORD_Y+STOPWATCH_WORD_SIZE,BLACK);
			  hal_lcd_fill(STOPWATCH_WORD_X+190-32,STOPWATCH_WORD_Y,STOPWATCH_WORD_X+190,STOPWATCH_WORD_Y+STOPWATCH_WORD_SIZE,BLACK);
				hal_lcd_show_string(STOPWATCH_WORD_X-32,STOPWATCH_WORD_Y,(uint8_t *)"->",BRRED,BLACK,CURSOR_SIZE,COVER_MODE);
			}
			else if(key_num==1)
			{
				hal_lcd_fill(STOPWATCH_WORD_X-32,STOPWATCH_WORD_Y,STOPWATCH_WORD_X,STOPWATCH_WORD_Y+STOPWATCH_WORD_SIZE,BLACK);
			  hal_lcd_fill(STOPWATCH_WORD_X+190-32,STOPWATCH_WORD_Y,STOPWATCH_WORD_X+190,STOPWATCH_WORD_Y+STOPWATCH_WORD_SIZE,BLACK);
				hal_lcd_show_string(STOPWATCH_WORD_X+90-32,STOPWATCH_WORD_Y,(uint8_t *)"->",BRRED,BLACK,CURSOR_SIZE,COVER_MODE);
			}
			else if(key_num==2)
			{
				hal_lcd_fill(STOPWATCH_WORD_X-32,STOPWATCH_WORD_Y,STOPWATCH_WORD_X,STOPWATCH_WORD_Y+STOPWATCH_WORD_SIZE,BLACK);
			  hal_lcd_fill(STOPWATCH_WORD_X+90-32,STOPWATCH_WORD_Y,STOPWATCH_WORD_X+90,STOPWATCH_WORD_Y+STOPWATCH_WORD_SIZE,BLACK);
				hal_lcd_show_string(STOPWATCH_WORD_X+190-32,STOPWATCH_WORD_Y,(uint8_t *)"->",BRRED,BLACK,CURSOR_SIZE,COVER_MODE);
			}
		}
	}


}
static void lcd_show_laser_control(void)
{
	if(lcd_display.language_value==0)
	{
		hal_lcd_show_string(LASER_CTRL_TITLE_X,LASER_CTRL_TITLE_Y,(uint8_t *)"LASER CONTROL",BRRED,BLACK,TITLE_SIZE,COVER_MODE);
		hal_lcd_show_string(MAIN_WORD_X,MAIN_WORD_Y,(uint8_t *)"mode:",BRRED,BLACK,BELONG_WORD_SIZE,COVER_MODE);
		hal_lcd_show_string(MAIN_WORD_X,MAIN_WORD_Y+MAIN_WORD_SIZE,(uint8_t *)"state:",BRRED,BLACK,BELONG_WORD_SIZE,COVER_MODE);
		hal_lcd_show_string(MAIN_WORD_X,MAIN_WORD_Y+2*MAIN_WORD_SIZE,(uint8_t *)"exist",BRRED,BLACK,BELONG_WORD_SIZE,COVER_MODE);
		if(laser_ctrl.mode_value==0)      hal_lcd_show_string(BELONG_WORD_X,BELONG_WORD_Y,(uint8_t *)"single",BRRED,BLACK,BELONG_WORD_SIZE,COVER_MODE);
		else if(laser_ctrl.mode_value==1) hal_lcd_show_string(BELONG_WORD_X,BELONG_WORD_Y,(uint8_t *)"auto  ",BRRED,BLACK,BELONG_WORD_SIZE,COVER_MODE);
		else if(laser_ctrl.mode_value==2) hal_lcd_show_string(BELONG_WORD_X,BELONG_WORD_Y,(uint8_t *)"key control  ",BRRED,BLACK,BELONG_WORD_SIZE,COVER_MODE);
		if(laser_ctrl.state_value==0)      hal_lcd_show_string(BELONG_WORD_X,BELONG_WORD_Y+BELONG_WORD_SIZE,(uint8_t *)"close",BRRED,BLACK,BELONG_WORD_SIZE,COVER_MODE);
		else if(laser_ctrl.state_value==1) hal_lcd_show_string(BELONG_WORD_X,BELONG_WORD_Y+BELONG_WORD_SIZE,(uint8_t *)"open ",BRRED,BLACK,BELONG_WORD_SIZE,COVER_MODE);
	}
	else if (lcd_display.language_value==1)
	{
		hal_lcd_font_GB2312_string(LCD_X2/2-TITLE_SIZE*4/2,LASER_CTRL_TITLE_Y,TITLE_SIZE,(uint8_t *)"�������",BRRED,BLACK);
		hal_lcd_font_GB2312_string(MAIN_WORD_X,MAIN_WORD_Y,BELONG_WORD_SIZE_C,(uint8_t *)"ģʽ:",BRRED,BLACK);
		hal_lcd_font_GB2312_string(MAIN_WORD_X,MAIN_WORD_Y+MAIN_WORD_SIZE,BELONG_WORD_SIZE_C,(uint8_t *)"״̬:",BRRED,BLACK);
		hal_lcd_font_GB2312_string(MAIN_WORD_X,MAIN_WORD_Y+2*MAIN_WORD_SIZE,BELONG_WORD_SIZE_C,(uint8_t *)"�뿪",BRRED,BLACK);
		if(laser_ctrl.mode_value==0)      hal_lcd_font_GB2312_string(BELONG_WORD_X,BELONG_WORD_Y,BELONG_WORD_SIZE_C,(uint8_t *)"����",BRRED,BLACK);
		else if(laser_ctrl.mode_value==1) hal_lcd_font_GB2312_string(BELONG_WORD_X,BELONG_WORD_Y,BELONG_WORD_SIZE_C,(uint8_t *)"�Զ�  ",BRRED,BLACK);
		else if(laser_ctrl.mode_value==2) hal_lcd_font_GB2312_string(BELONG_WORD_X,BELONG_WORD_Y,BELONG_WORD_SIZE_C,(uint8_t *)"��������  ",BRRED,BLACK);
		if(laser_ctrl.state_value==0)      hal_lcd_font_GB2312_string(BELONG_WORD_X,BELONG_WORD_Y+BELONG_WORD_SIZE,BELONG_WORD_SIZE_C,(uint8_t *)"�ر�",BRRED,BLACK);
		else if(laser_ctrl.state_value==1) hal_lcd_font_GB2312_string(BELONG_WORD_X,BELONG_WORD_Y+BELONG_WORD_SIZE,BELONG_WORD_SIZE_C,(uint8_t *)"���� ",BRRED,BLACK);

	}

	lcd_show_cursor(CURSOR_X,CURSOR_Y,key_ctrl.up_down);
	lcd_display.state=LCD_DISPLAY_ASTRONAUT;
}

static void lcd_show_laser_control_set(void)
{
	if(lcd_display.language_value==0)
	{
		if(lcd_display.laser_set==1) //set mode
		{
			hal_lcd_fill(CURSOR_X,CURSOR_Y,CURSOR_X+CURSOR_SIZE,CURSOR_Y+CURSOR_SIZE*LASER_CTRL_OPTIONS_NUM,BLACK);//clear last cursor
			hal_lcd_draw_rectangle(SET_RECTANGLE_X1,SET_RECTANGLE_Y1,SET_RECTANGLE_X2,SET_RECTANGLE_Y2,BRRED);
			hal_lcd_draw_line(SET_LINE_X1,SET_LINE_Y1,SET_LINE_X2,SET_LINE_Y2,BRRED);
			hal_lcd_show_string(230,37,(uint8_t *)"mode",BRRED,BLACK,SET_WORD_SIZE,COVER_MODE);
			hal_lcd_show_string(SET_WORD_X,SET_WORD_Y,(uint8_t *)"single",BRRED,BLACK,SET_WORD_SIZE,COVER_MODE);
			hal_lcd_show_string(SET_WORD_X,SET_WORD_Y+SET_WORD_SIZE,(uint8_t *)"auto",BRRED,BLACK,SET_WORD_SIZE,COVER_MODE);
			hal_lcd_show_string(SET_WORD_X,SET_WORD_Y+2*SET_WORD_SIZE,(uint8_t *)"key control",BRRED,BLACK,SET_WORD_SIZE,COVER_MODE);
			hal_lcd_show_string(SET_WORD_X,SET_WORD_Y+3*SET_WORD_SIZE,(uint8_t *)"exist",BRRED,BLACK,SET_WORD_SIZE,COVER_MODE);
			lcd_show_cursor(SET_CURSOR_X,SET_CURSOR_Y,key_ctrl.up_down);
			lcd_display.state=LCD_DISPLAY_ASTRONAUT;
		}
		else if(lcd_display.laser_set==2) //set state
		{
			hal_lcd_fill(CURSOR_X,CURSOR_Y,CURSOR_X+CURSOR_SIZE,CURSOR_Y+CURSOR_SIZE*LASER_CTRL_OPTIONS_NUM,BLACK);//clear last cursor
			hal_lcd_draw_rectangle(SET_RECTANGLE_X1,SET_RECTANGLE_Y1,SET_RECTANGLE_X2,SET_RECTANGLE_Y2,BRRED);
			hal_lcd_draw_line(SET_LINE_X1,SET_LINE_Y1,SET_LINE_X2,SET_LINE_Y2,BRRED);
			hal_lcd_show_string(208,37,(uint8_t *)"state",BRRED,BLACK,SET_WORD_SIZE,COVER_MODE);
			hal_lcd_show_string(SET_WORD_X,SET_WORD_Y,(uint8_t *)"close",BRRED,BLACK,SET_WORD_SIZE,COVER_MODE);
			hal_lcd_show_string(SET_WORD_X,SET_WORD_Y+SET_WORD_SIZE,(uint8_t *)"open",BRRED,BLACK,SET_WORD_SIZE,COVER_MODE);
			hal_lcd_show_string(SET_WORD_X,SET_WORD_Y+2*SET_WORD_SIZE,(uint8_t *)"exist",BRRED,BLACK,SET_WORD_SIZE,COVER_MODE);
			lcd_show_cursor(SET_CURSOR_X,SET_CURSOR_Y,key_ctrl.up_down);
			lcd_display.state=LCD_DISPLAY_ASTRONAUT;
		}
	}
	else if (lcd_display.language_value==1)
	{
		if(lcd_display.laser_set==1) //set mode
		{
			hal_lcd_fill(CURSOR_X,CURSOR_Y,CURSOR_X+CURSOR_SIZE,CURSOR_Y+CURSOR_SIZE*LASER_CTRL_OPTIONS_NUM,BLACK);//clear last cursor
			hal_lcd_draw_rectangle(SET_RECTANGLE_X1,SET_RECTANGLE_Y1,SET_RECTANGLE_X2,SET_RECTANGLE_Y2,BRRED);
			hal_lcd_draw_line(SET_LINE_X1,SET_LINE_Y1,SET_LINE_X2,SET_LINE_Y2,BRRED);
			hal_lcd_font_GB2312_string(230,37,SET_WORD_SIZE_C,(uint8_t *)"ģʽ",BRRED,BLACK);
			hal_lcd_font_GB2312_string(SET_WORD_X,SET_WORD_Y,SET_WORD_SIZE_C,(uint8_t *)"����",BRRED,BLACK);
			hal_lcd_font_GB2312_string(SET_WORD_X,SET_WORD_Y+SET_WORD_SIZE,SET_WORD_SIZE_C,(uint8_t *)"�Զ�",BRRED,BLACK);
			hal_lcd_font_GB2312_string(SET_WORD_X,SET_WORD_Y+2*SET_WORD_SIZE,SET_WORD_SIZE_C,(uint8_t *)"��������",BRRED,BLACK);
			hal_lcd_font_GB2312_string(SET_WORD_X,SET_WORD_Y+3*SET_WORD_SIZE,SET_WORD_SIZE_C,(uint8_t *)"�뿪",BRRED,BLACK);
			lcd_show_cursor(SET_CURSOR_X,SET_CURSOR_Y,key_ctrl.up_down);
			lcd_display.state=LCD_DISPLAY_ASTRONAUT;
		}
		else if(lcd_display.laser_set==2) //set state
		{
			hal_lcd_fill(CURSOR_X,CURSOR_Y,CURSOR_X+CURSOR_SIZE,CURSOR_Y+CURSOR_SIZE*LASER_CTRL_OPTIONS_NUM,BLACK);//clear last cursor
			hal_lcd_draw_rectangle(SET_RECTANGLE_X1,SET_RECTANGLE_Y1,SET_RECTANGLE_X2,SET_RECTANGLE_Y2,BRRED);
			hal_lcd_draw_line(SET_LINE_X1,SET_LINE_Y1,SET_LINE_X2,SET_LINE_Y2,BRRED);
			hal_lcd_font_GB2312_string(208,37,SET_WORD_SIZE_C,(uint8_t *)"״̬",BRRED,BLACK);
			hal_lcd_font_GB2312_string(SET_WORD_X,SET_WORD_Y,SET_WORD_SIZE_C,(uint8_t *)"�ر�",BRRED,BLACK);
			hal_lcd_font_GB2312_string(SET_WORD_X,SET_WORD_Y+SET_WORD_SIZE,SET_WORD_SIZE_C,(uint8_t *)"����",BRRED,BLACK);
			hal_lcd_font_GB2312_string(SET_WORD_X,SET_WORD_Y+2*SET_WORD_SIZE,SET_WORD_SIZE_C,(uint8_t *)"�뿪",BRRED,BLACK);
			lcd_show_cursor(SET_CURSOR_X,SET_CURSOR_Y,key_ctrl.up_down);
			lcd_display.state=LCD_DISPLAY_ASTRONAUT;
		}
	}

}

static void lcd_show_system(void)
{
	if(lcd_display.language_value==0)
	{
		hal_lcd_show_string(SYSTEM_SET_TITLE_X,SYSTEM_SET_TITLE_Y,(uint8_t *)"SYSTEM SET",BRRED,BLACK,TITLE_SIZE,COVER_MODE);
   	hal_lcd_show_string(MAIN_WORD_X,MAIN_WORD_Y,(uint8_t *)"language:",BRRED,BLACK,BELONG_WORD_SIZE,COVER_MODE);
	  hal_lcd_show_string(MAIN_WORD_X,MAIN_WORD_Y+MAIN_WORD_SIZE,(uint8_t *)"about",BRRED,BLACK,BELONG_WORD_SIZE,COVER_MODE);
	  hal_lcd_show_string(MAIN_WORD_X,MAIN_WORD_Y+2*MAIN_WORD_SIZE,(uint8_t *)"exist",BRRED,BLACK,BELONG_WORD_SIZE,COVER_MODE);
	}
	else if(lcd_display.language_value==1)
	{
		hal_lcd_font_GB2312_string(LCD_X2/2-TITLE_SIZE*4/2,SYSTEM_SET_TITLE_Y,TITLE_SIZE,(uint8_t *)"ϵͳ����",BRRED,BLACK);
   	hal_lcd_font_GB2312_string(MAIN_WORD_X,MAIN_WORD_Y,BELONG_WORD_SIZE_C,(uint8_t *)"����:",BRRED,BLACK);
	  hal_lcd_font_GB2312_string(MAIN_WORD_X,MAIN_WORD_Y+MAIN_WORD_SIZE,BELONG_WORD_SIZE_C,(uint8_t *)"����",BRRED,BLACK);
	  hal_lcd_font_GB2312_string(MAIN_WORD_X,MAIN_WORD_Y+2*MAIN_WORD_SIZE,BELONG_WORD_SIZE_C,(uint8_t *)"�뿪",BRRED,BLACK);
	}
	if(lcd_display.language_value==0)      hal_lcd_show_string(BELONG_WORD_X,BELONG_WORD_Y,(uint8_t *)"English",BRRED,BLACK,BELONG_WORD_SIZE,COVER_MODE);
	else if(lcd_display.language_value==1) hal_lcd_font_GB2312_string(BELONG_WORD_X,BELONG_WORD_Y,BELONG_WORD_SIZE_C,(uint8_t *)"��������",BRRED,BLACK);
	lcd_show_cursor(CURSOR_X,CURSOR_Y,key_ctrl.up_down);
	lcd_display.state=LCD_DISPLAY_ASTRONAUT;
}

static void lcd_show_system_set(void)
{
	if(lcd_display.language_value==0)
	{
		if(lcd_display.system_set==1) //set language
		{
			hal_lcd_fill(CURSOR_X,CURSOR_Y,CURSOR_X+CURSOR_SIZE,CURSOR_Y+CURSOR_SIZE*LASER_CTRL_OPTIONS_NUM,BLACK);//clear last cursor
			hal_lcd_draw_rectangle(SET_RECTANGLE_X1,SET_RECTANGLE_Y1,SET_RECTANGLE_X2,SET_RECTANGLE_Y2,BRRED);
			hal_lcd_draw_line(SET_LINE_X1,SET_LINE_Y1,SET_LINE_X2,SET_LINE_Y2,BRRED);
			hal_lcd_show_string(195,37,(uint8_t *)"language",BRRED,BLACK,SET_WORD_SIZE,COVER_MODE);
			hal_lcd_show_string(SET_WORD_X,SET_WORD_Y,(uint8_t *)"English",BRRED,BLACK,SET_WORD_SIZE,COVER_MODE);
			hal_lcd_font_GB2312_string(SET_WORD_X,SET_WORD_Y+SET_WORD_SIZE+2,BELONG_WORD_SIZE_C,(uint8_t *)"��������",BRRED,BLACK);
			hal_lcd_show_string(SET_WORD_X,SET_WORD_Y+2*SET_WORD_SIZE,(uint8_t *)"exist",BRRED,BLACK,SET_WORD_SIZE,COVER_MODE);
			lcd_show_cursor(SET_CURSOR_X,SET_CURSOR_Y,key_ctrl.up_down);
			lcd_display.state=LCD_DISPLAY_ASTRONAUT;
		}
	}
	else if(lcd_display.language_value==1)
	{
		if(lcd_display.system_set==1) //set language
		{
			hal_lcd_fill(CURSOR_X,CURSOR_Y,CURSOR_X+CURSOR_SIZE,CURSOR_Y+CURSOR_SIZE*LASER_CTRL_OPTIONS_NUM,BLACK);//clear last cursor
			hal_lcd_draw_rectangle(SET_RECTANGLE_X1,SET_RECTANGLE_Y1,SET_RECTANGLE_X2,SET_RECTANGLE_Y2,BRRED);
			hal_lcd_draw_line(SET_LINE_X1,SET_LINE_Y1,SET_LINE_X2,SET_LINE_Y2,BRRED);
			hal_lcd_font_GB2312_string(195,37,BELONG_WORD_SIZE_C,(uint8_t *)"����",BRRED,BLACK);
			hal_lcd_show_string(SET_WORD_X,SET_WORD_Y,(uint8_t *)"English",BRRED,BLACK,SET_WORD_SIZE,COVER_MODE);
			hal_lcd_font_GB2312_string(SET_WORD_X,SET_WORD_Y+SET_WORD_SIZE+2,BELONG_WORD_SIZE_C,(uint8_t *)"��������",BRRED,BLACK);
			hal_lcd_font_GB2312_string(SET_WORD_X,SET_WORD_Y+2*SET_WORD_SIZE,BELONG_WORD_SIZE_C,(uint8_t *)"�뿪",BRRED,BLACK);
			lcd_show_cursor(SET_CURSOR_X,SET_CURSOR_Y,key_ctrl.up_down);
			lcd_display.state=LCD_DISPLAY_ASTRONAUT;
		}
	}

}

static void lcd_show_system_about(void)
{
	if(lcd_display.language_value==0)
	{
		if(hal_get_user_data(CHAR_MCU_TYPE)==1)
		{
			hal_lcd_show_string(SHOW_WORD_X,SHOW_WORD_Y,(uint8_t *)"mcu type:stm32f401rct6",BRRED,BLACK,SHOW_WORD_SIZE,COVER_MODE);
			hal_lcd_show_string(SHOW_WORD_X,SHOW_WORD_Y+SHOW_WORD_SIZE,(uint8_t *)"mcu frequency:84M HZ",BRRED,BLACK,SHOW_WORD_SIZE,COVER_MODE);
			hal_lcd_show_string(SHOW_WORD_X,SHOW_WORD_Y+2*SHOW_WORD_SIZE,(uint8_t *)"flash:256kb",BRRED,BLACK,SHOW_WORD_SIZE,COVER_MODE);
			hal_lcd_show_string(SHOW_WORD_X,SHOW_WORD_Y+3*SHOW_WORD_SIZE,(uint8_t *)"ram:48kb",BRRED,BLACK,SHOW_WORD_SIZE,COVER_MODE);
			hal_lcd_show_string(SHOW_WORD_X,SHOW_WORD_Y+4*SHOW_WORD_SIZE,(uint8_t *)"usart baudrate:115200",BRRED,BLACK,SHOW_WORD_SIZE,COVER_MODE);
			hal_lcd_show_string(SHOW_WORD_X,SHOW_WORD_Y+5*SHOW_WORD_SIZE,(uint8_t *)"lcd type:240x280 TFT-LCD",BRRED,BLACK,SHOW_WORD_SIZE,COVER_MODE);
			hal_lcd_show_string(SHOW_WORD_X,SHOW_WORD_Y+6*SHOW_WORD_SIZE,(uint8_t *)"keyboard:double button",BRRED,BLACK,SHOW_WORD_SIZE,COVER_MODE);
			hal_lcd_show_string(SHOW_WORD_X,SHOW_WORD_Y+7*SHOW_WORD_SIZE,(uint8_t *)"hardware version:V1.0.0",BRRED,BLACK,SHOW_WORD_SIZE,COVER_MODE);
			hal_lcd_show_string(SHOW_WORD_X,SHOW_WORD_Y+8*SHOW_WORD_SIZE,(uint8_t *)"software version:V1.0.0",BRRED,BLACK,SHOW_WORD_SIZE,COVER_MODE);
		}
		else if(hal_get_user_data(CHAR_MCU_TYPE)==2)
		{
			hal_lcd_show_string(SHOW_WORD_X,SHOW_WORD_Y,(uint8_t *)"mcu type:gd32f130c8t6",BRRED,BLACK,SHOW_WORD_SIZE,COVER_MODE);
			hal_lcd_show_string(SHOW_WORD_X,SHOW_WORD_Y+SHOW_WORD_SIZE,(uint8_t *)"mcu frequency:72M HZ",BRRED,BLACK,SHOW_WORD_SIZE,COVER_MODE);
			hal_lcd_show_string(SHOW_WORD_X,SHOW_WORD_Y+2*SHOW_WORD_SIZE,(uint8_t *)"flash:64kb",BRRED,BLACK,SHOW_WORD_SIZE,COVER_MODE);
			hal_lcd_show_string(SHOW_WORD_X,SHOW_WORD_Y+3*SHOW_WORD_SIZE,(uint8_t *)"ram:8kb",BRRED,BLACK,SHOW_WORD_SIZE,COVER_MODE);
			hal_lcd_show_string(SHOW_WORD_X,SHOW_WORD_Y+4*SHOW_WORD_SIZE,(uint8_t *)"usart baudrate:115200",BRRED,BLACK,SHOW_WORD_SIZE,COVER_MODE);
			hal_lcd_show_string(SHOW_WORD_X,SHOW_WORD_Y+5*SHOW_WORD_SIZE,(uint8_t *)"lcd type:240x280 TFT-LCD",BRRED,BLACK,SHOW_WORD_SIZE,COVER_MODE);
			hal_lcd_show_string(SHOW_WORD_X,SHOW_WORD_Y+6*SHOW_WORD_SIZE,(uint8_t *)"keyboard:double button",BRRED,BLACK,SHOW_WORD_SIZE,COVER_MODE);
			hal_lcd_show_string(SHOW_WORD_X,SHOW_WORD_Y+7*SHOW_WORD_SIZE,(uint8_t *)"hardware version:V1.0.0",BRRED,BLACK,SHOW_WORD_SIZE,COVER_MODE);
			hal_lcd_show_string(SHOW_WORD_X,SHOW_WORD_Y+8*SHOW_WORD_SIZE,(uint8_t *)"software version:V1.0.0",BRRED,BLACK,SHOW_WORD_SIZE,COVER_MODE);
		}
		
	}
	else if(lcd_display.language_value==1)
	{
		if(hal_get_user_data(CHAR_MCU_TYPE)==1)
		{
			hal_lcd_font_GB2312_string(SHOW_WORD_X,SHOW_WORD_Y,SHOW_WORD_SIZE_C,(uint8_t *)"оƬ�ͺ�",BRRED,BLACK);hal_lcd_show_string(SHOW_WORD_X+4*SHOW_WORD_SIZE_C,SHOW_WORD_Y,(uint8_t *)":stm32f401rct6",BRRED,BLACK,SHOW_WORD_SIZE_C,COVER_MODE);
			hal_lcd_font_GB2312_string(SHOW_WORD_X,SHOW_WORD_Y+SHOW_WORD_SIZE,SHOW_WORD_SIZE_C,(uint8_t *)"����Ƶ��",BRRED,BLACK);hal_lcd_show_string(SHOW_WORD_X+4*SHOW_WORD_SIZE_C,SHOW_WORD_Y+1*SHOW_WORD_SIZE,(uint8_t *)":84M HZ",BRRED,BLACK,SHOW_WORD_SIZE_C,COVER_MODE);
			hal_lcd_font_GB2312_string(SHOW_WORD_X,SHOW_WORD_Y+2*SHOW_WORD_SIZE,SHOW_WORD_SIZE_C,(uint8_t *)"�洢�ռ�",BRRED,BLACK);hal_lcd_show_string(SHOW_WORD_X+4*SHOW_WORD_SIZE_C,SHOW_WORD_Y+2*SHOW_WORD_SIZE,(uint8_t *)":256kb",BRRED,BLACK,SHOW_WORD_SIZE_C,COVER_MODE);
			hal_lcd_font_GB2312_string(SHOW_WORD_X,SHOW_WORD_Y+3*SHOW_WORD_SIZE,SHOW_WORD_SIZE_C,(uint8_t *)"�����ڴ�",BRRED,BLACK);hal_lcd_show_string(SHOW_WORD_X+4*SHOW_WORD_SIZE_C,SHOW_WORD_Y+3*SHOW_WORD_SIZE,(uint8_t *)":64kb",BRRED,BLACK,SHOW_WORD_SIZE_C,COVER_MODE);
		}
		else if(hal_get_user_data(CHAR_MCU_TYPE)==2)
		{
			hal_lcd_font_GB2312_string(SHOW_WORD_X,SHOW_WORD_Y,SHOW_WORD_SIZE_C,(uint8_t *)"оƬ�ͺ�",BRRED,BLACK);hal_lcd_show_string(SHOW_WORD_X+4*SHOW_WORD_SIZE_C,SHOW_WORD_Y,(uint8_t *)":gd32f130c8t6",BRRED,BLACK,SHOW_WORD_SIZE_C,COVER_MODE);
			hal_lcd_font_GB2312_string(SHOW_WORD_X,SHOW_WORD_Y+SHOW_WORD_SIZE,SHOW_WORD_SIZE_C,(uint8_t *)"����Ƶ��",BRRED,BLACK);hal_lcd_show_string(SHOW_WORD_X+4*SHOW_WORD_SIZE_C,SHOW_WORD_Y+1*SHOW_WORD_SIZE,(uint8_t *)":72M HZ",BRRED,BLACK,SHOW_WORD_SIZE_C,COVER_MODE);
			hal_lcd_font_GB2312_string(SHOW_WORD_X,SHOW_WORD_Y+2*SHOW_WORD_SIZE,SHOW_WORD_SIZE_C,(uint8_t *)"�洢�ռ�",BRRED,BLACK);hal_lcd_show_string(SHOW_WORD_X+4*SHOW_WORD_SIZE_C,SHOW_WORD_Y+2*SHOW_WORD_SIZE,(uint8_t *)":64kb",BRRED,BLACK,SHOW_WORD_SIZE_C,COVER_MODE);
			hal_lcd_font_GB2312_string(SHOW_WORD_X,SHOW_WORD_Y+3*SHOW_WORD_SIZE,SHOW_WORD_SIZE_C,(uint8_t *)"�����ڴ�",BRRED,BLACK);hal_lcd_show_string(SHOW_WORD_X+4*SHOW_WORD_SIZE_C,SHOW_WORD_Y+3*SHOW_WORD_SIZE,(uint8_t *)":8kb",BRRED,BLACK,SHOW_WORD_SIZE_C,COVER_MODE);
		}
			hal_lcd_font_GB2312_string(SHOW_WORD_X,SHOW_WORD_Y+4*SHOW_WORD_SIZE,SHOW_WORD_SIZE_C,(uint8_t *)"���ڲ�����",BRRED,BLACK);hal_lcd_show_string(SHOW_WORD_X+5*SHOW_WORD_SIZE_C,SHOW_WORD_Y+4*SHOW_WORD_SIZE,(uint8_t *)":115200",BRRED,BLACK,SHOW_WORD_SIZE_C,COVER_MODE);
			hal_lcd_font_GB2312_string(SHOW_WORD_X,SHOW_WORD_Y+5*SHOW_WORD_SIZE,SHOW_WORD_SIZE_C,(uint8_t *)"��ʾ��",BRRED,BLACK);hal_lcd_show_string(SHOW_WORD_X+3*SHOW_WORD_SIZE_C,SHOW_WORD_Y+5*SHOW_WORD_SIZE,(uint8_t *)":240x280 TFT-LCD",BRRED,BLACK,SHOW_WORD_SIZE_C,COVER_MODE);
			hal_lcd_font_GB2312_string(SHOW_WORD_X,SHOW_WORD_Y+6*SHOW_WORD_SIZE,SHOW_WORD_SIZE_C,(uint8_t *)"����",BRRED,BLACK);hal_lcd_show_string(SHOW_WORD_X+2*SHOW_WORD_SIZE_C,SHOW_WORD_Y+6*SHOW_WORD_SIZE,(uint8_t *)":",BRRED,BLACK,SHOW_WORD_SIZE_C,COVER_MODE);hal_lcd_font_GB2312_string(SHOW_WORD_X+3*SHOW_WORD_SIZE_C,SHOW_WORD_Y+6*SHOW_WORD_SIZE,SHOW_WORD_SIZE_C,(uint8_t *)"˫����",BRRED,BLACK);
			hal_lcd_font_GB2312_string(SHOW_WORD_X,SHOW_WORD_Y+7*SHOW_WORD_SIZE,SHOW_WORD_SIZE_C,(uint8_t *)"Ӳ���汾��",BRRED,BLACK);hal_lcd_show_string(SHOW_WORD_X+5*SHOW_WORD_SIZE_C,SHOW_WORD_Y+7*SHOW_WORD_SIZE,(uint8_t *)":V1.0.0",BRRED,BLACK,SHOW_WORD_SIZE_C,COVER_MODE);
			hal_lcd_font_GB2312_string(SHOW_WORD_X,SHOW_WORD_Y+8*SHOW_WORD_SIZE,SHOW_WORD_SIZE_C,(uint8_t *)"����汾��",BRRED,BLACK);hal_lcd_show_string(SHOW_WORD_X+5*SHOW_WORD_SIZE_C,SHOW_WORD_Y+8*SHOW_WORD_SIZE,(uint8_t *)":V1.0.0",BRRED,BLACK,SHOW_WORD_SIZE_C,COVER_MODE);
	}
	lcd_display.state=LCD_DISPLAY_ASTRONAUT;
}

static void lcd_show_stopwatch(void)
{
	hal_get_stopwatch_timebuff(lcd_display.stopwatch_timebuff);
	hal_lcd_show_string(STOPWATCH_X,STOPWATCH_Y,lcd_display.stopwatch_timebuff,BRRED,BLACK,STOPWATCH_SIZE,COVER_MODE);
	if(lcd_display.language_value==0)
	{
		if(lcd_display.stopwatch_ctrl==0)hal_lcd_show_string(STOPWATCH_WORD_X,STOPWATCH_WORD_Y,(uint8_t *)"begin",BRRED,BLACK,SHOW_WORD_SIZE,COVER_MODE);
		else if(lcd_display.stopwatch_ctrl==1)hal_lcd_show_string(STOPWATCH_WORD_X,STOPWATCH_WORD_Y,(uint8_t *)"stop",BRRED,BLACK,SHOW_WORD_SIZE,COVER_MODE);
		else if(lcd_display.stopwatch_ctrl==2)hal_lcd_show_string(STOPWATCH_WORD_X,STOPWATCH_WORD_Y,(uint8_t *)"continue",BRRED,BLACK,SHOW_WORD_SIZE,COVER_MODE);

		hal_lcd_show_string(STOPWATCH_WORD_X+90,STOPWATCH_WORD_Y,(uint8_t *)"clear",BRRED,BLACK,SHOW_WORD_SIZE,COVER_MODE);
		hal_lcd_show_string(STOPWATCH_WORD_X+190,STOPWATCH_WORD_Y,(uint8_t *)"exist",BRRED,BLACK,SHOW_WORD_SIZE,COVER_MODE);
	}
	else if(lcd_display.language_value==1)
	{
		if(lcd_display.stopwatch_ctrl==0)	    hal_lcd_font_GB2312_string(STOPWATCH_WORD_X,STOPWATCH_WORD_Y,SHOW_WORD_SIZE,(uint8_t *)"��ʼ",BRRED,BLACK);
		else if(lcd_display.stopwatch_ctrl==1)hal_lcd_font_GB2312_string(STOPWATCH_WORD_X,STOPWATCH_WORD_Y,SHOW_WORD_SIZE,(uint8_t *)"ֹͣ",BRRED,BLACK);
		else if(lcd_display.stopwatch_ctrl==2)hal_lcd_font_GB2312_string(STOPWATCH_WORD_X,STOPWATCH_WORD_Y,SHOW_WORD_SIZE,(uint8_t *)"����",BRRED,BLACK);

		hal_lcd_font_GB2312_string(STOPWATCH_WORD_X+90,STOPWATCH_WORD_Y,SHOW_WORD_SIZE,(uint8_t *)"���",BRRED,BLACK);
		hal_lcd_font_GB2312_string(STOPWATCH_WORD_X+190,STOPWATCH_WORD_Y,SHOW_WORD_SIZE,(uint8_t *)"�뿪",BRRED,BLACK);
	}
	lcd_show_cursor(SET_CURSOR_X,SET_CURSOR_Y,key_ctrl.up_down);
}

static void lcd_show_ultrasound(void)
{
	hal_echo_lcd_get_distance(lcd_display.ultrasound_buff);
	
	hal_lcd_show_string(STOPWATCH_X,STOPWATCH_Y,lcd_display.ultrasound_buff,BRRED,BLACK,STOPWATCH_SIZE,COVER_MODE);
}
