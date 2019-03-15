#include "stm32f4xx.h"
#include "project_confi.h"

bsp_typedef bsp;

void lcd_func_init(void)
{
    bsp.lcd.init = &LCD_Init;
    bsp.lcd.dispframe = &DispFrame;
    bsp.lcd.dispband = &DispBand;
    bsp.lcd.writecomm = &WriteComm;
    bsp.lcd.writedata = &WriteData;
    bsp.lcd.dispcolor = &DispColor;
    bsp.lcd.lcd_drawpixel = &LCD_DrawPixel;
    bsp.lcd.writedispdata = &WriteDispData;
    bsp.lcd.blockwrite = &BlockWrite;
    bsp.lcd.lcd_showchar = &LCD_ShowChar;
    bsp.lcd.lcd_shownum = &LCD_ShowNum;
    bsp.lcd.lcd_showstring = &LCD_ShowString;
    bsp.lcd.lcd_showxnum = &LCD_ShowxNum;
    bsp.lcd.lcd_showfont = &LCD_ShowFont;
}

void adc_func_init()
{
    bsp.adc.init=&Rheostat_Init;
	bsp.adc.adc_softwarestartconv=&ADC_SoftwareStartConv;
}
void usb_func_init()
{
	bsp.usb.usbvcp_init = &usbVCP_Init;
	bsp.usb.usbvcp_sendbyte=&usbVCP_SendByte;
	bsp.usb.usbvcp_sendbuffer = &usbVCP_SendBuffer;
	bsp.usb.usbvcp_sendstring = &usbVCP_SendString;
	bsp.usb.usbvcp_printf = &usbVCP_Printf;
}
void function_config(void)
{
	lcd_func_init();
}
