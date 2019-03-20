#ifndef __PROJECT_CONFI_h_
#define __PROJECT_CONFI_h_

#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"
#include "Lcd_Driver.h"
#include "bsp_adc.h"
#include "Driver_USBVCP.h"
#include "bsp_key.h" 
#include "bsp_led.h"   
#include "gui.h"   

typedef struct
{
	lcd_func_typedef lcd;
	adc_func_typedef adc;
	usb_func_typedef usb;
    key_func_typedef key;
    led_func_typedef led;
    gui_func_typedef gui;
	
}bsp_typedef;


typedef struct
{
    u16 value_adc0;
    u16 value_adc1;
    u16 value_adc2;
    u16 value_adc3;
}adc_value;



void function_config(void);

extern adc_value simple;
extern bsp_typedef bsp;
#endif

