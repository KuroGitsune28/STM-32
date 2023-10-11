/*
 * led_button_ext.c
 *
 *  Created on: Sep 26, 2023
 *      Author: ARYAN
 */



#include "stm3f407xx.h"

#define BUTNPRESS		DISABLE


void delay(void){
	for(uint32_t i =0;i<500000/2;i++);
}

int main(void){
	// LED SETUP
	GPIO_Handle_t Gpioled;

	Gpioled.pGPIOx = GPIOD;
	Gpioled.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;
	Gpioled.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	Gpioled.GPIO_PinConfig.GPIO_PinSpeed = GPIO_OP_SPEED_HI;
	Gpioled.GPIO_PinConfig.GPIO_PinOType = GPIO_OP_TYPE_PP;
	Gpioled.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_PeriClockControl(GPIOD,ENABLE);

	GPIO_Init(&Gpioled);


	// BUTTON SETUP
	GPIO_Handle_t Gpiobut;

	Gpiobut.pGPIOx = GPIOD;
	Gpiobut.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_3; // PD 3 by default is high.
	Gpiobut.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	Gpiobut.GPIO_PinConfig.GPIO_PinSpeed = GPIO_OP_SPEED_HI;
//	Gpiobut.GPIO_PinConfig.GPIO_PinOType = GPIO_OP_TYPE_PP;
	Gpiobut.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;

	GPIO_PeriClockControl(GPIOD,ENABLE);

	GPIO_Init(&Gpiobut);


	while(1)
	{
		if(GPIO_ReadFromInputPin(GPIOD, GPIO_PIN_NO_3) == BUTNPRESS)
		{
			delay(); // To avoid pin bouncing (external noise)
			GPIO_ToggleOutputPin(GPIOD,GPIO_PIN_NO_15);
		}
	}



}
