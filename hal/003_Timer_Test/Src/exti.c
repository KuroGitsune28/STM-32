/*
 * exti.c
 *
 *  Created on: Oct 22, 2023
 *      Author: ARYAN
 */

#include "stm32f4xx_hal.h"
#include "exti.h"

void Gpio_PC13_Interrupt_Init(void)
{
	// Configure PC13 as interrupt pin
	GPIO_InitTypeDef Gpiostruct = {0};

	__HAL_RCC_GPIOC_CLK_ENABLE();

	Gpiostruct.Pin = BTN_PIN;
	Gpiostruct.Mode = GPIO_MODE_IT_RISING;
	Gpiostruct.Pull = GPIO_NOPULL;
	Gpiostruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(BTN_PORT,&Gpiostruct);

	// Configure EXTI

	HAL_NVIC_SetPriority(EXTI15_10_IRQn,0, 0);
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}

void HAL_GPIO_EXTI_Callback(uint16_t Gpio_pin)
{
	if(Gpio_pin == BTN_PIN){

		//DO something

	}
}

void EXTI15_10_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(BTN_PIN);
}
