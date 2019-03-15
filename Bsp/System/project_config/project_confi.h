#ifndef __PROJECT_CONFI_h_
#define __PROJECT_CONFI_h_

#include "lcd.h"
#include "bsp_adc.h"
#include "Driver_USBVCP.h"

typedef struct
{
	lcd_func_typedef lcd;
	adc_func_typedef adc;
	usb_func_typedef usb;
	
}bsp_typedef;

void function_config(void);

extern bsp_typedef bsp;
#endif

