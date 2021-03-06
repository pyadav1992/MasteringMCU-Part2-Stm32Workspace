/*
 * it.c
 *
 *  Created on: Jun 22, 2021
 *      Author: yadav
 */

#include "main.h"


extern UART_HandleTypeDef huart2;

void SysTick_Handler (void)
{
	HAL_IncTick(); // Increments systick global vairable
	HAL_SYSTICK_IRQHandler(); // Processes systick interrupt and calls  callback function
}

void USART2_IRQHandler (void)
{
	HAL_UART_IRQHandler(&huart2);
}
