/*
 * led.h
 *
 *  Created on: Oct 22, 2023
 *      Author: ARYAN
 */

#ifndef LED_H_
#define LED_H_

#include "stm32f4xx_hal.h"


// PD 5 as LED
#define LED_PORT		GPIOD
#define LED_PIN			GPIO_PIN_5

void PD5_Led_Init(void);


#endif /* LED_H_ */
