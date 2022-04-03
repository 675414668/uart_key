#include "task_key.h"
#include "task_lcd.h"

key_ctrl_t key_ctrl;

static void key_null(void);
static void key1_short(void);
static void key1_long(void);
static void key2_short(void);
static void key2_long(void);
static void key_default(void);

void task_key_scan(void)
{
	switch(hal_get_key_press())
	{
		case KEY_NULL:{ key_null();      break;};
		case KEY1_S:  { key1_short();    break;};
		case KEY1_L:  { key1_long();     break;};
		case KEY2_S:  { key2_short();    break;};
		case KEY2_L:  { key2_long();     break;};
		default :     { key_default();   break;};
	}
}

static void key_null(void)
{
	
}

static void key1_short(void)
{

}

static void key1_long(void)
{

}

static void key2_short(void)
{

}

static void key2_long(void)
{

}

static void key_default(void)
{
	
}

