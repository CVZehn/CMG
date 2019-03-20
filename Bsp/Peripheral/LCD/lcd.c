#include "stm32f4xx.h"
#include <lcd.h>
#include <font.h>
#include "delay.h"

#include "usart.h"


//lcd_func_typedef lcd;

//----------------------------------------------------------------------
void LCD1_GPIO_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd (LCD_CS_GPIO_CLK, ENABLE); 

		/*选择要控制的GPIO引脚*/															   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;  
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		/*调用库函数，使用上面配置的GPIO_InitStructure初始化GPIO*/
	GPIO_Init(LCD_CS_GPIO_PORT, &GPIO_InitStructure);	
    
}

void  SendDataSPI(unsigned char dat)
{  
   unsigned char i;
   
   for(i=0; i<8; i++)			
   {  
      if( (dat&0x80)!=0 ) 
          LCD_SDA_SET ;
        else 
          LCD_SDA_RESET ;

      dat <<= 1;

	  LCD_SCK_SET;
      LCD_SCK_RESET;			
   }
}

void WriteComm(unsigned int i)
{

    LCD_CS_RESET;
	LCD_A0_RESET;

	SendDataSPI(i);

	LCD_CS_SET;//CS0 = 1;

}
void WriteData(unsigned int i)
{
    LCD_CS_RESET;//CS0 = 0;
	LCD_A0_SET;//RS  = 1;

	SendDataSPI(i);

	LCD_CS_SET;//CS0 = 1;
}

void WriteDispData(unsigned char DataH,unsigned char DataL)
{
	 //CS0=0;

	 SendDataSPI(DataH);
	 SendDataSPI(DataL);

	 //CS0=1;
}

void LCD_Init(void)
{
	//CS0=0;
	LCD1_GPIO_Init();
    
	LCD_RST_SET;//RST=1;  
	delay_us(200);
	
	LCD_RST_RESET;//RST=0;
	delay_us(800);

	LCD_RST_SET;//RST=1;
	delay_us(800);

	//ILI9163C,FOR LB1.41
	
	WriteComm(0x11); //Exit Sleep
	delay_us(50);
	
    
	WriteComm(0x26); //Set Default Gamma
	WriteData(0x04);
	
    
	WriteComm(0xB1);//Set Frame Rate
	WriteData(0x0C);
	WriteData(0x14);
	
	WriteComm(0xC0); //Set VRH1[4:0] & VC[2:0] for VCI1 & GVDD
	WriteData(0x0C);
	WriteData(0x05);
	
	WriteComm(0xC1); //Set BT[2:0] for AVDD & VCL & VGH & VGL
	WriteData(0x02);//0x00
	
	WriteComm(0xC5); //Set VMH[6:0] & VML[6:0] for VOMH & VCOML
	WriteData(0x29);  //31  21  29
	WriteData(0x43);  //58   48  43
	
	WriteComm(0xC7);
	WriteData(0x40);
    
	
	WriteComm(0x3a); //Set Color Format
	WriteData(0x05);
	
	WriteComm(0x2A); //Set Column Address
	WriteData(0x00);
	WriteData(0x00);
	WriteData(0x00);
	WriteData(0x7F);
	
	WriteComm(0x2B); //Set Page Address
	WriteData(0x00);
	WriteData(0x00);
	WriteData(0x00);
	WriteData(0x9F);
	
	WriteComm(0x36); //Set Scanning Direction
	WriteData(0x68); //0xc8
	
	WriteComm(0xB7); //Set Source Output Direction
	WriteData(0x00);
	
    
	WriteComm(0xF2); //Enable Gamma bit
	WriteData(0x01);
	
	WriteComm(0xE0);
	WriteData(0x36);//p1
	WriteData(0x29);//p2
	WriteData(0x12);//p3
	WriteData(0x22);//p4
	WriteData(0x1C);//p5
	WriteData(0x15);//p6
	WriteData(0x42);//p7
	WriteData(0xB7);//p8
	WriteData(0x2F);//p9
	WriteData(0x13);//p10
	WriteData(0x12);//p11
	WriteData(0x0A);//p12
	WriteData(0x11);//p13
	WriteData(0x0B);//p14
	WriteData(0x06);//p15
	
	
	WriteComm(0xE1);
	WriteData(0x09);//p1
	WriteData(0x16);//p2
	WriteData(0x2D);//p3
	WriteData(0x0D);//p4
	WriteData(0x13);//p5
	WriteData(0x15);//p6
	WriteData(0x40);//p7
	WriteData(0x48);//p8
	WriteData(0x53);//p9
	WriteData(0x0C);//p10
	WriteData(0x1D);//p11
	WriteData(0x25);//p12
	WriteData(0x2E);//p13
	WriteData(0x34);//p14
	WriteData(0x39);//p15
    

    
	WriteComm(0x29); // Display On
	
	WriteComm(0x2c);


}

void BlockWrite(unsigned int Xstart,unsigned int Xend,unsigned int Ystart,unsigned int Yend) 
{
	//ILI9163C

	WriteComm(0x2A);             
	WriteData(Xstart>>8);             
	WriteData(Xstart);             
	WriteData(Xend>>8);             
	WriteData(Xend);             
	
	WriteComm(0x2B);             
	WriteData(Ystart>>8);             
	WriteData(Ystart);             
	WriteData(Yend>>8);             
	WriteData(Yend);   
	
	WriteComm(0x2c);
}
void LCD_DrawPixel(unsigned int color)
{ 
	
	LCD_CS_RESET;  
	LCD_A0_SET;	
	SendDataSPI(color>>8); 
	SendDataSPI(color);
	LCD_CS_SET;
}


void DispColorBOX(unsigned int Xstart,unsigned int Xend,unsigned int Ystart,unsigned int Yend,unsigned int color)
{
	unsigned int i,j;
	BlockWrite(Xstart,Xend,Ystart,Yend);

	LCD_CS_RESET;//CS0=0; 
	LCD_A0_SET;//RS=1;
	//RD0=1;

	for(i=Ystart;i<Yend;i++)
	{
	    for(j=Xstart;j<Xend;j++)
		{    
			SendDataSPI(color>>8);
			SendDataSPI(color);
		}
	}
	LCD_CS_SET;//CS0=1; 
}

void DispColor(unsigned int color)
{
	unsigned int i,j;
	BlockWrite(0,COL,0,ROW);

	LCD_CS_RESET;//CS0=0; 
	LCD_A0_SET;//RS=1;
	//RD0=1;

	for(i=0;i<ROW;i++)
	{
	    for(j=0;j<COL;j++)
		{    
			SendDataSPI(color>>8);
			SendDataSPI(color);
		}
	}
	LCD_CS_SET;//CS0=1; 
}

void DispBand(void)	 
{
	unsigned int i,j,k;
	//unsigned int color[8]={0x001f,0x07e0,0xf800,0x07ff,0xf81f,0xffe0,0x0000,0xffff};
	unsigned int color[8]={0xf800,0xf800,0x07e0,0x07e0,0x001f,0x001f,0xffff,0xffff};//0x94B2
	//unsigned int gray16[]={0x0000,0x1082,0x2104,0x3186,0x42,0x08,0x528a,0x630c,0x738e,0x7bcf,0x9492,0xa514,0xb596,0xc618,0xd69a,0xe71c,0xffff};

   	BlockWrite(0,COL-1,0,ROW-1);
    	
	LCD_CS_RESET;//CS0=0;
	//RD0=1;
	LCD_A0_SET;//RS=1;																									  

	for(i=0;i<8;i++)
	{
		for(j=0;j<ROW/8;j++)
		{
	        for(k=0;k<COL;k++)
			{
				SendDataSPI(color[i]>>8); 
				SendDataSPI(color[i]);  

			} 
		}
	}
	for(j=0;j<ROW%8;j++)
	{
        for(k=0;k<COL;k++)
		{
			    
			SendDataSPI(color[7]>>8);  
			SendDataSPI(color[7]); 

		} 
	}
	
	LCD_CS_RESET;//CS0=1;
}

void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u16 Color)
{
	u8 temp,t1,t;
	u16 x0=x;
    
    BlockWrite(x,x+(A_FONT_W-1),y,y+(A_FONT_H-1));
 	num=num-55;//得到偏移后的值（ASCII字库是从空格开始取模，所以-' '就是对应字符的字库）
	for(t=0;t<16;t++)
	{   
		temp=F8X16[num][t]; 	 	  
		for(t1=0;t1<8;t1++)
		{			    
			if(temp&0x80)LCD_DrawPixel(Color);
			else LCD_DrawPixel(white);
			temp<<=1;
		}  	 
	}
}

void LCD_ShowNum(u16 x,u16 y,u8 num,u8 size,u16 Color)
{
	u8 temp,t1,t;
	u16 x0=x;
    
    BlockWrite(x,x+(A_FONT_W-1),y,y+(A_FONT_H-1));
 	num=num;//得到偏移后的值（ASCII字库是从空格开始取模，所以-' '就是对应字符的字库）
	for(t=0;t<16;t++)
	{   
		temp=F8X16[num][t]; 	 	  
		for(t1=0;t1<8;t1++)
		{			    
			if(temp&0x80)LCD_DrawPixel(Color);
			else LCD_DrawPixel(white);
			temp<<=1;
		}  	 
	}
}

void LCD_ShowString(u16 x,u16 y,u8 *p,u8 size,u16 Color)
{
      while('A'<=*p&&'z'>=*p)
      {
		LCD_ShowChar(x,y,*p,size,Color);
		x=x+size;
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
        if(x+((len-t)*8)-1<ROW)
        {
            LCD_ShowNum(x+((len-t)*8),y,temp1,size,Color);
        }
	}
}

void LCD_ShowFont(u16 x,u16 y,u8 num,u8 size,u8 mode,u16 Color)
{
  u8 temp,t1,t;
	u16 x0=x;
    
    BlockWrite(x,x+(C_FONT_W-1),y,y+(C_FONT_H-1));
	for(t=0;t<32;t++)
	{   
//     temp=hz[num][t];	

		for(t1=0;t1<8;t1++)
		{			    
			if(temp&0x80)LCD_DrawPixel(Color);
			else if(mode==0)LCD_DrawPixel(white);
			temp<<=1;
//			x--;
//			if((x0-x)==size)
//			{
//				x=x0;
//				y--;
//				break;
//			}
		}  	 
	} 
} 
void DispFrame(void)
{
	unsigned int i,j;
	
	BlockWrite(0,COL-1,0,ROW-1);

	LCD_CS_RESET;//CS0=0;
	//RD0=1;
	LCD_A0_SET;//RS=1;
		
	SendDataSPI(0xf8);SendDataSPI(0x00);
	for(i=0;i<COL-2;i++){SendDataSPI(0xFF);SendDataSPI(0xFF);}
	SendDataSPI(0x00);SendDataSPI(0x1f);

	for(j=0;j<ROW-2;j++)
	{
		SendDataSPI(0xf8);SendDataSPI(0x00);
		for(i=0;i<COL-2;i++){SendDataSPI(0x00);SendDataSPI(0x00);}
		SendDataSPI(0x00);SendDataSPI(0x1F);
	}

	SendDataSPI(0xf8);SendDataSPI(0x00);
	for(i=0;i<COL-2;i++){SendDataSPI(0xFF);SendDataSPI(0xFF);}
	SendDataSPI(0x00);SendDataSPI(0x1F);
	
	LCD_CS_RESET;//CS0=1;
}

