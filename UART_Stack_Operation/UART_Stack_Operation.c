#include "StdTypes.h"
#include "Utils.h"


#include "DIO_Interface.h"
#include "USART_Interface.h"
#include "EX_Interrupt.h"
#include "LCD_Interface.h"
#include "UART_Service.h"
#include "UART_Stack_Operation.h"

static u8 uart_stack[STACK_SIZE];
static volatile u8 stack_pointer=0;
static volatile u8 flag1=0;
static volatile u8 flag2=0;
static volatile u8 flag3=0;

static void UART_Stack_Handler(void)
{
	if(stack_pointer==STACK_SIZE)
	{
		flag1=1;
	}	
	else
	{
		uart_stack[stack_pointer]=UART_ReceiveNoBlock();
		stack_pointer++;
	}
	
}

static void UART_Pop_Handler(void)
{
	if(stack_pointer==0)
	{
		flag2=1;
	}
	else
	{
		flag3=1;
	}
}

void UART_Stack_Operation_Init(void)
{
	DIO_Init();
	LCD_Init();
	UART_RX_InterruptEnable();
	UART_RX_SetCallBack(UART_Stack_Handler);
	EXI_TriggerEdge(EX_INT1,FALLING_EDGE);
	EXI_SetCallBack(EX_INT1,UART_Pop_Handler);
}

void UART_Stack_Pop(void)
{
	
	if(flag1==1)
	{
		UART_RX_InterruptDisable();
		UART_SendString("Stack Full");
		flag1=0;
	}
	if(flag2==1)
	{
		LCD_WriteString("              ");
		LCD_SetCursor(0,3);
		LCD_WriteString("Stack Empty");
		
		flag2=0;
	}
	if(flag3==1)
	{
		LCD_SetCursor(0,3);
		LCD_WriteString("                     ");
		LCD_SetCursor(0,7);
		LCD_WriteChar(uart_stack[stack_pointer-1]);
		stack_pointer--;
		flag3=0;
		UART_RX_InterruptEnable();
	}
	
}