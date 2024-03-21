#include "OLED.h"
#include "Oledfont.h"

/******************************************************************************/
/* ��������  : OLED_Write_Cmd              		  	      	               	  */
/* ��������  : дָ�IIC��ʼ�ź�֮���ȷ��ʹӻ���ַ���յ�Ӧ���źź���дָ��*/	
/* �������  : cmd                                                            */
/* ��������  : д���ָ��			                       		              */
/* ����ֵ    : ��			                                                   */
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
/* ��������  : OLED_Write_Data              		  	   	               	  */
/* ��������  : д���ݣ�IIC��ʼ�ź�֮���ȷ��ʹӻ���ַ���յ�Ӧ���źź���д���� */	
/* �������  : datas                                                           */
/* ��������  : д�������			                       		              */
/* ����ֵ    : ��			                                                  */
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
/* ��������  : OLED_Init          	    		  	      	               	  */
/* ��������  : дָ���ʼ��OLED											  */	
/* �������  : ��	                                                          */
/* ��������  : ��					                       		              */
/* ����ֵ    : ��			                                                  */
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
/* ��������  : OLED_Clear          	    		  	      	               	  */
/* ��������  : �����Ļ��������												  */	
/* �������  : ��	                                                          */
/* ��������  : ��					                       		              */
/* ����ֵ    : ��			                                                  */
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
/* ��������  : OLED_Clear_Speed          		  	      	               	  */
/* ��������  : �����Ļ�ĵ�2,3ҳ��speed֮�������							  */	
/* �������  : ��	                                                          */
/* ��������  : ��					                       		              */
/* ����ֵ    : ��			                                                  */
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
/* ��������  : OLED_Clear_Model          		  	      	               	  */
/* ��������  : �����Ļ�ĵ�4,5ҳ��Model֮�������							  */	
/* �������  : ��	                                                          */
/* ��������  : ��					                       		              */
/* ����ֵ    : ��			                                                  */
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
/* ��������  : OLED_Show_Fixed_Word          		      	               	  */
/* ��������  : �ڵ�0,1ҳ�У���ʾ�̶��ĺ������ݡ���ӭ��������С����			  */	
/* �������  : ��	                                                          */
/* ��������  : ��					                       		              */
/* ����ֵ    : ��			                                                  */
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
/* ��������  : OLED_Show_Char		          		      	               	  */
/* ��������  : ��xx��xx����ʾһ���ַ�										  */	
/* �������  : row, col, oledChar	                    	                   */
/* ��������  : row��ʾҳ�ţ�col��ʾ�кţ�oledChar��ʾ�ַ�    		           */
/* ����ֵ    : ��			                                                  */
/******************************************************************************/
void OLED_Show_Char(char row,char col,char oledChar){ //�ַ����ǿ��Ϊ8���߶�Ϊ16����,֧��ASCII��  ��Ӧ��ϵΪ  ASCII - 32
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
/* ��������  : OLED_Show_Str		          			   	               	  */
/* ��������  : ��xx��xx����ʾһ���ַ�										  */	
/* �������  : row, col, oledChar	                    	                 */
/* ��������  : row��ʾҳ�ţ�col��ʾ�кţ�str��ʾ�ַ�ָ��    	              */
/* ����ֵ    : ��			                                                  */
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
/* ��������  : OLED_Show_Init	          			      	               	  */
/* ��������  : ��ʼ���ϵ�����ʱ��ʾ���ַ�									  */	
/* �������  : ��					                    	                   */
/* ��������  : ��										   		              */
/* ����ֵ    : ��			                                                  */
/******************************************************************************/
void OLED_Show_Init()
{
	OLED_Init();
	OLED_Clear();
	OLED_Show_Fixed_Word();
	OLED_Show_Str(2,0, "-----Ready-----");
	OLED_Show_Str(3,0, "Model:    ");
}
