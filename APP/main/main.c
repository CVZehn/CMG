#include "project_confi.h"
#include "QDTFT_demo.h"


int main(void)
{
//	uart_init(115200);
    
	delay_init(84);
    
    
    function_config();
//-----------------------------------
    
	bsp.lcd.init();
    bsp.adc.init();
    bsp.led.init();
    bsp.key.init();
    bsp.usb.usbvcp_init(2,0);
//-----------------------------------  
//-----------------------------------
    bsp.led.led_off(LEDR_GPIO_PORT,LEDR_PIN);
    bsp.led.led_off(LEDG_GPIO_PORT,LEDG_PIN);
    bsp.led.led_off(LEDB_GPIO_PORT,LEDB_PIN);
//-----------------------------------  
//    demo_create();
    
    main_task();
//-----------------------------------
    while(1)
      {
          key_value();
          if(key_vlaues.key1==0)
          {
              display_break();
          }
          else if(key_vlaues.key1==1)
          {
            display_connect();
          }
        bsp.usb.usbvcp_printf("1:%d\r\n",key_vlaues.key1);
//          bsp.usb.usbvcp_printf("2:%d\r\n",*simple.value_adc1);
//          bsp.usb.usbvcp_printf("3:%d\r\n",*simple.value_adc2);
//          bsp.usb.usbvcp_printf("4:%d\r\n",*simple.value_adc3);
        lv_tick_inc(1);		
		lv_task_handler();
        datatransfer();
//          delay_ms(300);
      }
}



