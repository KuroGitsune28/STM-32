/*
 * led.c
 *
 *  Created on: Oct 22, 2023
 *      Author: ARYAN
 */

#include "led.h"
// PD 5

void PD5_Led_Init(void)
{
	GPIO_InitTypeDef Gpio_Initstruct = {0};

	__HAL_RCC_GPIOD_CLK_ENABLE();

	Gpio_Initstruct.Pin		= LED_PIN;
	Gpio_Initstruct.Mode	= GPIO_MODE_OUTPUT_PP;
	Gpio_Initstruct.Pull	= GPIO_NOPULL;
	Gpio_Initstruct.Speed	= GPIO_SPEED_FREQ_LOW;

	HAL_GPIO_Init(LED_PORT,&Gpio_Initstruct);
}
