 /*
 * main.c
 *
 *  Created on: Jun 22, 2021
 *      Author: yadav
 */

#include <string.h>

#include "main.h"

TIM_HandleTypeDef htim10; // Using timer 10 - linked to APB2 bus

void SystemClockConfig(void);
void TIMER10_init(void);
void Error_handler(void);
void GPIO_init(void);

int main()
{
	HAL_Init(); // Initialize Hardware Abstraction Layer
	SystemClockConfig(); // Initialize custom clock setting (If not then internal
	                     // oscillator will be used)
	GPIO_init();
	TIMER10_init();

	// Start timer
	HAL_TIM_Base_Start(&htim10);
	while(1)
	{
		while(!(TIM10->SR & TIM_SR_UIF));
		// Control comes here the required delay has elapsed
		// User code can be executed
		TIM10->SR = 0;
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
	}

	return 0;
}

void SystemClockConfig(void)
{

}

void GPIO_init(void)
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitTypeDef ledgpio;
	ledgpio.Pin = GPIO_PIN_5;
	ledgpio.Mode = GPIO_MODE_OUTPUT_PP;
	ledgpio.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &ledgpio);
}

void TIMER10_init(void)
{

	htim10.Instance = TIM10;
	htim10.Init.Prescaler = 24; // Timer clock = HSI = 16 MHz
	htim10.Init.Period = 64000-1;
	if(HAL_OK!=HAL_TIM_Base_Init(&htim10))
	{
		Error_handler();
	}
}

void Error_handler(void)
{
	while(1);
}
