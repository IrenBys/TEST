#include "usart.h"

pFIFO_s pUartRxFIFO = NULL;			// pointer to FIFO struct for RX_UART
pFIFO_s pUartTxFIFO = NULL;			// pointer to FIFO struct for TX_UART

//-------------------------------------------------------------------------------------------------------------
//Rx mode for USART1
void USART1_IRQHandler(void)
{
	UCHAR *Buf;
	UINT i = 0;
	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET) 		
	{
		
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		Buf[i] = USART_ReceiveData(USART1);
		if (FifoSetByteToFIFO(pUartRxFIFO, *Buf) == TRUE)
		{
			LED_RED_ON;
		}	
	}		
}
//-------------------------------------------------------------------------------------------------------------
//Tx mode for USART2
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
//----------------------------------------------------------------------------------------------------------------------
// if there are bytes in the TX buffer, start transmition
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






