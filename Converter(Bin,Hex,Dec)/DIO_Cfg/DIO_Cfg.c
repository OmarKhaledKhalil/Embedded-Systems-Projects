#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"

#include "DIO_Interface.h"
#include "DIO_Private.h"

const DIO_PinStatus_type PinsStatusArray[TOTAL_PINS]=
{
	OUTPUT, //PINA0
	OUTPUT, //PINA1
	OUTPUT, //PINA2
	OUTPUT, //PINA3
	OUTPUT, //PINA4
	OUTPUT, //PINA5
	OUTPUT, //PINA6
	OUTPUT, //PINA7
	OUTPUT, //PINB0
	OUTPUT, //PINB1
	OUTPUT, //PINB2
	OUTPUT, //PINB3
	OUTPUT, //PINB4
	OUTPUT, //PINB5
	OUTPUT, //PINB6
	OUTPUT, //PINB7
	OUTPUT, //PINC0
	OUTPUT, //PINC1
	OUTPUT, //PINC2
	OUTPUT, //PINC3
	OUTPUT, //PINC4
	OUTPUT, //PINC5
	OUTPUT, //PINC6
	OUTPUT, //PINC7
	INPULL, //PIND0
	INPULL, //PIND1
	INPULL, //PIND2--INT0
	INPULL, //PIND3--INT1
   INPULL, //PIND4
	INPULL, //PIND5
	INPULL, //PIND6
	INPULL  //PIND7
	
	
	};

