/*
 * stm32f407xx_gpio_drivers.h
 *
 *  Created on: Sep 21, 2023
 *      Author: ARYAN
 */

#ifndef INC_STM3F407XX_GPIO_DRIVERS_H_
#define INC_STM3F407XX_GPIO_DRIVERS_H_
#include <stdint.h>
#include "stm3f407xx.h"

/* GPIO PIN CONFIGURATION */

typedef struct{

	uint8_t	GPIO_PinNumber;				/* @GPIO_PINNUMBERS */
	uint8_t GPIO_PinMode;				/* @GPIO_MODES */
	uint8_t GPIO_PinSpeed;				/* @GPIO_TYPES */
	uint8_t GPIO_PinPuPdControl;		/* @GPIO_SPEED */
	uint8_t GPIO_PinOType;				/* @GPIO_PUPD */
	uint8_t GPIO_PinAFMode;

}GPIO_PinConfig_t;

/* GPIO HANDLE SRUCTURE */

typedef struct{

	GPIO_RegDef_t* pGPIOx;
	GPIO_PinConfig_t GPIO_PinConfig;

}GPIO_Handle_t;

/*@GPIO_PINNUMBERS*/
/* **********************************GPIO PIN NUMBERS ********************************* */
#define GPIO_PIN_NO_0			0
#define GPIO_PIN_NO_1			1
#define GPIO_PIN_NO_2			2
#define GPIO_PIN_NO_3			3
#define GPIO_PIN_NO_4			4
#define GPIO_PIN_NO_5			5
#define GPIO_PIN_NO_6			6
#define GPIO_PIN_NO_7			7
#define GPIO_PIN_NO_8			8
#define GPIO_PIN_NO_9			9
#define GPIO_PIN_NO_10			10
#define GPIO_PIN_NO_11			11
#define GPIO_PIN_NO_12			12
#define GPIO_PIN_NO_13			13
#define GPIO_PIN_NO_14			14
#define GPIO_PIN_NO_15			15


/*@GPIO_MODES*/
/* ***************************POSSIBLE MODES OF PIN************************************ */
#define GPIO_MODE_IN			0
#define GPIO_MODE_OUT			1
#define GPIO_MODE_ATLFN			2
#define GPIO_MODE_ANALOG		3
#define GPIO_MODE_IT_FT			4
#define GPIO_MODE_IT_RT			5
#define GPIO_MODE_IT_RFT		6


/*@GPIO_TYPES*/
/* ****************************POSSIBLE OUPUT TYPE ************************************* */

#define GPIO_OP_TYPE_PP  		0
#define GPIO_OP_TYPE_OD  		1


/*@GPIO_SPEED*/
/* ****************************POSSIBLE OUTPUT SPEED************************************ */

#define GPIO_OP_SPEED_LOW		0
#define GPIO_OP_SPEED_MED		1
#define GPIO_OP_SPEED_HI		2
#define GPIO_OP_SPEED_VERYHI	3


/*@GPIO_PUPD*/
/* *****************************POSSIBLE PULL UP PULL DOWN ***************************** */
#define GPIO_NO_PUPD			0
#define GPIO_PIN_PU				1
#define GPIO_PIN_PD				2

/* PERIPHERAL CLOCK EN */
void GPIO_PeriClockControl(GPIO_RegDef_t* pGPIOx , uint8_t EnorDi);

/* INITIALIZE N DEINITIALISZ */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t* pGPIOx);

/* DATA READ AND WRITE */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t* pGPIOx, uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t* pGPIOx);
void GPIO_WriteToOutputPin(GPIO_RegDef_t* pGPIOx, uint8_t PinNumber, uint8_t Value);
void GPIO_WriteToOutputPort(GPIO_RegDef_t* pGPIOx ,uint16_t Value);
void GPIO_ToggleOutputPin(GPIO_RegDef_t* pGPIOx, uint8_t PinNumber);

/* INTERRUPT */
void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t EnorDi);
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void GPIO_IRQHandling(uint8_t PinNumber);

#endif /* INC_STM3F407XX_GPIO_DRIVERS_H_ */
