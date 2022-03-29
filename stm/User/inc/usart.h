/**
  ******************************************************************************
  * @file    usart_init.h
  * @author  Irina Bystrova
  * @brief   This file contains all the functions prototypes for  
	*					 the initialization receive and transmition to USART modules.
  ******************************************************************************
  */
	
/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef USART_H
#define USART_H

/* Includes ------------------------------------------------------------------*/

#include "main.h"
#include "FIFO.h"

/* Exported constants --------------------------------------------------------*/

#define PACK_LEN 128

extern pFIFO_s pUartRxFIFO;  
extern pFIFO_s pUartTxFIFO;   

/* Exported functions --------------------------------------------------------*/

void UartTransmite(void);

#endif /*USART_H */
