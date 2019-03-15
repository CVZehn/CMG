
#ifndef __LCD_H__
#define __LCD_H__

#include "string.h"
#include "stm32f4xx.h"


#define LCD_DATA_GPIO_CLK   RCC_AHB1Periph_GPIOD           
#define LCD_DATA_GPIO_PORT            GPIOD                      


#define LCD_RD_GPIO_CLK     RCC_AHB1Periph_GPIOB
#define LCD_RD_GPIO_PORT        GPIOB
#define LCD_RD_GPIO_PIN         GPIO_Pin_5

#define LCD_WR_GPIO_CLK     RCC_AHB1Periph_GPIOB
#define LCD_WR_GPIO_PORT        GPIOB
#define LCD_WR_GPIO_PIN         GPIO_Pin_6

#define LCD_RS_GPIO_CLK     RCC_AHB1Periph_GPIOB
#define LCD_RS_GPIO_PORT        GPIOB
#define LCD_RS_GPIO_PIN         GPIO_Pin_7

#define LCD_CS_GPIO_CLK     RCC_AHB1Periph_GPIOB
#define LCD_CS_GPIO_PORT        GPIOB
#define LCD_CS_GPIO_PIN         GPIO_Pin_8

#define LCD_RST_GPIO_CLK       RCC_AHB1Periph_GPIOC
#define LCD_RST_GPIO_PORT        GPIOC
#define LCD_RST_GPIO_PIN         GPIO_Pin_12

#define LCD_DataPort            GPIOD->ODR

#define LCD_RD_SET               GPIOB->BSRRL = 0x0020
#define LCD_RD_RESET             GPIOB->BSRRH = 0x0020

#define LCD_WR_SET              GPIOB->BSRRL = 0x0040
#define LCD_WR_RESET            GPIOB->BSRRH = 0x0040

#define LCD_RS_SET               GPIOB->BSRRL = 0x0080
#define LCD_RS_RESET             GPIOB->BSRRH = 0x0080

#define LCD_CS_SET               GPIOB->BSRRL = 0x0100
#define LCD_CS_RESET             GPIOB->BSRRH = 0x0100

#define LCD_RST_SET             GPIOC->BSRRL = 0x1000
#define LCD_RST_RESET           GPIOC->BSRRH = 0x1000

void LCD_Init(void);
void LCD_GPIO_Init(void);
void LCD_Data_Wirte_Port(u8 data);
void LCD_Block(u16 xStart,u16 yStart,u16 xEnd,u16 yEnd);
void LCD_ColorBox(u16 xStart,u16 yStart,u16 xLong,u16 yLong,u16 Color);
void LCD_DrawPixel(u16 x,u16 y,u16 color);
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2,u16 Color);
void LCD_ShowChar(u16 x, u16 y, u8 num,u8 size,u16 Color);
void LCD_ShowNum(u16 x, u16 y, u8 num,u8 size,u16 Color);
void LCD_ShowFont(u16 x,u16 y,u8 num,u8 size,u8 mode,u16 Color);
void LCD_ShowString(u16 x,u16 y,u8 *p,u8 size,u16 Color);
void LCD_ShowxNum(u16 x,u16 y,u16 num,u8 size,u8 len,u16 Color);


#define blue           0xf800
#define green          0x07e0
#define black          0x0000
#define white          0xffff
#define yellow         0x07ff
#define orange         0x05bf
#define Chocolate4     0x4451
#define Grey           0xefbd//灰色

#define White          0xFFFF
#define Black          0x0000
#define Blue           0x001F
#define Blue2          0x051F
#define Red            0xF800
#define Magenta        0xF81F
#define Green          0x07E0
#define Cyan           0x7FFF
#define Yellow         0xFFE0

#endif