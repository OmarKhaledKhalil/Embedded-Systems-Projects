#include "StdTypes.h"
#include "Utils.h"

#include <util/delay.h>

#include "DIO_Interface.h"
#include "SevenSegment_Interface.h"
#include "Stop_Watch.h"

static void helper(); //static function to help in the main functions of the application.

static u8 start=STARTING_NUM; //default starting number of stopwatch.
static u8 current=STARTING_NUM; //value while operation , to be edited.

static StopWatch_Status_Type run_pause_and_incrementby10_pin=OFF;
static StopWatch_Status_Type reset_and_incrementby1_pin=OFF;
static StopWatch_Status_Type setting_pin=OFF;


static StopWatch_Operation_Status status_flag = PAUSE;
static StopWatch_Mode_Type current_mode=RUN;

void Stop_Watch_Init(void)
{
	DIO_Init();
	SeventSegment_Init();
}

void Stop_Watch_Operation(void)
{
	helper();
	if(current_mode==RUN)
	{
		if(status_flag==RESUME)
		{
			u16 i;
			SeventSegment_Display_MULX(L1,L2,current); // show starting number.
			while (current>NULL)
			{
				
				for(i=0;i<425;i++)
				{
					SeventSegment_Display_MULX(L1,L2,current); // show current number.
					helper(); // periodic check helper function to check buttons.
				}
				
				if(status_flag==PAUSE||current_mode==SET)
				{
					
					break; // break when set mode is operated // or while pausing.
				}
				
				current--; // decrement of current value shown.
			}
		}
		else if (status_flag==PAUSE)
		{
			SeventSegment_Display_MULX(L1,L2,current); // show current value while pause.
		}
	}
	
	
	
}

void Stop_Watch_Setting(void)
{
	//handling settings
	if(current_mode==SET)
	{
		
		SeventSegment_Display_MULX(L1,L2,start); // show starting default value.
		if(!DIO_ReadPin(BUTT_RUN_PAUSE))
		{
			
			if(run_pause_and_incrementby10_pin==OFF)
			{
				// increment 10th value.
				if(start/10==9)
				{
					start=start%10; 
				}
				else
				{
					start=start+10;
				}
				run_pause_and_incrementby10_pin=ON;
				_delay_ms(HALF_SECOND);
				
				current=start;
			}

			
		}
		else
		{
			run_pause_and_incrementby10_pin=OFF;
		}
		if(!DIO_ReadPin(BUTT_RESET))
		{
			// increment.
			
			if(run_pause_and_incrementby10_pin==OFF)
			{
				if(start%10==9)
				{
					start=start-start%10;
				}
				else
				{
					start=start+1;
				}
				run_pause_and_incrementby10_pin=ON;
				_delay_ms(HALF_SECOND);
				
				current=start;
				
			}

			
		}
		else
		{
			run_pause_and_incrementby10_pin=OFF;
		}
		
	}

	
}


static void helper()
{
	//periodic check function to see if user push any button of the 3 button.
	//according to the pushed button operation change.
	
	if(!DIO_ReadPin(BUTT_RUN_PAUSE)&&current_mode==RUN)
	{
		if(run_pause_and_incrementby10_pin==OFF)
		{
			status_flag=status_flag^1;//toggle status (between run and pause)
			
			run_pause_and_incrementby10_pin=ON;
			
		}

		
	}
	else
	{
		run_pause_and_incrementby10_pin=OFF;
	}
	
	if(!DIO_ReadPin(BUTT_RESET)&&current_mode==RUN)
	{
		if(reset_and_incrementby1_pin==OFF)
		{
			status_flag=PAUSE;
			current=start;
			reset_and_incrementby1_pin=ON;
			
		}
	}
	else
	{
		reset_and_incrementby1_pin=OFF;
	}
	
	if(!DIO_ReadPin(BUTT_SETTING))
	{
		if(setting_pin==OFF)
		{
			current_mode=current_mode^1; //toggle mode (between stop to do setting , re-start)
			status_flag=PAUSE;
			setting_pin=ON;
		}
	}
	else
	{
		setting_pin=OFF;
	}

}