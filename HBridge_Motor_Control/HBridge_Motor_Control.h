#ifndef HBRIDGE_MOTOR_CONTROL_H_
#define HBRIDGE_MOTOR_CONTROL_H_

typedef enum
{
	MOTOR_OFF=0,
	MOTOR_ON
	
}Operation_Motor_type;

typedef enum
{
	CLOCK_WISE=0,
	ANTI_CLOCK_WISE
	
}Direction_Motor_type;

void HBridge_Motor_Control_Init(void);

void HBridge_Motor_Control_Run(void);



#endif 