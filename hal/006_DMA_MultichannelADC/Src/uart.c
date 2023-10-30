
#include "stm32f4xx_hal.h"
#include <stdio.h>
/*
 * BOARD INFO :-
 *
 *	USART 1
 *	USART_TX	-	PA9			AF7
 *	USART_RX	- 	PA10		AF7
 *
 * */


UART_HandleTypeDef		Uart1;


int __io_putchar(int ch)
{
	HAL_UART_Transmit(&Uart1,(uint8_t*)&ch,1,100);
	return ch;
}


void UART1_Init(void)
{
	__HAL_RCC_GPIOA_CLK_ENABLE();

	// Configure Clock for UART
	__HAL_RCC_USART1_CLK_ENABLE();

	//GPIO init typedef
	GPIO_InitTypeDef	GpioStruct;

	GpioStruct.Pin			=	GPIO_PIN_9 | GPIO_PIN_10;
	GpioStruct.Mode 		=	GPIO_MODE_AF_PP;
	GpioStruct.Alternate	=	GPIO_AF7_USART1;
	GpioStruct.Pull			= 	GPIO_NOPULL;
	GpioStruct.Speed		= 	GPIO_SPEED_FREQ_VERY_HIGH;

	HAL_GPIO_Init(GPIOA,&GpioStruct);

	// USART2 Configuration


	Uart1.Instance				=	USART1; // USART2 Base Address is given
	// Don't get confused between UART and USART there is just a bit difference
	// We are configuring USART2 as UART

	Uart1.Init.BaudRate			=	115200;
	Uart1.Init.WordLength		=	UART_WORDLENGTH_8B;
	Uart1.Init.StopBits			=	UART_STOPBITS_1;
	Uart1.Init.Mode				=	UART_MODE_TX;
	Uart1.Init.Parity			=	UART_PARITY_NONE;
	Uart1.Init.HwFlowCtl		=	UART_HWCONTROL_NONE;
	Uart1.Init.OverSampling		=	UART_OVERSAMPLING_16;

	HAL_UART_Init(&Uart1);

}
