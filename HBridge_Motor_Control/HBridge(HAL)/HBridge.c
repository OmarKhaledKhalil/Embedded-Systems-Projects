#include "StdTypes.h"
#include "Utils.h"

#include "DIO_Interface.h"
#include "HBridge.h"

void HBridge_Init(void)
{
	DIO_Init();
}

void HBridge_Run(Direction_type direction)
{
	DIO_WritePin(PIN_POWER,HIGH);
	
		switch(direction)
		{
			case DIRECTION_ONE :
			DIO_WritePin(PIN_POWER,HIGH);
			DIO_WritePin(PIN_1_A,HIGH);
			DIO_WritePin(PIN_1_B,HIGH);
			DIO_WritePin(PIN_2_A,LOW);
			DIO_WritePin(PIN_2_B,LOW);
			break;
			
			case DIRECTION_TWO:
			DIO_WritePin(PIN_POWER,HIGH);
			DIO_WritePin(PIN_2_A,HIGH);
			DIO_WritePin(PIN_2_B,HIGH);
			DIO_WritePin(PIN_1_A,LOW);
			DIO_WritePin(PIN_1_B,LOW);
			break;
		}

}

void HBridge_Stop(void)
{
	DIO_WritePin(PIN_POWER,LOW);
}