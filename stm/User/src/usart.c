/**
  ******************************************************************************
  * @file    usart.c
  * @author  Irina Bystrova
  * @brief   This file provides functions to manage the following 
  *          functionalities:           
  *           + USART3 Handler provides receive mode
  *           + USART2 Handler provides transmite mode
	*           + The function provides the begining of transmition
  ******************************************************************************
  */
	
/* Includes ------------------------------------------------------------------*/

#include "usart.h"

/* Variables ----------------------------------------------------------------*/

pFIFO_s pUartRxFIFO;			// pointer to FIFO struct for RX_UART
pFIFO_s pUartTxFIFO;			// pointer to FIFO struct for TX_UART

/* Functions -----------------------------------------------------------------*/

/**
  * @brief  USART3 Handler provides receive mode
  * @param  None
  * @retval None
  */
void USART3_IRQHandler(void)
{
	UCHAR *Buf;
	UINT i = 0;
	
	if(USART_GetITStatus(USART3, USART_IT_RXNE) == SET) 		
	{
		
		USART_ClearITPendingBit(USART3, USART_IT_RXNE);
		Buf[i] = USART_ReceiveData(USART3);
		if (FifoSetByteToFIFO(pUartRxFIFO, *Buf) == TRUE)
		{
			LED_RED_ON;
		}	
	}		
}

/**
  * @brief  USART2 Handler provides transmite mode
  * @param  None
  * @retval None
  */
void USART2_IRQHandler(void)
{
	UCHAR *Buf;
	UINT len = 0;
	UINT i = 0;

	if(USART_GetITStatus(USART2, USART_IT_TXE) == SET) 		
	{
		USART_ClearITPendingBit(USART2, USART_IT_TXE);
		if (len == FifoGetNBytesFromFIFO(pUartTxFIFO, Buf, PACK_LEN))
		{
			USART_ITConfig(USART2, USART_IT_TXE, DISABLE); 	
			LED_GREEN_ON;
		}
		else
		{			
			//FifoGetByteFromFIFO(pUartTxFIFO, Buf);
			USART_SendData(USART2, Buf[i]);
			LED_GREEN_OFF;
		}		
	}
}

/**
  * @brief  If there are bytes in the TX buffer, start transmition
  * @param  None
  * @retval None
  *
  */
void UartTransmite(void)
{ 
	UCHAR byte;
	if(!(USART_GetITStatus(USART2, USART_IT_TXE) == SET))
	{
		if(FifoKeyhitFIFO(pUartTxFIFO))											
		{	
			LED_BLUE_ON;			 
			USART_SendData(USART2, byte);											 
			USART_ITConfig(USART2, USART_IT_TXE, ENABLE);			
		}  
	}		
}






