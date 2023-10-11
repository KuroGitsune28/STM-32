/*
 * main.c
 *
 *  Created on: Sep 24, 2023
 *      Author: ARYAN
 */

#include "stm3f407xx.h"

void delay(void){
	for(uint32_t i =0;i<1000000;i++);
}

void LedToggle(uint8_t GPIO_PinNumber){
		GPIO_Handle_t Gpioled;

		Gpioled.pGPIOx = GPIOD;
		Gpioled.GPIO_PinConfig.GPIO_PinNumber = GPIO_PinNumber;
		Gpioled.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
		Gpioled.GPIO_PinConfig.GPIO_PinSpeed = GPIO_OP_SPEED_HI;
		Gpioled.GPIO_PinConfig.GPIO_PinOType = GPIO_OP_TYPE_PP;
		Gpioled.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

		GPIO_PeriClockControl(GPIOD,ENABLE);

		GPIO_Init(&Gpioled);

		GPIO_ToggleOutputPin(GPIOD,GPIO_PinNumber);

}

int main(void){



	while(1)
	{
		LedToggle(GPIO_PIN_NO_12);
		LedToggle(GPIO_PIN_NO_13);
		delay();
	}


}
