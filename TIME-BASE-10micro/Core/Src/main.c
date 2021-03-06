 /*
 * main.c
 *
 *  Created on: Jun 22, 2021
 *      Author: yadav
 */

#include <string.h>

#include "main.h"

#define SYS_CLOCK_FREQ_50_MHz 0
#define SYS_CLOCK_FREQ_80_MHz 1

TIM_HandleTypeDef htim10; // Using timer 10 - linked to APB2 bus

void SystemClockConfig(uint8_t clock_frequency);
void TIMER10_init(void);
void Error_handler(void);
void GPIO_init(void);

int main()
{
	HAL_Init(); // Initialize Hardware Abstraction Layer
	SystemClockConfig(SYS_CLOCK_FREQ_50_MHz); // Initialize custom clock setting (If not then internal
	                     // oscillator will be used)
	GPIO_init();
	TIMER10_init();

	// Start timer in interrupt mode
	HAL_TIM_Base_Start_IT(&htim10);

	while(1);

	return 0;
}

void SystemClockConfig(uint8_t clock_frequency)
{
	RCC_OscInitTypeDef osc_init;
	RCC_ClkInitTypeDef clk_init;
	uint32_t FLatency = 0;

	memset(&osc_init, 0, sizeof(osc_init));
	memset(&clk_init, 0, sizeof(clk_init));

	osc_init.OscillatorType      = RCC_OSCILLATORTYPE_HSI;
	osc_init.HSIState            = RCC_HSI_ON;
	osc_init.HSICalibrationValue = 16;
	osc_init.PLL.PLLState        = RCC_PLL_ON;
	osc_init.PLL.PLLSource       = RCC_PLLSOURCE_HSI;
	switch (clock_frequency)
	{
		case SYS_CLOCK_FREQ_50_MHz:
		{
			osc_init.PLL.PLLM = 16;
			osc_init.PLL.PLLN = 100;
			osc_init.PLL.PLLP = 2;
			osc_init.PLL.PLLQ = 2;

			clk_init.ClockType = (RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_HCLK| \
					              RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2);
			clk_init.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;
			clk_init.AHBCLKDivider  = RCC_SYSCLK_DIV1;
			clk_init.APB1CLKDivider = RCC_HCLK_DIV2;
			clk_init.APB2CLKDivider = RCC_HCLK_DIV2;

			FLatency = FLASH_ACR_LATENCY_1WS;
			break;
		}
		case SYS_CLOCK_FREQ_80_MHz:
		{
			osc_init.PLL.PLLM = 16;
			osc_init.PLL.PLLN = 160;
			osc_init.PLL.PLLP = 2;
			osc_init.PLL.PLLQ = 2;

			clk_init.ClockType = (RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_HCLK| \
					              RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2);
			clk_init.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;
			clk_init.AHBCLKDivider  = RCC_SYSCLK_DIV1;
			clk_init.APB1CLKDivider = RCC_HCLK_DIV2;
			clk_init.APB2CLKDivider = RCC_HCLK_DIV2;

			FLatency = FLASH_ACR_LATENCY_2WS;
			break;
		}

		default:
			return;
	}

	if(HAL_OK != HAL_RCC_OscConfig(&osc_init))
	{
		Error_handler();
	}

	if(HAL_OK != HAL_RCC_ClockConfig(&clk_init, FLatency))
	{
		Error_handler();
	}

	// Systick configuration
	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
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
	htim10.Init.Prescaler = 9; // Timer clock = HSI = 50 MHz
	htim10.Init.Period = 50-1;
	if(HAL_OK!=HAL_TIM_Base_Init(&htim10))
	{
		Error_handler();
	}
}

/**
  * @brief  Period elapsed callback in non-blocking mode
  * @param  htim TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
}

void Error_handler(void)
{
	while(1);
}
