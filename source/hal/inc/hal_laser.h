#ifndef __HAL_LASER_H
#define __HAL_LASER_H

#include "laser.h"

void hal_laser_init(void);
uint8_t hal_laser_control(uint8_t laser,uint8_t state);
#endif 


