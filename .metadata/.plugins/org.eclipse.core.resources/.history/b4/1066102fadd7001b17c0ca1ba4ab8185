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

	memset(&clk_init, 0, sizeof(clk_init));

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
