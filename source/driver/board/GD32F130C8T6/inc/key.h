#ifndef __KEY_H
#define __KEY_H

#include "gd32f1x0.h"
#include "string.h"

enum 
{
	KEY_NULL=0,
	KEY1_S,
	KEY1_L,
	KEY2_S,
	KEY2_L,
};

#define KEY_RCC   RCU_GPIOB
#define KEY_PORT  GPIOB
#define KEY1_PIN  GPIO_PIN_8
#define KEY2_PIN  GPIO_PIN_9

#define KEY_TIM                TIMER2
#define KEY_TIM_RCC            RCU_TIMER2
#define KEY_TIM_PERIOD         (100)
#define KEY_TIM_PRESCALER      (72-1)//TIM_OUT = KEY_TIM_PERIOD*(KEY_TIM_PRESCALER+1)/84 =100us
#define KEY_TIM_IRQN           TIMER2_IRQn
#define KEY_TIM_IRQHANDLER     TIMER2_IRQHandler

#define KEY_S_TIM  (1000)
#define KEY_L_TIM  (15000)


void bsp_key_init(void);
uint8_t bsp_get_key_press(void);
void bsp_set_key_press(uint8_t state);
#endif 


