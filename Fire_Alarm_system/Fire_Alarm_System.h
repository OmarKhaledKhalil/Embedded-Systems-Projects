#ifndef FIRE_ALARM_SYSTEM_H_
#define FIRE_ALARM_SYSTEM_H_

#define HEAT_INDICATION_LED     PINC6
#define FIRE_INDICATION_LED        PINC7
#define TEMP_UPNORMAL   500 // TEMP FROM FINE STATUS TO OVER HEAT STATUS.
#define SMOKE_FIRE_VALUE       3  // 3 VOLTS VALUE FROM POTENIOMETER WHICH ACT LIKE SMOKE SENSOR.
#define PASSWORD_MAINTENANCE       12345 // PASSWORD TO BE ENETERED AFTER MAINTENANCE DONE.
#define PASS_DIG_COUNT        5 

typedef enum
{
	OFF=0,
	ON=1
	
}Flag_Status;

void Fire_Alarm_Init(void);
void Fire_Alarm_Normal(void);
void Fire_Alarm_Emergency(void);



#endif