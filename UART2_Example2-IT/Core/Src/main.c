/*
 * main.c
 *
 *  Created on: Jun 22, 2021
 *      Author: yadav
 */

#include <string.h>
#include <stdbool.h>
#include "main.h"

void SystemClockConfig(void);
void UART2_Init(void);
void Error_handler(void);

UART_HandleTypeDef huart2;

char *test_data = "The application is running\r\n";
uint8_t rx_data_buffer[100];
uint8_t rx_data;
uint32_t count = 0;
bool reception_complete = false;
/**
  * @brief  Rx Transfer completed callbacks.
  * @param  huart  Pointer to a UART_HandleTypeDef structure that contains
  *                the configuration information for the specified UART module.
  * @retval None
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if('\r'==rx_data)
	{
		reception_complete = true;
		rx_data_buffer[count++] = '\r';
		// Send data to user
		HAL_UART_Transmit(&huart2, (uint8_t*)rx_data_buffer, (uint16_t)count, HAL_MAX_DELAY);
	}
	else
	{
		// Substract difference of ASCII for RX data is data is small letters
		// This will convert the received character to capital letter
		if((rx_data>='a') && (rx_data<='z'))
		{
			rx_data = rx_data - ('a' - 'A');
		}
		rx_data_buffer[count++] = rx_data;
	}
}

int main()
{
	HAL_Init(); // Initialize Hardware Abstraction Layer
	SystemClockConfig(); // Initialize custom clock setting (If not then internal
	                     // oscillator will be used)
	UART2_Init();        // High level initialization of the UART

	HAL_UART_Transmit(&huart2, (uint8_t*)test_data, (uint16_t)strlen(test_data), HAL_MAX_DELAY);

	while(reception_complete!=true) // Rx characters until enter key is pressed
	{
		HAL_UART_Receive_IT(&huart2, &rx_data, 1);
	}

	while(1);

	return 0;
}

void SystemClockConfig(void)
{

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
