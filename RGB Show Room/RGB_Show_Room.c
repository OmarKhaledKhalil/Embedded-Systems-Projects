

#include "StdTypes.h"
#include "Utils.h"
#include "RGB_Interface.h"
#include "RGB_Show_Room.h"
#include "Timers.h"

#include "LCD_Interface.h"

#include <util/delay.h>

static volatile u8 c1=NULL;
static volatile u8 c2=NULL;
static volatile u8 c3=NULL;
static u8 c4=NULL;
static u8 c5=NULL;
static u8 c6=NULL;
static u8 flag_first_time=OFF;
static u16 inte=NULL;


static u8 flag3=OFF;

void f_RGB(void)
{
	if(flag3==OFF)
	{
		
	}
	else
	{
		
		inte ++;
		if(inte>=MAX_Interrupts)
		{
			if(c1<c4)
			{
				c1++;
				
			}
			else if(c1>c4)
			{
				c1--;
				
			}
			if(c2<c5)
			{
				c2++;
				
			}
			else if(c2>c5)
			{
				c2--;
				
			}
			if(c3<c6)
			{
				c3++;
			}
			else if (c3>c6)
			{
				c3--;
			}
			inte=NULL;
		}
		
	}
	if(c1==c4&&c2==c5&&c3==c6)
	{
		flag3=OFF;

	}
}

void RGB_Show_Room_Init(void)
{
	Timer1_OVF_SetCallBack(f_RGB);
}


Show_Room_Status RGB_Show_Room(colour_type colour1,colour_type colour2)
{
	Show_Room_Status status=UnDone;
	if(flag_first_time==OFF)
	{
		RGB_Colour_Show(colour1);
		c1=colours_array[colour1][0];
		c2=colours_array[colour1][1];
		c3=colours_array[colour1][2];
		c4=colours_array[colour2][0];
		c5=colours_array[colour2][1];
		c6=colours_array[colour2][2];
		
		flag_first_time=ON;
		flag3=ON;
		
	}
	else if(flag_first_time==ON)
	{
		RGB_Colour_Show2(c1,c2,c3);
		
	}
	
	if(flag3==0)
	{
		flag_first_time=OFF;
		status=Done;
		_delay_ms(100);
		
	}
	
	
	return status;
	
}

