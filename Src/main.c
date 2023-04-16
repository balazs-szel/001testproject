
#include "main.h"

int main(void)
{
	RCC_AHB1ENR_t volatile *const pClkCtrlReg   = (RCC_AHB1ENR_t*) 0x40023830;
	GPIOx_MODE_t  volatile *const pPortGModeReg = (GPIOx_MODE_t*) 0x40021800;
	GPIOx_ODR_t   volatile *const pPortGOutReg  = (GPIOx_ODR_t*) 0x40021814;

	//1. enable the clock for GPOIG peripheral in the AHB1ENR
	pClkCtrlReg->gpiog_en = 1;


	//2. configure the mode of the IO pins as output
	pPortGModeReg->pin_13 = 1;
	pPortGModeReg->pin_14 = 1;

	while(1)
	{
		//Set 13th and 14th bit of the output data register to make I/O pin-13 and pin-14 (LOW or HIGH)
		pPortGOutReg->pin_13  = 1;
		pPortGOutReg->pin_14  = 0;


		//introduce small human observable delay
		//This loop executes for 600K times
		for(uint32_t i=0 ; i < 600000 ; i++ );

		//Reset 13th and 14th bit of the output data register to make I/O pin-13 and pin-14 (LOW or HIGH)
		pPortGOutReg->pin_13  = 0;
		pPortGOutReg->pin_14  = 1;

		for(uint32_t i=0 ; i < 600000 ; i++ );
	}

}
