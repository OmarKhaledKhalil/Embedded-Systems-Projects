#ifndef RELAY_INTERFACE_H_
#define RELAY_INTERFACE_H_

typedef enum
{
	R1=0,
	R2
	
}Relay_type;

#define R1 PINC4
#define R2 PINC3


void Relay_On(Relay_type relay);
void Relay_OFF(Relay_type relay);


#endif 