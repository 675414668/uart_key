#ifndef __SYS_CLK_H
#define __SYS_CLK_H

#include "stm32f4xx.h"
#include "string.h"

 /*   
	HSE_VALUE=8M
	PLL_VCO input clock =( (HSE_VALUE or HSI_VALUE / PLL_M))  ����ֵΪ1-2M
	PLL_VCO output clock = (PLL_VCO input clock) * PLL_N
	System Clock=84M = (PLL_VCO output clock)/PLL_P 
	��PLL_M=4����PLL_VCO input clock=2M
	��PLL_N=168����PLL_VCO output clock=336M
	��PLL_P=4����System Clock=84M
	*/
#define	SYSCLK_FREQUENCY  (1)
#define	HCLK_FREQUENCY    (2)
#define	PCLK1_FREQUENCY   (3)
#define	PCLK2_FREQUENCY   (4)

#define HCLK_CONFIG    RCC_SYSCLK_Div1
#define PCLK1_CONFIG   RCC_HCLK_Div1
#define PCLK2_CONFIG   RCC_HCLK_Div1

#define	SYSCLK_TARGET_FRE  (84000000)
#define	HCLK_TARGET_FRE    (84000000)
#define	PCLK1_TARGET_FRE   (84000000)
#define	PCLK2_TARGET_FRE   (84000000)

#define PLL_M  (8)    //8M/8=1M
#define PLL_N  (336)  //1M*336=336M
#define PLL_P  (4)    //336M/4=82M
#define PLL_Q  (7)    //����usb��sd����д�ȹ��� 336M/7=48m

uint8_t bsp_sys_clk_init(void);
uint32_t bsp_get_clock_frequency(uint32_t clk);
#endif 
