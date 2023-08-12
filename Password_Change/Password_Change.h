#ifndef PASSWORD_CHANGE_H_
#define PASSWORD_CHANGE_H_

#define PASS 123
#define PASS_ADD 1
#define MAX_TRIALS 2

#define CHANGE_PASSWORD_OPTION_CHAR '1'

#define RESET_BUTTON PINC3

#define LED_RIGHT_PASS PINC1
#define LED_RESET_PASS PINC0



typedef enum
{
	OFF=0,
	ON
}flag_status;

void Pass_Reset(void);
void Pass_Init(void);
void Pass_Entering(void);
void Pass_Correct(void);
void Pass_Uncorrect(void);
void Pass_Editing(void);



#endif