/*
 * adc.h
 *
 *  Created on: Oct 23, 2023
 *      Author: ARYAN
 */

#ifndef ADC_H_
#define ADC_H_

uint32_t ADC_PA0_Read(void);
void ADC_Init_Start(void);
//void ADC_PA0_ContinuousConv_Init(void);
void ADC_PA0_SingleConv_Init(void);
void ADC_PA0_Interrupt_Init(void);

#endif /* ADC_H_ */
