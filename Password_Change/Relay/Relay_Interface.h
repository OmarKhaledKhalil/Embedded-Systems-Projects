#ifndef RELAY_INTERFACE_H_
#define RELAY_INTERFACE_H_

typedef enum
{
	R1=0,
	R2
	
}Relay_type;

#define R1 PINC0
#define R2 PINC1

void Relay_Init(void);
void Relay_On(Relay_type relay);
void Relay_OFF(Relay_type relay);


#endif 