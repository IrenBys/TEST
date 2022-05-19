/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef _MAIN_H_
#define _MAIN_H_

/* Includes ------------------------------------------------------------------*/

#include "stm32f4xx.h"
#include <stdlib.h>
#include <stdint.h>
#include "Types.h"
#include "FIFO.h"
#include "init.h"
#include "usart_init.h"

/* Defines ------------------------------------------------------------------*/

#define MAX_FIFO_LENGHT 128
#define LED_GREEN_ON    GPIO_SetBits(GPIOD, GPIO_Pin_12)
#define LED_ORANGE_ON   GPIO_SetBits(GPIOD, GPIO_Pin_13)
#define LED_RED_ON      GPIO_SetBits(GPIOD, GPIO_Pin_14)
#define LED_BLUE_ON     GPIO_SetBits(GPIOD, GPIO_Pin_15)
#define LED_GREEN_OFF   GPIO_ResetBits(GPIOD, GPIO_Pin_12)
#define LED_ORANGE_OFF  GPIO_ResetBits(GPIOD, GPIO_Pin_13)
#define LED_RED_OFF     GPIO_ResetBits(GPIOD, GPIO_Pin_14)
#define LED_BLUE_OFF    GPIO_ResetBits(GPIOD, GPIO_Pin_15)

#endif /*_MAIN_H_ */
