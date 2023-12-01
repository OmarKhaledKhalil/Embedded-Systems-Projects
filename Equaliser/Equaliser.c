#include "StdTypes.h"


#include "DIO_Interface.h"
#include "ADC_Interface.h"

#include "LCD_Interface.h"
#include "Sensors_Interface.h"

#include "Equaliser.h"

#include <util/delay.h>

static u16 percentage_value;
static u8 lcd_cursor=NULL;

void Equaliser_init(void)
{
	DIO_Init();
	ADC_Init();
	LCD_Init();
	
	//Creating custom character to send to LCD RAM.
	u8 pattern1[]={
		0x0E,
		0x0E,
		0x0E,
		0x0E,
		0x0E,
		0x0E,
		0x0E,
		0x0E
	};
	LCD_CustomChar(0,pattern1); //Save the custom character to LCD RAM, in location 0.
}

void Equaliser_Run(void)
{
	percentage_value=POT_Read();
	
	if ((percentage_value/10)>=lcd_cursor)
	{
		LCD_SetCursor(0,lcd_cursor);
		LCD_WriteChar(0);
		lcd_cursor++;
		//Increment Cursor of screen till equalize cursor variable, each increment
		//inserting the custom character we have send to the LCD RAM.
	}
	else if((percentage_value/10)<lcd_cursor)
	{
		LCD_SetCursor(0,lcd_cursor);
		LCD_WriteChar(' ');
		lcd_cursor--;
		//Decrement Cursor of screen till equalize cursor variable, each decrement
		//inserting space on screen to erase the location on screen.
	}
	
	
	
	// In this part we write the percentage value on the screen at the next line 
	// at the screen.
	
	if(percentage_value<10)
	{
		LCD_SetCursor(1,0);
		LCD_WriteNumber(percentage_value);
		
		LCD_WriteString(" %");
	}
	else
	{
		LCD_SetCursor(1,0);
		LCD_WriteNumber(percentage_value);
		LCD_WriteString("%");
	}
	
}
