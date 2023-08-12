#include "StdTypes.h"


#include "Timers.h"

#include "ServoMotor_Interface.h"


void Servo_Motor_Init()
{
	Timer1_Init(TIMER1_FASTPWM_OCRA_TOP_MODE,TIMER1_SCALER_8);
	Timer1_OCRB1Mode(OCRB_NON_INVERTING);
	SET_OCR1A(20000);
}

void Servo_Motor_Direction(ServoMotor_Type servo, u16 angle)
{
	switch(servo)
	{
		case SERVO_MOTOR_1 :
		angle=(((u32)angle*SLOPE)/MAX_ANGLE)+STARTING_TON_VALUE;
		SERVO1_PWM(angle);
		break;
		case SERVO_MOTOR_2 :
		angle=(((u32)angle*SLOPE)/MAX_ANGLE)+STARTING_TON_VALUE;
		SERVO2_PWM(angle);
		break;
		case SERVO_MOTOR_3 :
		angle=(((u32)angle*SLOPE)/MAX_ANGLE)+STARTING_TON_VALUE;
		SERVO3_PWM(angle);
		break;
		case SERVO_MOTOR_4 :
		angle=(((u32)angle*SLOPE)/MAX_ANGLE)+STARTING_TON_VALUE;
		SERVO4_PWM(angle);
		break;
	}
}