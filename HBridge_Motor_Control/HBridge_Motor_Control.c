#include "StdTypes.h"

#include "Utils.h"

#include "HBridge.h"
#include "DIO_Interface.h"
#include "EX_Interrupt.h"

#include "HBridge_Motor_Control.h"

static volatile Operation_Motor_type op =MOTOR_OFF;
static volatile Direction_Motor_type direc =CLOCK_WISE;

static void Operation (void)
{
	op=op^1;
}

static void Direction (void)
{
	direc=direc^1;
}

void HBridge_Motor_Control_Init(void)
{
	HBridge_Init();
	 EXI_Enable(EX_INT0);
	 EXI_Enable(EX_INT1);
	 EXI_TriggerEdge(EX_INT0,FALLING_EDGE);
	 EXI_TriggerEdge(EX_INT1,FALLING_EDGE);
	 
	 EXI_SetCallBack(EX_INT0,Operation);
	 EXI_SetCallBack(EX_INT1,Direction);
}

void HBridge_Motor_Control_Run(void)
{
	if(op==MOTOR_ON)
	{
		if(direc==CLOCK_WISE)
		{
			HBridge_Run(CLOCK_WISE);
		}
		else if (ANTI_CLOCK_WISE)
		{
			HBridge_Run(ANTI_CLOCK_WISE);
		}
	}
	else if (op==MOTOR_OFF)
	{
		HBridge_Stop();
	}
}