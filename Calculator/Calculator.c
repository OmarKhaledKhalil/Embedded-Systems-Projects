#include "StdTypes.h"
#include "Utils.h"

#include "DIO_Interface.h"
#include "LCD_Interface.h"
#include "KeyPad_Interface.h"
#include "Calculator.h"

static u8 flag_operator_access=OFF;
static u8 flag_new_calculation=OFF;
static u8 flag_negative_sign_before_first_number=ON;
static u8 neg_flag=OFF;
static u8 flag_undifined=OFF;


static s16 number[2]={0,0}; // global array to store the 2 input numbers
static s32 result=0; // global variable to store result
static u8 i=FIRST_NUMBER; //indicator
static u8 op=0; // variable to save the operator character input


#include <util/delay.h>

void Calculator_Init(void)
{
	DIO_Init();
	LCD_Init();
	KEYPAD_Init();
	LCD_Clear;
	LCD_WriteString("Welcome To Omar");
	LCD_SetCursor(1,0);
	LCD_WriteString("   Calculator");
	_delay_ms(1000);
	LCD_Clear();
	LCD_WriteString("Enter two Numbers");
	LCD_SetCursor(1,0);
	LCD_WriteString("1st,OP,2nd");
	_delay_ms(1500);
	LCD_Clear();
	LCD_WriteString("OP are (+,-,x,/)");
	_delay_ms(1500);
	LCD_Clear();
}

void Calculator_Run(void)
{
	u8 press=KEYPAD_Getkey();
	
	if(press=='-')
	{
		if(flag_new_calculation==1||flag_operator_access==ON)
		{
			// if it is an accumulative or a new operation ignores
		}
		else
		{
			LCD_WriteChar(press);
			neg_flag=ON; // to give a hint that user input first number as a negative
			
		}
		
	}
	
	if((press>='0'&&press<='9'))
	{
		if(flag_new_calculation==ON)
		{
			number[FIRST_NUMBER]=0;
			number[SECOND_NUMBER]=0;
			flag_new_calculation=OFF;
			i=FIRST_NUMBER;
			LCD_Clear();
		}
		LCD_WriteChar(press); //represent the number accumulative on the screen.
		number[i]=(number[i]*10)+press-'0'; //get the value and add to number in decimal.
		flag_operator_access=ON; // give access to enter operator.
		
	}

	if((press=='*'||press=='/'||press=='+'||press=='-')&&(flag_operator_access==ON))
	
	{
		if(i==FIRST_NUMBER)
		{
			flag_operator_access=OFF; // to prevent input many operators same time.
			LCD_WriteChar(press); // to represent operator on screen.
			op=press; // to save the operator.
			i++; // to jump to next number.
		}
		
	}
	else if((press=='*'||press=='/'||press=='+'||press=='-')&&(flag_new_calculation==ON))
	
	{
		LCD_Clear();
		LCD_WriteNumber(result); // show last result as a new number in calculation.
		flag_new_calculation=OFF; // to close this block from repeating.
		LCD_WriteChar(press); // to show the operator on screen.
		op=press; // to save the operator in the variable to use.
		
	}
	if((press=='=')&&(i==SECOND_NUMBER))
	{
		if(neg_flag==ON)
		{
			number[FIRST_NUMBER]=number[FIRST_NUMBER]*-1; // if the first input number had a negative sign.
			neg_flag=OFF; // to close this section from repeating.
		}
		// execute the operation
		if(op=='*')
		{
			result=number[FIRST_NUMBER]*number[SECOND_NUMBER]; // mult operation execution.
		}
		else if(op=='/')
		{
			if(number[SECOND_NUMBER]==0)
			{
				flag_undifined=ON;
			}
			result=number[FIRST_NUMBER]/number[SECOND_NUMBER]; // divide operation execution.
		}
		else if(op=='-')
		{
			result=number[FIRST_NUMBER]-number[SECOND_NUMBER]; // subtract operation execution.
		}
		else if(op=='+')
		{
			result=number[FIRST_NUMBER]+number[SECOND_NUMBER]; // plus operation execution.
		}
		
		if(flag_undifined==ON)
		{
			LCD_Clear();
			LCD_WriteString("Undefined !!");
			_delay_ms(1500);
			LCD_Clear();
			number[FIRST_NUMBER]=0;
			number[SECOND_NUMBER]=0;
			i=FIRST_NUMBER;
			flag_operator_access=OFF;
			flag_undifined=OFF;
			
		}
		else
		{
			
			LCD_SetCursor(1,0);
			LCD_WriteString("                              ");
			LCD_SetCursor(1,0);
			LCD_WriteNumber(result);
			LCD_SetCursor(0,0);
			LCD_WriteString("                              ");
			LCD_SetCursor(0,0); // tricks to put the result on proper place on screen
			i=SECOND_NUMBER; // points to second number
			number[FIRST_NUMBER]=result; // if you want to use last result as a new input(optional)
			number[SECOND_NUMBER]=0;
			flag_operator_access=OFF;
			flag_new_calculation=ON;
		}

		
	}
	if(press=='c')
	{
		if(flag_new_calculation==ON)
		{
			i=FIRST_NUMBER;
			flag_new_calculation=OFF; 
		}
		LCD_Clear();
		number[FIRST_NUMBER]=0;
		number[SECOND_NUMBER]=0;
		
		// to clear everything happens before 
	}
}