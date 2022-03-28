#ifndef __HAL_LCD_API_H
#define __HAL_LCD_API_H

#include "lcd.h"

//������ɫ
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE           	 0x001F  
#define BRED             0XF81F
#define GRED 			       0XFFE0
#define GBLUE			       0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			     0XBC40 //��ɫ
#define BRRED 			     0XFC07 //�غ�ɫ
#define GRAY  			     0X8430 //��ɫ
#define DARKBLUE      	 0X01CF	//����ɫ
#define LIGHTBLUE      	 0X7D7C	//ǳ��ɫ  
#define GRAYBLUE       	 0X5458 //����ɫ
#define LIGHTGREEN     	 0X841F //ǳ��ɫ
#define LGRAY 			     0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ
#define LGRAYBLUE        0XA651 //ǳ����ɫ(�м����ɫ)
#define LBBLUE           0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)

void hal_lcd_fill(uint16_t xsta,uint16_t ysta,uint16_t xend,uint16_t yend,uint16_t color);//ָ�����������ɫ
void hal_lcd_draw_fill(uint16_t color);
void hal_lcd_clear(uint16_t x,uint16_t y,uint16_t color);
void hal_lcd_draw_point(uint16_t x,uint16_t y,uint16_t color);//��ָ��λ�û�һ����
void hal_lcd_draw_line(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t color);//��ָ��λ�û�һ����
void hal_lcd_draw_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color);//��ָ��λ�û�һ������
void hal_lcd_draw_circle(uint16_t x0,uint16_t y0,uint8_t r,uint16_t color);//��ָ��λ�û�һ��Բ

void hal_lcd_show_Chinese(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);//��ʾ���ִ�
void hal_lcd_show_Chinese12x12(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);//��ʾ����12x12����
void hal_lcd_show_Chinese16x16(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);//��ʾ����16x16����
void hal_lcd_show_Chinese24x24(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);//��ʾ����24x24����
void hal_lcd_show_Chinese32x32(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);//��ʾ����32x32����

void hal_lcd_show_char(uint16_t x,uint16_t y,uint8_t num,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);//��ʾһ���ַ�
void hal_lcd_show_string(uint16_t x,uint16_t y,const uint8_t *p,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);//��ʾ�ַ���
uint32_t hal_lcd_show_num(uint8_t m,uint8_t n);//����
void hal_lcd_show_int_num(uint16_t x,uint16_t y,uint16_t num,uint8_t len,uint16_t fc,uint16_t bc,uint8_t sizey);//��ʾ��������
void hal_lcd_show_float_num(uint16_t x,uint16_t y,float num,uint8_t len,uint16_t fc,uint16_t bc,uint8_t sizey);//��ʾ��λС������

void hal_lcd_show_picture(uint16_t x,uint16_t y,uint16_t length,uint16_t width,const uint8_t pic[]);//��ʾͼƬ

#endif





