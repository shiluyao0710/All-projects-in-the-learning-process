#include "OLED.h"
#include "Oledfont.h"

/******************************************************************************/
/* 函数名称  : OLED_Write_Cmd              		  	      	               	  */
/* 函数描述  : 写指令，IIC开始信号之后，先发送从机地址，收到应答信号后，再写指令*/	
/* 输入参数  : cmd                                                            */
/* 参数描述  : 写入的指令			                       		              */
/* 返回值    : 无			                                                   */
/******************************************************************************/
void OLED_Write_Cmd(unsigned char cmd)
{
	IIC_Init();
	IIC_Start();
	IIC_Write_Data(0x78);
	IIC_Wait_Ack();
	IIC_Write_Data(0x00);
	IIC_Wait_Ack();
	IIC_Write_Data(cmd);
	IIC_Wait_Ack();
	IIC_Stop();
}

/******************************************************************************/
/* 函数名称  : OLED_Write_Data              		  	   	               	  */
/* 函数描述  : 写数据，IIC开始信号之后，先发送从机地址，收到应答信号后，再写数据 */	
/* 输入参数  : datas                                                           */
/* 参数描述  : 写入的数据			                       		              */
/* 返回值    : 无			                                                  */
/******************************************************************************/
void OLED_Write_Data(unsigned char datas)
{
	IIC_Init();
	IIC_Start();
	IIC_Write_Data(0x78);
	IIC_Wait_Ack();
	IIC_Write_Data(0x40);
	IIC_Wait_Ack();
	IIC_Write_Data(datas);
	IIC_Wait_Ack();
	IIC_Stop();
	
}

/******************************************************************************/
/* 函数名称  : OLED_Init          	    		  	      	               	  */
/* 函数描述  : 写指令，初始化OLED											  */	
/* 输入参数  : 无	                                                          */
/* 参数描述  : 无					                       		              */
/* 返回值    : 无			                                                  */
/******************************************************************************/
void OLED_Init()
{
	OLED_Write_Cmd(0xAE);
	OLED_Write_Cmd(0x00);
	OLED_Write_Cmd(0x10);
	OLED_Write_Cmd(0x40);
	OLED_Write_Cmd(0xB0);
	OLED_Write_Cmd(0x81);
	OLED_Write_Cmd(0xFF);
	OLED_Write_Cmd(0xA1);
	OLED_Write_Cmd(0xA6);
	OLED_Write_Cmd(0xA8);
	OLED_Write_Cmd(0x3F);
	OLED_Write_Cmd(0xC8);
	OLED_Write_Cmd(0xD3);
	OLED_Write_Cmd(0x00);
	OLED_Write_Cmd(0xD5);
	OLED_Write_Cmd(0x80);
	OLED_Write_Cmd(0xD8);
	OLED_Write_Cmd(0x05);
	OLED_Write_Cmd(0xD9);
	OLED_Write_Cmd(0xF1);
	OLED_Write_Cmd(0xDA);
	OLED_Write_Cmd(0x12);
	OLED_Write_Cmd(0xDB);
	OLED_Write_Cmd(0x30);
	OLED_Write_Cmd(0x8D);
	OLED_Write_Cmd(0x14);
	OLED_Write_Cmd(0xAF);
}

/******************************************************************************/
/* 函数名称  : OLED_Clear          	    		  	      	               	  */
/* 函数描述  : 清除屏幕所有内容												  */	
/* 输入参数  : 无	                                                          */
/* 参数描述  : 无					                       		              */
/* 返回值    : 无			                                                  */
/******************************************************************************/
void OLED_Clear()
{
	unsigned char i = 0;
	unsigned char j = 0;
	for(i=0;i<8;i++)
	{
		OLED_Write_Cmd(0xB0 + i);
		OLED_Write_Cmd(0x10);
		OLED_Write_Cmd(0x00);
		for(j=0;j<128;j++)
		{
			OLED_Write_Data(0);
		}
	}
}

/******************************************************************************/
/* 函数名称  : OLED_Clear_Speed          		  	      	               	  */
/* 函数描述  : 清除屏幕的第2,3页的speed之后的内容							  */	
/* 输入参数  : 无	                                                          */
/* 参数描述  : 无					                       		              */
/* 返回值    : 无			                                                  */
/******************************************************************************/
void OLED_Clear_Speed()
{
	unsigned char i;
	unsigned char j;
	for(i = 2; i < 4; i++)
	{
		OLED_Write_Cmd(0xB0 + i);
		OLED_Write_Cmd(0x13);
		OLED_Write_Cmd(0x00);
		for(j = 48; j < 128; j++)
		{
			OLED_Write_Data(0);
		}	
	}
	
}

/******************************************************************************/
/* 函数名称  : OLED_Clear_Model          		  	      	               	  */
/* 函数描述  : 清除屏幕的第4,5页的Model之后的内容							  */	
/* 输入参数  : 无	                                                          */
/* 参数描述  : 无					                       		              */
/* 返回值    : 无			                                                  */
/******************************************************************************/
void OLED_Clear_Model()
{
	unsigned char i;
	unsigned char j;
	for(i = 4; i < 6; i++)
	{
		OLED_Write_Cmd(0xB0 + i);
		OLED_Write_Cmd(0x13);
		OLED_Write_Cmd(0x00);
		for(j = 48; j < 128; j++)
		{
			OLED_Write_Data(0);
		}	
	}
}

/******************************************************************************/
/* 函数名称  : OLED_Show_Fixed_Word          		      	               	  */
/* 函数描述  : 在第0,1页中，显示固定的汉字内容“欢迎启动杂牌小车“			  */	
/* 输入参数  : 无	                                                          */
/* 参数描述  : 无					                       		              */
/* 返回值    : 无			                                                  */
/******************************************************************************/
void OLED_Show_Fixed_Word()
{
	unsigned char i;
	OLED_Write_Cmd(0xB0);
	OLED_Write_Cmd(0x10);
	OLED_Write_Cmd(0x00);
	for(i=0;i<128;i++)
	{
		OLED_Write_Data(fixed_word_up[i]);
	}
	OLED_Write_Cmd(0xB1);
	OLED_Write_Cmd(0x10);
	OLED_Write_Cmd(0x00);
	for(i=0;i<128;i++)
	{
		OLED_Write_Data(fixed_word_down[i]);
	}
}

/******************************************************************************/
/* 函数名称  : OLED_Show_Char		          		      	               	  */
/* 函数描述  : 在xx行xx列显示一个字符										  */	
/* 输入参数  : row, col, oledChar	                    	                   */
/* 参数描述  : row表示页号，col表示列号，oledChar表示字符    		           */
/* 返回值    : 无			                                                  */
/******************************************************************************/
void OLED_Show_Char(char row,char col,char oledChar){ //字符表是宽度为8，高度为16的字,支持ASCII码  对应关系为  ASCII - 32
	unsigned int  i;
	OLED_Write_Cmd(0xB0+(row*2-2));                           
	OLED_Write_Cmd(0x00+(col&0x0F));                         
	OLED_Write_Cmd(0x10+(col>>4));                            
	for(i=((oledChar-32)*16);i<((oledChar-32)*16+8);i++){
		OLED_Write_Data(F8X16[i]);                           
	}

	OLED_Write_Cmd(0xB0+(row*2-1));                           
	OLED_Write_Cmd(0x00+(col&0x0F));                         
	OLED_Write_Cmd(0x10+(col>>4));                            
	for(i=((oledChar-32)*16+8);i<((oledChar-32)*16+8+8);i++){
		OLED_Write_Data(F8X16[i]);                           
	}		
}

/******************************************************************************/
/* 函数名称  : OLED_Show_Str		          			   	               	  */
/* 函数描述  : 在xx行xx列显示一串字符										  */	
/* 输入参数  : row, col, oledChar	                    	                 */
/* 参数描述  : row表示页号，col表示列号，str表示字符指针    	              */
/* 返回值    : 无			                                                  */
/******************************************************************************/
void OLED_Show_Str(char row,char col,char *str){
	OLED_Write_Cmd(0x20);
	OLED_Write_Cmd(0x02);
	while(*str!=0){
		OLED_Show_Char(row,col,*str);
		str++;
		col += 8;	
	}		
}

/******************************************************************************/
/* 函数名称  : OLED_Show_Init	          			      	               	  */
/* 函数描述  : 初始化上电启动时显示的字符									  */	
/* 输入参数  : 无					                    	                   */
/* 参数描述  : 无										   		              */
/* 返回值    : 无			                                                  */
/******************************************************************************/
void OLED_Show_Init()
{
	OLED_Init();
	OLED_Clear();
	OLED_Show_Fixed_Word();
	OLED_Show_Str(2,0, "-----Ready-----");
	OLED_Show_Str(3,0, "Model:    ");
}
