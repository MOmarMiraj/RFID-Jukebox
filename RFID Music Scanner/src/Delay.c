
/**
  ******************************************************************************

  Timer Setup for Delay in STM32F446RE
  Author:   ControllersTech
  Updated:  2nd Aug 2020

  ******************************************************************************
  Copyright (C) 2017 ControllersTech.com

  This is a free software under the GNU license, you can redistribute it and/or modify it under the terms
  of the GNU General Public License version 3 as published by the Free Software Foundation.
  This software library is shared with public for educational purposes, without WARRANTY and Author is not liable for any damages caused directly
  or indirectly by this software, read more about this on the GNU General Public License.

  ******************************************************************************
*/

#include "Delay.h"
#include "RccConfig.h"

void TIM6Config (void)
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;  // Enable the timer6 clock
	
	TIM6->PSC = 90-1;  // 90MHz/90 = 1 MHz ~ 1 uS delay  s = 1/Hz = 1/10^6 = 10^-6s ~= 1uS
	TIM6->ARR = 0xffff;  // MAX ARR value
	
	TIM6->CR1 |= TIM_CR1_CEN; // Enable the Counter
	while (!(TIM6->SR & TIM_SR_UIF));  // flag when count register is updated
}

void Delay_us (uint16_t us)
{
	TIM6->CNT = 0;
	while (TIM6->CNT < us);
}

void Delay_ms (uint16_t ms)
{
	for (uint16_t i=0; i<ms; i++)
	{
		Delay_us (1000); // delay of 1 ms
	}
}

