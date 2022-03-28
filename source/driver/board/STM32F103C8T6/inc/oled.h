#ifndef __OLED_H
#define __OLED_H

#include "stm32f10x.h"
#include "string.h"
#include "osal.h"

#define OLED_MODE 				0//0:4�ߴ���ģʽ 1:����8080ģʽ
#define SIZE 					    16
#define XLevelL						0x00
#define XLevelH						0x10
#define Max_Column				128
#define Max_Row						64
#define	Brightness				0xFF 
#define X_WIDTH 					128
#define Y_WIDTH 					64	    

#define OLED_CMD  0				//д����
#define OLED_DATA 1				//д����

#define  OLED_GPIO_PORT   GPIOB		
#define  OLED_D0_PORT     GPIOB			
#define  OLED_D1_PORT     GPIOB							
#define  OLED_RES_PORT    GPIOB		
#define  OLED_DC_PORT     GPIOB				

#define  OLED_D0_Pin      GPIO_Pin_5				/* D0 */
#define  OLED_D1_Pin      GPIO_Pin_6				/* D1 */
#define  OLED_RES_Pin     GPIO_Pin_7				/* RES */
#define  OLED_DC_Pin     	GPIO_Pin_8				/* DC */

void bsp_oled_init(void);
void bsp_oled_write_byte(uint8_t dat,uint8_t cmd);
void bsp_oled_set_pos(unsigned char x, unsigned char y) ;//��������,������,������Ļ�Ǻ�ɫ��!��û����һ��
void bsp_oled_display_on(void);// ����OLED��ʾ
void bsp_oled_display_off(void);// �ر�OLED��ʾ   
void bsp_oled_clear(void);//��������,������,������Ļ�Ǻ�ɫ��!��û����һ��
void bsp_oled_show_char(uint8_t x,uint8_t y,uint8_t chr);//��ָ��λ����ʾһ���ַ�,���������ַ�x:0~127   y:0~63   mode:0,������ʾ  1,������ʾ	 size:ѡ������ 16/12 
void bsp_oled_show_char_adjust(uint8_t size,uint8_t x,uint8_t y,uint8_t chr);//��ָ��λ����ʾһ���ַ�,�ɵ����ַ���С x:0~127   y:0~63   mode:0,������ʾ  1,������ʾ	 size:ѡ������ 16/12 
uint32_t bsp_oled_pow(uint8_t m,uint8_t n);//m^n����
void bsp_oled_show_num(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size);//��ʾ2������
void bsp_oled_show_string(uint8_t x,uint8_t y,char *chr);

#endif 
