/*
 * 005spi_tx_aurdino_mytry.c
 *
 *  Created on: Oct 6, 2023
 *      Author: ARYAN
 */


#include <string.h>
#include "stm3f407xx.h"

void delay(void){
	for(uint32_t i =0;i<500000/2;i++);
}

/*
 * PA 15 --> NSS
 * PB 3 --> SCLK
 * PB 4 --> MISO
 * PB 5 --> MOSI
 *
 * */

void SPI2_GPIOInint(void)
{
	GPIO_Handle_t SPI_Pins,SPI_Pins2;

	SPI_Pins.pGPIOx = GPIOB;
	SPI_Pins2.pGPIOx = GPIOA;

	SPI_Pins.GPIO_PinConfig.GPIO_PinAFMode = GPIO_MODE_ATLFN;
	SPI_Pins.GPIO_PinConfig.GPIO_PinOType = GPIO_OP_TYPE_PP;
	SPI_Pins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	SPI_Pins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_OP_SPEED_HI;

	SPI_Pins2.GPIO_PinConfig.GPIO_PinAFMode = GPIO_MODE_ATLFN;
	SPI_Pins2.GPIO_PinConfig.GPIO_PinOType = GPIO_OP_TYPE_PP;
	SPI_Pins2.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	SPI_Pins2.GPIO_PinConfig.GPIO_PinSpeed = GPIO_OP_SPEED_HI;

	//NSS
	SPI_Pins2.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;
	GPIO_Init(&SPI_Pins2);

	// SCLK
	SPI_Pins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_3;
	GPIO_Init(&SPI_Pins);

	// MISO
	//SPI_Pins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;
	//GPIO_Init(&SPI_Pins);

	// MOSI
	SPI_Pins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
	GPIO_Init(&SPI_Pins);

}

void SPI2_Inint(void)
{
	SPI_Handle_t SPI_Handle,SPI_Handle2;

	SPI_Handle.pSPIx = SPI2;

	SPI_Handle.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
	SPI_Handle.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI_Handle.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV8; // to provide 2MHz clock
	SPI_Handle.SPIConfig.SPI_SSM = SPI_SSM_DI; // Software slave management mode as we dont actually need NSS
	SPI_Handle.SPIConfig.SPI_DFF = SPI_DFF_8BITS;
	SPI_Handle.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
	SPI_Handle.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;


	SPI_Init(&SPI_Handle);

	SPI_Handle2.pSPIx = SPI1;

	SPI_Handle2.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
	SPI_Handle2.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI_Handle2.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV8; // to provide 2MHz clock
	SPI_Handle2.SPIConfig.SPI_SSM = SPI_SSM_DI; // Software slave management mode as we dont actually need NSS
	SPI_Handle2.SPIConfig.SPI_DFF = SPI_DFF_8BITS;
	SPI_Handle2.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
	SPI_Handle2.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;


	SPI_Init(&SPI_Handle2);
}

/* FOR BUTTON */
void GPIO_Buttoninit()
{
	GPIO_Handle_t Gpiobut;

	Gpiobut.pGPIOx = GPIOA;
	Gpiobut.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
	Gpiobut.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	Gpiobut.GPIO_PinConfig.GPIO_PinSpeed = GPIO_OP_SPEED_HI;
//	Gpiobut.GPIO_PinConfig.GPIO_PinOType = GPIO_OP_TYPE_PP;
	Gpiobut.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

//	GPIO_PeriClockControl(GPIOA,ENABLE); NO NEED AS WE ARE ENABLING IN INIT FUNCTION

	GPIO_Init(&Gpiobut);
}

void GPIO_Led()
{
	GPIO_Handle_t Gpioled;

	Gpioled.pGPIOx = GPIOD;
	Gpioled.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	Gpioled.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	Gpioled.GPIO_PinConfig.GPIO_PinSpeed = GPIO_OP_SPEED_HI;
	Gpioled.GPIO_PinConfig.GPIO_PinOType = GPIO_OP_TYPE_PP;
	Gpioled.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

//	GPIO_PeriClockControl(GPIOD,ENABLE);

	GPIO_Init(&Gpioled);
}

int main(void)
{
	char Userdata[] = "Hello World";
	SPI2_GPIOInint();
	SPI2_Inint();
	GPIO_Buttoninit();
	GPIO_Led();
	// This will enable SSI and make NSS High internally and avoid MODF Error
//	SPI_SSIConfig(SPI2,ENABLE);

	SPI_SSOEConfig(SPI2,ENABLE);
	SPI_SSOEConfig(SPI1,ENABLE);

	while(1){


		while(!GPIO_ReadFromInputPin(GPIOA,GPIO_PIN_NO_0));// BUTTON PRESS

		delay();


		// Enable SPI in CR1 register
		SPI_PeripheralControl(SPI1,ENABLE);
		SPI_PeripheralControl(SPI2,ENABLE);

		// Slave need to know LENGTH INFO (1BYTE)
		uint8_t datalen = strlen(Userdata);
		SPI_SendData(SPI2,&datalen,1);

		SPI_SendData(SPI2,(uint8_t*)Userdata,strlen(Userdata));

		// Cannot disable abruptly
		// So check if SPI is busy or not using STATUS REGISTER
		while(SPI_GetFlagStatus(SPI2,SPI_BUSY_FLAG));

		SPI_PeripheralControl(SPI2,DISABLE);
		if(GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0) == ENABLE){
			delay(); // To avoid pin bouncing
			GPIO_ToggleOutputPin(GPIOD,GPIO_PIN_NO_12);
		}

	}

	return 0;
}
