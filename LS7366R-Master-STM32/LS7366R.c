#include "LS7366R.h"
#include <string.h>
#include "gpio.h"
#include "spi.h"
#include "uart.h"

uint8_t LS7366R_SPIRead(LS7366R_t *module, uint8_t addr) {
	uint8_t tmp;
	LS7366R_hw_SPICommand(module->hw, addr);
	tmp = LS7366R_hw_SPIReadByte(module->hw);
	LS7366R_hw_SetSS(module->hw, 1);
	return tmp;
}

uint16_t LS7366R_SPI2ByteRead(LS7366R_t *module, uint8_t addr) {
	uint8_t tmp1,tmp2;
	uint16_t tmp;
	LS7366R_hw_SPICommand(module->hw, addr);
	tmp1 = LS7366R_hw_SPIReadByte(module->hw);
	tmp2 = LS7366R_hw_SPIReadByte(module->hw);
	LS7366R_hw_SetSS(module->hw, 1);
	tmp = (tmp1<<8)|(tmp2);
	return tmp;
}

void LS7366R_SPIWrite(LS7366R_t *module, uint8_t addr, uint8_t cmd) {
	LS7366R_hw_SetSS(module->hw, 0);
	LS7366R_hw_SPICommand(module->hw, addr);
	LS7366R_hw_SPICommand(module->hw, cmd);
	LS7366R_hw_SetSS(module->hw, 1);
}

void LS7366R_clear(LS7366R_t *module) {
	LS7366R_hw_SetSS(module->hw, 0);// Begin SPI conversation 
	LS7366R_hw_SPICommand(module->hw,CLRR|CNTRR);
	LS7366R_hw_SetSS(module->hw, 1);// Terminate SPI conversation
}

void LS7366R_init(LS7366R_t *module) {
	int mdr0_conf = module->mdr0;
	int mdr1_conf = module->mdr1;
	//LS7366R_hw_init(module->hw);
	LS7366R_clear(module);
	while (LS7366R_SPIRead(module, MDR0|RD)!= ((NQUAD)|(FREE_RUN)|(DISABLE_INDX)|(FILTER_1))){
		LS7366R_hw_SetSS(module->hw, 0);// Begin SPI conversation
	LS7366R_SPIWrite(module,WR|MDR0,mdr0_conf);
	LS7366R_hw_SetSS(module->hw, 1);// Terminate SPI conversation
	}
	LS7366R_hw_DelayMs(5);
	while (LS7366R_SPIRead(module, MDR1|RD)!= ((module->byte_data_width)|(module->flag_mode))){
		LS7366R_hw_SetSS(module->hw, 0);// Begin SPI conversation
	LS7366R_SPIWrite(module,WR|MDR1,mdr1_conf);
	LS7366R_hw_SetSS(module->hw, 1);// Terminate SPI conversation
	}
	LS7366R_clear(module);
}

int isOverflowed(LS7366R_t *module)
{
if (LS7366R_hw_GetDFLAG(module->hw))
{
	return 1;
}
else {
	return 0;
}
}

uint32_t readCountOdr(LS7366R_t *module)
{
	uint16_t count;
	LS7366R_hw_SPICommand(module->hw,LOADD|OTRR);
	LS7366R_hw_SetSS(module->hw, 1);// Terminate SPI conversation
	LS7366R_hw_DelayMs(5);
	LS7366R_hw_SetSS(module->hw, 0);
	count = LS7366R_SPI2ByteRead(module, RD|OTRR);
	LS7366R_hw_SetSS(module->hw, 1);// Terminate SPI conversation
	return count;
}

void configMDR0(LS7366R_t *module,uint8_t count_mode, uint8_t running_mode, uint8_t index_mode,
		uint8_t filter_mode)
{
	module->running_modes = count_mode;
	//LS7366R.byte_data_width = BYTE_4;
	module->clock_filter_mode = filter_mode;
	module->count_modes = count_mode;
	//LS7366R.flag_mode = CY_FLAG;
	module->index_modes = index_mode;

	module->mdr0 = count_mode | filter_mode | count_mode | index_mode;

}

void configMDR1(LS7366R_t *module,uint8_t byte_data_width, uint8_t flag_mode)
{
	//LS7366R.running_modes = count_mode;
	module->byte_data_width =  byte_data_width;
	//LS7366R.clock_filter_mode = filter_mode;
	//LS7366R.count_modes = count_mode;
	module->flag_mode = flag_mode;
	//LS7366R.index_modes = index_mode;

	module->mdr1 = (byte_data_width)| (flag_mode)|(EN_CNTR);

}

