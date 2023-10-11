/*
 * 002buttonandled.c
 *
 *  Created on: Sep 26, 2023
 *      Author: ARYAN
 */


#include "stm3f407xx.h"

#define BUTNPRESS		ENABLE


void delay(void){
	for(uint32_t i =0;i<500000/2;i++);
}

int main(void){

	GPIO_Handle_t Gpioled;

	Gpioled.pGPIOx = GPIOD;
	Gpioled.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	Gpioled.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	Gpioled.GPIO_PinConfig.GPIO_PinSpeed = GPIO_OP_SPEED_HI;
	Gpioled.GPIO_PinConfig.GPIO_PinOType = GPIO_OP_TYPE_PP;
	Gpioled.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_PeriClockControl(GPIOD,ENABLE);

	GPIO_Init(&Gpioled);



	GPIO_Handle_t Gpiobut;

	Gpiobut.pGPIOx = GPIOA;
	Gpiobut.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
	Gpiobut.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	Gpiobut.GPIO_PinConfig.GPIO_PinSpeed = GPIO_OP_SPEED_HI;
//	Gpiobut.GPIO_PinConfig.GPIO_PinOType = GPIO_OP_TYPE_PP;
	Gpiobut.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_PeriClockControl(GPIOA,ENABLE);

	GPIO_Init(&Gpiobut);


	while(1)
	{
		if(GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0) == BUTNPRESS)
		{
			delay(); // To avoid pin bouncing
			GPIO_ToggleOutputPin(GPIOD,GPIO_PIN_NO_12);
		}
	}



}
