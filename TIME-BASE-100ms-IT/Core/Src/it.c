/*
 * it.c
 *
 *  Created on: Jun 22, 2021
 *      Author: yadav
 */

#include "main.h"

extern TIM_HandleTypeDef htim10; // Using timer 10 - linked to APB2 bus;

void SysTick_Handler (void)
{
	HAL_IncTick(); // Increments systick global vairable
	HAL_SYSTICK_IRQHandler(); // Processes systick interrupt and calls  callback function
}

void TIM1_UP_TIM10_IRQHandler (void)
{
	HAL_TIM_IRQHandler(&htim10);
}
