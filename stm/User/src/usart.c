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

pFIFO_s pUartRxFIFO = NULL;			// pointer to FIFO struct for RX_UART
pFIFO_s pUartTxFIFO = NULL;			// pointer to FIFO struct for TX_UART

/* Functions -----------------------------------------------------------------*/

/**
  * @brief  USART3 Handler provides receive mode
  * @param  None
  * @retval None
  */
void USART3_IRQHandler(void)
{
    char *Buf;
    uint8_t i = 0, Len;
    
    if(USART_GetITStatus(USART3, USART_IT_RXNE) == SET) 		
    {		
        LED_BLUE_ON;
        USART_ClearITPendingBit(USART3, USART_IT_RXNE);		
        if (FifoSetNBytesToFIFO(pUartRxFIFO, Buf, Len))
        {
            LED_RED_ON;
            for(i = 0; i < len; i++)
            {
                Buf[i] = USART_ReceiveData(USART3);                			
            }	
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
    char *Buf;
    uint8_t len;
    uint8_t i;

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
            LED_ORANGE_ON;
            do
            {
                USART_SendData(USART2, Buf[i]);
            }
            while(FifoGetByteFromFIFO(pUartTxFIFO, Buf) > 0)
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
    char byte;
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
