#include "StdTypes.h"
#include "Utils.h"
#include "Motors_Interface.h"
#include "DIO_Interface.h"
#include "Car_Joystick_Control.h"

void Car_Joystick_Control_Init(void)
{
	MOTOR_Init();
}

void Car_Joystick_Control_Run(void)
{
	if(!DIO_ReadPin(FORWARD_BUTTON))
	{
		MOTOR_CW(M1);
		MOTOR_CW(M2);
		MOTOR_CW(M3);
		MOTOR_CW(M4);
	}
	else if(!DIO_ReadPin(BACKWARD_BUTTON))
	{
		MOTOR_CCW(M1);
		MOTOR_CCW(M2);
		MOTOR_CCW(M3);
		MOTOR_CCW(M4);
	}

	else if(!DIO_ReadPin(RIGHT_BUTTON))
	{
		MOTOR_CW(M1);
		MOTOR_CW(M2);
		MOTOR_CCW(M3);
		MOTOR_CCW(M4);
	}
	else if(!DIO_ReadPin(LEFT_BUTTON))
	{
		MOTOR_CCW(M1);
		MOTOR_CCW(M2);
		MOTOR_CW(M3);
		MOTOR_CW(M4);
	}
		else
		{
			MOTOR_Stop(M1);
			MOTOR_Stop(M2);
			MOTOR_Stop(M3);
			MOTOR_Stop(M4);
		}
}
