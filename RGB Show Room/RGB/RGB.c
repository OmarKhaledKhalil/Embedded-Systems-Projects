#include "StdTypes.h"
#include "RGB_Interface.h"
#include "Timers.h"



const u8 colours_array[TOTAL_NUMBER_OF_COLOURS][RED_GREEN_BLUE]=
{{0,0,0},{255,255,255},{255,0,0},
 {0,255,0},{0,0,255},{255,255,0},
 {0,255,255},{255,0,255},{192,192,192},
 {128,128,128},{128,0,0},{128,128,0},
 {0,128,0},{128,0,128},{0,128,128},{0,0,128}};

void RGB_Colour_Show(colour_type colour)
{
	
	RED_PIN(colours_array[colour][RED]);
	GREEN_PIN(colours_array[colour][GREEN]);
	BLUE_PIN(colours_array[colour][BLUE]-1);
}

void RGB_Colour_Show2(u8 c1, u8 c2, u8 c3)
{
	
	RED_PIN(c1);
	GREEN_PIN(c2);
	BLUE_PIN(c3-1);
}