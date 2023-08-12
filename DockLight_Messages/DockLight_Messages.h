#ifndef DOCKLIGHT_MESSAGES_H_
#define DOCKLIGHT_MESSAGES_H_

#define LED1_PIN PINC0
#define LED2_PIN PINC1
#define LED3_PIN PINC2
#define LED4_PIN PINC3

void Docklight_Messages_Seperate(void);
void Docklight_Messages_Runnable(void);
u8  string_to_integer(u8*str,u16*n);




#endif