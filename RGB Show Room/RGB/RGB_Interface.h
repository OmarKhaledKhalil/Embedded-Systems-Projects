#ifndef RGB_INTERFACE_H_
#define RGB_INTERFACE_H_

#define RED_PIN SET_OCR1A
#define GREEN_PIN SET_OCR1B
#define BLUE_PIN SET_OCR0

typedef enum
{
	RED_LED=0,
	GREEN_LED,
	BLUE_LED,
	RED_GREEN_BLUE
	};

typedef enum
{
	BLACK=0,
	WHITE,
	RED,
	GREEN,
	BLUE,
	YELLOW,
	CYAN,
	PINK,
	SILVER,
	GREY,
	BROWN,
	OLIVE,
	DARK_GREEN,
	PURPLE,
	TEAL,
	NAVY,
	TOTAL_NUMBER_OF_COLOURS
	}colour_type;

extern const u8 colours_array[TOTAL_NUMBER_OF_COLOURS][RED_GREEN_BLUE];
void RGB_Colour_Show(colour_type colour);
void RGB_Colour_Show2(u8 c1, u8 c2, u8 c3);

#endif