#include "StdTypes.h"
#include "Utils.h"
#include "DIO_Interface.h"
#include "UltraSonic_Interface.h"



#include "Timers.h"


#include <util/delay.h>

static u32 t1,t2;
static u32 time_total;
static volatile u8 flag=NULL;

static volatile u32 counter=NULL;
static  u32 counter_copy=NULL;

static void counter_OVF(void)
{
	counter++;
}

static void dis(void)
{
	if(flag==NULL)
	{
		t1=Timer1_Get_ICR();
		Timer1_InputCaptureEdge(FALLING);
		flag=MAX_NEEDED_INTERRUPTS-1;
		
	}
	else if (flag==MAX_NEEDED_INTERRUPTS-1)
	{
		t2=Timer1_Get_ICR();
		counter_copy=counter;
		flag=MAX_NEEDED_INTERRUPTS;
	}
	
	
}

void Ultra_Sonic_Init(Ultra_Sonic_Type u)
{
	
	switch(u)
	{
		case ULTRASONIC1:
		Timer1_ICU_SetCallBack(dis);
		Timer1_OVF_SetCallBack(counter_OVF);
		DIO_WritePin(ULTRA_SONIC1_TRIG,HIGH);
		_delay_us(MIN_PULSE_TIME_INMICRO);
		DIO_WritePin(ULTRA_SONIC1_TRIG,LOW);
		break;
		
		case ULTRASONIC2:
		Timer1_ICU_SetCallBack(dis);
		Timer1_OVF_SetCallBack(counter_OVF);
		DIO_WritePin(ULTRA_SONIC2_TRIG,HIGH);
		_delay_us(MIN_PULSE_TIME_INMICRO);
		DIO_WritePin(ULTRA_SONIC2_TRIG,LOW);
		break;
		
		case ULTRASONIC3:
		Timer1_ICU_SetCallBack(dis);
		Timer1_OVF_SetCallBack(counter_OVF);
		DIO_WritePin(ULTRA_SONIC3_TRIG,HIGH);
		_delay_us(MIN_PULSE_TIME_INMICRO);
		DIO_WritePin(ULTRA_SONIC3_TRIG,LOW);
		break;
		
		case ULTRASONIC4:
		Timer1_ICU_SetCallBack(dis);
		Timer1_OVF_SetCallBack(counter_OVF);
		DIO_WritePin(ULTRA_SONIC4_TRIG,HIGH);
		_delay_us(MIN_PULSE_TIME_INMICRO);
		DIO_WritePin(ULTRA_SONIC4_TRIG,LOW);
		break;
	}
		
}

Read_Status Ultra_Sonic_GetRead(Ultra_Sonic_Type u,u16*distance)
{
	u16 c=NULL;
	Read_Status status=NO_READ;
	
	switch(u)
	{
		case ULTRASONIC1:
		Ultra_Sonic_Init(ULTRASONIC1);
	    Timer1_InputCaptureEdge(RISING);
		Timer1_ICU_InterruptEnable();
		counter=NULL;
		while(flag<MAX_NEEDED_INTERRUPTS&&c<TIME_OUT_INMICRO)
		{
			c++;
			_delay_us(1);
		}
		if(flag==MAX_NEEDED_INTERRUPTS)
		{
			time_total=(((u32)(t2-t1))+((u32)counter_copy*TOP));
			*distance=time_total/TIME_TOGET_ONE_CM;
			
			status=READ_EXIST;
			flag=NULL;
		}
		
		
	
		break;
		
		case ULTRASONIC2:
		Ultra_Sonic_Init(ULTRASONIC2);
		Timer1_InputCaptureEdge(RISING);
		Timer1_ICU_InterruptEnable();
		counter=NULL;
		while(flag<MAX_NEEDED_INTERRUPTS&&c<TIME_OUT_INMICRO)
		{
			c++;
			_delay_us(1);
		}
		if(flag==MAX_NEEDED_INTERRUPTS)
		{
			time_total=(((u32)(t2-t1))+((u32)counter_copy*TOP));
			*distance=time_total/TIME_TOGET_ONE_CM;
			flag=NULL;
			status=READ_EXIST;
			
		}
		
		
		
		break;
		
		case ULTRASONIC3:
		Ultra_Sonic_Init(ULTRASONIC3);
		Timer1_InputCaptureEdge(RISING);
		Timer1_ICU_InterruptEnable();
		counter=NULL;
		while(flag<MAX_NEEDED_INTERRUPTS&&c<TIME_OUT_INMICRO)
		{
			c++;
			_delay_us(1);
		}
		if(flag==MAX_NEEDED_INTERRUPTS)
		{
			time_total=(((u32)(t2-t1))+((u32)counter_copy*TOP));
			*distance=time_total/TIME_TOGET_ONE_CM;
			flag=NULL;
			status=READ_EXIST;
			
		}
		
	
		break;
		
		case ULTRASONIC4:
		Ultra_Sonic_Init(ULTRASONIC4);
		Timer1_InputCaptureEdge(RISING);
		Timer1_ICU_InterruptEnable();
		counter=NULL;
		while(flag<MAX_NEEDED_INTERRUPTS&&c<TIME_OUT_INMICRO)
		{
			c++;
			_delay_us(1);
		}
		if(flag==MAX_NEEDED_INTERRUPTS)
		{
			time_total=(((u32)(t2-t1))+((u32)counter_copy*TOP));
			*distance=time_total/TIME_TOGET_ONE_CM;
			flag=NULL;
			status=READ_EXIST;
			
		}
		
		
		break;
	}
	_delay_ms(TIME_BETWEEN_READINGS_INMILI);
	return status;
}
