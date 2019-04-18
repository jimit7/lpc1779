/*
===============================================================================
 Name        : k.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif

#include <cr_section_macros.h>

// TODO: insert other include files here
Delay(int x) //delay function
{
	int j,k;
	for(j=0;j<1000;j++)
	{
	for(k=0;k<x;k++)
	{}
		}
}
// TODO: insert other definitions and declarations here

int main(void) {

#if defined (__USE_LPCOPEN)
    // Read clock settings and update SystemCoreClock variable
    SystemCoreClockUpdate();
#if !defined(NO_BOARD_LIB)
    // Set up and initialize all required blocks and
    // functions related to the board hardware
    Board_Init();
    // Set the LED to the state of "On"

#endif
#endif
    while(1){

    Board_LED_Set(0, false);// Set the RED LED to the state of "On" & ALL OTHER OFF
    Board_LED_Set(1, true);
    Board_LED_Set(2, true);

    Delay(2000); // delay for 1 sec.

    Board_LED_Set(0, true);//Set the GREEN LED to the state of "On" & ALL OTHER OFF
    Board_LED_Set(1, false);
    Board_LED_Set(2, true);


    Delay(2000);// delay for 1 sec.
    Board_LED_Set(0, true);
    Board_LED_Set(1, true);//Set the Blue LED to the state of "On" & ALL OTHER OFF
    Board_LED_Set(2, false);
    Delay(2000); //delay for 1 sec.


    }
    // Force the counter to be placed into memory
    volatile static int i = 0 ;
    // Enter an infinite loop, just incrementing a counter
    while(1) {
        i++ ;
    }
    return 0 ;
}
