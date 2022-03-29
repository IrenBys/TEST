/**
  ******************************************************************************
  * @file    main.c
  * @author  Irina Bystrova
  * @brief   This file contains the main function to manage the following 
  *          functionalities:
	*           + creates a pair of RX/TX UART buffers 
  *           + initializes the peripheral modules
  *           + writes all bytes from the RX buffer to the TX buffer
  *           + iinitializes transmition start
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/

#include "stm32f4xx.h"
#include "main.h"
#include "usart.h"

/* Functions -----------------------------------------------------------------*/

int main()
{	
	/* creates a pair of RX/TX UART buffers with lenght = MAX_FIFO_LENGHT */
	FifoCreatePairFIFO(&(pUartRxFIFO), MAX_FIFO_LENGHT, &(pUartTxFIFO), MAX_FIFO_LENGHT);
	
	/* initializes the peripheral modules */
  USART_init();
	LED_ini();

	while(1)
	{		 		 
		/* writes all bytes from FIFO to FIFO */
		FifoFIFO2FIFO(pUartRxFIFO, pUartTxFIFO);
				
		/* if there are bytes in the TxFIFO buffer, starts sending */
		UartTransmite();	  																							
	}			
}
