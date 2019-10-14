@brief FreeRTOS Blinky example
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2014
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#include <stdlib.h>

#include "board.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

#define LED_ON		false
#define LED_OFF		true

#define LED_ON_TIME		(configTICK_RATE_HZ/2)
#define LONG_WAIT_TIME	(16*configTICK_RATE_HZ)
#define RECEIVER_TIME	(2*configTICK_RATE_HZ)

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/* Sets up system hardware */
static void prvSetupHardware(void)
{
	SystemCoreClockUpdate();
	Board_Init();

    // Set the LEDs to the state of "Off"
    Board_LED_Set(LED_RED, LED_OFF);
    Board_LED_Set(LED_GREEN, LED_OFF);
    Board_LED_Set(LED_BLUE, LED_OFF);
}

/* LED Color selection thread */
static void vLEDColorSelectTask(void *pvParameters) {
	portTickType tickCountStart, tickCountCurrent;
	xQueueHandle ledColorQueue = (xQueueHandle)pvParameters;
	printf("starting sender task\n");

	while (1) {
		printf("queue size begin: %u\n", uxQueueMessagesWaiting(ledColorQueue));
		tickCountStart = xTaskGetTickCount();

		// fill queue with LED colors for 4s at random intervals between 0 and 1 seconds
		do {

			uint8_t ledColors = rand() % 8;

			if (xQueueSendToBack(ledColorQueue, &ledColors, 0) != pdPASS) {
				// queue was full
				printf("queue full\n");
			}

			/* wait random time */
			vTaskDelay(rand() % configTICK_RATE_HZ);

			tickCountCurrent = xTaskGetTickCount();
		} while ((tickCountCurrent - tickCountStart) < 4*configTICK_RATE_HZ);

		// print the queue size for reference
		printf("queue size end: %u\n", uxQueueMessagesWaiting(ledColorQueue));

		// after 4s have passed, wait for a longer period
		vTaskDelay(LONG_WAIT_TIME);
	}
}

/* LED Color set thread */
static void vLEDColorSetTask(void *pvParameters) {
	xQueueHandle ledColorQueue = (xQueueHandle)pvParameters;
	printf("starting receiver task\n");

	while (1) {
		uint8_t ledColors;
		xQueueReceive(ledColorQueue, &ledColors, portMAX_DELAY);

		for (rgb_led_t led = LED_RED; led <= LED_BLUE; led++) {
			if (ledColors & (1 << led)) {
				Board_LED_Set(led, LED_ON);
			} else {
				Board_LED_Set(led, LED_OFF);
			}
		}

		/* wait with these LED colors */
		vTaskDelay(RECEIVER_TIME);
	}
}

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/**
 * @brief	main routine for FreeRTOS blinky example
 * @return	Nothing, function should not exit
 */
int main(void)
{
	xQueueHandle ledColorQueue;

	prvSetupHardware();

	ledColorQueue = xQueueCreate(10, sizeof(uint8_t));

	if (ledColorQueue != NULL) {
		/* LED color selection thread */
		xTaskCreate(vLEDColorSelectTask, (signed char *) "Color Select",
				configMINIMAL_STACK_SIZE, ledColorQueue, (tskIDLE_PRIORITY + 1UL),
				NULL);

		/* LED color setting thread */
		xTaskCreate(vLEDColorSetTask, (signed char *) "Color Show",
				configMINIMAL_STACK_SIZE, ledColorQueue, (tskIDLE_PRIORITY + 1UL),
				NULL);

		/* Start the scheduler */
		vTaskStartScheduler();
	}

	/* Should never arrive here */
	return 1;
}

/**
 * @}
 */
