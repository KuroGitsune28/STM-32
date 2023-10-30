/*
 * adc.c
 *
 *  Created on: Oct 23, 2023
 *      Author: ARYAN
 */
#include "stm32f4xx_hal.h"

ADC_HandleTypeDef hadc1;

static void ADC_PA0_ContinuousConv_Init(void);

uint32_t ADC_PA0_Read(void)
{
	return HAL_ADC_GetValue(&hadc1);
}

void ADC_Init_Start(void)
{
	ADC_PA0_ContinuousConv_Init();
	HAL_ADC_Start(&hadc1);
}


void ADC_PA0_ContinuousConv_Init(void)
{
	// Configure GPIO PA0 as analog mode
	__HAL_RCC_GPIOA_CLK_ENABLE();

	GPIO_InitTypeDef Gpiostruct;

	Gpiostruct.Pin 		= GPIO_PIN_0;
	Gpiostruct.Mode 	= GPIO_MODE_ANALOG;
	Gpiostruct.Pull		= GPIO_NOPULL;

	HAL_GPIO_Init(GPIOA,&Gpiostruct);

	// Configure ADC for continuous conversion mode

	__HAL_RCC_ADC1_CLK_ENABLE();

	hadc1.Instance 						= ADC1;
	hadc1.Init.ClockPrescaler 			= ADC_CLOCKPRESCALER_PCLK_DIV2;
	hadc1.Init.Resolution				= ADC_RESOLUTION_12B;
	hadc1.Init.ContinuousConvMode		= ENABLE;
	hadc1.Init.DiscontinuousConvMode	= DISABLE;
	hadc1.Init.ExternalTrigConvEdge		= ADC_EXTERNALTRIGCONVEDGE_NONE;
	hadc1.Init.ExternalTrigConv			= ADC_SOFTWARE_START;
	hadc1.Init.DataAlign				= ADC_DATAALIGN_RIGHT;
	hadc1.Init.NbrOfConversion			= 1;
	hadc1.Init.DMAContinuousRequests	= DISABLE;
	hadc1.Init.EOCSelection				= ADC_EOC_SINGLE_CONV;

	HAL_ADC_Init(&hadc1);

	// Configure Channel for ADC and link PA0  and ADC1

	ADC_ChannelConfTypeDef	sconfig;

	sconfig.Channel			=	ADC_CHANNEL_0;
	sconfig.Rank			= 	1;
	sconfig.SamplingTime	=	ADC_SAMPLETIME_480CYCLES;

	HAL_ADC_ConfigChannel(&hadc1, &sconfig);
}
