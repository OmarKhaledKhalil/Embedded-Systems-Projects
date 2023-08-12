#include "StdTypes.h"
#include "Utils.h"
#include "UltraSonic_Interface.h"
#include "Ultra_Sonic_Runnable.h"
#include "LCD_Interface.h"
#include <util/delay.h>

 u16 live_read[TOTAL_ULTRA_SONIC];
 u16 read[TOTAL_ULTRA_SONIC];	 
	
static u8 i=NULL;

void Ultra_Sonic_Runnable(void)
{
	Ultra_Sonic_GetRead(i,&live_read[i]);
	
	i++;
	if(i==TOTAL_ULTRA_SONIC)
	{
		read[ULTRASONIC1]=live_read[ULTRASONIC1];
		read[ULTRASONIC2]=live_read[ULTRASONIC2];
		read[ULTRASONIC3]=live_read[ULTRASONIC3];
		read[ULTRASONIC4]=live_read[ULTRASONIC4];
		i=NULL;
	}
	
	
}

void UltraSonic_Runnable_GetRead(Ultra_Sonic_Type u , u16*distance)
{
	switch(u)
	{
		case ULTRASONIC1:
		*distance=read[ULTRASONIC1];
		break;
		
		case ULTRASONIC2:
	    *distance=read[ULTRASONIC2];
		break;
		
		case ULTRASONIC3:
		*distance=read[ULTRASONIC3];
		break;
		
		case ULTRASONIC4:
		*distance=read[ULTRASONIC4];
		break;
	}
}

void UltraSonic_Runnable_GetReadAll(u16*distances)
{
	distances[ULTRASONIC1]=read[ULTRASONIC1];
	distances[ULTRASONIC2]=read[ULTRASONIC2];
	distances[ULTRASONIC3]=read[ULTRASONIC3];
	distances[ULTRASONIC4]=read[ULTRASONIC4];
}