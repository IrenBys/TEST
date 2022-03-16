#include "usart_init.h"

//------------------------------------------------------------------------------------------------------
void USART_init(void)
{
	//init port
	GPIO_InitTypeDef GPIO_struct_USART;  												// port structure 
	USART_InitTypeDef USART1_struct;														// USART1 structure
	USART_InitTypeDef USART2_struct;														// USART1 structure
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);			  // port clock enable 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);		 	// USART1 clock enable
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);			// USART2 clock enable 
			
	GPIO_struct_USART.GPIO_Pin 			= GPIO_Pin_2 | GPIO_Pin_10 | GPIO_Pin_3 | GPIO_Pin_9;	
	GPIO_struct_USART.GPIO_Mode 		= GPIO_Mode_AF;							
	GPIO_struct_USART.GPIO_Speed 		= GPIO_Low_Speed;						
	GPIO_struct_USART.GPIO_OType 		= GPIO_OType_PP;						
	GPIO_struct_USART.GPIO_PuPd 		= GPIO_PuPd_UP;							
	
	GPIO_Init(GPIOA, &GPIO_struct_USART); 											
		
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9,  GPIO_AF_USART1); 	// TX USART1 pin config
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1); 	// RX USART1 pin config
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2,  GPIO_AF_USART2); 	// TX USART2 pin config
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3,  GPIO_AF_USART2); 	// RX USART2 pin config
	
	// init USART
	USART1_struct.USART_BaudRate	 					= 9600; 												
	USART1_struct.USART_WordLength 					= USART_WordLength_8b; 			
	USART1_struct.USART_StopBits 						= USART_StopBits_1; 					
	USART1_struct.USART_Parity 							= USART_Parity_No; 							
	USART1_struct.USART_Mode								= USART_Mode_Rx | USART_Mode_Tx; 
	USART1_struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None; 
	
	USART_Init(USART1, &USART1_struct);
	USART_Cmd(USART1, ENABLE);
	
	USART2_struct.USART_BaudRate 						= 115200; 											
	USART2_struct.USART_WordLength 					= USART_WordLength_8b; 			
	USART2_struct.USART_StopBits 						= USART_StopBits_1; 					
	USART2_struct.USART_Parity 							= USART_Parity_No; 							
	USART2_struct.USART_Mode 								= USART_Mode_Rx | USART_Mode_Tx;  
	USART2_struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None; 
	
	USART_Init(USART2, &USART2_struct);
	USART_Cmd(USART2, ENABLE);
	
	// interrupt ENABLE
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); 							
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); 							
	NVIC_EnableIRQ(USART1_IRQn); 																
	NVIC_EnableIRQ(USART2_IRQn); 	
}
//------------------------------------------------------------------------------------------------------
// initializes LEDs
void LED_ini(void)
{
	GPIO_InitTypeDef GPIO_struct_LED;  
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);	
	
	GPIO_struct_LED.GPIO_Pin		= GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;	
	GPIO_struct_LED.GPIO_Mode		= GPIO_Mode_OUT;	
	GPIO_struct_LED.GPIO_Speed	= GPIO_Low_Speed;	
	GPIO_struct_LED.GPIO_OType	= GPIO_OType_PP;	
	GPIO_struct_LED.GPIO_PuPd		= GPIO_PuPd_NOPULL;	
	
	GPIO_Init(GPIOD, &GPIO_struct_LED); 
}
