#ifndef __ECHO_H
#define __ECHO_H

#include "gd32f1x0.h"
#include "string.h"

#define ECHO_RCC   RCU_GPIOB
#define ECHO_PORT  GPIOB
#define ECHO_PIN   GPIO_PIN_8
#define TRIG_PIN   GPIO_PIN_5

#define SOUND_SPEED  (340)

void bsp_echo_init(void);
void bsp_echo_get_time(void);
void bsp_echo_lcd_get_distance(uint8_t *data);
#endif 


