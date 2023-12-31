/*
 * stm3f407xx_spi_drivers.c
 *
 *  Created on: Oct 2, 2023
 *      Author: ARYAN
 */
#include "stm3f407xx_spi_drivers.h"


/*********************************************************
 *
 * @fn 			- SPI_PeriClockControl
 *
 * @brief		- it will enable peripheral clock for SPI
 *
 * @param[in] 	- SPI1/SPI2/SPI3/SPI4
 * @param[in] 	- ENABLE OR DISABLE
 * @param[in] 	-
 *
 * @return 		- none
 *
 * @Note		- none
 *
 * */

void SPI_PeriClockControl(SPI_RegDef_t* pSPIx , uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(pSPIx == SPI1)
		{
			SPI1_PCLK_EN();
		}
		else if(pSPIx == SPI2)
		{
			SPI2_PCLK_EN();
		}
		else if(pSPIx == SPI3)
		{
			SPI3_PCLK_EN();
		}
		else if(pSPIx == SPI4)
		{
			SPI4_PCLK_EN();
		}

	}
	else
	{
		if(pSPIx == SPI1)
		{
			SPI1_PCLK_DIS();
		}
		else if(pSPIx == SPI2)
		{
			SPI2_PCLK_DIS();
		}
		else if(pSPIx == SPI3)
		{
			SPI3_PCLK_DIS();
		}
		else if(pSPIx == SPI4)
		{
			SPI4_PCLK_DIS();
		}
	}
}

uint8_t SPI_GetFlagStatus(SPI_RegDef_t* pSPIx,uint32_t Flagname)
{
	if(pSPIx->SR & Flagname)
	{
		return FLAG_SET;
	}
	return FLAG_RESET;
}


/*********************************************************
 *
 * @fn 			- SPI_Init
 *
 * @brief		- it will initialize spi
 *
 * @param[in] 	- spi handle address
 * @param[in] 	-
 * @param[in] 	-
 *
 * @return 		- none
 *
 * @Note		- none
 *
 * */

void SPI_Init(SPI_Handle_t *pSPIHandle)
{
	uint32_t tempreg =0;

	// Enable the peripheral clock

	SPI_PeriClockControl(pSPIHandle->pSPIx,ENABLE);


	// 1. Configure device mode
	tempreg |= (pSPIHandle->SPIConfig.SPI_DeviceMode << 2);

	// 2. Configure Bus config

	if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_FD)
	{
		// BIDIMODE = 0
		tempreg &= ~(1 << 15);
	}
	else if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_HD)
	{
		// BIDIMODE = 1 and O/P EN accordingly
		tempreg |= (1 << 15);
	}
	else if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_SIM_RX)
	{
		// BIDIMODE = 0 and RXONLY should be set
		tempreg &= ~(1 << 15);
		tempreg |= (1 << 10);
	}

	// 3. Configure SCLK (baud rate)

	tempreg |= (pSPIHandle->SPIConfig.SPI_SclkSpeed << 3);

	// 4. Configure data frame format(DFF)

	tempreg |= (pSPIHandle->SPIConfig.SPI_DFF << 11);

	// 5. Configure Clock Phase(CPHA)

	tempreg |= (pSPIHandle->SPIConfig.SPI_CPHA << 0);

	// 6. Configure Clock polarity(CPOL)
	tempreg |= (pSPIHandle->SPIConfig.SPI_CPOL << 1);

	// 7. Configure SSM (software slave management)
	tempreg |= (pSPIHandle->SPIConfig.SPI_SSM << 9);

	// assign value to CR1 register
	pSPIHandle->pSPIx->CR1 = tempreg;
}

/*********************************************************
 *
 * @fn 			- SPI_DeInit
 *
 * @brief		- it will de-initialize spi
 *
 * @param[in] 	- SPI1/SPI2/SPI3/SPI4
 * @param[in] 	-
 * @param[in] 	-
 *
 * @return 		- none
 *
 * @Note		- none
 *
 * */


void SPI_DeInit(SPI_RegDef_t* pSPIx)
{
	if(pSPIx == SPI1)
	{
		SPI1_REG_RESET();
	}
	else if(pSPIx == SPI2)
	{
		SPI2_REG_RESET();
	}
	else if(pSPIx == SPI3)
	{
		SPI3_REG_RESET();
	}
	else if(pSPIx == SPI4)
	{
		SPI4_REG_RESET();
	}

}


/*********************************************************
 *
 * @fn 			- SPI_SendData
 *
 * @brief		- it will send data through spi
 *
 * @param[in] 	- SPI1/SPI2/SPI3/SPI4
 * @param[in] 	- txBuffer data
 * @param[in] 	- Lenght of data
 *
 * @return 		- none
 *
 * @Note		- This is called blocking or Polling as while loop can run forever
 *
 * */

void SPI_SendData(SPI_RegDef_t* pSPIx, uint8_t *pTxBuffer, uint32_t Len)
{
	while(Len > 0)
	{
		// 1. Check if TXBUFFER is empty
		while(! SPI_GetFlagStatus(pSPIx,SPI_TXE_FLAG));

		// 2. Check if DFF is 0 or 1
		if(pSPIx->CR1 & (1 << SPI_CR1_DFF))
		{
			// 16 bits DFF
			pSPIx->DR = *((uint16_t*)pTxBuffer);
			Len--;
			Len--;
			(uint16_t*)pTxBuffer++;
		}
		else
		{
			//8-bit DFF
			pSPIx->DR = *pTxBuffer;
			Len--;
			pTxBuffer++;
		}
	}


}

/*********************************************************
 *
 * @fn 			- SPI_ReceiveData
 *
 * @brief		- it will receive data from spi
 *
 * @param[in] 	- SPI1/SPI2/SPI3/SPI4
 * @param[in] 	- txBuffer data
 * @param[in] 	- Lenght of data
 *
 * @return 		- none
 *
 * @Note		- This is called blocking or Polling as while loop can run forever
 *
 * */
void SPI_ReceiveData(SPI_RegDef_t* pSPIx, uint8_t *pRxBuffer, uint32_t Len)
{
	while(Len > 0)
	{
		// 1. Check if RXBUFFER is empty
		while(! SPI_GetFlagStatus(pSPIx,SPI_RXNE_FLAG));

		// 2. Check if DFF is 0 or 1
		if(pSPIx->CR1 & (1 << SPI_CR1_DFF))
		{
			// 16 bits DFF
			*((uint16_t*)pRxBuffer) = pSPIx->DR;
			Len--;
			Len--;
			(uint16_t*)pRxBuffer++;
		}
		else
		{
			//8-bit DFF
			*pRxBuffer = pSPIx->DR;
			Len--;
			pRxBuffer++;
		}
	}

}



/*********************************************************
 *
 * @fn 			- SPI_PeripheralControl
 *
 * @brief		- It enables SPI peripheral in CR1
 *
 * @param[in] 	- SPI1/SPI2/SPI3/SPI4
 * @param[in] 	- Enable or Disable
 * @param[in] 	-
 *
 * @return 		- none
 *
 * @Note		-
 *
 * */

void SPI_PeripheralControl(SPI_RegDef_t* pSPIx, uint8_t EnOrDi)
{

	if (EnOrDi == ENABLE)
	{
		pSPIx->CR1 |= (1 << SPI_CR1_SPE);
	}
	else
	{
		pSPIx->CR1 &= ~(1 << SPI_CR1_SPE);
	}
}

/*********************************************************
 *
 * @fn 			- SPI_SSIConfig
 *
 * @brief		- It enables SSI and avoids MODF errors
 *
 * @param[in] 	- SPI1/SPI2/SPI3/SPI4
 * @param[in] 	- Enable or Disable
 * @param[in] 	-
 *
 * @return 		- none
 *
 * @Note		-This bit has an effect only when the SSM bit is set (Software mode).
 * The value of this bit is forced onto the NSS pin and the I/O value of the NSS pin is ignored.
 *
 * */

void SPI_SSIConfig(SPI_RegDef_t* pSPIx, uint8_t EnOrDi)
{
	if (EnOrDi == ENABLE)
		{
			pSPIx->CR1 |= (1 << SPI_CR1_SSI);
		}
		else
		{
			pSPIx->CR1 &= ~(1 << SPI_CR1_SSI);
		}
}

/*********************************************************
 *
 * @fn 			- SPI_SSOEConfig
 *
 * @brief		- It enables SSOE, for single master as SSOE->0 for MULTI master.
 *
 * @param[in] 	- SPI1/SPI2/SPI3/SPI4
 * @param[in] 	- Enable or Disable
 * @param[in] 	-
 *
 * @return 		- none
 *
 * @Note		-0:--->SS output is disabled in master mode and the cell can work in multimaster configuration
 * 1:--->SS output is enabled in master mode and when the cell is enabled. The cell cannot work in a multimaster environment
 *
 * */

void SPI_SSOEConfig(SPI_RegDef_t* pSPIx, uint8_t EnOrDi)
{
	if (EnOrDi == ENABLE)
		{
			pSPIx->CR2 |= (1 << SPI_CR2_SSOE);
		}
		else
		{
			pSPIx->CR2 &= ~(1 << SPI_CR2_SSOE);
		}
}
