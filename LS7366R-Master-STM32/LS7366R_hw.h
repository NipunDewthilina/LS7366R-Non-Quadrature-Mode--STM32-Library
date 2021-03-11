/**
 * Author Wojciech Domski <Wojciech.Domski@gmail.com>
 * www: www.Domski.pl
 *
 * Hardware layer for LS7366R LoRa module
 */

#ifndef __LS7366R_HW_HEADER
#define __LS7366R_HW_HEADER

#include <stdint.h>

typedef struct {
	int pin;
	void *port;
} LS7366R_hw_dio_t;

typedef struct {
	LS7366R_hw_dio_t reset;
	LS7366R_hw_dio_t dflag;
	LS7366R_hw_dio_t ss;
	LS7366R_hw_dio_t mode;
	void *spi;
} LS7366R_hw_t;

/**
 * \brief Initialize hardware layer
 *
 * Clears NSS and resets LoRa module.
 *
 * \param[in]   hw 		Pointer to hardware structure
 */
void LS7366R_hw_init(LS7366R_hw_t *hw);

/**
 * \brief Control NSS
 *
 * Clears and sets NSS according to passed value.
 *
 * \param[in]   hw 		Pointer to hardware structure.
 * \param[in]   value   1 sets NSS high, other value sets NSS low.
 */
void LS7366R_hw_SetSS(LS7366R_hw_t *hw, int value);

/**
 * \brief Resets LoRa module
 *
 * Resets LoRa module.
 *
 * \param[in]   hw 		Pointer to hardware structure
 */
void LS7366R_hw_Reset(LS7366R_hw_t *hw);

/**
 * \brief Send command via SPI.
 *
 * Send single byte via SPI interface.
 *
 * \param[in]   hw 		Pointer to hardware structure
 * \param[in]   cmd		Command
 */
void LS7366R_hw_SPICommand(LS7366R_hw_t *hw, uint8_t cmd);

/**
 * \brief Reads data via SPI
 *
 * Reads data via SPI interface.
 *
 * \param[in]   hw 		Pointer to hardware structure
 *
 * \return				Read value
 */
uint8_t LS7366R_hw_SPIReadByte(LS7366R_hw_t *hw);
/**
 * \brief ms delay
 *
 * Milisecond delay.
 *
 * \param[in]   msec 		Number of milliseconds to wait
 */
void LS7366R_hw_DelayMs(uint32_t msec);

/**
 * \brief Reads DIO0 state
 *
 * Reads LoRa DIO0 state using GPIO.
 *
 * \param[in]   hw 		Pointer to hardware structure
 *
 * \return				0 if DIO0 low, 1 if DIO high
 */
int LS7366R_hw_GetDFLAG(LS7366R_hw_t *hw);

#endif

