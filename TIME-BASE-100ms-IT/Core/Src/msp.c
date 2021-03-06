/*
 * msp.c
 *
 *  Created on: Jun 22, 2021
 *      Author: yadav
 */


/**
  * @brief  Initialize the MSP.
  * @retval None
  */
#include "stm32f4xx_hal.h"

void HAL_MspInit(void)
{
// Here we do low layer processor specific inits
	//1. Set up priority grouping of the arm cortex mx processor
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
	//2. Enable the required system exception of the arm cortex mx processor
	     // System exception are controlled by system handler control and status register
	SCB->SHCSR |= (0x7)<<16; // Enable usg fault, memory fault and bus fault exceptions
	//3. Configure the priority for the system exceptions
	HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
	HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
	HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);

}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htimer)
{
	// 1. Enable the clock for the TIM10 peripheral
	__HAL_RCC_TIM10_CLK_ENABLE();
	// 2. Enable the IRQ of TIM 10
	HAL_NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);
	// 3. Set up priority
	HAL_NVIC_SetPriority(TIM1_UP_TIM10_IRQn, 15, 0);
}
