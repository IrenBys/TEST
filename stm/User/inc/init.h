/**
  ******************************************************************************
  * @file    init.h
  * @author  Irina Bystrova
  * @brief   This file contains all defines and functionc for init LEDs
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef INIT_H
#define INIT_H

/* Includes ------------------------------------------------------------------*/

#include "main.h"

/* Exported defines ----------------------------------------------------------*/

#define LED_GREEN_ON GPIO_SetBits(GPIOD, GPIO_Pin_12)
#define LED_GREEN_OFF GPIO_ResetBits(GPIOD, GPIO_Pin_12)

#define LED_ORANGE_ON GPIO_SetBits(GPIOD, GPIO_Pin_13)
#define LED_ORANGE_OFF GPIO_ResetBits(GPIOD, GPIO_Pin_13)

#define LED_RED_ON GPIO_SetBits(GPIOD, GPIO_Pin_14)
#define LED_RED_OFF GPIO_ResetBits(GPIOD, GPIO_Pin_14)

#define LED_BLUE_ON GPIO_SetBits(GPIOD, GPIO_Pin_15)
#define LED_BLUE_OFF GPIO_ResetBits(GPIOD, GPIO_Pin_15)

#define BUTTON_READ GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)

#define DWT_CYCCNT    *(volatile unsigned long *)0xE0001004
#define DWT_CONTROL   *(volatile unsigned long *)0xE0001000
#define SCB_DEMCR     *(volatile unsigned long *)0xE000EDFC

/* Exported functions --------------------------------------------------------*/

void LED_init(void);
void Button_init(void);
void GPIO_init(void);
void delay_ms (uint16_t delay_temp);
void LED_button(void);

#endif /* INIT_H */

