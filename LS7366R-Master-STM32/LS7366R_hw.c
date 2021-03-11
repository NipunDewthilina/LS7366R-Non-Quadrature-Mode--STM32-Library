/**
 * Author Wojciech Domski <Wojciech.Domski@gmail.com>
 * www: www.Domski.pl
 *
 * Hardware layer for LS7366R  module
 */

#include "LS7366R_hw.h"
#include <string.h>

#include "gpio.h"
#include "spi.h"
#include "uart.h"

__weak void LS7366R_hw_init(LS7366R_hw_t *hw) {
	LS7366R_hw_SetSS(hw, 1);
	//HAL_GPIO_WritePin(hw->reset.port, hw->reset.pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(hw->dflag.port, hw-> dflag.pin,GPIO_PIN_SET);
}

__weak void LS7366R_hw_SetSS(LS7366R_hw_t *hw, int value) {
	HAL_GPIO_WritePin(hw->ss.port, hw->ss.pin,
			(value == 1) ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

__weak void LS7366R_hw_Reset(LS7366R_hw_t *hw) {
	LS7366R_hw_SetSS(hw, 1);
	HAL_GPIO_WritePin(hw->reset.port, hw->reset.pin, GPIO_PIN_RESET);

	LS7366R_hw_DelayMs(1);

	HAL_GPIO_WritePin(hw->reset.port, hw->reset.pin, GPIO_PIN_SET);

	LS7366R_hw_DelayMs(100);
}

__weak void LS7366R_hw_SPICommand(LS7366R_hw_t *hw, uint8_t cmd) {
	LS7366R_hw_SetSS(hw, 0);
	HAL_SPI_Transmit(hw->spi, &cmd, 1, 1000);
	while (HAL_SPI_GetState(hw->spi) != HAL_SPI_STATE_READY)
		;
}

__weak uint8_t LS7366R_hw_SPIReadByte(LS7366R_hw_t *hw) {
	uint8_t rxByte = 0x00;
	uint8_t txByte = 0x00;
	LS7366R_hw_SetSS(hw, 0);
	HAL_SPI_TransmitReceive(hw->spi ,&txByte, &rxByte, 1, 1000);
	while (HAL_SPI_GetState(hw->spi) != HAL_SPI_STATE_READY)
		;
	return rxByte;
}

__weak void LS7366R_hw_DelayMs(uint32_t msec) {
	HAL_Delay(msec);
}

__weak int LS7366R_hw_GetDFLAG(LS7366R_hw_t *hw)
{
	if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(hw->ss.port,hw->ss.pin))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

