#include "project_confi.h"
#include "QDTFT_demo.h"


int main(void)
{
//	uart_init(115200);
	delay_init(84);
    
    
    function_config();
//-----------------------------------
    
	bsp.lcd.init();
//    bsp.usb.usbvcp_init(2,0);
    bsp.adc.init();
    bsp.led.init();
    bsp.key.init();
//-----------------------------------  
//-----------------------------------
    bsp.lcd.clear(WHITE);
    bsp.gui.drawfont_GBK24(16,2,BLUE,WHITE,"test");
    bsp.led.led_off(LEDR_GPIO_PORT,LEDR_PIN);
    bsp.led.led_off(LEDG_GPIO_PORT,LEDG_PIN);
    bsp.led.led_off(LEDB_GPIO_PORT,LEDB_PIN);
    while(1)
      {
          if(bsp.key.get_key(KEY1_GPIO_PORT,KEY1_PIN)==0)
          {
            bsp.led.led_on(LEDR_GPIO_PORT,LEDR_PIN);
          }
          bsp.led.led_on(LEDG_GPIO_PORT,LEDG_PIN);
          bsp.led.led_on(LEDB_GPIO_PORT,LEDB_PIN);
          bsp.usb.usbvcp_sendstring("asrtr");
          delay_ms(20);
      }
}



