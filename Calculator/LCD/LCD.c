#include "StdTypes.h"
#include "Utils.h"

#include <util/delay.h>


#include "DIO_Interface.h"
#include "LCD_Interface.h"
#include "LCD_Cfg.h"
static u32 string_len(u8*str);
static void int_to_string (s32 n, u8 *str);
static  void string_reverse(u8*str);
static void int_to_Binary (u8 n, u8 *str);
static void int_to_Hex_to_string (u8 n, u8 *str);

#define FIRST_ROW 0
#define SECOND_ROW 1

#if LCD_MODE==_8_BIT
static void WriteIns(u8 ins)
{
	
	DIO_WritePin(RS,LOW);
	DIO_WritePort(LCD_PORT,ins);
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	
}

static void WriteData(u8 data)
{
	DIO_WritePin(RS,HIGH);
	DIO_WritePort(LCD_PORT,data);
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}



void LCD_Init(void)
{
	_delay_ms(50);
	
	WriteIns(0x38);//5*7 2 lines
	WriteIns(0x0c);//0x0c,0x0e,0x0f cursor
	WriteIns(0x01);//clear screen
	_delay_ms(1);
	WriteIns(0x06);// increment DDRAM address, no shift
	
}

#elif LCD_MODE ==_4_BIT
static void WriteIns(u8 ins)
{
	
	
	DIO_WritePin(RS,LOW);
	DIO_WritePin(D7,READ_BIT(ins,7));
	DIO_WritePin(D6,READ_BIT(ins,6));
	DIO_WritePin(D5,READ_BIT(ins,5));
	DIO_WritePin(D4,READ_BIT(ins,4));
	
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	DIO_WritePin(D7,READ_BIT(ins,3));
	DIO_WritePin(D6,READ_BIT(ins,2));
	DIO_WritePin(D5,READ_BIT(ins,1));
	DIO_WritePin(D4,READ_BIT(ins,0));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}

static void WriteData(u8 data)
{
	DIO_WritePin(RS,HIGH);
	DIO_WritePin(D7,READ_BIT(data,7));
	DIO_WritePin(D6,READ_BIT(data,6));
	DIO_WritePin(D5,READ_BIT(data,5));
	DIO_WritePin(D4,READ_BIT(data,4));

	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	DIO_WritePin(D7,READ_BIT(data,3));
	DIO_WritePin(D6,READ_BIT(data,2));
	DIO_WritePin(D5,READ_BIT(data,1));
	DIO_WritePin(D4,READ_BIT(data,0));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}



void LCD_Init(void)
{
	_delay_ms(50);
	WriteIns(0x02);
	WriteIns(0x28);//5*7 2 lines
	WriteIns(0x0c);//0x0c,0x0e,0x0f cursor
	WriteIns(0x01);//clear screen
	_delay_ms(1);
	WriteIns(0x06);// increment DDRAM address, no shift
	
}

#endif

void LCD_WriteChar(u8 ch)
{
	WriteData(ch);
}


void LCD_WriteString(u8*str)
{
	u8 i;
	for (i=0;str[i];i++)
	{
		LCD_WriteChar(str[i]);
	}
	
}


void LCD_SetCursor(u8 line,u8 cell)
{
	if (line==0)
	{
		WriteIns(0x80|cell);
	}
	else if (line ==1)
	{
		WriteIns(0x80+0x40+cell);
	}
	
}

void LCD_Clear(void)
{
	WriteIns(0x01);
	_delay_ms(1);
}


void LCD_WriteNumber(u32 num)
{
u8 str[32]={0};

int_to_string(num,str);

LCD_WriteString(str);
	
}
void LCD_WriteBinary(u8 num)
{
	u8 str[9]={0};
	int_to_Binary (num, str);
	LCD_WriteString(str);
		
}
void LCD_WriteHex(u8 num)
{
	u8 str[3]={0};
	 int_to_Hex_to_string (num,str);
	LCD_WriteString(str);
	
}
 
void LCD_CustomChar(u8 loc,u8*pattern)
{
	WriteIns(0x40+(loc*8));
	u8 i;
	
	for(i=0;i<8;i++)
	{
		WriteData(pattern[i]);
	}
	WriteIns(0x80);
	 
}
 
 static void int_to_Binary (u8 n, u8 *str)
 {
	 s8 i,j;
	 for(i=7,j=0;i>=0;i--,j++)
	 {
		 str[j]=READ_BIT(n,i)+'0';
	 }
 }
 
 static void int_to_Hex_to_string (u8 n, u8 *str)
 {
	 u8 s1,s2;
	 s1=n&(0x0f);
	 s2=n>>4;
	  
	  if(s1<=9)
	  {
		  str[1]=s1+'0';
	  }
	  else if(s1>9)
	  {
		  str[1]=(s1-10)+'A';
	  }
	  if(s2<=9)
	  {
		  str[0]=s2+'0';
	  }
	  else if (s2>9)
	  {
		  str[0]=(s2-10)+'A';
	  }
 }

 static void int_to_string (s32 n, u8 *str)
{
	u8 i=0,flag=0;
	
	s32 rem;

	if(n==0)
	{
		str[0]='0';
		str[1]=0;
		return;
	}
	if(n<0)
	{
		n=n*(-1);
		flag=1;
	}

	while(n)
	{
		rem=n%10;
		rem=rem+'0';
		str[i]=rem;
		i++;
		n=n/10;
	}

	if (flag==1)
	{
		str[i]='-';
		i++;
	}
	str[i]=0;
	string_reverse(str);

}

 static void string_reverse(u8*str)
{
	s32 j,i,len=string_len(str);
	j=len-1;
	u8 temp;
	for(i=0;i<=j;i++,j--)
	{
		temp=str[i];
		str[i]=str[j];
		str[j]=temp;
	}

}

 static u32 string_len(u8*str)
{
	u32 i;
	for(i=0;str[i];i++);
	return i;

}
