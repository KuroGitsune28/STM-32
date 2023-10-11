/*
 * 003button_interrupt.c
 *
 *  Created on: Sep 29, 2023
 *      Author: ARYAN
 */

#include "stm3f407xx.h"
#include <stdint.h>
#include <string.h>

void delay(void){
	for(uint32_t i =0;i<500000/2;i++); // 200ms delay
}

int main(void)
{
	GPIO_Handle_t gpioled;
	memset(&gpioled,0,sizeof(gpioled)); //set bits at address location

	gpioled.pGPIOx = GPIOD;
	gpioled.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	gpioled.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	gpioled.GPIO_PinConfig.GPIO_PinOType = GPIO_OP_TYPE_PP;
	gpioled.GPIO_PinConfig.GPIO_PinSpeed = GPIO_OP_SPEED_HI;
	gpioled.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_PeriClockControl(GPIOD,ENABLE);

	GPIO_Init(&gpioled);

	GPIO_Handle_t gpiobut;

	gpiobut.pGPIOx = GPIOD;
	gpiobut.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
	gpiobut.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
//	gpiobut.GPIO_PinConfig->GPIO_PinOType = GPIO_OP_TYPE_PP;
	gpiobut.GPIO_PinConfig.GPIO_PinSpeed = GPIO_OP_SPEED_HI;
	gpiobut.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;

	GPIO_PeriClockControl(GPIOD,ENABLE);

	GPIO_Init(&gpiobut);

	//IRQ COnfiguration
	//OPTIONAL (priority)
	GPIO_IRQPriorityConfig(IRQ_NO_EXTI5_9, NVIC_IRQ_PRI15);
	GPIO_IRQConfig(IRQ_NO_EXTI5_9,ENABLE);


	while(1);

	return 0;

}

void EXTI9_5_IRQHandler(void)
{
	GPIO_IRQHandling(GPIO_PIN_NO_5);
	GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_12);
}
