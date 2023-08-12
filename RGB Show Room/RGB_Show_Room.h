

#ifndef RGB_SHOW_ROOM_H_
#define RGB_SHOW_ROOM_H_

#define MAX_Interrupts 100
#define ON 1
#define OFF 0
#define NULL 0

typedef enum
{
	UnDone=0,
	Done=1
	
}Show_Room_Status;


Show_Room_Status RGB_Show_Room(colour_type colour1,colour_type colour2);
void RGB_Show_Room_Init(void);

#endif