#ifndef HBRIDGE_H_
#define HBRIDGE_H_

#define PIN_POWER PINC0
#define PIN_1_A PINC1
#define PIN_1_B PINC2
#define PIN_2_A PINC3
#define PIN_2_B PINC4

typedef enum
{
	OFF=0,
	ON
}Operation_type;

typedef enum
{
	DIRECTION_ONE=0,
	DIRECTION_TWO
}Direction_type;

void HBridge_Init(void);

void HBridge_Run(Direction_type direction);

void HBridge_Stop(void);

#endif