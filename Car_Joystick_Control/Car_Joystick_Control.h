#ifndef CAR_JOYSTICK_CONTROL_H_
#define CAR_JOYSTICK_CONTROL_H_

#define FORWARD_BUTTON PIND0
#define BACKWARD_BUTTON PIND1
#define RIGHT_BUTTON PIND2
#define LEFT_BUTTON PIND3

void Car_Joystick_Control_Init(void);

void Car_Joystick_Control_Run(void);



#endif