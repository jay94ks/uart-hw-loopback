/*
 * App.cpp
 *
 *  Created on: Feb 27, 2024
 *      Author: jay94
 */

#include "main.h"
#include "usbd_cdc_if.h"
#include "Queue.h"

Queue<uint8_t, 512> g_rxbuf;
Queue<uint8_t, 512> g_txbuf;
uint8_t g_uart = 0;

extern "C" {
	extern UART_HandleTypeDef huart2;

	void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart) {
		HAL_UART_RxCpltCallback(huart);
	}

	void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
		const uint8_t val = g_uart;

		// --> re-arm UART interrupt.
		HAL_UART_Receive_IT(&huart2, &g_uart, sizeof(g_uart));

		if (!g_rxbuf.avail()) {
			return; // --> buffer overflow.
		}

		g_rxbuf.enqueue(val);
	}

	uint8_t CDC_OnRxBytes(uint8_t* buf, uint32_t len) {
		if (len > g_txbuf.avail()) {
			return 0; // --> no space avail.
		}

		// --> enqueue bytes.
		g_txbuf.enqueue(buf, len);
		return 1;
	}

	// --
	void runApp() {
		uint8_t temp[256] = { 0, };

		HAL_UART_Receive_IT(&huart2, &g_uart, sizeof(g_uart));
		while(true) {
			if (g_txbuf.used()) {
				uint16_t len = g_txbuf.peek(0, temp, sizeof(temp));
				if (HAL_UART_Transmit(&huart2, temp, len, 100 * len) == HAL_OK) {
					g_txbuf.dequeue(temp, len);
				}
			}

			if (g_rxbuf.used()) {
				uint16_t len = g_rxbuf.peek(0, temp, sizeof(temp));
				if (CDC_Transmit_FS(temp, len) == USBD_OK) {
					g_rxbuf.dequeue(temp, len);
				}
			}
		}
	}


}
