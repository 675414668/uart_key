#include "hal_echo.h"

	
void hal_echo_init(void)
{
	bsp_echo_init();
}

void hal_echo_lcd_get_distance(uint8_t *data)
{
	bsp_echo_lcd_get_distance(data);
}

