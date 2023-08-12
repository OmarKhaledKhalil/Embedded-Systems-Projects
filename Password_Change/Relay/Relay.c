#include "StdTypes.h"
#include "DIO_Interface.h"

#include "Relay_Interface.h"

void Relay_Init(void)
{
	 DIO_Init();
}

void Relay_On(Relay_type relay)
{
	DIO_WritePin(relay,HIGH);
}
void Relay_OFF(Relay_type relay)
{
	DIO_WritePin(relay,LOW);
}