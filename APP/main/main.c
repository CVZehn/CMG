#include "project_confi.h"
#include "QDTFT_demo.h"


int main(void)
{
//	uart_init(115200);
    
    u8 ii[30]={'1','2','3'};
    u8 k;
    u16 j;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(84);
     
    
    function_config();
//-----------------------------------
    
	bsp.lcd.init();
    bsp.adc.init();
    bsp.led.init();
    bsp.key.init();
    bsp.nrf.init();
    bsp.usb.usbvcp_init(2,0);
 	TIM3_Int_Init(1000-1,420-1);	//定时器时钟84M，分频系数8400，所以84M/8400=10Khz的计数频率，计数5000次为500ms 
//-----------------------------------  
    bsp.led.led_off(LEDG_GPIO_PORT,LEDG_PIN);
    bsp.led.led_off(LEDR_GPIO_PORT,LEDR_PIN);
    bsp.led.led_off(LEDB_GPIO_PORT,LEDB_PIN);
//-----------------------------------
    	while(!bsp.nrf.check())
	{
        bsp.led.led_off(LEDR_GPIO_PORT,LEDR_PIN);
		delay_ms(500);
        bsp.led.led_on(LEDR_GPIO_PORT,LEDR_PIN);
 		delay_ms(500);
	}
    
//        bsp.led.led_on(LEDG_GPIO_PORT,LEDG_PIN);
//-----------------------------------  
    main_task();
    bsp.nrf.tx_mode();
//-----------------------------------
    while(1)
      {
        key_value();
        lv_tick_inc(1);		
		lv_task_handler();
        datatransfer();
          k=bsp.nrf.tx_data(ii);
       j++;
//       if(j>=6000)
//       {
            if(k ==TX_DS)
            {
                bsp.led.led_on(LEDR_GPIO_PORT,LEDB_PIN);
            }
            
            if( k==MAX_RT)
            {
                bsp.led.led_on(LEDR_GPIO_PORT,LEDR_PIN);
            }
            if(k==0)
            {
                bsp.led.led_on(LEDR_GPIO_PORT,LEDG_PIN);
            }
            j=0;
           
//       }
       delay_ms(200);
        bsp.led.led_off(LEDG_GPIO_PORT,LEDG_PIN);
        bsp.led.led_off(LEDG_GPIO_PORT,LEDB_PIN);
        bsp.led.led_off(LEDR_GPIO_PORT,LEDR_PIN);
       delay_ms(200);
      }
}



