/*
 * 004spi_tx_testing.c
 *
 *  Created on: Oct 4, 2023
 *      Author: ARYAN
 */
#include <string.h>
#include "stm3f407xx.h"

/*
 * PB 12 --> NSS
 * PB 13 --> SCLK
 * PB 14 --> MISO
 * PB 15 --> MOSI
 *
 * */

void SPI2_GPIOInint(void)
{
	GPIO_Handle_t SPI_Pins;

	SPI_Pins.pGPIOx = GPIOB;

	SPI_Pins.GPIO_PinConfig.GPIO_PinAFMode = GPIO_MODE_ATLFN;
	SPI_Pins.GPIO_PinConfig.GPIO_PinOType = GPIO_OP_TYPE_PP;
	SPI_Pins.GPIO_PinConfig.GPIO_PinAFMode = 5;
	SPI_Pins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	SPI_Pins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_OP_SPEED_HI;

	// NSS
	//SPI_Pins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	//GPIO_Init(&SPI_Pins);

	// SCLK
	SPI_Pins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	GPIO_Init(&SPI_Pins);

	// MISO
	//SPI_Pins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;
	//GPIO_Init(&SPI_Pins);

	// MOSI
	SPI_Pins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;
	GPIO_Init(&SPI_Pins);

}


void SPI2_Inint(void)
{
	SPI_Handle_t SPI_Handle;

	SPI_Handle.pSPIx = SPI2;

	SPI_Handle.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
	SPI_Handle.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI_Handle.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV2;
	SPI_Handle.SPIConfig.SPI_SSM = SPI_SSM_EN; // Software slave management mode as we dont actually need NSS
	SPI_Handle.SPIConfig.SPI_DFF = SPI_DFF_8BITS;
	SPI_Handle.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
	SPI_Handle.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;


	SPI_Init(&SPI_Handle);
}

void delay(void){
	for(uint32_t i =0;i<1000000;i++);
}


int main(void)
{
	char Userdata[] = "Hello World";
	SPI2_GPIOInint();
	SPI2_Inint();
	Led_Init();
	// This will enable SSI and make NSS High internally and avoid MODF Error
	SPI_SSIConfig(SPI2,ENABLE);

	// Enable SPI in CR1 register (SPE is set)
	SPI_PeripheralControl(SPI2,ENABLE);

	// So check if SPI is busy or not using STATUS REGISTER
	while(SPI_GetFlagStatus(SPI2,SPI_BUSY_FLAG));

	// AFTER check disable SPI
	SPI_SendData(SPI2,(uint8_t*)Userdata,strlen(Userdata));


	SPI_PeripheralControl(SPI2,DISABLE);


	while(1);

	return 0;
}
