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

void UART2_Init(void);
void Error_handler(void);

UART_HandleTypeDef huart2;


int main()
{
	RCC_OscInitTypeDef osc_init;
	RCC_ClkInitTypeDef clk_init;
	char msg[100] = "The application is running.\r\n";

	HAL_Init(); // Initialize Hardware Abstraction Layer

	memset(&osc_init, 0, sizeof(osc_init));
	osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	osc_init.HSEState = RCC_HSE_BYPASS;
	if( HAL_OK != HAL_RCC_OscConfig(&osc_init))
	{
		Error_handler();
	}

	memset(&clk_init, 0, sizeof(clk_init));
	clk_init.ClockType = (RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_HCLK| \
			              RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2);
	clk_init.SYSCLKSource   = RCC_SYSCLKSOURCE_HSE;
	clk_init.AHBCLKDivider  = RCC_SYSCLK_DIV2;
	clk_init.APB1CLKDivider = RCC_HCLK_DIV2;
	clk_init.APB2CLKDivider = RCC_HCLK_DIV2;

	if( HAL_OK != HAL_RCC_ClockConfig(&clk_init, FLASH_ACR_LATENCY_0WS))
	{
		Error_handler();
	}

	// Disable HSI as we are using HSE
	__HAL_RCC_HSI_DISABLE();

	// Systick configuration
	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);


	UART2_Init();        // High level initialization of the UART

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
