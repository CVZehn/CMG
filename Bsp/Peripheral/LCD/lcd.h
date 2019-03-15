#ifndef __LCD_h__
#define __LCD_h__
#include "string.h"
#include "stm32f4xx.h"
//---------------------------------------------------------------------

#define ROW  128		    //显示的行、列数
#define COL  160

//---------------------------------------------------------------------

#define LCD_CS_GPIO_CLK     RCC_AHB1Periph_GPIOD
#define LCD_CS_GPIO_PORT        GPIOD
#define LCD_CS_GPIO_PIN         GPIO_Pin_6

#define LCD_SCK_GPIO_CLK     RCC_AHB1Periph_GPIOD
#define LCD_SCK_GPIO_PORT        GPIOD
#define LCD_SCK_GPIO_PIN         GPIO_Pin_5

#define LCD_SDA_GPIO_CLK     RCC_AHB1Periph_GPIOD
#define LCD_SDA_GPIO_PORT        GPIOD
#define LCD_SDA_GPIO_PIN         GPIO_Pin_4

#define LCD_A0_GPIO_CLK     RCC_AHB1Periph_GPIOD
#define LCD_A0_GPIO_PORT        GPIOD
#define LCD_A0_GPIO_PIN         GPIO_Pin_3

#define LCD_RST_GPIO_CLK       RCC_AHB1Periph_GPIOD
#define LCD_RST_GPIO_PORT        GPIOD
#define LCD_RST_GPIO_PIN         GPIO_Pin_2

//---------------------------------------------------------------------

#define LCD_CS_SET               GPIOD->BSRRL = 0x0040
#define LCD_CS_RESET             GPIOD->BSRRH = 0x0040

#define LCD_SCK_SET              GPIOD->BSRRL = 0x0020
#define LCD_SCK_RESET            GPIOD->BSRRH = 0x0020

#define LCD_SDA_SET              GPIOD->BSRRL = 0x0010
#define LCD_SDA_RESET            GPIOD->BSRRH = 0x0010

#define LCD_A0_SET               GPIOD->BSRRL = 0x0008
#define LCD_A0_RESET             GPIOD->BSRRH = 0x0008

#define LCD_RST_SET             GPIOD->BSRRL = 0x0004
#define LCD_RST_RESET           GPIOD->BSRRH = 0x0004
//---------------------------------------------------------------------

/*
#define LCD_CS_SET               GPIO_SetBits(LCD_CS_GPIO_PORT,LCD_CS_GPIO_PIN)
#define LCD_CS_RESET             GPIO_ResetBits(LCD_CS_GPIO_PORT,LCD_CS_GPIO_PIN)

#define LCD_SCK_SET              GPIO_SetBits(LCD_SCK_GPIO_PORT,LCD_SCK_GPIO_PIN)
#define LCD_SCK_RESET            GPIO_ResetBits(LCD_SCK_GPIO_PORT,LCD_SCK_GPIO_PIN)

#define LCD_SDA_SET              GPIO_SetBits(LCD_SDA_GPIO_PORT,LCD_SDA_GPIO_PIN)
#define LCD_SDA_RESET            GPIO_ResetBits(LCD_SDA_GPIO_PORT,LCD_SDA_GPIO_PIN)

#define LCD_A0_SET               GPIO_SetBits(LCD_A0_GPIO_PORT,LCD_A0_GPIO_PIN)
#define LCD_A0_RESET             GPIO_ResetBits(LCD_A0_GPIO_PORT,LCD_A0_GPIO_PIN)

#define LCD_RST_SET             GPIO_SetBits(LCD_RST_GPIO_PORT,LCD_RST_GPIO_PIN)
#define LCD_RST_RESET           GPIO_ResetBits(LCD_RST_GPIO_PORT,LCD_RST_GPIO_PIN)
*/
//---------------------------------------------------------------------


#define blue           0xf800
#define green          0x07e0
#define black          0x0000
#define white          0xffff
#define yellow         0x07ff
#define orange         0x05bf
#define Chocolate4     0x4451
#define Grey           0xefbd//灰色

#define  A_FONT_W  8
#define  A_FONT_H  16

#define  C_FONT_W  8
#define  C_FONT_H  16

//---------------------------------------------------------------------

void DispFrame(void);
void LCD_Init(void);
void DispBand(void);
void WriteComm(unsigned int i);
void WriteData(unsigned int i);
void DispColor(unsigned int color);
void LCD_DrawPixel(unsigned int color);
void WriteDispData(unsigned char DataH,unsigned char DataL);
void BlockWrite(unsigned int Xstart,unsigned int Xend,unsigned int Ystart,unsigned int Yend) ;
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u16 Color);
void LCD_ShowNum(u16 x,u16 y,u8 num,u8 size,u16 Color);
void LCD_ShowString(u16 x,u16 y,u8 *p,u8 size,u16 Color);
void LCD_ShowxNum(u16 x,u16 y,u16 num,u8 size,u8 len,u16 Color);
void LCD_ShowFont(u16 x,u16 y,u8 num,u8 size,u8 mode,u16 Color);
//---------------------------------------------------------------------

typedef struct
{
    void (*init)(void);
    void (*dispframe)(void);
    void (*dispband)(void);
    void (*writecomm)(unsigned int i);
    void (*writedata)(unsigned int i);
    void (*dispcolor)(unsigned int color);
    void (*lcd_drawpixel)(unsigned int color);
    void (*writedispdata)(unsigned char DataH,unsigned char DataL);
    void (*blockwrite)(unsigned int Xstart,unsigned int Xend,unsigned int Ystart,unsigned int Yend);
    void (*lcd_showchar)(u16 x,u16 y,u8 num,u8 size,u16 Color);
    void (*lcd_shownum)(u16 x,u16 y,u8 num,u8 size,u16 Color);
    void (*lcd_showstring)(u16 x,u16 y,u8 *p,u8 size,u16 Color);
    void (*lcd_showxnum)(u16 x,u16 y,u16 num,u8 size,u8 len,u16 Color);
    void (*lcd_showfont)(u16 x,u16 y,u8 num,u8 size,u8 mode,u16 Color);
}lcd_func_typedef;

//---------------------------------------------------------------------
extern lcd_func_typedef lcd;

void lcd_func_init(void);	

#endif
