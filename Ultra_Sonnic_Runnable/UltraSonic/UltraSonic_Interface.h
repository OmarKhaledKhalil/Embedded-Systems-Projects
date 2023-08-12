#ifndef ULTRASONIC_INTERFACE_H_
#define ULTRASONIC_INTERFACE_H_

#define ULTRA_SONIC1_TRIG  PINC0
#define ULTRA_SONIC2_TRIG  PINC1
#define ULTRA_SONIC3_TRIG  PINC2
#define ULTRA_SONIC4_TRIG  PINC3

#define TOP OVF_VALUE

#define OVF_VALUE 65535  //255,65535,..

#define  MIN_PULSE_TIME_INMICRO  10

#define TIME_OUT_INMICRO 6000

#define TIME_BETWEEN_READINGS_INMILI 10

#define MAX_NEEDED_INTERRUPTS 2

#define TIME_TOGET_ONE_CM  58

typedef enum
{
	ULTRASONIC1=0,
	ULTRASONIC2=1,
	ULTRASONIC3=2,
	ULTRASONIC4=3,
	TOTAL_ULTRA_SONIC
	
}Ultra_Sonic_Type;

typedef enum
{
	NO_READ=0,
	READ_EXIST=1
	
}Read_Status;

void Ultra_Sonic_Init(Ultra_Sonic_Type u);

Read_Status Ultra_Sonic_GetRead(Ultra_Sonic_Type u,u16*distance);



#endif