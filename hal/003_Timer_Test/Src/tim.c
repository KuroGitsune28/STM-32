/*
 * tim.c
 *
 *  Created on: Oct 22, 2023
 *      Author: ARYAN
 */

#include "tim.h"
TIM_HandleTypeDef TimHandle;

void tim_timebase_Init(void)
{

	_TIMx_CLK_ENABLE;

	TimHandle.Instance 					= TIMx;
	TimHandle.Init.Prescaler 			= 1600 - 1;
	TimHandle.Init.Period 				= 10000 - 1;
	TimHandle.Init.ClockDivision 		= 0 ;
	TimHandle.Init.CounterMode			= TIM_COUNTERMODE_UP;
	TimHandle.Init.AutoReloadPreload	= TIM_AUTORELOAD_PRELOAD_DISABLE;

	HAL_TIM_Base_Init(&TimHandle);

	HAL_NVIC_SetPriority(TIMx_IRQn,0, 0);
	HAL_NVIC_EnableIRQ(TIMx_IRQn);

	HAL_TIM_Base_Start_IT(&TimHandle);

}

void TIMx_IRQHandler(void)
{

	HAL_TIM_IRQHandler(&TimHandle);
}


