#ifndef __LS7366R_H__
#define __LS7366R_H__

#include <stdint.h>
#include <stdbool.h>

#include "LS7366R_hw.h"

//Count modes
#define NQUAD 0x00                   //non-quadrature mode
#define QUADRX1 0x01              //X1 quadrature mode
#define QUADRX2 0x02              //X2 quadrature mode
#define QUADRX4 0x03              //X4 quadrature mode

//Running modes
#define FREE_RUN 0x00
#define SINGE_CYCLE 0x04
#define RANGE_LIMIT 0x08
#define MODULO_N 0x0C

//Index modes
#define DISABLE_INDX 0x00         //index_disabled
#define INDX_LOADC 0x10           //index_load_CNTR
#define INDX_RESETC 0x20          //index_rest_CNTR
#define INDX_LOADO 0x30          //index_load_OL
#define ASYNCH_INDX 0x00        //asynchronous index
#define SYNCH_INDX 0x80          //synchronous index

//Clock filter modes
#define FILTER_1 0x00                 //filter clock frequncy division factor 1
#define FILTER_2 0x80                 //filter clock frequncy division factor 2

/* **MDR1 configuration data; any of these***
***data segments can be ORed together***/

//Flag modes
#define NO_FLAG 0x00              //all flags disabled
#define IDX_FLAG 0x10              //IDX flag
#define CMP_FLAG 0x20            //CMP flag
#define BW_FLAG 0x40              //BW flag
#define CY_FLAG 0x80                //CY flag

//1 to 4 bytes data-width
#define BYTE_4 0x00                  //four byte mode
#define BYTE_3 0x01                  //three byte mode
#define BYTE_2 0x02                  //two byte mode
#define BYTE_1 0x03                  //one byte mode

//Enable/disable counter
#define EN_CNTR 0x00               //counting enabled
#define DIS_CNTR 0x04              //counting disabled


#define CLRR 0x00
#define RD 0x40
#define WR 0x80
#define LOADD 0xB0

#define MDR0 0x08
#define MDR1 0x10
#define DTR 0x18
#define CNTRR 0x20
#define OTRR 0x28
#define STR 0x30

// filter factor 1
// asynch index
// no index
// free-running
// 4x quadrature
#define MDR0_CONF B00110100

// no flag
// enabled
// 32 bits
#define MDR1_CONF B10100010


//structure definition

typedef struct 
{
	LS7366R_hw_t *hw;
	uint8_t count_modes;
	uint8_t running_modes;
	uint8_t index_modes;
	uint8_t clock_filter_mode;
	uint8_t flag_mode;
	uint8_t byte_data_width;
	uint8_t mdr0;
	uint8_t mdr1;

}LS7366R_t;
/**
 * \brief Read byte from  module
 *
 * Reads data from  module from given address.
 *
 * \param[in]  module	Pointer to  structure
 * \param[in]  addr		Address from which data will be read
 *
 * \return              Read data
 */

uint8_t LS7366R_SPIRead(LS7366R_t *module, uint8_t addr);

/**
 * \brief Write byte to  module
 *
 * Writes data to  module under given address.
 *
 * \param[in]  module	Pointer to  structure
 * \param[in]  addr		Address under which data will be written
 * \param[in]  cmd 		Data to write
 */
void LS7366R_SPIWrite(LS7366R_t *module, uint8_t addr, uint8_t cmd);


uint16_t LS7366R_SPI2ByteRead(LS7366R_t *module, uint8_t addr);
/**
 * \brief Clear IRQ
 *
 * Clears interrupt flags.
 *
 * \param[in]  module	Pointer to  structure
 */
void LS7366R_clear(LS7366R_t *module);

uint32_t readCountOdr(LS7366R_t *module);

//Initiation function
void LS7366R_init(LS7366R_t *module);
int isOverflowed(LS7366R_t *module);
void configMDR0(LS7366R_t *module,uint8_t count_mode, uint8_t running_mode, uint8_t index_mode,
		uint8_t filter_mode);
void configMDR1(LS7366R_t *module,uint8_t byte_data_width, uint8_t flag_mode);

#endif
