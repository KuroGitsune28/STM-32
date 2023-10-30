/*
 * tim.h
 *
 *  Created on: Oct 22, 2023
 *      Author: ARYAN
 */

#ifndef TIM_H_
#define TIM_H_

#include "stm32f4xx_hal.h"

#define TIMx				TIM3
#define _TIMx_CLK_ENABLE	__HAL_RCC_TIM3_CLK_ENABLE()
#define TIMx_IRQn			TIM3_IRQn
#define TIMx_IRQHandler		TIM3_IRQHandler

void tim_timebase_Init(void);

#endif /* TIM_H_ */
