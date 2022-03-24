#ifndef USART_INIT_H
#define USART_INIT_H
//-----------------------------------------------------------------------------------------------------
#include "main.h"
//-----------------------------------------------------------------------------------------------------
// set USART parameters
#define BAUD_RATE   115200
#define PARITY_BIT  USART_Parity_No
#define WORD_LENGHT USART_WordLength_8b
#define STOP_BIT		USART_StopBits_1
//-----------------------------------------------------------------------------------------------------
// initializate USART and LED modules
void USART_init(void);
void LED_ini(void);
//-----------------------------------------------------------------------------------------------------

#endif
