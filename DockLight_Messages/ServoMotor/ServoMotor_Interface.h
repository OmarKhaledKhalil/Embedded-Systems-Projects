#ifndef SERVOMOTOR_INTERFACE_H_
#define SERVOMOTOR_INTERFACE_H_


#define SERVO1_PWM  SET_OCR1B
#define SERVO2_PWM  SET_OCR1A
#define SERVO3_PWM  SET_OCR1B
#define SERVO4_PWM  SET_OCR1A

#define SLOPE 1000

#define MAX_ANGLE 180

#define STARTING_TON_VALUE 999

typedef enum
{
	SERVO_MOTOR_1=0,
	SERVO_MOTOR_2,
	SERVO_MOTOR_3,
	SERVO_MOTOR_4
	
}ServoMotor_Type;

void Servo_Motor_Init();

void Servo_Motor_Direction(ServoMotor_Type Servo, u16 Angle);

#endif