#include "stm32f4xx.h"
#include "project_confi.h"
 
arm_cfft_radix4_instance_f32 scfft;
adc_value simple;
bsp_typedef bsp;

void lcd_func_init(void)
{
    bsp.lcd.init = &Lcd_Init;
    bsp.lcd.clear = &Lcd_Clear;
    bsp.lcd.setxy = &Lcd_SetXY;
    bsp.lcd.writedata = &Lcd_WriteData_16Bit;
    bsp.lcd.drawpixel = &Lcd_DrawPoint;
    bsp.lcd.blockwrite = &Lcd_SetRegion;
    bsp.lcd.colorblock = &Lcd_Colorblock;
}

void gui_func_init()
{
    bsp.gui.brg2rgb = &LCD_BGR2RGB;
    bsp.gui.circle = &Gui_Circle;
    bsp.gui.drawline = &Gui_DrawLine;
    bsp.gui.box = &Gui_box;
    bsp.gui.box2 = &Gui_box2;
    bsp.gui.displaybuttondown = &DisplayButtonDown;
    bsp.gui.displaybuttonup = &DisplayButtonUp;
    bsp.gui.drawfont_GBK16 = &Gui_DrawFont_GBK16;
    bsp.gui.drawfont_GBK24 = &Gui_DrawFont_GBK24;
    bsp.gui.drawfont_num32 = &Gui_DrawFont_Num32;
}
void adc_func_init()
{
    bsp.adc.init=&Rheostat_Init;
	bsp.adc.adc_softwarestartconv=&ADC_SoftwareStartConv;
    bsp.adc.get_adc = &Get_Adc;
    simple.value_adc0 = &ADC_ConvertedValue[0];
    simple.value_adc1 = &ADC_ConvertedValue[1];
    simple.value_adc2 = &ADC_ConvertedValue[2];
    simple.value_adc3 = &ADC_ConvertedValue[3];
}

void usb_func_init()
{
	bsp.usb.usbvcp_init = &usbVCP_Init;
	bsp.usb.usbvcp_sendbyte=&usbVCP_SendByte;
	bsp.usb.usbvcp_sendbuffer = &usbVCP_SendBuffer;
	bsp.usb.usbvcp_sendstring = &usbVCP_SendString;
	bsp.usb.usbvcp_printf = &usbVCP_Printf;
}

void key_func_init()
{
    bsp.key.init = &Key_GPIO_Config;
    bsp.key.get_key = &Key_Scan;
    key_vlaues.key1 = 2;
    key_vlaues.key2 = 2;
    key_vlaues.key3 = 2;
    key_vlaues.key4 = 2;
}

void led_func_init()
{
    bsp.led.init = &LED_GPIO_Config;
    bsp.led.led_on  = &GPIO_ResetBits;
    bsp.led.led_off = &GPIO_SetBits;
}
void nrf_func_init()
{
    bsp.nrf.init = &init_nrf24l01_io;
    bsp.nrf.rx_mode = &NRF_RX_Mode;
    bsp.nrf.tx_mode = &ifnnrf_tx_mode;
    bsp.nrf.tx_data = &NRF_tx_Dat;
    bsp.nrf.rx_data = &NRF_Rx_Dat;
    bsp.nrf.check = &NRF_Check;
}
void function_config(void)
{
    
	lcd_func_init();
    usb_func_init();
    adc_func_init();
    led_func_init();
    key_func_init();
    nrf_func_init();
    gui_func_init();
	lv_init();
	tft_init();
  
    #ifdef USE_FFT  
        arm_cfft_radix4_init_f32(&scfft,128,0,1);
    #endif
}
