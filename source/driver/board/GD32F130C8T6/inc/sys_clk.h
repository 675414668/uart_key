#ifndef __SYS_CLK_H
#define __SYS_CLK_H

#include "gd32f1x0.h"
#include "string.h"

#define SYSCLK_FREQUENCY (72000000)

uint8_t bsp_sys_clk_init(void);
uint32_t bsp_get_clock_frequency(uint32_t clk);
#endif 
