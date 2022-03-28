#ifndef __TASK_KEY_H
#define __TASK_KEY_H

#include "hal_key.h"

typedef  struct
{
	uint8_t up_down;
}key_ctrl_t;

extern key_ctrl_t key_ctrl;

void task_key_scan(void);
#endif 
