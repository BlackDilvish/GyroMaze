#ifndef UART_H
#define UART_H

bool isQueueFull();
bool isReceiverReady();
void writeString(const char* string);
void initUart();
void initTimer0();
void TIMER0_IRQHandler();
void initRTC();
void RTC_IRQHandler();

#endif