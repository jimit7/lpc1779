/*
 * @brief FreeRTOS Blinky example
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

#include "board.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"



xSemaphoreHandle ledMutex;

static void prvSetupHardware(void)
		{
		SystemCoreClockUpdate();
		Board_Init();
		}

static void prvLED(uint8_t *pvLED)
		{
		xSemaphoreTake(ledMutex,1000);
		{
		Board_LED_Set((uint8_t)pvLED, false);
		vTaskDelay(2000);
		Board_LED_Set((uint8_t)pvLED, true);
        vTaskDelay(2000);
        }
		}

static void vLEDTask(void *pvParameters)
		{
		uint8_t *RLED;
		RLED = (uint8_t*) pvParameters;
		while (1)
		{
		prvLED(RLED);
		xSemaphoreGive( ledMutex );
		vTaskDelay(2000);
		}
		}

int main(void)
		{
    	prvSetupHardware();

    	ledMutex = xSemaphoreCreateMutex();

    	if( ledMutex != NULL )
    	{
    	/* LED1 toggle thread */
    	xTaskCreate(vLEDTask, (signed char *) "vTaskLed1",configMINIMAL_STACK_SIZE,0,(tskIDLE_PRIORITY +2UL),(xTaskHandle *) NULL);

    	xTaskCreate(vLEDTask, (signed char *) "vTaskLed1",configMINIMAL_STACK_SIZE,1,(tskIDLE_PRIORITY +1UL),(xTaskHandle *) NULL);

    	xTaskCreate(vLEDTask, (signed char *) "vTaskLed1",configMINIMAL_STACK_SIZE,2,(tskIDLE_PRIORITY +0UL),(xTaskHandle *) NULL);

    	/* Start the scheduler */
    	vTaskStartScheduler();
    	}
    	/* Should never arrive here */
    	return 1;
		}

/**
 * @}
 */
