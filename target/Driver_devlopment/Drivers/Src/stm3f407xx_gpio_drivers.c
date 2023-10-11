/*
 * stm32f407xx_gpio_drivers.c
 *
 *  Created on: Sep 21, 2023
 *      Author: ARYAN
 */

#include "stm3f407xx_gpio_drivers.h"

/*********************************************************
 *
 * @fn 			- GPIO_PeriClockControl
 *
 * @brief		- it enables or disables peripheral clock for given GPIO port
 *
 * @param[in] 	- base address of GPIO peripheral
 * @param[in] 	- enable or disable GPIO Macros
 * @param[in] 	-
 *
 * @return 		- none
 *
 * @Note		- none
 *
 * */
void GPIO_PeriClockControl(GPIO_RegDef_t* pGPIOx , uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(pGPIOx == GPIOA)
		{
			GPIOA_PCLK_EN();
		}
		else if(pGPIOx == GPIOB)
		{
			GPIOB_PCLK_EN();
		}
		else if(pGPIOx == GPIOC)
		{
			GPIOC_PCLK_EN();
		}
		else if(pGPIOx == GPIOD)
		{
			GPIOD_PCLK_EN();
		}
		else if(pGPIOx == GPIOE)
		{
			GPIOE_PCLK_EN();
		}
		else if(pGPIOx == GPIOF)
		{
			GPIOF_PCLK_EN();
		}
		else if(pGPIOx == GPIOG)
		{
			GPIOG_PCLK_EN();
		}
		else if(pGPIOx == GPIOH)
		{
			GPIOH_PCLK_EN();
		}
		else if(pGPIOx == GPIOI)
		{
			GPIOI_PCLK_EN();
		}
	}
	else
	{
		if(pGPIOx == GPIOA)
		{
			GPIOA_PCLK_DIS();
		}
		else if(pGPIOx == GPIOB)
		{
			GPIOB_PCLK_DIS();
		}
		else if(pGPIOx == GPIOC)
		{
			GPIOC_PCLK_DIS();
		}
		else if(pGPIOx == GPIOD)
		{
			GPIOD_PCLK_DIS();
		}
		else if(pGPIOx == GPIOE)
		{
			GPIOE_PCLK_DIS();
		}
		else if(pGPIOx == GPIOF)
		{
			GPIOF_PCLK_DIS();
		}
		else if(pGPIOx == GPIOG)
		{
			GPIOG_PCLK_DIS();
		}
		else if(pGPIOx == GPIOH)
		{
			GPIOH_PCLK_DIS();
		}
		else if(pGPIOx == GPIOI)
		{
			GPIOI_PCLK_DIS();
		}
	}
}

/*********************************************************
 *
 * @fn 			- GPIO_Init
 *
 * @brief		- it initializes GPIO pin by setting mode,type ,speed,etc.
 *
 * @param[in] 	- base address of GPIO handle
 * @param[in] 	-
 * @param[in] 	-
 *
 * @return 		- none
 *
 * @Note		- none
 *
 * */

/* INITIALIZE N DEINITIALISZ */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
	uint32_t temp=0;

	// Enable peripheral clock

	GPIO_PeriClockControl(pGPIOHandle->pGPIOx, ENABLE);


	// 1. Configure the mode for GPIO
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG)
	{
		temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2* pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) );
		pGPIOHandle->pGPIOx->MODER &= ~(0x3 << (2* pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); // resetting or clearing
		pGPIOHandle->pGPIOx->MODER |= temp; //setting

		temp=0;
	}
	else
	{
		/****************************************************************************************************************/
		// THIS WILL BE WRITTTEN LATER (INTERRUPT MODE)
		if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT)
		{
			//configure FTSR
			EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			//clear corresponding RTSR bit
			EXTI->RTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}
		else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT)
		{
			//configure RTSR
			EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			//clear corresponding FTSR bit
			EXTI->FTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}
		else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT)
		{
			//configure Both RTSR and FTSR
			EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}

		// 2. Configure the GPIO port selection in SYSCFG_EXTICR

		uint8_t temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 4;
		uint8_t temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 4;
		uint8_t portcode = GPIO_BASEADDR_TO_CODE(pGPIOHandle->pGPIOx);
		SYSCFG_PCLK_EN();
		SYSCFG->EXTICR[temp1] = (portcode << (temp2 * 4));

		// 3. Enable the exti interrupt delivery using IMR
		EXTI->IMR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);

	}
	// 2. Configure the ospeed for GPIO

	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2* pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) );
	pGPIOHandle->pGPIOx->OSPEEDR &= ~(0x3 << (2* pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); ///****************************************************IMP NOTE***************************************************************************
	pGPIOHandle->pGPIOx->OSPEEDR |= temp;

	temp=0;
	// 3. Configure the pupd for GPIO

	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << (2* pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) );
	pGPIOHandle->pGPIOx->PUPDR &= ~(0x3 << (2* pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->PUPDR |= temp;

	temp=0;
	// 4. Configure the otype for GPIO

	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinOType << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->OTYPER &= ~(0x1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->OTYPER |= temp;

	temp=0;
	// 5. Configure the alt functionality for GPIO

	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ATLFN)
	{
		uint8_t temp1=0,temp2=0;
		temp1 = (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)/8 ;
		temp2 = (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)%8 ;
		pGPIOHandle->pGPIOx->AFR[temp1] &= ~(0xF << (4 * temp2) );
		pGPIOHandle->pGPIOx->AFR[temp1] |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinAFMode << (4 * temp2) );
	}
}
void GPIO_DeInit(GPIO_RegDef_t* pGPIOx)
{
	if(pGPIOx == GPIOA)
	{
		GPIOA_REG_RESET();
	}
	else if(pGPIOx == GPIOB)
	{
		GPIOB_REG_RESET();
	}
	else if(pGPIOx == GPIOC)
	{
		GPIOC_REG_RESET();
	}
	else if(pGPIOx == GPIOD)
	{
		GPIOD_REG_RESET();
	}
	else if(pGPIOx == GPIOE)
	{
		GPIOE_REG_RESET();
	}
	else if(pGPIOx == GPIOF)
	{
		GPIOF_REG_RESET();
	}
	else if(pGPIOx == GPIOG)
	{
		GPIOG_REG_RESET();
	}
	else if(pGPIOx == GPIOH)
	{
		GPIOH_REG_RESET();
	}
	else if(pGPIOx == GPIOI)
	{
		GPIOI_REG_RESET();
	}
}

/*********************************************************
 *
 * @fn 			- GPIO_ReadFromInputPin
 *
 * @brief		- it will return value stored at a pin.
 *
 * @param[in] 	- base address of GPIO peripherals
 * @param[in] 	- pin numbers taken at call.
 * @param[in] 	-
 *
 * @return 		- 0 or 1
 *
 * @Note		- none
 *
 * */


/* DATA READ AND WRITE */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t* pGPIOx, uint8_t PinNumber)
{
	uint8_t value;
	value = (uint8_t) ((pGPIOx->IDR >> PinNumber) & 0x00000001);

	return value;
}

/*********************************************************
 *
 * @fn 			- GPIO_ReadFromInputPort
 *
 * @brief		- it will return value stored at an entire port
 *
 * @param[in] 	- base address of GPIO peripherals
 * @param[in] 	-
 * @param[in] 	-
 *
 * @return 		- 16 bit value
 *
 * @Note		- none
 *
 * */

uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t* pGPIOx)
{
	uint16_t value;
	value = (uint16_t)pGPIOx->IDR ;

	return value;
}

/*********************************************************
 *
 * @fn 			- GPIO_WriteToOutputPin
 *
 * @brief		- it will write value to ODR at a pin location
 *
 * @param[in] 	- base address of GPIO peripherals
 * @param[in] 	- Pin number at call
 * @param[in] 	- value at call (0 or 1)
 *
 * @return 		- none
 *
 * @Note		- none
 *
 * */

void GPIO_WriteToOutputPin(GPIO_RegDef_t* pGPIOx, uint8_t PinNumber, uint8_t Value)
{
	if(Value == GPIO_PIN_SET)
	{
		pGPIOx ->ODR |= (1 << PinNumber) ;
	}
	else
	{
		pGPIOx ->ODR &= ~(1 << PinNumber) ;
	}
}

/*********************************************************
 *
 * @fn 			- GPIO_WriteToOutputPort
 *
 * @brief		- it will write entire 16 bit value to ODR
 *
 * @param[in] 	- base address of GPIO peripherals
 * @param[in] 	- value at call (16 bit)
 * @param[in] 	-
 *
 * @return 		- none
 *
 * @Note		- none
 *
 * */

void GPIO_WriteToOutputPort(GPIO_RegDef_t* pGPIOx ,uint16_t Value)
{
	pGPIOx ->ODR = Value;
}

/*********************************************************
 *
 * @fn 			- GPIO_ToggleOutputPin
 *
 * @brief		- it will toggle ODR at specific pin no.
 *
 * @param[in] 	- base address of GPIO peripherals
 * @param[in] 	- pin number at call
 * @param[in] 	-
 *
 * @return 		- none
 *
 * @Note		- XOR USE CASE
 *
 * */

void GPIO_ToggleOutputPin(GPIO_RegDef_t* pGPIOx, uint8_t PinNumber)
{
	pGPIOx ->ODR ^= (1 << PinNumber);
}

/* INTERRUPT */

/*********************************************************
 *
 * @fn 			- GPIO_IRQConfig
 *
 * @brief		- it configures the interrupt
 *
 * @param[in] 	- IRQ number all call.
 * @param[in] 	- IRQ priority at call.
 * @param[in] 	- enable or disable at call.
 *
 * @return 		- none
 *
 * @Note		- This API is processor specific...
 *
 * */

void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(IRQNumber <= 31) // 0 to 31
		{
			*NVIC_ISER0 |= (1 << IRQNumber);
		}
		else if(IRQNumber > 31 && IRQNumber < 64) // 32 to 63
		{
			*NVIC_ISER1 |= (1 << IRQNumber % 32);
		}
		else if(IRQNumber >= 64 && IRQNumber < 96) // 64 to 95
		{
			*NVIC_ISER2 |= (1 << IRQNumber % 64);
		}

	}
	else
	{
		if(IRQNumber <= 31)
		{
			*NVIC_ICER0 |= (1 << IRQNumber);
		}
		else if(IRQNumber > 31 && IRQNumber < 64)
		{
			*NVIC_ICER1 |= (1 << IRQNumber % 32);
		}
		else if(IRQNumber >= 64 && IRQNumber < 96)
		{
			*NVIC_ICER2 |= (1 << IRQNumber % 64);
		}
	}
}

/*********************************************************
 *
 * @fn 			- IRQPriorityConfig
 *
 * @brief		- it used to configure priority registers
 *
 * @param[in] 	- IRQ number all call.
 * @param[in] 	- IRQ priority at call.
 * @param[in] 	-
 *
 * @return 		- none
 *
 * @Note		- it will store IRQpriority in priority register at that IRQ number.
 * 				  IRQno -> IRQpriority set.
 * 				  IRQ priority - 0000 to 1111 (0 to 15)
 *
 * */


void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority)
{
	uint8_t iprx = IRQNumber / 4;
	uint8_t iprx_section = IRQNumber % 4;
	uint8_t shift_amount = (iprx_section * 8) + (8 - NO_PR_BITS_IMPLIMENTED);
	* (NVIC_PR_BASEADDR + (iprx)) |= ( IRQPriority << shift_amount );
}

/*********************************************************
 *
 * @fn 			- GPIO_IRQHandling
 *
 * @brief		- it is used for handling IRQ by clearing PR register.
 *
 * @param[in] 	- Pinnumber at call
 * @param[in] 	-
 * @param[in] 	-
 *
 * @return 		- none
 *
 * @Note		- clears the PR(pending register) by setting it.
 *
 * */

void GPIO_IRQHandling(uint8_t PinNumber)
{
	if(EXTI->PR & (1 << PinNumber))
	{
		//clear the bit by writing 1
		EXTI->PR |= (1 << PinNumber);
	}
}
