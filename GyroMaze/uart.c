#include "PIN_LPC17xx.h"
#include "GPIO_LPC17xx.h"

int isQueueFull()
{
	return !(LPC_UART0->LSR & (1<<5));
}

int isReceiverReady()
{
	return (LPC_UART0->LSR & 1);
}

void writeString(const char* string)
{
	int i=0;
	for(; string[i] != '\0'; i++)
	{
		if(isQueueFull())
		{
			i--;
			continue;
		}
		LPC_UART0->THR = string[i];
	}
	
	LPC_UART0->THR = '\r';
	LPC_UART0->THR = '\n';
}

void initUart()
{
	//A=1, M=15, B=115200, DL=13,56
	LPC_UART0->LCR = (1<<7) | 3;
	LPC_UART0->DLL = 13;
	LPC_UART0->DLM = 0;
	LPC_UART0->FDR = 1 | (15 << 4);
	LPC_UART0->LCR = 3;
	
	PIN_Configure(0, 3, 1, PIN_PINMODE_TRISTATE, 0);
	PIN_Configure(0, 2, 1, PIN_PINMODE_TRISTATE, 0);
}

void initTimer0()
{
	LPC_TIM0->PR = 0;
	LPC_TIM0->MR0 = (((SystemCoreClock / 2) / 4) - 1); 
	LPC_TIM0->MCR = 3;
	LPC_TIM0->TCR = 1;
	
	NVIC_EnableIRQ(TIMER0_IRQn);
}


void initRTC()
{
	LPC_RTC->CCR = 1;
	LPC_RTC->ILR = 1;
	LPC_RTC->CIIR = 1;
	
	NVIC_EnableIRQ(RTC_IRQn);
}

