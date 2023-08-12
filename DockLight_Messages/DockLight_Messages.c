#include "StdTypes.h"
#include "Utils.h"

#include "DIO_Interface.h"
#include "LCD_Interface.h"
#include "ServoMotor_Interface.h"



#include "DockLight_Messages.h"



static u8 data_rec[20]={0};
static u8 data_str[10]={0};
static u8 data_num[10]={0};
static volatile u8 flag1 =1;
static u8 flag2=0;

static u16 num=0;

u8*servo="servo";
u8*ledon="ledon";
u8*ledoff="ledoff";
u8*lcd="lcd";



void recieve_data_inISR(void)
{
	if(flag1==1)
	{
			static u8 j=0;
			u8 data= UART_ReceiveNoBlock();
			if(data!=' ')
			{
				if(data=='#')
				{
					data_rec[j]=0;
					j=0;
					flag1=0;
				}
				else
				{
					data_rec[j]=data;
					j++;
				}
			}
	}

}

void Docklight_Messages_Init(void)
{
	DIO_Init();
	LCD_Init();
	Servo_Motor_Init();
	UART_RX_InterruptEnable();
	UART_RX_SetCallBack(recieve_data_inISR);
}

void Docklight_Messages_Seperate(void)
{
	if(flag1==0)
	{
		u8 i;
		u8 j=0,z=0;
		for(i=0;data_rec[i];i++)
		{
			if(data_rec[i]>='0'&&data_rec[i]<='9')
			{
				data_num[j]=data_rec[i];
				j++;
			}
			if (data_rec[i]>='a'&&data_rec[i]<='z')
			{
				data_str[z]=data_rec[i];
				z++;
			}
		}
		data_num[j]=0;
		data_str[z]=0;
		string_to_integer(data_num,&num);
		
	
		flag2=1;
		flag1=1;
	}
	
		
	
}

void Docklight_Messages_Runnable(void)
{
	if(flag2==1)
	{
		u8 flag_servo=1;
		u8 flag_lcd=1;
		u8 flag_ledon=1;
		u8 flag_ledoff=1;
		
		u8 i;
	
		
		for(i=0;data_str[i];i++)
		{
			if(data_str[i]!=servo[i])
			{
				flag_servo=0;
			}
			if(data_str[i]!=lcd[i])
			{
				flag_lcd=0;
			}
			if(data_str[i]!=ledon[i])
			{
				flag_ledon=0;
			}
			if(data_str[i]!=ledoff[i])
			{
				flag_ledoff=0;
			}
			
		}
		if(flag_servo==1)
		{
			Servo_Motor_Direction(SERVO_MOTOR_1,num);
			LCD_SetCursor(1,7);
			LCD_WriteString("                      ");
			LCD_SetCursor(1,7);
			LCD_WriteString("Servo");
			LCD_WriteNumber(num);
		}
		if(flag_lcd==1)
		{
			LCD_SetCursor(0,4);
			LCD_WriteString("                      ");
			LCD_SetCursor(0,4);
			LCD_WriteNumber(num);
		}
		if(flag_ledon==1)
		{
			switch(num)
			{
				case 1:
				DIO_WritePin(LED1_PIN,HIGH);
				LCD_SetCursor(1,7);
				LCD_WriteString("                      ");
				LCD_SetCursor(1,7);
				LCD_WriteString("LED1 ON");
				break;
				case 2:
				DIO_WritePin(LED2_PIN,HIGH);
				LCD_SetCursor(1,7);
				LCD_WriteString("                      ");
				LCD_SetCursor(1,7);
				LCD_WriteString("LED2 ON");
				break;
				case 3:
				DIO_WritePin(LED3_PIN,HIGH);
				LCD_SetCursor(1,7);
				LCD_WriteString("                      ");
				LCD_SetCursor(1,7);
				LCD_WriteString("LED3 ON");
				break;
				case 4:
				DIO_WritePin(LED4_PIN,HIGH);
				LCD_SetCursor(1,7);
				LCD_WriteString("                      ");
				LCD_SetCursor(1,7);
				LCD_WriteString("LED4 ON");
				break;
				
			}
		}
		if(flag_ledoff==1)
		{
			switch(num)
			{
				case 1:
				DIO_WritePin(LED1_PIN,LOW);
				LCD_SetCursor(1,7);
				LCD_WriteString("                      ");
				LCD_SetCursor(1,7);
				LCD_WriteString("LED1 OFF");
				break;
				case 2:
				DIO_WritePin(LED2_PIN,LOW);
				LCD_SetCursor(1,7);
				LCD_WriteString("                      ");
				LCD_SetCursor(1,7);
				LCD_WriteString("LED2 OFF");
				break;
				case 3:
				DIO_WritePin(LED3_PIN,LOW);
				LCD_SetCursor(1,7);
				LCD_WriteString("                      ");
				LCD_SetCursor(1,7);
				LCD_WriteString("LED3 OFF");
				break;
				case 4:
				DIO_WritePin(LED4_PIN,LOW);
				LCD_SetCursor(1,7);
				LCD_WriteString("                      ");
				LCD_SetCursor(1,7);
				LCD_WriteString("LED4 OFF");
				break;
				
			}
		}
		
		num=0;
		flag2=0;
		
	}
	
}


static u8  string_to_integer(u8*str,u16*n) 
{
	u8 flag=0,i=0;

	if (str[0]=='-')
	{
		flag=1;
		i=1;
	}
	for(; str[i]; i++)
	{
		if(str[i]>='0'&&str[i]<='9')

		{
			*n=(*n*10)+str[i]-'0';
		}
		else
		{
			return 0;
		}
	}

	if(flag==1)
	{
		*n=*n*(-1);
	}
	return 1 ;
}