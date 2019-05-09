#define STM32F1X_LD
#include<stm32f10x.h>
#include "RTE_Device.h"                 // Keil::Device:Startup
#include "RTE_Components.h"             // Component selection
#include "GPIO_STM32F10x.h"             // Keil::Device:GPIO
void delay(int del){
	for(int x=0;x<=del;x++)
	for(int y=0;y<=1000;y++);
}
int main(){
	//Pll
	RCC-> CFGR = RCC_CFGR_PLLSRC_HSE; // Ext Clock Selected
	RCC-> CFGR = RCC_CFGR_PLLMULL6;  // Multiplier 6X
	RCC-> CFGR = RCC_CFGR_MCO_PLL;  // MCO PLL Clk Selected
	RCC-> CFGR = RCC_CFGR_SWS_PLL;
	
	
	RCC -> CR = RCC_CR_PLLON;
	
	while(!(((RCC->CR)&RCC_CR_PLLRDY) == RCC_CR_PLLRDY));
	//--------
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	GPIOC->CRH &= ~GPIO_CRH_CNF13;
	GPIOC->CRH |= GPIO_CRH_MODE13_0;
	GPIOB->CRH &= ~GPIO_CRH_CNF12;
	GPIOB->CRH |= GPIO_CRH_MODE12_0;
	while(1){
		GPIOC->BSRR = (1<<13);
		GPIOB->BSRR = (1<<12);
		delay(100);
		GPIOC->BSRR = (1<<29);
		GPIOB->BSRR = (1<<28);
		delay(100);
	}
	return 0;
}
