#ifndef __BSP_ADC_H
#define	__BSP_ADC_H

#include "stm32f4xx.h"

#define RHEOSTAT_NOFCHANEL      4

/*=====================通道1 IO======================*/

#define RHEOSTAT_ADC_GPIO_PORT1    GPIOA
#define RHEOSTAT_ADC_GPIO_PIN1     GPIO_Pin_4
#define RHEOSTAT_ADC_GPIO_CLK1     RCC_AHB1Periph_GPIOA
#define RHEOSTAT_ADC_CHANNEL1      ADC_Channel_4
/*=====================通道2 IO ======================*/

#define RHEOSTAT_ADC_GPIO_PORT2    GPIOA
#define RHEOSTAT_ADC_GPIO_PIN2     GPIO_Pin_5
#define RHEOSTAT_ADC_GPIO_CLK2     RCC_AHB1Periph_GPIOA
#define RHEOSTAT_ADC_CHANNEL2      ADC_Channel_5
/*=====================通道3 IO ======================*/

#define RHEOSTAT_ADC_GPIO_PORT3    GPIOA
#define RHEOSTAT_ADC_GPIO_PIN3     GPIO_Pin_6
#define RHEOSTAT_ADC_GPIO_CLK3     RCC_AHB1Periph_GPIOA
#define RHEOSTAT_ADC_CHANNEL3      ADC_Channel_6
/*=====================通道4 IO ======================*/

#define RHEOSTAT_ADC_GPIO_PORT4    GPIOA
#define RHEOSTAT_ADC_GPIO_PIN4     GPIO_Pin_7
#define RHEOSTAT_ADC_GPIO_CLK4     RCC_AHB1Periph_GPIOA
#define RHEOSTAT_ADC_CHANNEL4      ADC_Channel_7

// ADC 序号宏定义
#define RHEOSTAT_ADC              ADC1
#define RHEOSTAT_ADC_CLK          RCC_APB2Periph_ADC1
// ADC DR寄存器宏定义，ADC转换后的数字值则存放在这里
#define RHEOSTAT_ADC_DR_ADDR    ((u32)ADC1+0x4c)


// ADC DMA 通道宏定义，这里我们使用DMA传输
#define RHEOSTAT_ADC_DMA_CLK      RCC_AHB1Periph_DMA2
#define RHEOSTAT_ADC_DMA_CHANNEL  DMA_Channel_0
#define RHEOSTAT_ADC_DMA_STREAM   DMA2_Stream0



void Rheostat_Init(void);
u16 Get_Adc(u8 ch);   



//--------------------------------------------------------------------------------


typedef struct
{
    void (*init)(void);
	void (*adc_softwarestartconv)(ADC_TypeDef* ADCx);
    u16 (*get_adc)(u8 ch);
	
}adc_func_typedef;


//extern adc_func_typedef adc;
//extern adc_value simple;
void adc_func_init(void);

extern u16 ADC_ConvertedValue[RHEOSTAT_NOFCHANEL];

#endif /* __BSP_ADC_H */



