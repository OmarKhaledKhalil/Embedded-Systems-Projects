#include "StdTypes.h"
#include "Utils.h"

#include "DIO_Interface.h"
#include "LCD_Interface.h"
#include "KeyPad_Interface.h"
#include "Converter.h"

#include <util/delay.h>


static u8 flag_operation_choice=CONVERSION_FIRST_DATA_REPRESENTATION;//ready to take first input
static u8 flag_start_convertion=OFF; // flag to start the conversion after choosing
static s32 number=0; // Ram Storage to store number in order to convert
static u8 conv_operation_type_array[CONVERSION_LIMIT_CHOOSED]={0,0}; // array to carry use choice character to choose operation
static Converter_Parameters_type i=FIRST_DATA_TYPE; // indices to this array

void Converter_Init(void)
{
	DIO_Init();
	LCD_Init();
	KEYPAD_Init();
	LCD_Clear();
	LCD_WriteString("Welcome To Omar");
	LCD_SetCursor(1,0);
	LCD_WriteString("   Converter");
	_delay_ms(1500);
	LCD_Clear();
	LCD_WriteString("Please Choose");
	LCD_SetCursor(1,0);
	LCD_WriteString(" Your Operation");
	_delay_ms(1500);
	LCD_Clear();
}


void Converter_Selection(void)
{
	if(flag_operation_choice<CONVERSION_LIMIT_CHOOSED)
	{
		u8 press=KEYPAD_Getkey();
		
		if(press==DECIMAL||press==HEXDECIMAL||press==BINARY)
		{
			flag_operation_choice++; // increment if user has chosen operation.
			conv_operation_type_array[i]=press; // put operation type in the array.
			i++;
		}
		
		if(flag_operation_choice==CONVERSION_FIRST_DATA_REPRESENTATION)
		{
			//choose first data type in conversion.
			LCD_WriteString("  Convert From");
			LCD_SetCursor(1,0);
			LCD_WriteString("1-Dec,2-Hex,3-Bi");
		}
		if(flag_operation_choice==CONVERSION_SECOND_DATA_REPRESENTATION)
		{
			//choose second data type in conversion.
			
			LCD_SetCursor(0,0);
			LCD_WriteString("   Convert  To");
			LCD_SetCursor(1,0);
			LCD_WriteString("1-Dec,2-Hex,3-Bi");
		}
		if(flag_operation_choice==CONVERSION_LIMIT_CHOOSED)
		{
			flag_start_convertion=ON; // user has chosen everything, so conversion starts.
			LCD_Clear();
		}
		
	}
	
}
void Converter_Operation(void)
{
	//This part of CODE Contains Problem Solving Tricks to Convert HEX , Bin , Decimals
	// characters to REAL Number to be saved in RAM in the Variable Number 
	//then Represent the 2 data types in once 
	//depending to String to number conversion , number to string conversions.
	if(flag_start_convertion==ON)
	{
		u8 press=0;
		
		if(conv_operation_type_array[0]==DECIMAL)
		{
			if(conv_operation_type_array[1]==DECIMAL)
			{
				LCD_WriteString("Dec:");
				LCD_SetCursor(1,0);
				LCD_WriteString("Dec:");
				
				while(press!=RESET)
				{
					press=KEYPAD_Getkey();
					
					if(press>='0'&&press<='9')
					{
						LCD_SetCursor(1,5);
						LCD_WriteString("                ");
						number=(number*10)+(press-'0');
						LCD_SetCursor(0,5);
						LCD_WriteString("                 ");
						LCD_SetCursor(0,5);
						LCD_WriteNumber(number);
					}
					if(press==GENERATE_CONV)
					{
						LCD_SetCursor(1,5);
						LCD_WriteNumber(number);
						number=0;
						
					}
					
				}
				number=0;
				flag_start_convertion=OFF;
				flag_operation_choice=CONVERSION_FIRST_DATA_REPRESENTATION;
				i=FIRST_DATA_TYPE;
				LCD_Clear();
				
			}
		}
		if(conv_operation_type_array[0]==DECIMAL)
		{
			if(conv_operation_type_array[1]==HEXDECIMAL)
			{
				LCD_WriteString("Dec:");
				LCD_SetCursor(1,0);
				LCD_WriteString("Hex:");
				
				while(press!=RESET)
				{
					press=KEYPAD_Getkey();
					if(press>='0'&&press<='9')
					{
						LCD_SetCursor(1,5);
						LCD_WriteString("                ");
						number=(number*10)+(press-'0');
						LCD_SetCursor(0,5);
						LCD_WriteString("                 ");
						LCD_SetCursor(0,5);
						LCD_WriteNumber(number);
					}
					if(press==GENERATE_CONV)
					{
						LCD_SetCursor(1,5);
						LCD_WriteHex(number);
						number=0;
						
					}
					
				}
				number=0;
				flag_start_convertion=OFF;
				flag_operation_choice=CONVERSION_FIRST_DATA_REPRESENTATION;
				i=FIRST_DATA_TYPE;
				LCD_Clear();
			}
		}
		if(conv_operation_type_array[0]==DECIMAL)
		{
			if(conv_operation_type_array[1]==BINARY)
			{
				LCD_WriteString("Dec:");
				LCD_SetCursor(1,0);
				LCD_WriteString("Bin:");
				
				while(press!=RESET)
				{
					press=KEYPAD_Getkey();
					if(press>='0'&&press<='9')
					{
						LCD_SetCursor(1,5);
						LCD_WriteString("                ");
						number=(number*10)+(press-'0');
						LCD_SetCursor(0,5);
						LCD_WriteString("                 ");
						LCD_SetCursor(0,5);
						LCD_WriteNumber(number);
					}
					if(press==GENERATE_CONV)
					{
						LCD_SetCursor(1,5);
						LCD_WriteBinary(number);
						number=0;
						
					}
					
				}
				number=0;
				flag_start_convertion=OFF;
				flag_operation_choice=CONVERSION_FIRST_DATA_REPRESENTATION;
				i=FIRST_DATA_TYPE;
				LCD_Clear();
			}
		}
		if(conv_operation_type_array[0]==BINARY)
		{
			
			if(conv_operation_type_array[1]==DECIMAL)
			{
				LCD_WriteString("Bin:");
				LCD_SetCursor(1,0);
				LCD_WriteString("Dec:");
				
				while(press!=RESET)
				{
					press=KEYPAD_Getkey();
					if(press=='0'||press=='1')
					{
						LCD_SetCursor(1,5);
						LCD_WriteString("                ");
						number=(number*2)+(press-'0'+0);
						LCD_SetCursor(0,5);
						LCD_WriteString("                 ");
						LCD_SetCursor(0,5);
						LCD_WriteBinary(number);
					}
					if(press==GENERATE_CONV)
					{
						LCD_SetCursor(1,5);
						LCD_WriteNumber(number);
						number=0;
						
					}
					
				}
				number=0;
				flag_start_convertion=OFF;
				flag_operation_choice=CONVERSION_FIRST_DATA_REPRESENTATION;
				i=FIRST_DATA_TYPE;
				LCD_Clear();
			}
		}
		if(conv_operation_type_array[0]==BINARY)
		{
			
			if(conv_operation_type_array[1]==BINARY)
			{
				LCD_WriteString("Bin:");
				LCD_SetCursor(1,0);
				LCD_WriteString("Bin:");
				
				while(press!=RESET)
				{
					press=KEYPAD_Getkey();
					if(press=='0'||press=='1')
					{
						LCD_SetCursor(1,5);
						LCD_WriteString("                ");
						number=(number*2)+(press-'0');
						LCD_SetCursor(0,5);
						LCD_WriteString("                 ");
						LCD_SetCursor(0,5);
						LCD_WriteBinary(number);
					}
					if(press==GENERATE_CONV)
					{
						LCD_SetCursor(1,5);
						LCD_WriteBinary(number);
						number=0;
						
					}
					
				}
				number=0;
				flag_start_convertion=OFF;
				flag_operation_choice=CONVERSION_FIRST_DATA_REPRESENTATION;
				i=FIRST_DATA_TYPE;
				LCD_Clear();
			}
		}
		if(conv_operation_type_array[0]==BINARY)
		{
			
			if(conv_operation_type_array[1]==HEXDECIMAL)
			{
				LCD_WriteString("Bin:");
				LCD_SetCursor(1,0);
				LCD_WriteString("Hex:");
				
				while(press!=RESET)
				{
					press=KEYPAD_Getkey();
					if(press=='0'||press=='1')
					{
						LCD_SetCursor(1,5);
						LCD_WriteString("                ");
						number=(number*2)+(press-'0');
						LCD_SetCursor(0,5);
						LCD_WriteString("                 ");
						LCD_SetCursor(0,5);
						LCD_WriteBinary(number);
					}
					if(press==GENERATE_CONV)
					{
						LCD_SetCursor(1,5);
						LCD_WriteHex(number);
						number=0;
						
					}
					
				}
				number=0;
				flag_start_convertion=OFF;
				flag_operation_choice=CONVERSION_FIRST_DATA_REPRESENTATION;
				i=FIRST_DATA_TYPE;
				LCD_Clear();
			}
		}
		if(conv_operation_type_array[0]==HEXDECIMAL)
		{
			
			if(conv_operation_type_array[1]==DECIMAL)
			{
				LCD_WriteString("Hex:");
				LCD_SetCursor(1,0);
				LCD_WriteString("Dec:");
				
				while(press!=RESET)
				{
					press=KEYPAD_Getkey();
					if(press>='0'&&press<='9')
					{
						LCD_SetCursor(1,5);
						LCD_WriteString("                ");
						number=(number*16)+(press-'0');
						LCD_SetCursor(0,5);
						LCD_WriteString("                 ");
						LCD_SetCursor(0,5);
						LCD_WriteHex(number);
					}
					if(press>='A'&&press<='F')
					{
						LCD_SetCursor(1,5);
						LCD_WriteString("                ");
						number=(number*16)+((press-'A')+10);
						LCD_SetCursor(0,5);
						LCD_WriteString("                 ");
						LCD_SetCursor(0,5);
						LCD_WriteHex(number);
					}
					if(press==GENERATE_CONV)
					{
						LCD_SetCursor(1,5);
						LCD_WriteNumber(number);
						number=0;
						
					}
					
				}
				number=0;
				flag_start_convertion=OFF;
				flag_operation_choice=CONVERSION_FIRST_DATA_REPRESENTATION;
				i=FIRST_DATA_TYPE;
				LCD_Clear();
			}
		}
		if(conv_operation_type_array[0]==HEXDECIMAL)
		{
			
			if(conv_operation_type_array[1]==HEXDECIMAL)
			{
				LCD_WriteString("Hex:");
				LCD_SetCursor(1,0);
				LCD_WriteString("Hex:");
				
				while(press!=RESET)
				{
					press=KEYPAD_Getkey();
					if(press>='0'&&press<='9')
					{
						LCD_SetCursor(1,5);
						LCD_WriteString("                ");
						number=(number*16)+(press-'0');
						LCD_SetCursor(0,5);
						LCD_WriteString("                 ");
						LCD_SetCursor(0,5);
						LCD_WriteHex(number);
					}
					if(press>='A'&&press<='F')
					{
						LCD_SetCursor(1,5);
						LCD_WriteString("                ");
						number=(number*16)+((press-'A')+10);
						LCD_SetCursor(0,5);
						LCD_WriteString("                 ");
						LCD_SetCursor(0,5);
						LCD_WriteHex(number);
					}
					if(press==GENERATE_CONV)
					{
						LCD_SetCursor(1,5);
						LCD_WriteHex(number);
						number=0;
						
					}
					
				}
				number=0;
				flag_start_convertion=OFF;
				flag_operation_choice=CONVERSION_FIRST_DATA_REPRESENTATION;
				i=FIRST_DATA_TYPE;
				LCD_Clear();
			}
		}
		if(conv_operation_type_array[0]==HEXDECIMAL)
		{
			
			if(conv_operation_type_array[1]==BINARY)
			{
				LCD_WriteString("Hex:");
				LCD_SetCursor(1,0);
				LCD_WriteString("Bin:");
				
				while(press!=RESET)
				{
					press=KEYPAD_Getkey();
					if(press>='0'&&press<='9')
					{
						LCD_SetCursor(1,5);
						LCD_WriteString("                ");
						number=(number*16)+(press-'0');
						LCD_SetCursor(0,5);
						LCD_WriteString("                 ");
						LCD_SetCursor(0,5);
						LCD_WriteHex(number);
					}
					if(press>='A'&&press<='F')
					{
						LCD_SetCursor(1,5);
						LCD_WriteString("                ");
						number=(number*16)+((press-'A')+10);
						LCD_SetCursor(0,5);
						LCD_WriteString("                 ");
						LCD_SetCursor(0,5);
						LCD_WriteHex(number);
					}
					if(press==GENERATE_CONV)
					{
						LCD_SetCursor(1,5);
						LCD_WriteBinary(number);
						number=0;
						
					}
					
				}
				number=0;
				flag_start_convertion=OFF;
				flag_operation_choice=CONVERSION_FIRST_DATA_REPRESENTATION;
				i=FIRST_DATA_TYPE;
				LCD_Clear();
			}
		}
		
	}
	
}