#include "task_usart.h"

static void task_usart_callback(void);

void task_usart_init(void)
{
hal_usart_callback(task_usart_callback);
}

static void task_usart_callback(void)
{
	
}

