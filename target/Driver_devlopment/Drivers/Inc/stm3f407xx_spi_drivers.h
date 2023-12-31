/*
 * stm3f407xx_spi_drivers.h
 *
 *  Created on: Oct 2, 2023
 *      Author: ARYAN
 */

#ifndef INC_STM3F407XX_SPI_DRIVERS_H_
#define INC_STM3F407XX_SPI_DRIVERS_H_
#include <stdint.h>
#include "stm3f407xx.h"

typedef struct{

	uint8_t	SPI_DeviceMode;				/* @SPI_DeviceMode */
	uint8_t SPI_BusConfig;				/* @SPI_BusConfig */
	uint8_t SPI_SclkSpeed;				/* @SPI_SclkSpeed */
	uint8_t SPI_DFF;					/* @SPI_DFF */
	uint8_t SPI_CPHA;					/* @SPI_CPHA */
	uint8_t SPI_CPOL;					/* @SPI_CPOL */
	uint8_t SPI_SSM;					/* @SPI_SSM */

}SPI_Config_t;

typedef struct{

	SPI_RegDef_t	*pSPIx;
	SPI_Config_t	SPIConfig;

}SPI_Handle_t;

/* CONFIG MACROS */

// @SPI_DeviceMode
#define SPI_DEVICE_MODE_SLAVE			0
#define SPI_DEVICE_MODE_MASTER			1

// @SPI_BusConfig
#define SPI_BUS_CONFIG_FD				1
#define SPI_BUS_CONFIG_HD				2
//#define SPI_BUS_CONFIG_SIM_TX			3 no need as wee can disable rx to transmit
#define SPI_BUS_CONFIG_SIM_RX			3

// @SPI_SclkSpeed
#define SPI_SCLK_SPEED_DIV2				0
#define SPI_SCLK_SPEED_DIV4				1
#define SPI_SCLK_SPEED_DIV8				2
#define SPI_SCLK_SPEED_DIV16			3
#define SPI_SCLK_SPEED_DIV32			4
#define SPI_SCLK_SPEED_DIV64			5
#define SPI_SCLK_SPEED_DIV128			6
#define SPI_SCLK_SPEED_DIV256			7

// @SPI_DFF
#define SPI_DFF_8BITS					0
#define SPI_DFF_16BITS					1

// @SPI_CPHA
#define SPI_CPHA_LOW					0
#define SPI_CPHA_HIGH					1

// @SPI_CPOL
#define SPI_CPOL_LOW					0
#define SPI_CPOL_HIGH					1

// @SPI_SSM
#define SPI_SSM_EN						1
#define SPI_SSM_DI						0


/* STATUS FLAGS */
#define SPI_TXE_FLAG					(1 << SPI_SR_TXE)
#define SPI_RXNE_FLAG					(1 << SPI_SR_RXNE)
#define SPI_BUSY_FLAG					(1 << SPI_SR_BSY)
#define SPI_CHSIDE_FLAG					(1 << SPI_SR_CHSIDE)
#define SPI_UDR_FLAG					(1 << SPI_SR_UDR)
#define SPI_CRCERR_FLAG					(1 << SPI_SR_CRCERR)
#define SPI_MODF_FLAG					(1 << SPI_SR_MODF)
#define SPI_OVR_FLAG					(1 << SPI_SR_OVR)
#define SPI_FRE_FLAG					(1 << SPI_SR_FRE)



/* SPI CLOCK ENABLE */
void SPI_PeriClockControl(SPI_RegDef_t* pSPIx , uint8_t EnorDi);

/* INTIALIZE AND DEINITIALIZE */
void SPI_Init(SPI_Handle_t *pSPIHandle);
void SPI_DeInit(SPI_RegDef_t* pSPIx);

/* SEND AND RECEIVE */
void SPI_SendData(SPI_RegDef_t* pSPIx, uint8_t *pTxBuffer, uint32_t Len);
void SPI_ReceiveData(SPI_RegDef_t* pSPIx, uint8_t *pRxBuffer, uint32_t Len);

/* INTERRUPT */
void SPI_IRQConfig(uint8_t IRQNumber, uint8_t EnorDi);
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void SPI_IRQHandling(SPI_Handle_t *pSPIHandle);

/* OTHER USEFUL PERIPHERALS */
void SPI_PeripheralControl(SPI_RegDef_t* pSPIx, uint8_t EnOrDi);
uint8_t SPI_GetFlagStatus(SPI_RegDef_t* pSPIx,uint32_t Flagname);
void SPI_SSIConfig(SPI_RegDef_t* pSPIx, uint8_t EnOrDi);
void SPI_SSOEConfig(SPI_RegDef_t* pSPIx, uint8_t EnOrDi);

#endif /* INC_STM3F407XX_SPI_DRIVERS_H_ */
