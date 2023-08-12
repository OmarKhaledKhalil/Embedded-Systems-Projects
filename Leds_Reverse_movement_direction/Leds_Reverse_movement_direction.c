#include "StdTypes.h"
#include "Utils.h"
#include "DIO_Interface.h"


#include "Leds_Reverse_movement_direction.h"

static volatile s16 level=FIRST_LAMP;

#include <util/delay.h>

void LEDS_REVERSE_MOVEMENT_DIRECTION_Init (void)
{
	DIO_Init(); //initiate DIO
DIO_WritePort(LEDS_PORT,level); //first lamp is on by default
}



void LEDS_REVERSE_MOVEMENT_DIRECTION_Run (void)
{
	if(!DIO_ReadPin(BUTTON_FORWARD))
	{
		while(!DIO_ReadPin(BUTTON_FORWARD))
		{
			level=level<<1; // shifting to next lamp in forward direction
			if(level>LAST_LAMP)
			{
				level=FIRST_LAMP; // when reach last lamp it resets to the first in same direction
			}
			DIO_WritePort(LEDS_PORT,level); // put value of variable in the led port
			_delay_ms(DELAY_VALUE_INMS); // delay to see the change
		}
		
	}
	
	if(!DIO_ReadPin(BUTTON_BACKWARD))
	{
		while(!DIO_ReadPin(BUTTON_BACKWARD))
		{
			level=level>>1; // shifting to next lamp in backward direction
			if(level<FIRST_LAMP)
			{
				level=LAST_LAMP;// when reach first lamp it resets to the last in same direction
			}
			DIO_WritePort(LEDS_PORT,level); // put value of variable in the led port
			_delay_ms(DELAY_VALUE_INMS); // delay to see the change
		}
		
	}
	
	
}