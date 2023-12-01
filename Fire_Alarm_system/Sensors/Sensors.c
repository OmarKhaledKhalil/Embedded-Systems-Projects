#include "StdTypes.h"
#include "DIO_Interface.h"
#include "ADC_Interface.h"


#include "Sensors_Interface.h"


void LM35_Init(void)
{
	
}

u16  LM35_ReadTemp(void)
{
	u16 volt =ADC_ReadVolt(LM35_CHANNEL); 
	u16 temp=volt;
	return temp;
}

void MPX_Init(void)
{
	
}
u16 MPX_PRESSURE_READ(void)
{
	
	u16 volt = ADC_ReadVolt(MPX_CHANNEL); //M.VOLT
	
	u16 pressure = ((220*(u32)volt)/1000)+100; //K.PA
	
	return pressure;
	
	
}	



u16 POT_Read(void)
{
	u16 adc=ADC_Read(POT_CHANNEL);
	u16 pot=((u32)100*adc)/RESOLUTION;
	return pot;
}