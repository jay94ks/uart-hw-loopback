/*
 * App.cpp
 *
 *  Created on: Feb 27, 2024
 *      Author: jay94
 */

#include "main.h"
#include "usbd_cdc_if.h"
#include "Queue.h"

extern "C" {
	extern UART_HandleTypeDef huart2;

	uint8_t CDC_OnRxBytes(uint8_t* buf, uint32_t len) {
		if (HAL_UART_Transmit(&huart2, buf, len, 100 * len) != HAL_OK) {
			return 0;
		}

		return 1;
	}

	// --
	void runApp() {
		uint8_t temp[32] = { 0, };
		uint8_t pos = 0;

		while(true) {
			if (HAL_UART_Receive(&huart2, temp + pos, 1, 0) == HAL_OK) {
				if (pos < sizeof(temp)) {
					pos++;
					continue;
				}
			}

			while(true) {
				auto ret = CDC_Transmit_FS(temp, pos);
				if (ret != USBD_OK) {
					continue;
				}

				pos = 0;
				break;
			}

			pos = 0;
		}
	}


}
