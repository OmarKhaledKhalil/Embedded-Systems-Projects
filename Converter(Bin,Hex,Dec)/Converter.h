#ifndef CONVERTER_H_
#define CONVERTER_H_


#define DECIMAL '1'
#define HEXDECIMAL '2'
#define BINARY '3'
#define RESET 'c'
#define GENERATE_CONV '='

#define CONVERSION_FIRST_DATA_REPRESENTATION 0
#define CONVERSION_SECOND_DATA_REPRESENTATION 1
#define CONVERSION_LIMIT_CHOOSED 2

#define OFF 0
#define ON 1

typedef enum
{
	FIRST_DATA_TYPE=0,
	SECOND_DATA_TYPE
	
	}Converter_Parameters_type;

void Converter_Init(void);
void Converter_Selection(void);
void Converter_Operation(void);



#endif