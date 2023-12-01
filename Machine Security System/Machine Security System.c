#include "StdTypes.h"
#include "Utils.h"

#include "DIO_Interface.h"
#include "NVM_Interface.h"
#include "EX_Interrupt.h"

#include "LCD_Interface.h"
#include "KeyPad_Interface.h"
#include "Relay_Interface.h"


#include "Password.h"

#include <util/delay.h>


static u8 pass=0; 
static u8 count_password=0;
static u8 count_wrong=0;
static u8 password=0;

static u8 flag_right=0;
static u8 flag_wrong=0;
static u8 flag_edit=0;


void Pass_Reset(void)
{
	NVM_Write(2,0);
	DIO_WritePin(PINC0,HIGH);
}


void Pass_Init(void)
{
	u8 check=NVM_Read(2);
	if(check==1)
	{
		pass=NVM_Read(1);
	}
	else
	{
		NVM_Write(PASS_ADD,PASS);
		pass=PASS;
	}
	
}

void Pass_Entering(void)
{
	if(flag_right==1||flag_wrong==1)
	{
		
	}
	else
	{
		LCD_SetCursor(0,0);
		LCD_WriteString("Enter Password");
		LCD_SetCursor(1,0);
		
		if(count_password<3)
		{
			u8 key= KEYPAD_Getkey();
			if(key!=NO_KEY)
			{
				if((key>='0'&&key<='9'))
				{
					
					password=(password*10)+(key-'0');
					LCD_WriteNumber(password);
					count_password++;
				}
				
			}
		}
		else
		{
			if(password==pass)
			{
				flag_right=1;
				LCD_Clear();
			}
			else
			{
				flag_wrong=1;
				LCD_Clear();
			}
			
		}
		
	}
	
	
	
}

void Pass_Correct(void)
{
	static u8 key=0;
	if(flag_right==1&&flag_edit==0)
	{
		LCD_WriteString("Right Pass");
		LCD_SetCursor(1,0);
		LCD_WriteString("1 to change pass");
		Relay_On(R1);
		DIO_WritePin(PINC1,HIGH);
		password=0;
		count_password=0;
		LCD_SetCursor(0,0);
		key= KEYPAD_Getkey();
		if(key=='1')
		{
			
			
			flag_edit=1;
			password=0;
			count_password=0;
			LCD_Clear();
			
		}
		
	}
	if(flag_right==1&&flag_edit==2)
	{
		LCD_WriteString("Sys on");
		LCD_SetCursor(1,0);
		LCD_WriteString("Welcome");
		Relay_On(R1);
		DIO_WritePin(PINC1,HIGH);
		password=0;
		count_password=0;
		LCD_SetCursor(0,0);
	}
	
	
}

void Pass_Uncorrect(void)
{
	if(flag_wrong==1&&count_wrong<MAX_TRIALS)
	{
		LCD_WriteString("Wrong Pass");
		LCD_SetCursor(1,0);
		LCD_WriteString("Try again");
		_delay_ms(1000);
		count_wrong++;
		flag_wrong=0;
		password=0;
		count_password=0;
		LCD_Clear();
	}
	if(flag_wrong==1&&count_wrong==MAX_TRIALS)
	{
		LCD_WriteString("Wrong Pass");
		LCD_SetCursor(1,0);
		LCD_WriteString("Wait 5 sec");
		_delay_ms(5000);
		flag_wrong=0;
		password=0;
		count_password=0;
		count_wrong=0;
		LCD_Clear();
	}
}

void Pass_Editing(void)
{
	if(flag_edit==1)
	{
		LCD_SetCursor(0,0);
	   LCD_WriteString("Enter New Pass");
		LCD_SetCursor(1,0);
		u8 key2= KEYPAD_Getkey();
		if(key2!=NO_KEY)
		{
			if((key2>='0'&&key2<='9'))
			{
				
				password=(password*10)+(key2-'0');
				LCD_WriteNumber(password);
				count_password++;
			}
			if(count_password==3)
			{
				
				_delay_ms(500);
				flag_edit=2;
				NVM_Write(1,password);
				pass=password;
				NVM_Write(2,1);
				LCD_Clear();
				LCD_WriteString("Changing done");
				_delay_ms(1000);
				LCD_Clear();
				
			}
			
		}
	}
	
}


