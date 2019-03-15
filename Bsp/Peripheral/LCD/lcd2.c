#include "lcd.h"
#include "font.h"
#include "delay.h"
#include "usart.h"

void LCD_Data_Wirte_Port(u8 data)
{
    u8 tem=0;
    tem=data&0x01;
    tem=(tem<<1)|((data>>1)&0x01);
    tem=(tem<<1)|((data>>2)&0x01);
    tem=(tem<<1)|((data>>3)&0x01);
    tem=(tem<<1)|((data>>4)&0x01);
    tem=(tem<<1)|((data>>5)&0x01);
    tem=(tem<<1)|((data>>6)&0x01);
    tem=(tem<<1)|((data>>7)&0x01);
    LCD_DataPort=tem;

}
void LCD_Writ_Bus(u16 V)   //并行数据写入函数
{	
	u8 VH,VL;
	VH=V>>8;
	VL=V;
    
    LCD_Data_Wirte_Port(VH);
//    LCD_DataPort=VH;	
    LCD_WR_RESET;
	LCD_WR_SET;	
    LCD_Data_Wirte_Port(VL);
//	LCD_DataPort=VL;	
	LCD_WR_RESET;
	LCD_WR_SET;
}


void Lcd_Write_Com(u16 V) //发送数据-8位参数
{
	u8 VL;
	VL=V;

    LCD_RS_RESET;
    LCD_Data_Wirte_Port(VL);
//	LCD_DataPort=VL;		
	LCD_WR_RESET;
	LCD_WR_SET;
    LCD_RS_SET;
}
void Lcd_Write_Data(u16 V) //发送数据-8位参数
{
  LCD_RS_SET;
  LCD_Writ_Bus(V);
}
void WriteRegister(u16 com,u16 val)		   //发送数据命令
{
	Lcd_Write_Com(com);
    Lcd_Write_Data(val);
}

void LCD_GPIO_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd (LCD_DATA_GPIO_CLK|LCD_WR_GPIO_CLK|LCD_RST_GPIO_CLK, ENABLE); 

		/*选择要控制的GPIO引脚*/															   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3
    |GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;  
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		/*调用库函数，使用上面配置的GPIO_InitStructure初始化GPIO*/
	GPIO_Init(LCD_DATA_GPIO_PORT, &GPIO_InitStructure);	
    
    		/*选择要控制的GPIO引脚*/															   
	GPIO_InitStructure.GPIO_Pin = LCD_RD_GPIO_PIN|LCD_WR_GPIO_PIN|LCD_RS_GPIO_PIN|LCD_CS_GPIO_PIN|GPIO_Pin_12;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;  
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		/*调用库函数，使用上面配置的GPIO_InitStructure初始化GPIO*/
	GPIO_Init(LCD_WR_GPIO_PORT, &GPIO_InitStructure);	
    
    GPIO_InitStructure.GPIO_Pin = LCD_RST_GPIO_PIN;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;  
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		/*调用库函数，使用上面配置的GPIO_InitStructure初始化GPIO*/
	GPIO_Init(LCD_RST_GPIO_PORT, &GPIO_InitStructure);	
    
//    GPIO_SetBits(GPIOB,GPIO_Pin_5);
    GPIO_SetBits(GPIOB,GPIO_Pin_6);
    GPIO_SetBits(GPIOB,GPIO_Pin_7);
    GPIO_SetBits(GPIOB,GPIO_Pin_8);
    GPIO_ResetBits(GPIOB,GPIO_Pin_12);
    GPIO_SetBits(GPIOC,GPIO_Pin_12);
    GPIOD->ODR=0XFFFF;
}

void LCD_Init(void)
{
    
    LCD_GPIO_Init();
	delay_ms(20);
    LCD_CS_RESET;
	LCD_RST_SET;  
	delay_ms(20);
	
	LCD_RST_RESET;
	delay_ms(60);

	LCD_RST_SET;
	delay_ms(60);
	WriteRegister(0x0011, 0x0000);
    WriteRegister(0x0012, 0x0000);
    WriteRegister(0x0013, 0x0000);
	WriteRegister(0x0014, 0x0000);
		
	WriteRegister(0x0012, 0x3121);
	WriteRegister(0x0013, 0x0066);
	WriteRegister(0x0014, 0x515B);
		
	WriteRegister(0x00C7, 0x030C);
	WriteRegister(0x00EC, 0x120F);
		
	WriteRegister(0x0010, 0x0A00);
	WriteRegister(0x0011, 0x103B);
		
	WriteRegister(0x0001, 0x001C);
	WriteRegister(0x0002, 0x0100);
	WriteRegister(0x0003, 0x1030);
	WriteRegister(0x000C, 0x0000);
		
	WriteRegister(0x30, 0x0000);
	WriteRegister(0x31, 0x00DB);
	WriteRegister(0x32, 0x0000);
	WriteRegister(0x33, 0x0000);
	WriteRegister(0x34, 0x00DB);
	WriteRegister(0x35, 0x0000);
	WriteRegister(0x36, 0x00AF);
	WriteRegister(0x37, 0x0000);
	WriteRegister(0x38, 0x00DB);
	WriteRegister(0x39, 0x0000);
		
	WriteRegister(0x0020, 0x0000);
	WriteRegister(0x0021, 0x0000);
		
	WriteRegister(0x0050, 0x0000);
	WriteRegister(0x0051, 0x0403);
	WriteRegister(0x0052, 0x0B06);
	WriteRegister(0x0053, 0x0103);
	WriteRegister(0x0054, 0x060B);
	WriteRegister(0x0055, 0x0304);
	WriteRegister(0x0056, 0x0000);
	WriteRegister(0x0057, 0x0301);
	WriteRegister(0x0058, 0x0E00);
	WriteRegister(0x0059, 0x000E);
		
	WriteRegister(0x000F, 0x0A01);
	WriteRegister(0x0007, 0x1017); 
    
	delay_us(2);
	Lcd_Write_Com(0x0022);
}

void Address_set(u16 x1,u16 y1)
{
	Lcd_Write_Com(0x0020);
    Lcd_Write_Data(x1);	  //设置X坐标位置
    Lcd_Write_Com(0x0021);
    Lcd_Write_Data(y1);   //设置Y坐标位置
	Lcd_Write_Com(0x0022); 
}


	 
void LCD_ColorBox(u16 xStart,u16 yStart,u16 xEnd,u16 yEnd,u16 Color)
{
	 u8 temp1,temp2;
	
    LCD_CS_RESET;
	for (temp2=yStart; temp2<yEnd; temp2++)
	{
        for(temp1=xStart; temp1<xEnd; temp1++)
        {
	      Address_set(temp1,temp2);
	      Lcd_Write_Data(Color);
        }
	}
	LCD_CS_SET;
}
void LCD_DrawPixel(u16 x,u16 y,u16 color)
{
    LCD_CS_RESET;
	delay_us(2);
	Address_set(x,y);
	Lcd_Write_Data(color);
	LCD_CS_SET;
	
}
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2,u16 Color)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	delta_x=x2-x1; //计算坐标增量 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //设置单步方向 
	else if(delta_x==0)incx=0;//垂直线 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//水平线 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//画线输出 
	{  

		LCD_DrawPixel(uRow,uCol,Color);//画点 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
} 
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u16 Color)
{
	u8 temp,t1,t;
	u16 x0=x;
 	num=num-0x35;//得到偏移后的值（ASCII字库是从空格开始取模，所以-' '就是对应字符的字库）
	for(t=0;t<16;t++)
	{   
		temp=F8X16[num][t]; 	 	  
		for(t1=0;t1<8;t1++)
		{			    
			if(temp&0x80)LCD_DrawPixel(x,y,Color);
			else LCD_DrawPixel(x,y,white);
			temp<<=1;
			x--;
			if((x0-x)==16)
			{
				x=x0;
				y--;
				break;
			}
		}  	 
	}
}
void LCD_ShowNum(u16 x,u16 y,u8 num,u8 size,u16 Color)
{
	u8 temp,t1,t;
	u16 x0=x;
 	num=num+1;//得到偏移后的值（ASCII字库是从空格开始取模，所以-' '就是对应字符的字库）
	for(t=0;t<16;t++)
	{   
		temp=F8X16[num][t]; 	 	  
		for(t1=0;t1<8;t1++)
		{			    
			if(temp&0x80)LCD_DrawPixel(x,y,Color);
			else LCD_DrawPixel(x,y,white);
			temp<<=1;
			x--;
			if((x0-x)==16)
			{
				x=x0;
				y--;
				break;
			}
		}  	 
	}
}
void LCD_ShowString(u16 x,u16 y,u8 *p,u8 size,u16 Color)
{
      while('A'<=*p&&'Z'>=*p)
      {
		LCD_ShowChar(x,y,*p,size,Color);
		y=y-size/2;
		p++;
      }
}

void LCD_ShowxNum(u16 x,u16 y,u16 num,u8 size,u8 len,u16 Color)
{
	u8 t,temp1;
    u16 temp2;
    temp2=num;
	for(t=0;t<len;t++)
	{
        if(t!=0)
        {
        temp2=temp2/10;
		temp1=temp2%10;
        }
        else
        {
		temp1=num%10;
        }
        y=y+8;
		LCD_ShowNum(x,y,temp1,size,Color);
	}
}

void LCD_ShowFont(u16 x,u16 y,u8 num,u8 size,u8 mode,u16 Color)
{
  u8 temp,t1,t;
	u16 x0=x;
	for(t=0;t<32;t++)
	{   
     temp=hz[num][t];	

		for(t1=0;t1<8;t1++)
		{			    
			if(temp&0x80)LCD_DrawPixel(x,y,Color);
			else if(mode==0)LCD_DrawPixel(x,y,white);
			temp<<=1;
			x--;
			if((x0-x)==size)
			{
				x=x0;
				y--;
				break;
			}
		}  	 
	} 
} 