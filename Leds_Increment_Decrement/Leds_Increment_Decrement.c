#include "StdTypes.h"
#include "Utils.h"
#include "DIO_Interface.h"
#include "EX_Interrupt.h"

#include "Leds_Increment_Decrement.h"

static volatile s16 level=LEAST_VALUE;

static void Helper_Func_INT0(void)
{
	level++;
}

static void Helper_Func_INT1(void)
{
	level--;
}


void LEDS_INCREMENT_DECREMENT_Init(void)
{
	  EXI_Enable(EX_INT0);
	  
	  EXI_Enable(EX_INT1);
	  
	 EXI_TriggerEdge(EX_INT0,RISING_EDGE); //External Interrupt occurs when Pin reads ground
	 
	 EXI_TriggerEdge(EX_INT1,RISING_EDGE); //External Interrupt occurs when Pin reads ground
	 
	 EXI_SetCallBack(EX_INT0,Helper_Func_INT0); //set Call back , to increment the variable
	 
	 EXI_SetCallBack(EX_INT1,Helper_Func_INT1); //set Call back , to decrement the variable
	 
}

void LEDS_INCREMENT_DECREMENT_Run(void)
{
	if(level<LEAST_VALUE)
	{
		level=MAX_VALUE;  // If The value decrement till reach value less than 0;
	}
	if(level>MAX_VALUE)
	{
		level=LEAST_VALUE;    // If The value increment till reach value less than 0;
	}
	DIO_WritePort(LEDS_PORT,level); //Right the Port by the Value of The variable
	
}