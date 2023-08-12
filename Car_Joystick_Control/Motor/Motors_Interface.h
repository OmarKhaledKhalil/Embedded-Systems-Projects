#ifndef MOTOR_INTERFACE_H_
#define MOTOR_INTERFACE_H_

typedef enum{
	M1,
	M2,
	M3,
	M4,
	TOTAL_NUMBER_MOTORS
}MOTOR_type;

typedef enum
{
	IN1,
	IN2,
	EN,
	TOTAL_MOTOR_PINS
	
}MOTOR_PIN_NUMBERS;


void MOTOR_Init(void);

void MOTOR_Stop(MOTOR_type motor);

void MOTOR_CW(MOTOR_type motor);

void MOTOR_CCW(MOTOR_type motor);

#endif