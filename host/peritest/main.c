/*
 * main.c
 *
 *  Created on: Sep 19, 2023
 *      Author: ARYAN
 */
#include <stdint.h>
#include <stdio.h>
#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#define GPIOA_BASE_ADDR         0x40020000UL
#define GPIOA_OTYPER_ADDR       (GPIOA_BASE_ADDR + 0x04UL)
#define RCC_BASE_ADDR           0x40023800UL
#define ABH1ENR_OFFSET_ADDR     0x30UL
#define RCC_ABH1ENR_ADDR        (ABH1ENR_OFFSET_ADDR + RCC_BASE_ADDR)
int main(void)
{
	uint32_t* abh1ptr = (uint32_t*)RCC_ABH1ENR_ADDR;
	uint32_t* gpioptr = (uint32_t*)GPIOA_OTYPER_ADDR;
	*abh1ptr |= (1<<0);
	*gpioptr |= (1<<1);

    /* Loop forever */
	for(;;);
}

