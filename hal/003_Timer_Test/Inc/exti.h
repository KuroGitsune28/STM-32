/*
 * exti.h
 *
 *  Created on: Oct 22, 2023
 *      Author: ARYAN
 */
#ifndef EXTI_H_
#define EXTI_H_

/* BUTTON DEFINITION */
#define BTN_PORT	GPIOC
#define BTN_PIN		GPIO_PIN_13

void Gpio_PC13_Interrupt_Init(void);

#endif /* EXTI_H_ */
