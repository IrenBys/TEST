/**
  ******************************************************************************
  * @file    init.c
  * @author  Irina Bystrova
  * @brief   This file provides functions to manage the following 
  *          functionalities:           
  *           + Initialize LEDs, button, delay function 
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/

#include "init.h"

/* Variables -----------------------------------------------------------------*/

uint16_t delay_count = 0;	
uint8_t Button_state = 0;		
uint8_t Led_state = 0;		

/* Functions -----------------------------------------------------------------*/

/**
    * @brief  Initializes LEDs
    * @param  None
    * @retval None
    */
void LED_init(void)
{
    /* calls button structure */
    GPIO_InitTypeDef GPIO_struct_LED; 
    
    /* LED port clock enable */	
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);	
    
    GPIO_struct_LED.GPIO_Pin   = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_struct_LED.GPIO_Mode  = GPIO_Mode_OUT;
    GPIO_struct_LED.GPIO_Speed = GPIO_Low_Speed;
    GPIO_struct_LED.GPIO_OType = GPIO_OType_PP;
    GPIO_struct_LED.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    
    /* initialize LED structure */
    GPIO_Init(GPIOD, &GPIO_struct_LED);
}

/**
  * @brief  Initializes buttom
  * @param  None
  * @retval None
  */
void Button_init(void)
{
    /* calls button structure */
    GPIO_InitTypeDef GPIO_struct_Button;

    /* button port clock enable */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 
    
    /*set button structure */
    GPIO_struct_Button.GPIO_Pin   = GPIO_Pin_0;
    GPIO_struct_Button.GPIO_Mode  = GPIO_Mode_IN;
    GPIO_struct_Button.GPIO_Speed = GPIO_Low_Speed;
    GPIO_struct_Button.GPIO_OType = GPIO_OType_PP;
    GPIO_struct_Button.GPIO_PuPd  = GPIO_PuPd_NOPULL;	
    
    /* initialize button structure */
    GPIO_Init(GPIOA, &GPIO_struct_Button);
}

void GPIO_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;   
        
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);   

    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_1; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT; 
        
    /* initialize GPIO structure */
    GPIO_Init(GPIOB, &GPIO_InitStructure); 
      
}


/**
    * @brief  Initializes SysTick Handler innrerups
    * @param  None
    * @retval None
    */
void SysTick_Handler(void) 
{
    if(delay_count > 0)
    {
        delay_count--; 
    }
}
/**
    * @brief  Creates delay function
    * @param  delay_temp: delay in microiseconds
    * @retval None
    */
void delay_ms(uint16_t delay_temp) 
{
    delay_count = delay_temp;
    
    while(delay_count) {}
}

/**
    * @brief  LED control function using button
    * @param  None
    * @retval None
    */
void LED_button(void)
{	
    if ((BUTTON_READ) == 1) 
    {
        delay_ms(50);				
        if (Button_state == 0)	
        {
            Button_state = 1;
            Led_state++;			
            switch(Led_state){
            case 1:
                LED_GREEN_ON;
                break;
            case 2:
                LED_GREEN_OFF;
                LED_ORANGE_ON;
                break;
            case 3:
                LED_ORANGE_OFF;
                LED_RED_ON;
                break;
            case 4:
                LED_RED_OFF;
                LED_BLUE_ON;
                break;
            case 5:
                LED_GREEN_ON;
                LED_BLUE_OFF;
                Led_state = 1;
                break;
            }
        }							
    }				
    else
    {
        delay_ms(50);
        Button_state = 0;																				
    }	
}	
