#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"
#include "lcd.h"
#include "bsp_adc.h"
#include "Driver_USBVCP.h"
#include "project_confi.h"

int main(void)
{
	u32 t=0;
	uart_init(115200);
	delay_init(84);
    
    function_config();
////-----------------------------------
	bsp.lcd.init();
//-----------------------------------    
    usbVCP_Init(2,0);
//-----------------------------------
    delay_ms(200);
    bsp.lcd.dispcolor(white);
    bsp.lcd.lcd_showxnum(0,10,12345,8,5,blue);
    bsp.lcd.lcd_showxnum(150,30,12345,8,5,blue);
    bsp.lcd.lcd_showstring(20,40,"ASasd",8,black);
    while(1)
      {
          usbVCP_SendString("asrtr");
          delay_ms(20);
      }
}



