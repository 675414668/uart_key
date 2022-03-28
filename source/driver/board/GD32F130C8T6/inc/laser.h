#ifndef __LASER_H
#define __LASER_H

#include "gd32f1x0.h"
#include "stdio.h"

#define LASER_RCC  RCU_GPIOA
#define LASER_PORT GPIOA
#define LASER_PIN  GPIO_PIN_9


#define LASER    (1)
#define LASER_ON  (1)
#define LASER_OFF (0)
void bsp_laser_init(void);
uint8_t bsp_laser_control(uint8_t laser,uint8_t state);
#endif 
