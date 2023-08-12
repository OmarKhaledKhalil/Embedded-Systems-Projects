#include "StdTypes.h"

#include "DIO_Interface.h"
#include "Motors_Interface.h"
#include "Motors_Cfg.h"


extern DIO_Pin_type MotorPinsArray[TOTAL_NUMBER_MOTORS][TOTAL_MOTOR_PINS];

void MOTOR_Init(void)
{
	DIO_Init();
}

void MOTOR_Stop(MOTOR_type motor)
{
	DIO_WritePin(MotorPinsArray[motor][IN1],LOW);
	DIO_WritePin(MotorPinsArray[motor][IN2],LOW);
}

void MOTOR_CW(MOTOR_type motor)
{
	DIO_WritePin(MotorPinsArray[motor][IN1],HIGH);
	DIO_WritePin(MotorPinsArray[motor][IN2],LOW);
}

void MOTOR_CCW(MOTOR_type motor)
{
	DIO_WritePin(MotorPinsArray[motor][IN1],LOW);
	DIO_WritePin(MotorPinsArray[motor][IN2],HIGH);
}