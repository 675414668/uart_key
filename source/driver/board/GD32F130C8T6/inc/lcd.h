#ifndef __LCD_H
#define __LCD_H

#include "gd32f1x0.h"
#include "string.h"

#define LCD_CONTROL_RCU  RCU_GPIOA
#define LCD_CONTROL_PORT GPIOA
#define LCD_CONTROL_RES  GPIO_PIN_0
#define LCD_CONTROL_DC   GPIO_PIN_1
#define LCD_CONTROL_BLK  GPIO_PIN_2
#define LCD_CONTROL_CS1  GPIO_PIN_3
#define LCD_CONTROL_CS2  GPIO_PIN_4
#define LCD_CONTROL_SCK  GPIO_PIN_5
#define LCD_CONTROL_MISO GPIO_PIN_6
#define LCD_CONTROL_SDA  GPIO_PIN_7




#define USE_HORIZONTAL 2  //设置横屏或者竖屏显示 0或1为竖屏 2或3为横屏


#if USE_HORIZONTAL==0||USE_HORIZONTAL==1
#define LCD_W 135
#define LCD_H 240

#else
#define LCD_W 240
#define LCD_H 135
#endif


#define LCD_SCK_RESET()   gpio_bit_reset(LCD_CONTROL_PORT,LCD_CONTROL_SCK)//SCK
#define LCD_SCK_SET()     gpio_bit_set(LCD_CONTROL_PORT,LCD_CONTROL_SCK)

#define LCD_SDA_RESET()   gpio_bit_reset(LCD_CONTROL_PORT,LCD_CONTROL_SDA)//SDA
#define LCD_SDA_SET()     gpio_bit_set(LCD_CONTROL_PORT,LCD_CONTROL_SDA)

#define LCD_RES_RESET()   gpio_bit_reset(LCD_CONTROL_PORT,LCD_CONTROL_RES)//RES
#define LCD_RES_SET()     gpio_bit_set(LCD_CONTROL_PORT,LCD_CONTROL_RES)

#define LCD_DC_RESET()    gpio_bit_reset(LCD_CONTROL_PORT,LCD_CONTROL_DC)//DC
#define LCD_DC_SET()      gpio_bit_set(LCD_CONTROL_PORT,LCD_CONTROL_DC)

#define LCD_BLK_RESET()   gpio_bit_reset(LCD_CONTROL_PORT,LCD_CONTROL_BLK)//BLK
#define LCD_BLK_SET()     gpio_bit_set(LCD_CONTROL_PORT,LCD_CONTROL_BLK)

#define LCD_MISO_READ     gpio_input_bit_get(LCD_CONTROL_PORT,LCD_CONTROL_MISO)//MISO  读取字库数据引脚

#define LCD_CS1_RESET()   gpio_bit_reset(LCD_CONTROL_PORT,LCD_CONTROL_CS1)//CS1
#define LCD_CS1_SET()     gpio_bit_set(LCD_CONTROL_PORT,LCD_CONTROL_CS1)

#define LCD_CS2_RESET()   gpio_bit_reset(LCD_CONTROL_PORT,LCD_CONTROL_CS2)//CS2 字库片选
#define LCD_CS2_SET()     gpio_bit_set(LCD_CONTROL_PORT,LCD_CONTROL_CS2)	

#define ASTRONAUT_IMAGE_NUM    (14)
#define ASTRONAUT_IMAGE_SPEED  (200)
#define ASTRONAUT_IMAGE_TIM    (ASTRONAUT_IMAGE_NUM*ASTRONAUT_IMAGE_SPEED)

#define WAITING_NUM    (3)
#define WAITING_SPEED  (10000)
#define WAITING_TIM    (WAITING_NUM*WAITING_SPEED)

void bsp_lcd_init(void);
void bsp_lcd_gpio_init(void);//初始化GPIO
void bsp_lcd_write_bus(uint8_t dat);//模拟SPI时序
void bsp_lcd_write_8bit(uint8_t dat);//写入一个字节
void bsp_lcd_write_16bit(uint16_t dat);//写入两个字节
void bsp_lcd_write_reg(uint8_t dat);//写入一个指令
void bsp_lcd_set_addr(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);//设置坐标函数

uint8_t bsp_lcd_get_astronaut_image_num(void);
uint8_t bsp_lcd_get_waiting_time(void);
void bsp_get_stopwatch_timebuff(uint8_t *data);
void bsp_stopwatch_timebuff_clear(void);
void bsp_stopwatch_ctrl(uint8_t state);
void lcd_astronaut_image_change(void);
void lcd_waiting_time_change(void);
void bsp_timer_stopwatch(void);
#endif 


