#include "StdTypes.h"

#include "ADC_Interface.h"

#include "Potentiometer_Interface.h"


void Potentiometer_Init(void)
{
	
}

u8 Potentiometer_ReadVoltage(void)
{
	u16 volt= ADC_ReadVolt(POT_CHANNEL);
	volt=volt/1000;
	return volt;
}
