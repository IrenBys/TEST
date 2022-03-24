#include "usart_init.h"

//------------------------------------------------------------------------------------------------------
void USART_init(void)
{
	//init
	GPIO_InitTypeDef GPIO_struct_port_A;  											// port_A structure 
	GPIO_InitTypeDef GPIO_struct_port_D;  											// port_B structure	
	USART_InitTypeDef USART2_struct;														// USART2 structure
	USART_InitTypeDef USART3_struct;														// USART3 structure
	
	//clock enable
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);			  												// port clock enable for USART2 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);																// port clock enable for USART3
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 | RCC_APB1Periph_USART3, ENABLE);			// USART2 and USART3 clock enable
	
	//set port A for USART2 pinouts
	GPIO_struct_port_A.GPIO_Pin	  = GPIO_Pin_2 | GPIO_Pin_3;	
	GPIO_struct_port_A.GPIO_Mode 	= GPIO_Mode_AF;							
	GPIO_struct_port_A.GPIO_Speed	= GPIO_Low_Speed;						
	GPIO_struct_port_A.GPIO_OType = GPIO_OType_PP;						
	GPIO_struct_port_A.GPIO_PuPd 	= GPIO_PuPd_UP;						
	GPIO_Init(GPIOA, &GPIO_struct_port_A); 		
 
  //set port B for USART3 pinouts
	GPIO_struct_port_D.GPIO_Pin 	= GPIO_Pin_8 | GPIO_Pin_9;	
	GPIO_struct_port_D.GPIO_Mode 	= GPIO_Mode_AF;							
	GPIO_struct_port_D.GPIO_Speed = GPIO_Low_Speed;						
	GPIO_struct_port_D.GPIO_OType = GPIO_OType_PP;						
	GPIO_struct_port_D.GPIO_PuPd 	= GPIO_PuPd_UP;						
	GPIO_Init(GPIOD, &GPIO_struct_port_D);
	
  //set pin configurations	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2); 	// TX USART2 pin config
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2); 	// RX USART2 pin config
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_USART3); 	// TX USART3 pin config
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_USART3); 	// TX USART3 pin config
	
	// init USART2
	USART2_struct.USART_BaudRate 						= BAUD_RATE; 											
	USART2_struct.USART_WordLength 					= WORD_LENGHT; 			
	USART2_struct.USART_StopBits 						= STOP_BIT; 					
	USART2_struct.USART_Parity 							= PARITY_BIT; 							
	USART2_struct.USART_Mode 								= USART_Mode_Rx | USART_Mode_Tx;  
	USART2_struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None; 	
	USART_Init(USART2, &USART2_struct);
	USART_Cmd(USART2, ENABLE);
	
	// init USART3
	USART3_struct.USART_BaudRate	 					= BAUD_RATE; 												
	USART3_struct.USART_WordLength 					= USART_WordLength_8b; 			
	USART3_struct.USART_StopBits 						= USART_StopBits_1; 					
	USART3_struct.USART_Parity 							= USART_Parity_No; 							
	USART3_struct.USART_Mode								= USART_Mode_Rx | USART_Mode_Tx; 
	USART3_struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	
	USART_Init(USART3, &USART3_struct);
	USART_Cmd(USART3, ENABLE);
	
	// interrupt ENABLE
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); 							
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE); 							
	NVIC_EnableIRQ(USART2_IRQn); 																
	NVIC_EnableIRQ(USART3_IRQn); 	
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
