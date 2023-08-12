#ifndef SEVENSEGMENT_INTERFACE_H_
#define SEVENSEGMENT_INTERFACE_H_

#define SEGMENT1_PORT  PORTA
#define SEGMENT2_PORT  PORTA
#define SEGMENT1_POWER PORTC
#define SEGMENT2_POWER PORTC

#define S1_LEDA  PINA1
#define S1_LEDB  PINA2
#define S1_LEDC  PINA3
#define S1_LEDD  PINA4
#define S1_LEDE  PINA5
#define S1_LEDF  PINA6
#define S1_LEDG  PINA7
#define S1_LEDDP PINB0
#define S1_OP    PINC6

#define S2_LEDA  PINA1
#define S2_LEDB  PINA2
#define S2_LEDC  PINA3
#define S2_LEDD  PINA4
#define S2_LEDE  PINA5
#define S2_LEDF  PINA6
#define S2_LEDG  PINA7
#define S2_LEDDP PINB0
#define S2_OP    PINC7

typedef enum
{
	L1,
	L2,
	TOTAL_SEGMENTS_NUMBER
}Segment_Type;



void SeventSegment_Init(void);
void SeventSegment_Display(Segment_Type segment,u8 n);
void SeventSegment_Display_MULX(Segment_Type segment_1,Segment_Type segment_2,u8 n);


#endif