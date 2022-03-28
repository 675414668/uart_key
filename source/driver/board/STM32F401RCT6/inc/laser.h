#ifndef __LASER_H
#define __LASER_H

#include "stm32f4xx.h"
#include "stdio.h"


#define LASER    (1)
#define LASER_ON  (1)
#define LASER_OFF (0)
void bsp_laser_init(void);
uint8_t bsp_laser_control(uint8_t laser,uint8_t state);
#endif 
