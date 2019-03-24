#include "project_confi.h"
#include "QDTFT_demo.h"


int main(void)
{
//	uart_init(115200);
    
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(84);
     
    
    function_config();
 	TIM3_Int_Init(100-1,420-1);	//定时器时钟84M，分频系数8400，所以84M/8400=10Khz的计数频率，计数5000次为500ms 
//-----------------------------------
    
	bsp.lcd.init();
    bsp.adc.init();
    bsp.led.init();
    bsp.key.init();
    bsp.usb.usbvcp_init(2,0);
//-----------------------------------  
//-----------------------------------
    bsp.led.led_off(LEDR_GPIO_PORT,LEDG_PIN);
    bsp.led.led_off(LEDG_GPIO_PORT,LEDG_PIN);
//-----------------------------------  
//    demo_create();
    
    main_task();
//-----------------------------------
    while(1)
      {
          
          key_value();
          
    #ifdef USE_FFT
         FFT();
    #endif
        lv_tick_inc(1);		
		lv_task_handler();
        datatransfer();
      }
}



