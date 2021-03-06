/*
 * main.c
 *
 *  Created on: Jun 22, 2021
 *      Author: yadav
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <memory.h>

#include "main.h"

#define SYS_CLOCK_FREQ_50_MHz 0
#define SYS_CLOCK_FREQ_80_MHz 1

void UART2_Init(void);
void Error_handler(void);

UART_HandleTypeDef huart2;


int main()
{


	char msg[100] = "The application is running.\r\n";

	HAL_Init(); // Initialize Hardware Abstraction Layer

	SystemClock_Config(SYS_CLOCK_FREQ_50_MHz);

	UART2_Init();

	HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);

	memset(msg, 0, sizeof(msg));
	sprintf(msg, "SYSCLK : %ld\r\n", HAL_RCC_GetSysClockFreq());
	HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);

	memset(msg, 0, sizeof(msg));
	sprintf(msg, "HCLK : %ld\r\n", HAL_RCC_GetHCLKFreq());
	HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);

	memset(msg, 0, sizeof(msg));
	sprintf(msg, "PCLK1 : %ld\r\n", HAL_RCC_GetPCLK1Freq());
	HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);

	memset(msg, 0, sizeof(msg));
	sprintf(msg, "PCLK2 : %ld\r\n", HAL_RCC_GetPCLK2Freq());
	HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);

	while(1);

	return 0;
}

void SystemClock_Config(uint8_t clock_frequency)
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

void UART2_Init(void)
{
	huart2.Instance = USART2;                    // USART2 base address in the peripheral memory
	huart2.Init.BaudRate = 115200;                // Select baudrate
	huart2.Init.WordLength = UART_WORDLENGTH_8B; // 8 bits in a word
	huart2.Init.StopBits = UART_STOPBITS_1;      // 1 stop bit
	huart2.Init.Parity = UART_PARITY_NONE;       // None parity
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE; // Hardware flow control
	huart2.Init.Mode      = UART_MODE_TX_RX;     // Rx and Tx

	if (HAL_OK != HAL_UART_Init(&huart2))                      // Initialize the UART
	{
		// THere is a problem
		Error_handler();
	}
}


void Error_handler(void)
{
	while(1);
}
