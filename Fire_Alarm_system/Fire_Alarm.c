#include "StdTypes.h"


#include <util/delay.h>

#include "DIO_Interface.h"
#include "ADC_Interface.h"
#include "Motors_Interface.h"
#include "LCD_Interface.h"
#include "KeyPad_Interface.h"
#include "Sensors_Interface.h"
#include "Potentiometer_Interface.h"


#include "Fire_Alarm_System.h"

static u16 temp_value=NULL;
static u16 smoke_value=NULL;
static u16 password=NULL;
static u8 count_password=NULL;

static Flag_Status flag_fine=OFF;
static Flag_Status flag_heat=OFF;
static Flag_Status flag_fire=OFF;
static Flag_Status flag_reset=OFF;
static Flag_Status flag_maintenance=OFF;


void Fire_Alarm_Init(void)
{
	DIO_Init();
	ADC_Init();
	LCD_Init();
	KEYPAD_Init();
	
	_delay_ms(400);
}

void Fire_Alarm_Normal(void)
{
	if(flag_maintenance==OFF)
	{
		// IF THERE IS NO MAINTENANCE GOING ON.
		
		temp_value=LM35_ReadTemp();
		
		//CHECK TEMP VALUE 
		
		if(temp_value<TEMP_UPNORMAL)
		{
			if(flag_reset==OFF)
			{
				flag_fine=ON;
				flag_heat=OFF;
			}
			
		}
		else if (temp_value>=TEMP_UPNORMAL)
		{
			smoke_value=Potentiometer_ReadVoltage();
			//POTENTIOMETER ACT LIKE SMOKE SENSOR,
			
			
			if(smoke_value>=SMOKE_FIRE_VALUE)
			{
				flag_fire=ON;
				flag_fine=OFF;
				flag_heat=OFF;
				flag_reset=ON;
				// THERE IS A FIRE , MAINTENANCE TEAM SHALL INTERRUPT.
			}
			if(flag_reset==OFF)
			{
				flag_heat=ON;
				flag_fine=OFF;
			}
			
			
		}
		
		
		if(flag_fine==ON)
		{
			// IF TEMP IS OKAY .
			
			LCD_WriteString("   ");
			LCD_SetCursor(0,0);
			LCD_WriteNumber(temp_value/10);  // to get Reading in C
			LCD_WriteString(" C");
			LCD_WriteString("  Fine");
			DIO_WritePin(HEAT_INDICATION_LED,LOW);
			DIO_WritePin(FIRE_INDICATION_LED,LOW);
			
		}
		if(flag_heat==ON)
		{
			// IF TEMP EXCEEDS NORMAL VALUE.
			
			LCD_WriteString("   ");
			LCD_SetCursor(0,0);
			LCD_WriteNumber(temp_value/10);
			LCD_WriteString(" C");
			LCD_WriteString("  Heat");
			DIO_WritePin(HEAT_INDICATION_LED,HIGH);
			
		}
		if(flag_fire==ON)
		{
			
			// IF FIRE HAPPENS BUT SMOKE HASN'T REACH THE EMERGENCY VALUE.
			
			LCD_WriteString("   ");
			LCD_SetCursor(0,0);
			LCD_WriteNumber(temp_value/10);  // to get Reading in C
			LCD_WriteString(" C");
			LCD_WriteString("  fire");
			DIO_WritePin(FIRE_INDICATION_LED,HIGH);
			DIO_WritePin(HEAT_INDICATION_LED,LOW);
			MOTOR_CCW(M1);
		}
		
	}

	
}


void Fire_Alarm_Emergency(void)
{
	// IF EMERGENCY CASE HAPPENS, SYSTEM REQUIRES MAINTENANCE INTERVENTION.
	// AFTER MAINETNANCE TEAM FINISH THIER WORK , SOMEONE SHALL ENTER PASSWORD TO RE-OPEN THE SYSTEM.
	
	if(flag_reset==ON)
	{
		u8 key= KEYPAD_Getkey();
		if(key=='c')
		{
			LCD_SetCursor(0,0);
			LCD_WriteString("Enter Password");
			_delay_ms(1000);
			LCD_Clear();
			LCD_WriteString("Pass= ");
			flag_maintenance=ON;
			flag_reset=OFF;
		}
	}
	if(flag_maintenance==ON)
	{
		u8 key= KEYPAD_Getkey();
		if(key!=NO_KEY)
		{
			if((key>='0'&&key<='9'))
			{
				LCD_WriteChar(key);
				password=(password*10)+(key-'0');
				count_password++;
			}
			
		}
		if(count_password==PASS_DIG_COUNT)
		{
			if (password==PASSWORD_MAINTENANCE)
			{
				flag_maintenance=OFF;
				flag_fire=OFF;
				flag_reset=OFF;
				password=NULL;
				count_password=NULL;
				MOTOR_Stop(M1);
				DIO_WritePin(FIRE_INDICATION_LED,LOW);
			}
			else
			{
				LCD_Clear();
				LCD_WriteString("Wrong Pass");
				_delay_ms(1000);
				LCD_Clear();
				LCD_WriteString("Enter Password");
				_delay_ms(1000);
				LCD_Clear();
				LCD_WriteString("Pass= ");
				flag_reset=OFF;
				password=NULL;
				count_password=NULL;
			}
		}
		
	}
}
