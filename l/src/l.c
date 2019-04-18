/*
===============================================================================
 Name        : l.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/
#include "board.h"
#include "FreeRTOS.h"
#include "task.h"

static void prvSetupHardware(void)
{
	SystemCoreClockUpdate();
	Board_Init();

	/* Initial LED0 state is off */
	Board_LED_Set(0, false);
}
void delay()
{
	int i,j;
	for(i=0;i<1000;i++)
	{
		for(j=0;j<2000;j++)
		{}
	}
}
static void vLEDTask1(void *pvParameters) {
	//bool LedState = false;

	while (1) {
		Board_LED_Set(0, false);
		//LedState = (bool) !LedState;
delay();
        Board_LED_Set(0, true);
		/* About a 3Hz on/off toggle rate */
	delay();
        //vTaskDelay(configTICK_RATE_HZ / 6);
	}
}
  int main()
  {
	  prvSetupHardware();

	  	/* LED1 toggle thread */
	  	xTaskCreate(vLEDTask1, (signed char *) "vTaskLed1",
	  				configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
	  				(xTaskHandle *) NULL);

	  	return 1;
  }


