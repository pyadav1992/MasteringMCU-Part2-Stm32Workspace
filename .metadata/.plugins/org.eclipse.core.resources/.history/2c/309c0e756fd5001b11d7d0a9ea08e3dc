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

/**
  * @brief  UART MSP Init.
  * @param  huart  Pointer to a UART_HandleTypeDef structure that contains
  *                the configuration information for the specified UART module.
  * @retval None
  */
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	GPIO_InitTypeDef gpio_uart;
// Do the low level initialization of the USART2 peripheral
	//1. Enable the clock for hte USART and GPIOA peripherals
	__HAL_RCC_USART2_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	//2. Do the pin muxing configuration
	gpio_uart.Pin       = GPIO_PIN_2;
	gpio_uart.Mode      = GPIO_MODE_AF_PP;
	gpio_uart.Pull      = GPIO_PULLUP;
	gpio_uart.Speed     = GPIO_SPEED_FREQ_LOW;
	gpio_uart.Alternate = GPIO_AF7_USART2; // Pin Muxing for selecting UART2_TX functionality on PA2
	HAL_GPIO_Init(GPIOA, &gpio_uart);

	gpio_uart.Pin       = GPIO_PIN_3; // Pin Muxing for selecting UART2_RX functionality on PA3
	HAL_GPIO_Init(GPIOA, &gpio_uart);

	//3. Enable the IRQ and set up the priority (NVIC setting)
	HAL_NVIC_EnableIRQ(USART2_IRQn);
	HAL_NVIC_SetPriority(USART2_IRQn, 15, 0);

}
