#ifndef STOP_WATCH_H_
#define STOP_WATCH_H_

#define BUTT_RUN_PAUSE   PIND2
#define BUTT_RESET    PIND3
#define BUTT_SETTING    PIND4

#define NULL      0
#define STARTING_NUM 60

#define SECOND 1000
#define HALF_SECOND 500

typedef enum
{
	OFF=0,
	ON=1
	
}StopWatch_Status_Type;

typedef enum
{
	PAUSE=0,
	RESUME=1
	
}StopWatch_Operation_Status;

typedef enum
{
	RUN=0,
	SET=1
	
}StopWatch_Mode_Type;


void Stop_Watch_Init(void);
void Stop_Watch_Operation(void);
void Stop_Watch_Setting(void);



#endif
