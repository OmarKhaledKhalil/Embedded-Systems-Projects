
#ifndef SENSORS_INTERFACE_H_
#define SENSORS_INTERFACE_H_

#define ADC_RESOLUTION 1024
#define LM35_MAX_READ  1500
#define LM35_CHANNEL CH_0
#define MPX_CHANNEL CH_7
#define POT_CHANNEL CH_0

void LM35_Init(void);
u16  LM35_ReadTemp(void);

void MPX_Init(void);
u16 MPX_PRESSURE_READ(void);
u16 POT_Read(void);



#endif