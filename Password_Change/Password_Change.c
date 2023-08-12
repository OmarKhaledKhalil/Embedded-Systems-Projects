#include "StdTypes.h"
#include "Utils.h"

#include "DIO_Interface.h"
#include "NVM_Interface.h"


#include "LCD_Interface.h"
#include "KeyPad_Interface.h"
#include "Relay_Interface.h"


#include "Password_change.h"

#include <util/delay.h>


static u8 ram_mirror_password=0;
static u8 count_password_digits=0;
static u8 count_wrong_attempts=0;
static u8 user_input_password=0;

static u8 flag_right=OFF;
static u8 flag_wrong=OFF;
static u8 flag_edit=OFF;


void Pass_Reset(void)
{
	if(!DIO_ReadPin(RESET_BUTTON))
	{
		//if user pushed the reset button. 
		//Password backs to default case.
		NVM_Write(2,0);
		DIO_WritePin(LED_RESET_PASS,HIGH);
		LCD_Clear();
		LCD_WriteString("PASS Reseted");
		_delay_ms(1500);
		LCD_Clear();
		while(!DIO_ReadPin(RESET_BUTTON));
	}
	
}


void Pass_Init(void)
{
	DIO_Init();
	LCD_Init();
	KEYPAD_Init();
	
	u8 check=NVM_Read(2);
	//If user changed the default password , we should take RAM Mirror from NVM.
	//IF user hasn't Changed the default Password, we should take Default password as RAM Mirror.
	if(check==1)
	{
		ram_mirror_password=NVM_Read(1);
	}
	else
	{
		NVM_Write(PASS_ADD,PASS);
		ram_mirror_password=PASS;
	}
	
}

void Pass_Entering(void)
{
	if(flag_right==ON||flag_wrong==ON)
	{
		
	}
	else
	{
		LCD_SetCursor(0,0);
		LCD_WriteString("Enter Password");
		LCD_SetCursor(1,0);
		
		if(count_password_digits<3)
		{
			//Because password in only 3-digits.
			
			u8 key= KEYPAD_Getkey();
			if(key!=NO_KEY)
			{
				if((key>='0'&&key<='9'))
				{
					//Converting input characters into Number ( Decimal ).
					user_input_password=(user_input_password*10)+(key-'0');
					LCD_WriteNumber(user_input_password);
					count_password_digits++;
					//To count password Digits
				}
				
			}
		}
		else
		{
			if(user_input_password==ram_mirror_password)
			{
				//Entered password by user is the same of RAM Mirror password.
				flag_right=ON;
				LCD_Clear();
			}
			else
			{
				//Entered password by user is not the same of RAM Mirror password.
				flag_wrong=ON;
				LCD_Clear();
			}
			
		}
		
	}
	
	
	
}

void Pass_Correct(void)
{
	static u8 key=0;
	if(flag_right==ON&&flag_edit==OFF)
	{
		LCD_WriteString("Right Pass");
		
		LCD_SetCursor(1,0);
		LCD_WriteString("1 to change pass");
		
		Relay_On(R1);
		//Operate the Motor by the relay
		
		DIO_WritePin(PINC1,HIGH);
		
		//Operate the lamp.
		
		user_input_password=0;
		count_password_digits=0;
		
		LCD_SetCursor(0,0);
		key= KEYPAD_Getkey();
		
		
		if(key==CHANGE_PASSWORD_OPTION_CHAR)
		{
			
			
			flag_edit=ON;
			//User wants to edit the Password.
			
			user_input_password=0;
			count_password_digits=0;
			LCD_Clear();
			
		}
		
	}
	if(flag_right==ON&&flag_edit==2)
	{
		LCD_WriteString("Sys on");
		LCD_SetCursor(1,0);
		LCD_WriteString("Welcome");
		
		Relay_On(R1);
		//Operate the Motor.
		
		DIO_WritePin(LED_RIGHT_PASS,HIGH);
		//Operate the LED.
		
		user_input_password=0;
		count_password_digits=0;
		LCD_SetCursor(0,0);
	}
	
	
}

void Pass_Uncorrect(void)
{
	if(flag_wrong==ON&&count_wrong_attempts<MAX_TRIALS)
	{
		//Give trials for another attempts if user input wrong password.
		LCD_WriteString("Wrong Pass");
		LCD_SetCursor(1,0);
		LCD_WriteString("Try again");
		_delay_ms(1000);
		count_wrong_attempts++;
		flag_wrong=OFF;
		user_input_password=0;
		count_password_digits=0;
		LCD_Clear();
	}
	if(flag_wrong==1&&count_wrong_attempts==MAX_TRIALS)
	{
		//If user exceeds max trials number , he should wait 5 sec to re-enter Password.
		LCD_WriteString("Wrong Pass");
		LCD_SetCursor(1,0);
		LCD_WriteString("Wait 5 sec");
		_delay_ms(5000);
		flag_wrong=OFF;
		user_input_password=0;
		count_password_digits=0;
		count_wrong_attempts=0;
		LCD_Clear();
	}
}

void Pass_Editing(void)
{
	//enter new pass to be saved in NVM , and be new RAM Mirror.
	if(flag_edit==ON)
	{
		LCD_SetCursor(0,0);
		LCD_WriteString("Enter New Pass");
		LCD_SetCursor(1,0);
		u8 key2= KEYPAD_Getkey();
		if(key2!=NO_KEY)
		{
			if((key2>='0'&&key2<='9'))
			{
				//Take Input Numbers Character and change it into real decimal number.
				
				user_input_password=(user_input_password*10)+(key2-'0');
				LCD_WriteNumber(user_input_password);
				count_password_digits++;
			}
			if(count_password_digits==3)
			{
				//Max Password digits are 3 digits.
				
				_delay_ms(500);
				flag_edit=2;
				NVM_Write(1,user_input_password);
				ram_mirror_password=user_input_password;
				NVM_Write(2,1);
				LCD_Clear();
				LCD_WriteString("Changing done");
				_delay_ms(1000);
				LCD_Clear();
				
			}
			
		}
	}
	
}


